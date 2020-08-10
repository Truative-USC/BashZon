#include <QWidget>
#include <QVBoxLayout>
#include <QLabel>
#include <QLineEdit>
#include <QTextEdit>
#include <QPushButton>
#include <QListWidget>
#include <QComboBox>
#include <QMessageBox>
#include <QGridLayout>
#include <string>
#include <vector>
#include <iostream>
#include "mydatastore.h"
#include <QRadioButton>
#include <QHBoxLayout>
#include <QString>
#include <QCalendarWidget>
#include <QDate>
#include "msort.h"
#include <cmath>

using namespace std;




class MainWindow : public QWidget
{
	Q_OBJECT

public:
	MainWindow(myDataStore* ds);
	~MainWindow();
	unsigned long long hashPassword(string userPassword);


private slots:
	//Following are all functions to commense mechanisms througout program
	void showCart();
	void quitMain();
	void addProdToCart();
	void addProdToList();
	void dumpData();
	void buyCart();
	void removeItem();
	void writeAReview();
	void closeReviewWindow();
	void addReviewToDataBase();
	void displayReview();
	void displayProductInfo();
	void displayReviewInfo();
	void prodOrder();
	void avgRatingFunc();
	void dateCompSort();
	void displayAmazon();
	void createAccount();
	void checkUser();
	void displayReccomend();
	void closeRecommend();
	void outputReccomended();
	void computeRecs();
	// void displayCartProdInfo();

//hi


private:
	QListWidget* recList;
	QString selectedUser;
	QWidget* displayAmazonWidget;
	QLabel* prodCartInfo;
	//Amazon Layout
	QVBoxLayout* prodOrderLayout;
	QHBoxLayout* dateGrid;
	QPushButton* decendingProds;
	QPushButton* acendingProds;
	QVBoxLayout* reviewInfoLayout;
	QLabel* reviewInfoHeader;
	QComboBox* month;
	QComboBox* date;
	QComboBox* year;
	QVBoxLayout* amazonLayout;
	QLabel* dateLabel;
	QHBoxLayout* reviewRatingLayout;
	QGridLayout* prodReviewLayout;
	QLabel* reviewLabel;
	QHBoxLayout* bottomSection;
	QLabel* reviewInfo;
	//Search Layoud
	QLabel* topIntroForProduct;
	QLabel* productInfo;
	QLineEdit* searchTerm;
	QRadioButton* andButton;
	QRadioButton* orButton;
	QPushButton* searchButton;
	QLabel* ratingLabel;

	QWidget* buttonWidget; //Button Row Widget for addcart and view cart
	QGridLayout* CartGrid;

	//Left Side
	QVBoxLayout* leftCol;

	//info for product output
	QVBoxLayout* prodLayout;
	QLabel* prodOutput;
	//###############################//

	//Review INFO
	QVBoxLayout* reviewLayout;
	// QLabel* prodReview;
	//###############################//

	QWidget* andOrWig;
	QGridLayout* andOrBox;

	QWidget* topLayout;

	QWidget* keywordWidget; //Keyword next to box Widget
	QGridLayout* keyGrid;
	//right side layout
	QVBoxLayout* rightCol;
	QLabel* keywords;
	QLineEdit* inputKeyword;

	QVBoxLayout* sortReviewGrid;
	QWidget* reviewSorter;
	QLabel* reviewSortLabel;
	QComboBox* reviewSortSelector;
	QPushButton* sortButton;
	//sort the products that are displayed at the top
	QListWidget* reviewList;
	QWidget* sortWig;
	QLabel* sortProducts;
	QComboBox* sortList;
	QGridLayout* TopSection;
	//List of searchedProducts
	QListWidget* searchedProds;
	QPushButton* addAReview;
	QVBoxLayout* reviewWindowLayout;
	QWidget* reviewWindow;
	//AddCart Button
	QPushButton* addToCart;

	//User Entry
	QComboBox* selectUser;

	//ViewCart
	QPushButton* viewCart;

	//Bottom Section Layout
	QHBoxLayout* bottomLayout;
	// bool itemIsClicked = false;
	//User drop Down
	QLabel* selectUserLabel;
	QComboBox* userDisplay;
	QWidget* userWig;
	//Bottom Buttons
	QPushButton* exitButton;
	QPushButton* printDatabase;

	// int test = 0;
	// QString s = QString::number(test);


	//Message Box Layout
	QVBoxLayout* msgBoxLayout;
	QListWidget* myCart;
	QWidget* cart;

	QWidget* otherWin;
	QListWidget* userCart;

	QGridLayout* cartLayout;


	// QLineEdit* reviewUser;
	// QLineEdit* reviewDate;
	QComboBox* reviewRating;
	QLineEdit* prodReview;
	QLineEdit* reviewDate;
	QStringList* ratingOptions;
	QPushButton* addReview;
	QPushButton* closeWindow ;
	QPushButton* checkDate;
	QLineEdit* outputName;
	QLabel* outputLabel;


	/*Authentication system*/
	QVBoxLayout* signInLayout;
	QHBoxLayout* userInput;
	QHBoxLayout* passInput;
	QHBoxLayout* signInButtonLayout;
	QWidget* signInScreen;
	QWidget* userInputWidget;
	QWidget* passInputWidget;
	QWidget* signInWidget;
	QLabel* userNameLabel;
	QLabel* passwordLabel;
	QLineEdit* userNameInput;
	QLineEdit* passwordInput;
	QPushButton* signInButton;
	QPushButton* newAccount;
	QPushButton* quitSignIn;



	//Product Reccomendations
	QPushButton* reccomendButton;
	QWidget* reccomendWindow;
	QGridLayout* reccomendLayout;
	QListWidget* reccomendedList;
	QPushButton* doneButton;
	
//Prev Searches
	vector<string> prevSearches;

	// deque<Product*> currCart;

	//My data store initializatn
	myDataStore* amazonStore;

};

