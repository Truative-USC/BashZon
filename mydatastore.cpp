#include "mydatastore.h"
#include <deque>
#include "review.h"
#include "heap.h"
using namespace std;



/*******************
*This is myDataStore
*It is composed of all the function that i run in my program
*Each function is clearly labled what they do
*Do not change any function in this file
*As it will cause MASSIVE segfaults and Break the program :)
********************/




myDataStore::myDataStore() { //constructor. Blank no purpose

}

myDataStore::~myDataStore() { //deconstructor is used for deallocation

	map<string, User*>::iterator it;
	for (it = userMap.begin(); it != userMap.end(); it++) {

//deallocating the second term, as it will then deallocate the first as well
		delete it->second;
	}
	set<Product*>::iterator it2;
	for (it2 = productSet.begin(); it2 != productSet.end(); it2++) {
		delete *it2; //deleting the derefernced pointer as it only has one term.
	}

	prodReviews.clear();
}

void myDataStore::addProduct(Product* p) {
	productSet.insert(p); //inserting the product into our set of products
	vector<Review*> tempProdReviews;
	prodReviews.insert(make_pair(p, tempProdReviews));

	set<string> keyWords = p->keywords(); //finding keywords for that product

	set<string>::iterator it; //declaring set of keywords iterator

	map<string, set<Product*> >::iterator it2;  //declaring map iterator
	//iterating through set of keywords
	for (it = keyWords.begin(); it != keyWords.end(); ++it) {
		//setting the map iterator = to the set returned from the keyword of it
		it2 = sameProducts.find(convToLower((*it)));
		if (it2 == sameProducts.end()) { //checking to see if it exists
			set<Product*> tempSet; //it doesnt so make a tempset
			tempSet.insert(p);
			//insert into our sameproducts set
			sameProducts.insert(make_pair((convToLower(*it)), tempSet));
		}
		//if it does, just insert like normal
		else {
			it2->second.insert(p);

		}
	}

}

void myDataStore::addUser(User* u) {
	//adding user to usermap
	userMap.insert(make_pair(u->getName(), u));
	userVec.push_back(u->getName());
	deque<Product*> newCart;
	//adding user to cartmap with an empty cart
	myCart.insert(make_pair(u->getName(), newCart));


}
std::vector<Product*> myDataStore::search(std::vector<std::string>& terms, int
        type) {
//0 = itersection
//1 = union
	//intersection search
	if (type == 0) { //itersection
		std::vector<Product*> myProds;

		std::set<Product*> prevSet;
		prevSet = sameProducts[terms[0]]; //setting first set = to prevset
		//going over size of vec
		for (unsigned int i = 1; i < terms.size(); i++) {
			//setting prevset = to intersec of prevset and new set of [i]
			prevSet = setIntersection(prevSet, sameProducts[terms[i]]);
		}
		//iterate through and push the products into a vector
		std::set<Product*>::iterator it;
		for (it = prevSet.begin(); it != prevSet.end(); it++) {
			myProds.push_back(*it);
		}
		return myProds; //return the vector
	}
	//union search
	else if (type == 1) { //union
		std::vector<Product*> myProds; //vector we are passing back
		std::set<Product*> prevSet;
		prevSet = sameProducts[terms[0]]; //setting first set = to prevset

		//going over size of vec
		for (unsigned int i = 1; i < terms.size(); i++) {
			//calling union on prev set and new set of terms [i]
			prevSet = setUnion(prevSet, sameProducts[terms[i]]);
		}
		//iterating through products and pushing them into a vector
		std::set<Product*>::iterator it;
		for (it = prevSet.begin(); it != prevSet.end(); it++) {
			myProds.push_back(*it);
		}
		return myProds; //returning vector
	}

	else {	//if an invalid type was passed in, invalid request!

		cout << "Invalid Request" << endl;
		std::vector<Product*> v;
		return v;
	}
}
//dump function to output file of database
void myDataStore::dump(std::ostream & ofile) {
	ofile << "<Products>" << endl;
	//iterator to go through products
	std::set<Product*>::iterator it;
	for (it = productSet.begin(); it != productSet.end(); it++) {
		(*it)->dump(ofile);//calling dump on the product's pointer
	}
	ofile << "</Product>" << endl;
	ofile << "<users>" << endl;
	//iterating through the users
	std::map<string, User*>::iterator it2;
	for (it2 = userMap.begin(); it2 != userMap.end(); it2++) {
		it2->second->dump(ofile); //calling dump on user pointer
	}
	ofile << "</users>" << endl;
	ofile << "<reviews>" << endl;
	std::map<Product*, std::vector<Review*> >::iterator it3;
	for (it3 = prodReviews.begin(); it3 != prodReviews.end(); it3++) {
		vector<Review*> prodVec = it3->second;
		vector<Review*>::iterator it5;
		for (it5 = prodVec.begin(); it5 != prodVec.end(); it5++) {
			(*it5)->dump(ofile);
		}
	}
	set<Review*>::iterator it4;
	for (it4 = noProdReviews.begin(); it4 != noProdReviews.end(); it4++) {
		(*it4)->dump(ofile);
	}
	ofile << "</reviews>" << endl;



}

