#ifndef UTIL_H
#define UTIL_H

#include <string>
#include <iostream>
#include <set>


/** Complete the setIntersection and setUnion functions below
 *  in this header file (since they are templates
 */
using namespace std;
template <typename T>
std::set<T> setIntersection(std::set<T>& s1, std::set<T>& s2)
{

	std::set<T> newSet; //declaring new set
	typename std::set<T>::iterator it;
	typename std::set<T>::iterator it2;
	for (it = s1.begin(); it != s1.end(); ++it) {
		for (it2 = s2.begin(); it2 != s2.end(); ++it2) {
			//checking to see if iterators are equal to one another
			if (*it == *it2) { 
				newSet.insert(*it);
			}
		}
	}
	//return the iterated set
	return newSet;
}
template <typename T>
std::set<T> setUnion(std::set<T>& s1, std::set<T>& s2)
{

	std::set<T> newSet;
	//iterate through first set
	typename set<T>::iterator it;
	for (it = s1.begin(); it != s1.end(); ++it) {
		newSet.insert(*it); //already checks for duplicates
	}
	//iterate through second set
	typename set<T>::iterator it2;
	for (it2 = s2.begin(); it2 != s2.end(); ++it2) {
		newSet.insert(*it2); //checks for duplicates
	}
	return newSet; //return iterated set
}

/***********************************************/
/* Prototypes of functions defined in util.cpp */
/***********************************************/

std::string convToLower(std::string src);

std::set<std::string> parseStringToWords(std::string line);

// Used from http://stackoverflow.com/
//questions/216823/whats-the-best-way-to-trim-stdstring
// trim from start
std::string &ltrim(std::string &s) ;

// trim from end
std::string &rtrim(std::string &s) ;

// trim from both ends
std::string &trim(std::string &s) ;
#endif
