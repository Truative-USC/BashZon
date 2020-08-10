#include "movie.h"
#include <sstream>
using namespace std;

//constructor for Movie
Movie::Movie(const std::string category,
             const std::string name, double price,
             int qty, string genre, string rating)
  : Product(category, name, price, qty) {
  genre_ = genre;
  rating_ = rating;
}

string Movie::getGenre() { return genre_; } //return movie Genre
string Movie::getRating() { return rating_; } //return Movie Rating
void Movie::dump(std::ostream &os) const {
  os << category_ << "\n" //dump data to file info
     << name_ << "\n"
     << price_ << "\n"
     << qty_ << "\n"
     << genre_ << "\n"
     << rating_ << endl;
}
string Movie::displayString() const {
  stringstream ss;
  ss << qty_; //ss int to string
  stringstream ss2;
  ss2 << price_; //ss double to string

  string price = ss.str();
  string qty = ss2.str();

  //concatenating string for display in program
  string output =  name_ + "\n" + "Genre: " +
                   genre_ + " " + "Rating: " +
                   rating_ + "\n" + qty + " " + price + " left.";
  return output;
}

std::set<std::string> Movie::keywords() const {
  string output = name_  + "\n" + rating_;//concatenate name&rating
  set<string> tempSet = parseStringToWords(output); //parse through ^^
  tempSet.insert(genre_); //insert unconcatenated genre
  return tempSet; //return set
}