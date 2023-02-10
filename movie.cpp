#include <iostream>
#include <string>
#include <set>
#include <vector>
#include <sstream>
#include "movie.h"
#include "util.h"

using namespace std;

Movie::Movie(const std::string category,const std::string name, double price, int qty, string genre, string rating): Product("movie", name, price, qty)
{
    genre_ = genre;
    rating_ = rating;

}

Movie::~Movie(){

}

std::set<std::string> Movie::keywords() const{
    set <string> all_keywords;
    
    all_keywords = parseStringToWords(name_);

    all_keywords.insert(convToLower(genre_));
    return all_keywords;
}

std::string Movie::displayString() const{
    /*
    stringstream ss;
    ss << name_ << endl;
    ss << "Genre: " << genre_ << " Rating: " << rating_ << endl;
    ss << price_ << " " << qty_ << " left." << endl;
    
    string display = ss.str();
    return display;
    */
    string display = name_ + '\n' + "Genre: " + genre_ + " Rating: " + rating_ + '\n' + to_string(price_) + " " + to_string(qty_) + " left." + '\n';
    return display;


}

void Movie::dump(std::ostream& os) const{
    os << "movie" << '\n' << name_ << '\n' << price_ << '\n' << qty_ << '\n' << genre_ << '\n' << rating_ << endl;
}