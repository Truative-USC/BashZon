#include "main_window.h"
#include <iostream>
#include <sstream>
#include <QString>
#include <fstream>
#include <QSpacerItem>
#include <QBoxLayout>
#include <cmath>
#include <iomanip>
using namespace std;




MainWindow::MainWindow(myDataStore* ds) {
	displayAmazonWidget = new QWidget();
//Layout Initilizations
	amazonStore = ds;
	setWindowTitle("Amazon ");
	leftCol = new QVBoxLayout();
	amazonLayout = new QVBoxLayout();
	displayAmazonWidget->setLayout(amazonLayout);
	rightCol = new QVBoxLayout();
	CartGrid = new QGridLayout();
	keyGrid = new QGridLayout();
	TopSection = new QGridLayout();
	prodLayout = new QVBoxLayout();
	reviewLayout = new QVBoxLayout();
	bottomLayout = new QHBoxLayout();
	msgBoxLayout = new QVBoxLayout();
	sortReviewGrid = new QVBoxLayout();
	reviewWindowLayout = new QVBoxLayout();
	reviewRatingLayout = new QHBoxLayout();
	reviewInfoLayout = new QVBoxLayout();
	bottomSection = new QHBoxLayout();
	signInScreen = new QWidget();
	signInLayout = new QVBoxLayout();
	userInput = new QHBoxLayout();
	passInput = new QHBoxLayout();
	signInButtonLayout = new QHBoxLayout();
	recList = new QListWidget();
	//Sign In Screen
	signInScreen->setLayout(signInLayout);
	signInLayout->addLayout(userInput);
	signInLayout->addLayout(passInput);
	signInLayout->addLayout(signInButtonLayout);
	//End Initialization for Sign in screen

	//Begin Sign in Widgets
	signInScreen->setWindowTitle("Amazon Login");
	signInScreen->move(20, 20);
	userNameLabel = new QLabel("UserName: ");
	userInput->addWidget(userNameLabel);
	userNameInput = new QLineEdit();
	passwordInput = new QLineEdit();
	userInput->addWidget(userNameInput);
	passwordLabel = new QLabel("Password:   ");
	passInput->addWidget(passwordLabel);
	passInput->addWidget(passwordInput);
	passwordInput->setEchoMode(QLineEdit::Password);
	signInButton = new QPushButton("Sign In");
	newAccount = new QPushButton("New Account");
	quitSignIn = new QPushButton("Quit");
	signInButtonLayout->addWidget(signInButton);
	signInButtonLayout->addWidget(newAccount);
	signInButtonLayout->addWidget(quitSignIn);
	connect(signInButton, SIGNAL(clicked()), this, SLOT(checkUser()));
	connect(quitSignIn, SIGNAL(clicked()), this, SLOT(closeReviewWindow()));
	connect(quitSignIn, SIGNAL(clicked()), this, SLOT(closeRecommend()));
	// connect(quitSignIn, SIGNAL(clicked()), this, SLOT((quitMain())));
	connect(newAccount, SIGNAL(clicked()), this, SLOT(createAccount()));
	connect(quitSignIn, SIGNAL(clicked()), this, SLOT(quitMain()));
		connect(quitSignIn, SIGNAL(clicked()), this, SLOT(close()));



	//End Layout intilizations

	//Middle Searched Products
	prodCartInfo = new QLabel("Product info: ");
	topIntroForProduct = new QLabel("Product info: ");
	productInfo = new QLabel(" ");
	prodLayout->addWidget(topIntroForProduct);

	//Top sectoin layout for Seached, Reviews and Prod Info
	topLayout = new QWidget();
	amazonLayout->addWidget(topLayout);
	topLayout->setLayout(TopSection);

	//adding layout to top section for prod and review;
	TopSection->addLayout(prodLayout, 0, 1);
	TopSection->addLayout(sortReviewGrid, 0 , 2);


	//The following is the layout for the Review Wins
	prodOutput = new QLabel(" ");
	prodLayout->addWidget(prodOutput);
	prodLayout->addWidget(productInfo);
	prodLayout->addStretch();
	reviewList = new QListWidget();
	sortReviewGrid->addWidget(reviewList);
	reccomendButton = new QPushButton("Reccomendations");
	prodLayout->addWidget(reccomendButton);
	sortButton = new QPushButton("Sort Reviews");
	prodLayout->addWidget(sortButton);
	connect(sortButton, SIGNAL(clicked()), this, SLOT(dateCompSort()));
	addAReview = new QPushButton("Add Reiview");

	dateGrid = new QHBoxLayout();
	reviewWindowLayout->addLayout(dateGrid);
	dateLabel = new QLabel("Date: ");
	dateGrid->addWidget(dateLabel);


	reviewWindow = new QWidget();
	reviewWindow->setLayout(reviewWindowLayout);
	reccomendWindow = new QWidget();
	reccomendLayout = new QGridLayout();
	reccomendWindow->setLayout(reccomendLayout);
	reccomendWindow->setWindowTitle("Product Reccomendations");
	reccomendedList = new QListWidget();
	connect(reccomendButton, SIGNAL(clicked()), this, SLOT(displayReccomend()));
	connect(reccomendButton, SIGNAL(clicked()), this, SLOT(outputReccomended()));
	doneButton = new QPushButton("Done");
	reccomendLayout->addWidget(doneButton, 100, 50, 1, 50);
	connect(doneButton, SIGNAL(clicked()), this, SLOT(closeRecommend()));
	//Initilization of Date Sequence
	month = new QComboBox();
	year = new QComboBox();
	date = new QComboBox();
	for (int i = 1; i < 32; i++) {
		if (i < 10) {
			stringstream ss;
			ss << i;
			string newString = ss.str();
			string temp = "0" + newString;
			QString qstr = QString::fromStdString(temp);

			date->addItem(qstr);
		}
		else {
			QString qstr = QString::number(i);
			date->addItem(qstr);
		}
	}
	for (int j = 1; j < 13; j++) {
		if (j < 10) {
			stringstream ss;
			ss << j;
			string newString = ss.str();
			string temp = "0" + newString;
			QString qstr = QString::fromStdString(temp);

			month->addItem(qstr);
		}
		else {
			QString qstr = QString::number(j);

			month->addItem(qstr);
		}
	}
	for (int k = 2016; k < 2031; k++) {
		QString qstr = QString::number(k);
		year->addItem(qstr);
	}

	//Initilization for the bottom section of the Layout
	dateGrid->addWidget(year);
	dateGrid->addWidget(month);
	dateGrid->addWidget(date);
	reviewWindowLayout->addLayout(reviewRatingLayout);
	ratingLabel = new QLabel("Rating: ");
	reviewRating = new QComboBox();
	reviewRatingLayout->addWidget(ratingLabel);
	reviewRatingLayout->addWidget(reviewRating);
	prodReviewLayout = new QGridLayout();
	reviewWindowLayout->addLayout(prodReviewLayout);
	reviewWindowLayout->addLayout(bottomSection);
	reviewLabel = new QLabel("Product Review");
	prodReview = new QLineEdit();
	prodReviewLayout->addWidget(reviewLabel, 0, 0, 0, 10);
	prodReviewLayout->addWidget(prodReview, 1, 10, 40, 50);
	addReview = new QPushButton("Add Review");
	closeWindow = new QPushButton("Close");
	bottomSection->addWidget(addReview);
	bottomSection->addWidget(closeWindow);
	for (int i = 1; i < 6; i++) {
		// string temp = i.toStdString();
		reviewRating->addItem(QString::number(i));
	}
	// checkDate = new QPushButton("Check Date");
	// bottomSection->addWidget(checkDate);
	connect(addAReview, SIGNAL(clicked()), this, SLOT(writeAReview()));
	prodLayout->addWidget(addAReview);
	productInfo = new QLabel(" ");
	searchedProds = new QListWidget();
	// connect(searchedProds, SIGNAL(currentRowChanged(int)), this, SLOT(displayProds()));
	TopSection->addWidget(searchedProds, 0 , 0);
	buttonWidget = new QWidget();
	amazonLayout->addWidget(buttonWidget);
	buttonWidget->setLayout(CartGrid);
	cartLayout = new QGridLayout();
	otherWin = new QWidget;
	otherWin->setLayout(cartLayout);
	addToCart = new QPushButton("Add to Cart");
	connect(addToCart, SIGNAL(clicked()), this, SLOT(addProdToCart()));
	CartGrid->addWidget(addToCart, 0, 0, 1 , 1);
	viewCart = new QPushButton("View Cart");
	connect(viewCart, SIGNAL(clicked()), this, SLOT(showCart()));
	CartGrid->addWidget(viewCart, 0, 1, 1, 1);

	//Sort Product Section
	sortProducts = new QLabel("Sort Products: ");
	keyGrid->addWidget(sortProducts, 0 , 2);
	prodOrderLayout = new QVBoxLayout();
	keyGrid->addLayout(prodOrderLayout, 0, 3);
	decendingProds = new QPushButton("Alphabetical");
	connect(decendingProds, SIGNAL(clicked()), this, SLOT(prodOrder()));
	// conect(decendingProds, SIGNAL(clicked()), this, decendingOrder());
	acendingProds = new QPushButton("By Avg Rating");
	connect(acendingProds, SIGNAL(clicked()), this, SLOT(avgRatingFunc()));
	// connect(acendingProds, SIGNAL(clicked()))
	prodOrderLayout->addWidget(decendingProds);
	prodOrderLayout->addWidget(acendingProds);


	//Product Search Section
	keywordWidget = new QWidget();
	amazonLayout->addWidget(keywordWidget);
	keywordWidget->setLayout(keyGrid);


	keywords = new QLabel("Keyword(s):");
	keyGrid->addWidget(keywords, 0 , 0);

	inputKeyword = new QLineEdit();
	keyGrid->addWidget(inputKeyword, 0 , 1);
	//initializing the right layout

	sortWig = new QWidget();
	keyGrid->addWidget(sortWig);




	//radio Button for And Search
	amazonLayout->addLayout(rightCol);

	andButton = new QRadioButton("And Search");
	rightCol->addWidget(andButton);


	//Or Radio Button
	orButton = new QRadioButton("or Search");
	rightCol->addWidget(orButton);

	//Search Button

	searchButton = new QPushButton("Search");
	connect(searchButton, SIGNAL(clicked()), this, SLOT(addProdToList()));
	rightCol->addWidget(searchButton);
	connect(searchedProds, SIGNAL(itemClicked(QListWidgetItem*)), this, SLOT(displayReview()));
	connect(searchedProds, SIGNAL(itemClicked(QListWidgetItem*)), this, SLOT(displayProductInfo()));

	//adding Bottom Section for users and extra Buttons
	amazonLayout->addLayout(bottomLayout);
	selectUserLabel = new QLabel("Current User: ");
	bottomLayout->addWidget(selectUserLabel);

	//Display All Users
	userDisplay = new QComboBox();
	bottomLayout->addWidget(userDisplay);



	// dataBaseName = new QLineEdit();
	exitButton = new QPushButton("Quit");
	connect(exitButton, SIGNAL(clicked()), this, SLOT(quitMain()));
	connect(exitButton, SIGNAL(clicked()), this, SLOT(closeRecommend()));
	connect(exitButton, SIGNAL(clicked()), this, SLOT(close()));
	
	outputName = new QLineEdit();

	printDatabase = new QPushButton("Print DataBase");
	outputLabel = new QLabel("FileName: ");
	bottomLayout->addWidget(exitButton);
	bottomLayout->addWidget(outputLabel);
	bottomLayout->addWidget(outputName);
	bottomLayout->addWidget(printDatabase);

	connect(printDatabase, SIGNAL(clicked()), this, SLOT(dumpData()));
	setLayout(signInLayout);
}

