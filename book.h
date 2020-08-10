#ifndef BOOK_H
#define BOOK_H

#include "product.h"

using namespace std;

class Book : public Product {

public:
  //delcarations for book class
  Book(const std::string category, const std::string name, 
    double price, int qty, string author, string isbn);
  ~Book() {};
  string getIsbn();
  string getAuthor();
  void dump(std::ostream &os) const;
  std::string displayString() const;
  std::set<std::string> keywords() const;
  

private:
  string isbn_;
  string author_;
};

#endif