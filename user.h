#ifndef USER_H
#define USER_H
#include <iostream>
#include <string>

/**
 * Implements User functionality and information storage
 *  You should not need to derive anything from User at this time
 */
class User {
public:
    User();
    User(std::string name, double balance, int type, unsigned long long Password);
    virtual ~User();
    std::string getUser() const;
    double getBalance() const;
    std::string getName() const;
    void deductAmount(double amt);
    void setPassword(unsigned long long Password);
    virtual void dump(std::ostream& os);
    unsigned long long getPassword();
    // void setPassword(unsigned long long Password);

private:
    std::string name_;
    double balance_;
    int type_;
    unsigned long long password_;
};
#endif