MainWindow::~MainWindow() {}
void MainWindow::outputReccomended() {
	string output = "rec.txt";
	ofstream ofile(output.c_str());
	QString currUser = userDisplay->currentText();
	string userName = currUser.toStdString();
}

void MainWindow::closeRecommend() {
	reccomendWindow->hide();
}

void MainWindow::displayReccomend() {
	reccomendWindow->show();
	reccomendWindow->move(20, 20);
	reccomendLayout->addWidget(reccomendedList, 50, 50, 50, 50);
	computeRecs();




}

void MainWindow::computeRecs() {
	reccomendedList->clear();
	string output = "rec";
	ofstream ofile(output.c_str());
	QString currUser = userDisplay->currentText();
	string userName = currUser.toStdString();
		ofile << userName << endl;

	recList->addItem(currUser);

	vector<std::pair<string, double> >currProducts = amazonStore->makeSuggestion(userName);
	sortProd<pair<string, double> > sort;
	mergeSortStarter(currProducts, sort);


	for(unsigned int i =0; i < currProducts.size();i++) {
		QString qstr = QString::number(currProducts[i].second, 'f', 2)
		 + QString::fromStdString(" ") + 
		 QString::fromStdString(currProducts[i].first);
		reccomendedList->addItem(qstr);
		ofile << fixed << setprecision(2) <<currProducts[i].second << " " << currProducts[i].first << endl;
	}


ofile.close();
}

