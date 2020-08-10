#include "book.h"

#include <sstream>


using namespace std;
//Constuctor for Book
Book::Book(const std::string category, const std::string name,
 double price, int qty, string author, string isbn)
  : Product(category, name, price, qty) {

  isbn_ = isbn; //setting isbn
  author_ = author; //setting author
}


std::string Book::getIsbn() { return isbn_; } //return isbn func
std::string Book::getAuthor() { return author_; } //return auth func

std::string Book::displayString() const {

//here i am converting int's and doubles into Strings
  stringstream ss; 
  ss << qty_; 
  stringstream ss2;
  ss2 << price_;

  string price = ss.str();
  string qty = ss2.str();
//concatenate the string 
  string output = name_ + "\n" + "Author : " + author_ + " " 
  + "ISBN: "+ isbn_ + "\n" + qty + " " + price + " left.";
                   


  return output; //return the string
}

void Book::dump(std::ostream &os) const { //dumping all file info
  os << category_ << "\n"
     << name_ << "\n"
     << price_ << "\n"
     << qty_ << "\n"
     << isbn_ << "\n"
     << author_ << endl;
}

std::set<std::string> Book::keywords() const {

  string output = name_  + "\n" + author_; //concatenate auth & name

  set<string> tempSet = parseStringToWords(output); //parse through auth&name
  tempSet.insert(isbn_); //throw unparsed isbn in set
  return tempSet; //return set

} 

// os << category_ << "\n"
//      << name_ << "\n" 
//     << "Author: " << author_ << " " << "ISBN: " << isbn_ << "\n"
//      << qty_ << "\n" <<" Left" << price_ << "\n"
//      << endl;