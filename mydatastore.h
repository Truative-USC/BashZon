#ifndef MYDATASTORE_H
#define MYDATASTORE_H
#include <map>
#include <deque>

#include "datastore.h"
#include "util.h"
#include "review.h"
// #include "heap.h"

using namespace std;


//Delcarations for all my datastore functions
class myDataStore : public DataStore {
public:
	myDataStore();
	~myDataStore();
	void addProduct(Product* p);
	void addUser(User* u);
	std::vector<Product*> search(std::vector<std::string>& terms, int type);
	void dump(std::ostream& ofile);
	void addToCart(string user, Product* p);
	void viewCart(string user);
	void buyCart(string name);
	bool userPresent(string username);
	void addReview(Review* r);
	void removeFromCart(string username, string product);
	void addReviewToDataBase(Review* r);
	double prodAvg(Product* p);
	void createNewUser(string username, unsigned long long Password);
	std::vector<string> userToStrings();
	set<Product*> returnProds();
	map<string, deque<Product*> > returnCart();
	deque<Product*> userProds(string username);
	map<Product*, vector<Review*> > returnReviews();
	map<string, User*> users();
	void calculateSims();
	User* currUser(string username);
	void shortestPath(User* user);
	std::map<string, double> dijkstra(string username);
	std::vector<std::pair<std::string, double> > makeSuggestion(std::string currentUser);
	

	// User* 
private:
	map<string, User*> userMap; //holds username in string and User*
	std::vector<string> userVec;
	set<Product*> productSet; //set of product pointers
	map<string, std::set<Product*> >sameProducts; //keywords to product*'s
	std::map<string, deque<Product*> >myCart; //username to cart
	std::vector<Review*> reviews;
	std::map<Product*, std::vector<Review*> > prodReviews; 
	set<Review*> noProdReviews;
	map<string, map<string, double> > similarities;
	//change map to insert strings instead of User*'s'
	map<string, double> basicSim;

};	
#endif