void MainWindow::quitMain() {
	close();
	displayAmazonWidget->close();

}
void MainWindow::checkUser() {
	string user = userNameInput->text().toStdString();

	map<string, User*>currUsers = amazonStore->users();
	map<string, User*>::iterator it = currUsers.find(user);
	QMessageBox msgBox;

	if (it == currUsers.end()) {
		msgBox.setWindowTitle("User Error");
		msgBox.setText("Username does not exist");
		msgBox.exec();
	}
	else {

		unsigned long long currPassword = hashPassword(passwordInput->text().toStdString());
		unsigned long long userPassword = (it)->second->getPassword();
		if (currPassword == userPassword) {
			userDisplay->clear();
			selectedUser = userNameInput->text();
			// Qstring qstr =
			// vector<string> currUserVector = amazonStore->userToStrings();
			// for (unsigned int i = 0; i < currUserVector.size(); i++) {
			// 	string tempString = currUserVector[i];
			// 	QString qstr =  QString::fromStdString(tempString);

				userDisplay->addItem(selectedUser);
				// if (selectedUser == qstr) {
					userDisplay->setCurrentIndex(0);
				// }
			// }
			displayAmazon();
			userNameInput->clear();
			passwordInput->clear();

		}
		else {
			msgBox.setWindowTitle("User Fail");
			msgBox.setText("Password incorrect. Please try again");
			msgBox.exec();
		}
	}
}

