#pragma once
#include<string>

using namespace std;

class User
{
public:
	User(const string& login, const string& password, const string& name)
		: login_(login), password_(password), name_(name){}

	const string& getUserLogin() const { return login_; }

	const string& getUserPassword() const { return password_; }
	const string& setUserPassword(const string& password) { password_ = password; }

	const string& getUserName() const { return name_; }
	const string& setUserName(const string& name) { name_ = name; }

private:
	const string login_;
	string password_;
	string name_;
};

