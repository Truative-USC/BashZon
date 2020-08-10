#ifndef CLOTHING_H
#define CLOTHING_H

#include "product.h"
using namespace std;


//declarations for clothing class
class Clothing : public Product {
public:
  Clothing(const std::string category, const std::string name, double price,
           int qty, string size, string brand);
  ~Clothing(){};
  string getSize();
  string getBrand();
  void dump(std::ostream &os) const;
  std::string displayString() const;
  std::set<std::string> keywords() const;

private:
  string size_;
  string brand_;
};

#endif
