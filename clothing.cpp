#include <iostream>
#include <string>
#include <set>
#include <vector>
#include <sstream>
#include "clothing.h"
#include "util.h"

using namespace std;

Clothing::Clothing(const std::string category, const std::string name, double price, int qty, string size, string brand): Product("clothing", name, price, qty)
{
    size_ = size;
    brand_ = brand;

}

Clothing::~Clothing(){

}

std::set<std::string> Clothing::keywords() const{
    set <string> all_keywords;
    
    set<string> name_keywords = parseStringToWords(name_);
    set<string> brand_keywords = parseStringToWords(brand_);

    all_keywords = setUnion(name_keywords, brand_keywords);

    return all_keywords;
    
}

std::string Clothing::displayString() const{
    
    string display = name_ + '\n' + "Size: " + size_ + " Brand: " + brand_ + '\n' + to_string(price_) + " " + to_string(qty_) + " left." + '\n';
    
    return display;

}

void Clothing::dump(std::ostream& os) const{
    os << "clothing" << '\n' << name_ << '\n' << price_ << '\n' << qty_ << '\n' << size_ << '\n' << brand_ << endl;
}