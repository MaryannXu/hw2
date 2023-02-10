#include <iostream>
#include <string>
#include <set>
#include <vector>
#include <sstream>
#include "book.h"
#include "util.h"

using namespace std;

Book::Book(const std::string category,const std::string name, double price, int qty, string ISBN, string author): Product("book", name, price, qty)
{
    ISBN_ = ISBN;
    author_ = author;

}

Book::~Book(){

}

std::set<std::string> Book::keywords() const{
    
    set <string> all_keywords;
    
    set<string> name_keywords = parseStringToWords(name_);
    set<string> author_keywords = parseStringToWords(author_);

    all_keywords = setUnion(name_keywords, author_keywords);
    all_keywords.insert(convToLower(ISBN_)); 

    return all_keywords;

}

std::string Book::displayString() const{
    
    stringstream ss;
    ss << name_ << endl;
    ss << "Author: " << author_ << " ISBN: " << ISBN_ << endl;
    ss << price_ << " " << qty_ << " left." << endl;
    
    string display = ss.str();
    return display;

}

void Book::dump(std::ostream& os) const{
    os << "book" << '\n' << name_ << '\n' << price_ << '\n' << qty_ << '\n' << ISBN_ << '\n'<< author_ << endl;
}

