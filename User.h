#pragma once

using namespace std;

class User {
private:
	string _login;
	string _password;
	int _id{};
public:

	static int _countUsers; // количество  пользователей - id 
	static string _curentName;
	static int _curentId;

	User() {
		
	}

	User(const string& login, const string& password) :_login(login), _password(password) {}	// конструктор с инициализацие по логину и паролю

	~User() {
		
	}	// деструктор

	void setLogin(const string& login);	

	const string& getLogin()const;

	void setPassword(const string& password);

	const string& getPassword()const;

	void setId(const int val);

	int getId();

};