void myDataStore::addToCart(string user, Product* p) {
	//adding items to your cart
	map<string, deque<Product*> >::iterator it;
	for (it = myCart.begin(); it != myCart.end(); ++it) {
		if (it->first == user) {//checking to make sure the user exists first
			it->second.push_back(p); //if he does, add the product
		}
	}
}
void myDataStore::viewCart(string user) { //viewing the cart of the user
	std::map<string, deque<Product*> >::iterator it2; //map iterator for cart
	for (it2 = myCart.begin(); it2 != myCart.end(); it2++)
		if (it2->first == user) { //checking for the username to see if exists
			deque<Product*>::iterator it;
			for (it = it2->second.begin(); it != it2->second.end(); ++it) {
				//displaying all the users products
				cout << (*it)->displayString() << endl;
			}
		}
}

void myDataStore::buyCart(string name) { //buy cart!!!!
	map<string, deque<Product*> >::iterator it = myCart.find(name);
	//if you cant find the user, then invalid usernam
	if (it == myCart.end()) {
		cout << "invalid username" << endl;
		return;
	}
	deque<Product*>::iterator dequeIt;	//making deque iterator

	deque<Product*> cart = it->second; //making tempdeque for cleaner code


	map<string, User*>::iterator userIt = userMap.find(name);
	deque<Product*> tempyDecky; //tempdque to push back on to hold onto
	int size = 0;

	//iterate through your cart

	for (dequeIt = cart.begin(); dequeIt != cart.end(); dequeIt++) {
		//need to check if you have enough money to spend
		//checking to see if quantity is greater than 0
		if (((userIt)->second->getBalance() >= (*dequeIt)->getPrice())
		        && ((*dequeIt)->getQty() > 0)) {
			(*dequeIt)->subtractQty(1); //if true, subtract quantity
			double amount = (*dequeIt)->getPrice();
			//deduct amount from balance
			(userIt)->second->deductAmount(amount);
			//take out of cart
			cart.pop_front();
			//also take out of user cart
			it->second.pop_front();

		}

		else {
			//push back our product if we dont have enough money && QTY =0
			tempyDecky.push_back((cart.front()));
			cart.pop_front(); //pop from cart
			size += 1; //counter to see how much we need to push back later
		}
	}
	for (int i = 0; i < size; i++) {
		//push the remaining products we couldnt buy into our cart
		cart.push_back(tempyDecky.front());
		tempyDecky.pop_front();
	}
}




/*Function to see if the user exists in our userMap */
bool myDataStore::userPresent(string username) {

	map<string, User*>::iterator it;

	bool foundUser = false;
	for (it = userMap.begin(); it != userMap.end(); it++) {
		if (it->first == username) {
			foundUser = true;
		}
	}
	return foundUser;
}


void myDataStore::addReview(Review* r) {

	set<Product*>::iterator it2;
	for (it2 = productSet.begin(); it2 != productSet.end(); it2++) {
		if ((*it2)->getName() == r->prodName) {
			map<Product*, vector<Review*> >::iterator it = prodReviews.find(*it2);
			it->second.push_back(r);
			vector<Review*> currReviews = it->second;
			double average = 0;
			double count = 0;
			for (unsigned int i = 0; i <  currReviews.size(); i++) {
				average += currReviews[i]->rating;
				count++;
			}
			double totalAverage = average / count;
			(*it2)->setAverageRating(totalAverage);
		}

	}
	reviews.push_back(r);
	// map<Product*, vector<Review*> >::iterator it = prodReviews.find(r->prodName);

}
void myDataStore::removeFromCart(string username, string product) {
	map<string, deque<Product*> >::iterator it = myCart.find(username);
	deque<Product*> Prods  = it->second;
	for (unsigned int i = 0; i < Prods.size(); i++) {
		if (Prods[i]->getName() == product) {
			it->second.erase(Prods.begin() + i);
			break;
		}
	}
}
void myDataStore::createNewUser(string username, unsigned long long Password) {


// unsigned long long pass;
	User* newUser = new User(username, 100.00, 1, Password);
	addUser(newUser);

}

map<string, User*> myDataStore::users() {
	return userMap;
}

vector<string> myDataStore::userToStrings() {
	return userVec;
}

set<Product*> myDataStore::returnProds() {
	return productSet;
}
map<string, deque<Product*> > myDataStore::returnCart() {
	return myCart;
}

map<Product*, vector<Review*> > myDataStore::returnReviews() {
	return prodReviews;
}
deque<Product*> myDataStore::userProds(string username) {

	deque<Product*> blankDeque;
	map<string, deque<Product*> >:: iterator it;
	for (it = myCart.begin(); it != myCart.end(); it++) {
		if (it->first == username) {
			return it->second;

		}
	}
	return blankDeque;
}


