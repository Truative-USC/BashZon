#include "util.h"
#include <algorithm>
#include <cctype>
#include <iostream>
#include <sstream>

using namespace std;
std::string convToLower(std::string src) {
  std::transform(src.begin(), src.end(), src.begin(), ::tolower);
  return src;
}

/** Complete the code to convert a string containing a rawWord
    to a set of words based on the criteria given in the assignment **/
std::set<std::string> parseStringToWords(string rawWords) {
  set<string> wordSet;
  stringstream ss(rawWords);
  string keyWord;
  // int counter = 0;
  for (unsigned int j = 0; j < rawWords.size(); j++) {
    if (ispunct(rawWords[j])) { //checking to see if char is a punct
      rawWords[j] =  ' '; //if so then set it equal to space
    }
  }
  string newString = rawWords;  
  stringstream ss2(newString); 
  string inputWord;

  //string stream through your depuncted string
  while (ss2 >> inputWord) {
    //make sure the length of the word is greater than 2
    if (inputWord.length() >= 2) {
      // cout << inputWord <<endl;
      wordSet.insert(inputWord); //insert into our set
    }
  }
  return wordSet; //return set

}

/**************************************************
 * COMPLETED - You may use the following functions
 **************************************************/

// Used from
// http://stackoverflow.com/questions/216823/whats-the-best-way-to-trim-stdstring
// trim from start
std::string &ltrim(std::string & s) {
  s.erase(s.begin(),
          std::find_if(s.begin(), s.end(),
                       std::not1(std::ptr_fun<int, int>(std::isspace))));
  return s;
}

// trim from end
std::string &rtrim(std::string & s) {
  s.erase(std::find_if(s.rbegin(), s.rend(),
                       std::not1(std::ptr_fun<int, int>(std::isspace)))
          .base(),
          s.end());
  return s;
}

// trim from both ends
std::string &trim(std::string & s) { return ltrim(rtrim(s)); }



//  if (ispunct(keyWord[i]) && counter > 1) {
//   cout << "I went in" << endl;
//   cout << keyWord[i] << endl;
//   string tempString = keyWord.substr(0, i);
//   wordSet.insert(tempString);
//   counter = 0;
// }
// int starWord = 0;
// bool found = false;
// while (ss >> keyWord) {
//   for (unsigned int i = 0; i < keyWord.size(); i++) {
//   if (ispunct(keyWord[i]) != 0) {
//     if (2 <= counter) {
//       wordSet.insert(keyWord.substr(starWord, counter));
//       counter = 0;
//     }

//   }
//   if (keyWord.length() > (i + 1)) {
//     starWord = i + 1;
//   }

//   else {
//     counter = counter + 1;
//     if ((2 <= counter) && (i == (keyWord.length() - 1)))  {
//       wordSet.insert(keyWord.substr(starWord, counter));
//     }
//   }
// }
// counter = 0;
//   if (ispunct(keyWord[i]) && counter > 1) {
//     string tempString = keyWord.substr(0, i);
//     wordSet.insert(tempString);
//     counter = 0;
//   }
//   counter++;
// }
// set<string>::iterator it;
// for (it = wordSet.begin(); it != wordSet.end(); it++) {
//   cout << *it << endl;
// }
// }