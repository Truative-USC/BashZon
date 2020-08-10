#ifndef MOVIE_H
#define MOVIE_H

#include "product.h"

using namespace std;


/******************
*This class is the Movie Class.
*It is composed of name, price,
 category,Genre, and rating. See
 the .CPP to see the files and what they do
**************************/

class Movie : public Product {
public:
  Movie(const std::string category, const std::string name, double price,
        int qty, string genre, string rating);
  ~Movie() {};
  string getGenre();
  string getRating();
  void dump(std::ostream &os) const;
  std::string displayString() const;
  std::set<std::string> keywords() const;

private:
  string genre_;
  string rating_;
};


#endif