unsigned long long MainWindow::hashPassword(string userPassword) {
	unsigned long long hash = 0;
	// string userPassword = passwordInput->text().toStdString();
	int k = 0;
	for (int i = userPassword.size() - 1; i > -1; i--) {
		hash += ((int)userPassword[i] * (unsigned long long)pow(128, k));
		++k;
	}

	unsigned int array[4];
	array[3] = hash % 65521;
	hash = hash / 65521;
	array[2] = hash % 65521;
	hash = hash / 65521;
	array[1] = hash % 65521;
	hash = hash / 65521;
	array[0] = hash % 65521;
	hash = hash / 65521;

	unsigned long long total = array[3] * 4625 + array[2] * 65169 + array[1] * 35511 + array[0] * 45912;
	hash = total % 65521;
	return hash;

}

void MainWindow::createAccount() {
	QMessageBox msgBox;
	msgBox.setWindowTitle("Error");
	string userName = userNameInput->text().toStdString();

	if (userNameInput->text().isEmpty() || passwordInput->text().isEmpty()) {

		msgBox.setText("Please fill in required fields");
		msgBox.exec();
	}

	else if (amazonStore->userPresent(userName)) {
		msgBox.setText("Username already exists");
		msgBox.exec();
	}

	else if (passwordInput->text().toStdString().size() > 8) {
		msgBox.setText("Password length cannot be longer than ");
		msgBox.exec();
	}
	else {
		unsigned long long userPassword = hashPassword(passwordInput->text().toStdString());
		amazonStore->createNewUser(userName, userPassword);
		QString qstr =  QString::fromStdString(userName);
		selectedUser = qstr;
		// userDisplay->addItem(qstr);
		vector<string> currUserVector = amazonStore->userToStrings();
		// for (unsigned int i = 0; i < currUserVector.size(); i++) {
			// string tempString = currUserVector[i];
			// QString qstr =  QString::fromStdString(tempString);

			userDisplay->addItem(qstr);
			// if (selectedUser == qstr) {
				userDisplay->setCurrentIndex(0);
			// }
		// }
		displayAmazon();
		passwordInput->clear();
		userNameInput->clear();
	}
}

