#include "review.h"

#include <iostream>


using namespace std;



void Review::dump(std::ostream &os) {
	os << prodName << endl;
	os << rating << "\n"
	   << username << "\n" <<
	   date << "\n" << reviewText
	   << endl;


}
string Review::getdate() {
	return date;
}

string Review::getUser() const {
	return username;
}