#include <iostream>
#include <string>
#include <set>
#include <map>
#include <vector>
#include <sstream>
#include "mydatastore.h"
#include "product.h"

using namespace std;

MyDataStore::MyDataStore(){

}

MyDataStore::~MyDataStore(){
    //delete the products in each cart and then delete the user
    for (unsigned int i = 0; i < products_.size(); i++){
        delete products_[i];
    }
    
    std::map<std::string,User*>::iterator it;
    for (it = user_map_.begin(); it != user_map_.end(); ++it){
        delete (it->second);
    }

    /*
    std::map<std::string,vector<Product*>>::iterator other;
    for (other = cart_.begin(); other != cart_.end(); ++other){
            while (!(other->second).empty()){
            delete (other->second).back();
            (other->second).pop_back();
            }
    }
    */
}

void MyDataStore::addProduct(Product* p){
    std::set<string>::iterator it;
    set<string>keywords = p->keywords();
    for (it = keywords.begin(); it != keywords.end(); ++it){
        if (product_map_.find(*it) != product_map_.end()){
            product_map_[*it].insert(p);
        }
        else{
            set<Product*>empty;
            product_map_[*it] = empty;
            product_map_[*it].insert(p);
        }
        }
    products_.push_back(p);

}

void MyDataStore::addUser(User* u){
    user_map_[u->getName()] = u;
    //user_map_.insert(pair<string,User*>(u->getName(),u));


    //std::vector<Product*> new_cart;
    //cart_[u->getName()] = new_cart;

}

vector<Product*> MyDataStore::search(vector<string>& terms, int type){
    
    std::set<Product*> temp;

    vector<Product*> result;
    if (type == 0){
        for (unsigned int i = 0; i < terms.size(); i++){
            if (i == 0){
                temp = product_map_[terms[0]];
                
            }
            if(product_map_.find(terms[i]) != product_map_.end()){
                
                // if (temp.empty()){
                //     temp = product_map_[terms[i]];
                // }
                temp = setIntersection(temp,product_map_[terms[i]]);
            }
            else {
                vector<Product*> empty;
                return empty;
            }
        }    
    }
    else if (type == 1){
        for (unsigned int i = 0; i < terms.size(); i++){
            if(product_map_.find(terms[i]) != product_map_.end()){
                if (temp.empty()){
                    temp = product_map_[terms[i]];
                }
                temp = setUnion(temp,product_map_[terms[i]]);
            }        
        }
    }

    std::set<Product*>::iterator it;
    for (it = temp.begin(); it != temp.end(); ++it){
        result.push_back(*it);
    }
    return result;

}

void MyDataStore::dump(std::ostream& ofile){
    ofile << "<products>" << endl;
    for (unsigned int i = 0; i < products_.size(); i++){
        (products_[i])->dump(ofile);
    }
    ofile << "</products>" << endl;

    ofile << "<users>" << endl;
    std::map<std::string,User*>::iterator it;
    for (it = user_map_.begin(); it != user_map_.end(); ++it){
        (it->second)->dump(ofile);
    }
    ofile << "</users>" << endl;
}

void MyDataStore::addToCart(string username, Product* hit_result_index){
    if (user_map_.find(username) == user_map_.end()){
        cout << "Invalid request" << endl;
    }    

    else{

    
    if (cart_.find(username) != cart_.end()){
        cart_[username].push_back(hit_result_index);
    }
    else {
    vector<Product*> user_products;
    user_products.push_back(hit_result_index);

    //create empty vector
    //add product* to vector
    //insert vector to cart
    cart_.insert(make_pair(username,user_products));
    }
    }
}


void MyDataStore::viewCart(string username){
    if (user_map_.find(username) == user_map_.end()){
        cout << "Invalid username" << endl;
    }
    else{

    int count = 0;
    vector<Product*> current = cart_[username];
        for (unsigned int i = 0; i < (current).size(); i++){
        cout << "Item ";
        cout << count+1 << endl;
        cout << (current[i])->displayString() << endl;
        count++;
        }
    }
    }





void MyDataStore::buyTheCart(string username){
    if (user_map_.find(username) == user_map_.end()){
        cout << "Invalid username" << endl;
    }
    else {

    vector<Product*> current = cart_[username];
    vector<Product*> newCart;
    User* current_user = user_map_[username];
    for (unsigned int i = 0; i < current.size(); i++){
        if (current[i]->getQty() > 0 && current_user->getBalance() >= current[i]->getPrice()){
            current[i]->subtractQty(1);
            current_user->deductAmount(current[i]->getPrice());
        }
        else {
            newCart.push_back(current[i]);
        }
    }
    cart_[username] = newCart;
    }
}