void MainWindow::displayAmazon() {
	displayAmazonWidget->setLayout(amazonLayout);
	signInScreen->hide();
	displayAmazonWidget->show();

}



//The following function is to display the reviews on the right side of the UI
void MainWindow::displayReview() {


	reviewList->clear();
	QString currProd = searchedProds->currentItem()->text();
	string prodString = currProd.toStdString();
	map<Product*, std::vector<Review*> > reviews = amazonStore->returnReviews();
	map<Product*, vector<Review*> >::iterator it;
	vector<Review*>::iterator it2;
	vector<Review*> currentReviews;
	for (it = reviews.begin(); it != reviews.end(); it++) {
		if ((it)->first->getName() == prodString) {
			currentReviews = (it)->second;

		}
	}

	for (unsigned int i = 0; i < currentReviews.size(); i++) {

		string review;
		stringstream ss;
		ss << currentReviews[i]->rating;
		string date = currentReviews[i]->date;
		string user = currentReviews[i]->username;
		string productName = currentReviews[i]->prodName;
		string reviewInfo = currentReviews[i]->reviewText;
		string reviewRating = ss.str();

		review = productName + "\n" + reviewRating + " " +
		         date + " " + reviewInfo + " " + user + "\n";


		QString currString = QString::fromStdString(review);
		reviewList->addItem(currString);
	}

}

void MainWindow::displayProductInfo() {
	prodOutput->clear();
	QString currProd = searchedProds->currentItem()->text();
	string prodString = currProd.toStdString();
	set<Product*>::iterator it;
	set<Product*> currProdSet = amazonStore->returnProds();
	for (it = currProdSet.begin(); it != currProdSet.end(); it++) {
		if (prodString == (*it)->getName()) {
			stringstream stream;
			(*it)->dump(stream);
			QString prodText;
			prodText += QString::fromStdString(stream.str());
			prodOutput->setText(prodText);



		}
	}

}

void MainWindow::displayReviewInfo() {


	QString currProd = searchedProds->currentItem()->text();
	string prodString = currProd.toStdString();
	map<Product*, vector<Review*> > reviewMap = amazonStore->returnReviews();
	map<Product*, vector<Review*> >::iterator it;
	vector<Review*> currReviews;
	for (it = reviewMap.begin(); it != reviewMap.end(); it++) {
		if ((it)->first->getName() == prodString) {
			currReviews = (it)->second;
		}
	}

	QString currReview = reviewList->currentItem()->text();
	string reviewString = currReview.toStdString();

	reviewInfo->clear();
	for (unsigned int i = 0; i < currReviews.size(); i++) {
		if (currReviews[i]->reviewText == reviewString) {
			stringstream stream;
			currReviews[i]->dump(stream);
			QString review = QString::fromStdString(stream.str());
			reviewInfo->setText(review);
		}

	}

}

