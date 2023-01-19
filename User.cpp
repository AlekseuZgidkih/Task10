#include <iostream>
#include"User.h"

void User::setLogin(const string& login) {
	_login = login;
}

const string& User::getLogin()const {
	return _login;
}

void User::setPassword(const string& password) {
	_password = password;
}

const string& User::getPassword()const {
	return _password;
}

void User::setId(const int val) { _id = val; }
int User::getId() { return _id; }
int User::_countUsers = 0;
string User::_curentName = "";
int User::_curentId = 0;