User* myDataStore::currUser(string username) {
	map<string, User*>::iterator it = userMap.find(username);

	return it->second;
}

// User* myDataStore::returnUser(string userName) {
// 	map<string, User*>::iterator it = userMap.find(userName);
// 	return it->second;
// }

void myDataStore::calculateSims() {

	for (unsigned int i = 0; i < reviews.size(); i++) {
		double average = 0;
		int count = 0;
		double total = 0;
		for (unsigned int j = 0; j < reviews.size(); j++) {
			double score = 0;
			if (reviews[i]->reviewText == reviews[j]->reviewText) {
				continue;
			}
			if (reviews[i]->prodName == reviews[j]->prodName && reviews[i]->reviewText != reviews[j]->reviewText) {
				score = abs((reviews[i]->rating - reviews[j]->rating) / 4);
			}
			if (score >= 1) {
				continue;
			}
			if (similarities.find(reviews[i]->getUser()) != similarities.end()) {

				map<string, map<string, double> >::iterator it = similarities.find(reviews[i]->username);
				it->second.insert(make_pair(reviews[j]->username, score));
			}
			else {
				map<string, double> tempMap;
				tempMap.insert(make_pair(reviews[j]->username, score));
				similarities.insert(make_pair(reviews[i]->username, tempMap));
			}
			average += score;
			count++;
		}
		total = average / count;
		basicSim.insert(make_pair(reviews[i]->username, total));
	}

}


map<string, double> myDataStore::dijkstra(string username)
{
	calculateSims();
	// minHeap represents set E
	// struct MinHeap* minHeap = createMinHeap(V);
	Heap<string> minHeap;
	// int max;≠≠≠
	map<string, double> userMap;
	userMap.insert(make_pair(username, 0));
	minHeap.push(0.0, username);
	// map<string, double> checkUser;

	map<string, map<string, double> >::iterator it = similarities.begin();
	for (; it != similarities.end(); it++) {
		userMap.insert(make_pair(it->first, numeric_limits<double>::infinity()));
		minHeap.push(numeric_limits<double>::infinity(), it->first);
		// checkUser.insert(make_pair(it->first, numeric_limits<double>::infinity()));
	}
	while (!minHeap.empty()) {
		string minUser = minHeap.top();
		minHeap.pop();
		map<string, double> tempMap = similarities.find(minUser)->second;
		map<string, double>::iterator it2 = tempMap.begin();

		for (; it2 != tempMap.end(); it2++) {
			if (userMap.find(it2->first) != userMap.end()) {

				double neighorVal = tempMap.find(it2->first)->second;
				double heapVal = userMap.find(it2->first)->second;
				double UserVal = userMap.find(minUser)->second;
				if (neighorVal + UserVal < heapVal) {
					userMap[it2->first] = UserVal + neighorVal;
					minHeap.decreaseKey(UserVal + neighorVal, it2->first);
				}
			}
		}
	}
	return userMap;
}

vector<pair<string, double> > myDataStore::makeSuggestion(std::string currentUser) {
	dijkstra(currentUser);
	set<string> reviewedProducts;
	set<string> notReviewed;
	set<string> users;
	map<string, set<Review*> >prodToUsers;
	vector<pair<string, double> >products;
	for (unsigned int i = 0; i < reviews.size(); i++) {
		if (reviews[i]->username == currentUser) {
			reviewedProducts.insert(reviews[i]->prodName);
		}
	}




	for (unsigned int i = 0; i < reviews.size(); i++) {
		
		 
			if (reviewedProducts.find(reviews[i]->prodName) == reviewedProducts.end()) {
				if (prodToUsers.find(reviews[i]->prodName) == prodToUsers.end()) {
					set<Review*>tempSet;
					tempSet.insert(reviews[i]);
					prodToUsers.insert(make_pair(reviews[i]->prodName, tempSet));
				}
				else {
					prodToUsers[reviews[i]->prodName].insert(reviews[i]);
				}
			}
		
	}

	map<string, set<Review*> >::iterator it = prodToUsers.begin();
	for (; it != prodToUsers.end(); it++) {
		set<Review*>::iterator set_it = it->second.begin();
		map<string, double> currUsers = similarities.find(currentUser)->second;
		double rPSum = 0;
		double wSum = 0;
		for (; set_it != it->second.end(); set_it++) {
			double userRating = currUsers.find((*set_it)->username)->second;
			rPSum += ((1 - userRating) * ((*set_it)->rating));
			wSum += (1 - userRating);
		}
		if (wSum == 0) {
			products.push_back(make_pair(it->first, 0));
			break;
		}
		else {
			double total = rPSum / wSum;
			products.push_back(make_pair(it->first, total));
		}
	}
	return products;
}