void MainWindow::showCart() {
	otherWin->show();
	otherWin->move(20, 20);

	QString currUser = userDisplay->currentText();
	string userName = currUser.toStdString();

	deque<Product*> currCart = amazonStore->userProds(userName);
	QPushButton* buyCart = new QPushButton("Buy Cart");
	QPushButton* removeItembutton = new QPushButton("Remove Item");
	connect(buyCart, SIGNAL(clicked()), this, SLOT(buyCart()));
	connect(removeItembutton, SIGNAL(clicked()), this, SLOT(removeItem()));
	userCart = new QListWidget();
	cartLayout->addWidget(userCart, 50, 50, 50, 50);
	cartLayout->addWidget(buyCart, 100, 80, 1 , 20);
	cartLayout->addWidget(removeItembutton, 100, 50, 1, 20);
	deque<Product*>::iterator it2;
	for (it2 = currCart.begin(); it2 != currCart.end(); it2++) {
		string tempString = (*it2)->getName();
		QString qstr = QString::fromStdString(tempString);
		userCart->addItem(qstr);
	}



}

//Search function
void MainWindow::addProdToList() {
	if (keywords->text().isEmpty() || inputKeyword->text().isEmpty()) {
		return;
	}
	else if (andButton->isChecked()) {
		if (inputKeyword->text().isEmpty()) {
			return;
		}
		searchedProds->clear();

		vector<string> terms;
		string inputText = inputKeyword->text().toStdString();
		stringstream ss(inputText);
		string tempString;
		while (ss >> tempString) {
			terms.push_back(convToLower(tempString));
		}
		vector<Product*> prods = amazonStore->search(terms, 0);
		for (unsigned int i = 0; i < prods.size(); i++) {

			string productName = prods[i]->getName();
			QString qstr = QString::fromStdString(productName);

			searchedProds->addItem(qstr);
		}

		searchedProds->setCurrentRow(0);


	}
	else if (orButton->isChecked()) {
		if (keywords->text().isEmpty()) {
			return;
		}
		searchedProds->clear();

		vector<string> terms;
		string inputText = inputKeyword->text().toStdString();
		stringstream ss(inputText);
		string tempString;
		while (ss >> tempString) {
			terms.push_back(convToLower(tempString));
		}
		vector<Product*> prods = amazonStore->search(terms, 1);
		for (unsigned int i = 0; i < prods.size(); i++) {

			string productName = prods[i]->getName();
			QString qstr = QString::fromStdString(productName);

			searchedProds->addItem(qstr);
		}
		searchedProds->setCurrentRow(0);


	}
	else {
		return;
	}
}

void MainWindow::addProdToCart() {

	if (searchedProds->count() > 0) {
		QString currProd = searchedProds->currentItem()->text();
		QString currUser = userDisplay->currentText();

		string userString = currUser.toStdString();
		string prodString = currProd.toStdString();

		set<Product*>::iterator it;
		set<Product*> prodSet = amazonStore->returnProds();
		for (it = prodSet.begin(); it != prodSet.end(); it++) {
			if ((*it)->getName() == prodString) {
				amazonStore->addToCart(userString, (*it));
			}
		}
		showCart();
	}
	else {
		return;
	}

}
//Opening Write a review Window
void MainWindow::writeAReview() {

	reviewWindow->show();
	reviewWindow->move(20, 20);

	connect(addReview, SIGNAL(clicked()), this, SLOT(addReviewToDataBase()));
	connect(closeWindow, SIGNAL(clicked()), this, SLOT(closeReviewWindow()));
}

