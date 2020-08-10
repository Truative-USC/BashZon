#include "clothing.h"
#include <sstream>

using namespace std;

//constructor for clothing
Clothing::Clothing(const std::string category, const std::string name,
                   double price, int qty, string size, string brand)
  : Product(category, name, price, qty) {
  size_ = size;
  brand_ = brand;
}



std::string Clothing::getSize() { return size_; } //return clothing size
 
std::string Clothing::getBrand() { return brand_; } //return brand

std::string Clothing::displayString() const { 

  stringstream ss; //convert int to string
  ss << qty_;
  stringstream ss2; 
  ss2 << price_; //convert double to string
  string price = ss.str();
  string qty = ss2.str();

  //concatentate converting string 
  string output = name_  + "\n" + "Brand: " + brand_ + " Size: " +  
  size_ + "\n" + "Price: " + qty + " " + price + " left."; 
  return output;  //return concatenated string
}


void Clothing::dump(std::ostream &os) const { //dump data to file func
  os << category_ << "\n"
     << name_ << "\n"
     << price_ << "\n"
     << qty_ << "\n"
     << size_ << "\n"
     << brand_ << endl;
}


std::set<std::string> Clothing::keywords() const {
  //function takes name size and brand and parses through them and returns
  string output = name_ + "\n" + size_ + "\n" + brand_;
  return parseStringToWords(output);
}
