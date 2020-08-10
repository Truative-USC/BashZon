#include "user.h"
using namespace std;

User::User() : name_("unknown"), balance_(0.0), type_(1)
{

}
User::User(std::string name, double balance, int type, unsigned long long Password) :
    name_(name), balance_(balance), type_(type), password_(Password)
{

}

User::~User()
{

}



std::string User::getName() const
{
    return name_;
}

double User::getBalance() const
{
    return balance_;
}

void User::deductAmount(double amt)
{
    balance_ -= amt;
}

void User::dump(std::ostream& os)
{
    os << name_ << " "  << balance_ << " " << type_ << endl;
}
void User::setPassword(unsigned long long Password) {
	password_ = Password;
}
unsigned long long User::getPassword() {
	return password_;
}

// void User::setPassword(unsigned long long Password) {
// 	password_
// }