//Buycart Button
void MainWindow::buyCart() {

	QString currUser = userDisplay->currentText();
	string userName = currUser.toStdString();
	amazonStore->buyCart(userName);
	userCart->clear();
}
//Removing item from your list of items in cart
void MainWindow::removeItem() {
	if (userCart->count() < 1 ) {
		return;
	}
	QString currUser = userDisplay->currentText();
	string userName = currUser.toStdString();
	deque<Product*> currCart = amazonStore->userProds(userName);
	deque<Product*>::iterator it;
	QList<QListWidgetItem*> cartItems = userCart->selectedItems();
	QString currProd = userCart->currentItem()->text();
	string product = currProd.toStdString();
	amazonStore->removeFromCart(userName, product);
	foreach (QListWidgetItem* item, cartItems) {
		string qstr = item->text().toStdString();
		delete userCart->takeItem(userCart->row(item));
	}
}
void MainWindow::dumpData() {
	QString fileQstring = outputName->text();

	string filename = fileQstring.toStdString();

	ofstream ofile(filename.c_str());
	amazonStore->dump(ofile);
	ofile.close();
}
//closing the window for your review
void MainWindow::closeReviewWindow() {
	reviewWindow->hide();
}
//adding the review to the databse after you have typed in all the data
void MainWindow::addReviewToDataBase() {

	if (!(searchedProds->currentRow() >= 0) || prodReview->text().isEmpty()) {
		return;
	}
	string currReview = prodReview->text().toStdString();
	QString currProd = searchedProds->currentItem()->text();
	QString currUser = userDisplay->currentText();
	QString currDate = date->currentText();
	QString currMonth = month->currentText();
	QString currYear = year->currentText();
	QString currRate = reviewRating->currentText();
	string currRate_ = currRate.toStdString();
	istringstream ss(currRate_);
	int currRateInt = 0;
	ss >> currRateInt;
	string currdate_ = currDate.toStdString();
	string currMonth_ = currMonth.toStdString();
	string currYear_ = currYear.toStdString();
	string userString = currUser.toStdString();
	string prodString = currProd.toStdString();
	string totalDate = currYear_ + "-" + currMonth_ + "-" + currdate_;

	Review* newReview = new Review(prodString, currRateInt, userString, totalDate, currReview);
	amazonStore->addReview(newReview);

}
//Alphabetical sorting for products
void MainWindow::prodOrder() {

	vector<string> productVec;

	for (int i = 0; i < searchedProds->count(); i++) {

		QString  itemQstring = searchedProds->item(i)->text();
		string temp = itemQstring.toStdString();
		productVec.push_back(temp);
		// searchedProds->clear();

	}


	AlphaStrComp<string> comp1;
	mergeSortStarter(productVec, comp1);
	searchedProds->clear();



	for (unsigned int j = 0; j < productVec.size(); j++) {

		string prodStr = productVec[j];
		QString qstr = QString::fromStdString(prodStr);
		searchedProds->addItem(qstr);
	}
	searchedProds->setCurrentRow(0);
}
//Rating sorting option
void MainWindow::avgRatingFunc() {
	set<Product*> currProdSet = amazonStore->returnProds();
	vector<Product*> compVec;
	for (int i = 0; i < searchedProds->count(); i++) {

		set<Product*>::iterator it = currProdSet.begin();
		string currProd = searchedProds->item(i)->text().toStdString();
		for (; it != currProdSet.end(); it++) {
			if (currProd == (*it)->getName()) {
				compVec.push_back(*it);
			}
		}

	}

	searchedProds->clear();
	avgRatingComp<Product*> comp1;
	mergeSortStarter(compVec, comp1);

	for (unsigned int j = 0; j < compVec.size(); j++) {

		string prodStr = compVec[j]->getName();
		QString qstr = QString::fromStdString(prodStr);
		searchedProds->addItem(qstr);
	}
}
//sort reviews by date function
void MainWindow::dateCompSort() {
	if (reviewList->count() < 1) {
		return;
	}
	string currProd = searchedProds->currentItem()->text().toStdString();
	map<Product*, vector<Review*> > prodToReviews = amazonStore->returnReviews();
	map<Product*, vector<Review*> >::iterator it;
	vector<Review*> currReviews;
	for (it = prodToReviews.begin(); it != prodToReviews.end(); it++) {
		if ((it)->first->getName() == currProd) {
			currReviews = it->second;
		}
	}

	reviewList->clear();
	dateSortComp<Review*> comp1;
	mergeSortStarter(currReviews, comp1);


	for (unsigned int i = 0; i < currReviews.size(); i++) {

		string review;
		stringstream ss;
		ss << currReviews[i]->rating;
		string date = currReviews[i]->date;
		string user = currReviews[i]->username;
		string productName = currReviews[i]->prodName;
		string reviewInfo = currReviews[i]->reviewText;
		string reviewRating = ss.str();

		review = productName + "\n" + reviewRating + " " + date + " " + reviewInfo + " " + user + "\n";


		QString currString = QString::fromStdString(review);
		reviewList->addItem(currString);
	}
}


