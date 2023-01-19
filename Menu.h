#pragma once
#include <iostream>
#include"User.h"
#include"Mesange.h"
#include <vector>
#include <memory>

using namespace std;

class Menu {

private:
	vector <User> users;				// ������ �������������
	vector <Mesange> mesanges_;			// ������ ���������

public:
	Menu() {}							// �����������
	~Menu() {}							// ����������
	 
	static bool chatRun;						// ��� �������� ������������� ������ �����

	int changeLogin(/*string& login*/) {		// ������� �������� ������ �� �������
		cout << " Enter login: ";
		string login;
		cin >> login;		

		User::_curentName = login;				// ���������� �������� ������������
		int numberLogin = 0;

		for (numberLogin; numberLogin < User::_countUsers; numberLogin++) {		// ��������� ���� ���������������� ������������� �� ���
			if (login == users[numberLogin].getLogin()) {						// ���� ������ � ����� ������ ������
				cout << " Ok" << endl;
				return numberLogin;												// ���������� ����� �� ������ �������������
			}

		}

		return 255;																// ���� ������ ������ � ���� ��� 
	}

	int changeLoginTo(const string& nameTo) {	// ����� �������� ���������
		int numberLogin = 0;
		for (numberLogin; numberLogin < User::_countUsers; numberLogin++) {

			if (nameTo == users[numberLogin].getLogin()) {		// ������������ ������
				cout << "user found, ";
				return numberLogin + 1;							// ���������� ���������� �����

			}
		}
		cout << "no user" << endl;								// ������������ �� ������
		return 0;
	}

	bool changePassword(int i) {					// �������� ������

		string password;

		cout << "passworwd:";
		cin >> password;

		if (password == users[i].getPassword()) return 1;	// ������ ������������� 

		else cout << "try again" << endl;					// ������ �� ������
		return 0;

	}

	void saveLogin() {														// ������ ������

		if (changeLogin() == 255) {											// 255 ������������ ��������, ���� �� ������ ����� �����
			++User::_countUsers;											// ����������� ���������� ������������� 

			users.resize(User::_countUsers);								// ������ ������ �������
			users[User::_countUsers - 1].setLogin(User::_curentName);		// ���������� �����
			users[User::_countUsers - 1].setId(User::_countUsers);			// ���������� id
			User::_curentId = User::_countUsers;							// ������� id
			cout << "saved" << endl;
		}

	}

	void savePassword() {										// ��������� ������
		string password;

		cout << "password: ";				
		cin >> password;
		users[User::_countUsers - 1].setPassword(password);		// ������ ������
		cout << "saved" << endl << endl;

	}

	bool start(/*char operation*/) {							// ���� ���������

		char operation;
		cout << " 1 - Enter, 2 - Registration, 0 - Out" << endl;

		cin >> operation;

		switch (operation)
		{
		case '1': {																// ���� � �������
			if (users.size() < 1) { cout << "No users" << endl; return 1; }		// ���� ������������� � ���� ���
			int i = 0;
			i = changeLogin();
			if (i != 255) {														// ����� ������ ��������
				if (changePassword(i)) {										// ������ ������ ��������
					User::_curentId = ++i;										// ������� id	

					chatRun = true;
				}
			}

			else { cout << "Try again" << endl; }
			return 1;
		}
		case '2': {					// ����������� ������������
			saveLogin();			// ��������� �����
			savePassword();			// ��������� ������

			chatRun = true;
			return 1;

		}

		case '0': {					// ����� �� ���������
			chatRun = false;
			return 0;
		}
		default: {
			cout << "no" << endl;	// �� ��������� ������� ��������
			return 1; }

		}

	}

	bool chat(/*char operation*/) {			// ���� ���� ( ����� ����� � �������
		char operation;
		cout << "1 - read, 2 - send,3 - send to all, 4 - delete mesanges, other - exit" << endl;
		cin >> operation;

		switch (operation)
		{
		case '1': {														// ��������� ���������
			cout << "read messenge" << endl;

			for (unsigned int i = 0; i < mesanges_.size(); i++) {		// ���� ��� ��������� ������������ ������� ������������
				if (User::_curentName == mesanges_[i].getTo()) {
					cout << "from "
						<< mesanges_[i].getFrom() 
						<<": " << mesanges_[i].getText()
						<< endl;
				}
			}
			return 1;													// �������� � ���� ����
		}
		case '2': {														// ��������� ��������� ��������
			cout << "send to: ";
			string nameTo;
			cin >> nameTo;

			if (!changeLoginTo(nameTo)) { return 1; }					// �������� �������� �� �������

			cout << "text: ";// << endl;
			string text;
			cin >> text;

			mesanges_.push_back(Mesange(nameTo, users[User::_curentId - 1].getLogin(), text));	// ��������� ��������� � ����� ������� ���������

			return 1;													// �������� � ���� ����
		}
		case '3': {														// ��������� ���� �������������
			cout << "text:";// << endl;
			string text;
			cin >> text;
			
			for (unsigned int i = 0; i < users.size(); i++) {			// �������� �� ������ �������������
				if (User::_curentName== users[i].getLogin())continue;	// ����� ����

				mesanges_.push_back(Mesange(users[i].getLogin(),		// ��������� ��������� � ����� ������� ���������
					users[User::_curentId - 1].getLogin(), 
					text));
			}
			return 1;
		}

		case '4': {												// ������� ��� ��������� ������������
		
			for (int i = mesanges_.size()-1; i >=0 ; i--) {		// ���� ��������� � ���� ������� ������������
				string name = mesanges_[i].getTo();
				if (User::_curentName == name) {				// ��� �������

					mesanges_.erase(mesanges_.begin()+i);		// ������� 
				}
			}
			
			return 1;											// �������� � ���� ����

		}
		default:
			chatRun = false;
			return 0;											// �������� ���
		}

	}

};

bool Menu::chatRun = 0;
