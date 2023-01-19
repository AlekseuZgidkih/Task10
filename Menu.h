#pragma once
#include <iostream>
#include"User.h"
#include"Mesange.h"
#include <vector>
#include <memory>

using namespace std;

class Menu {

private:
	vector <User> users;				// массив пользоваетелй
	vector <Mesange> mesanges_;			// массив сообщений

public:
	Menu() {}							// конструктор
	~Menu() {}							// деструктор
	 
	static bool chatRun;						// для проверки промежуточной версии проги

	int changeLogin(/*string& login*/) {		// функция проверки логина на наличие
		cout << " Enter login: ";
		string login;
		cin >> login;		

		User::_curentName = login;				// запоминаем текущего пользователя
		int numberLogin = 0;

		for (numberLogin; numberLogin < User::_countUsers; numberLogin++) {		// проверяем всех зарегесрированых пользователей на имя
			if (login == users[numberLogin].getLogin()) {						// если найден с таким именем хорошо
				cout << " Ok" << endl;
				return numberLogin;												// возвращаем номер из списка пользователей
			}

		}

		return 255;																// если такого логина в базе нет 
	}

	int changeLoginTo(const string& nameTo) {	// поиск адресата сообщения
		int numberLogin = 0;
		for (numberLogin; numberLogin < User::_countUsers; numberLogin++) {

			if (nameTo == users[numberLogin].getLogin()) {		// пользователь найден
				cout << "user found, ";
				return numberLogin + 1;							// возвращаем порядковый номер

			}
		}
		cout << "no user" << endl;								// пользователь не найден
		return 0;
	}

	bool changePassword(int i) {					// проверка пароля

		string password;

		cout << "passworwd:";
		cin >> password;

		if (password == users[i].getPassword()) return 1;	// пароль соответствует 

		else cout << "try again" << endl;					// пароль не верный
		return 0;

	}

	void saveLogin() {														// запись логина

		if (changeLogin() == 255) {											// 255 возвращаемое значение, если не найдет такой логин
			++User::_countUsers;											// увеличиваем количество пользователей 

			users.resize(User::_countUsers);								// меняем размер массива
			users[User::_countUsers - 1].setLogin(User::_curentName);		// записываем логин
			users[User::_countUsers - 1].setId(User::_countUsers);			// записываем id
			User::_curentId = User::_countUsers;							// текущий id
			cout << "saved" << endl;
		}

	}

	void savePassword() {										// сохраняет пароль
		string password;

		cout << "password: ";				
		cin >> password;
		users[User::_countUsers - 1].setPassword(password);		// запись пароля
		cout << "saved" << endl << endl;

	}

	bool start(/*char operation*/) {							// меню стартовое

		char operation;
		cout << " 1 - Enter, 2 - Registration, 0 - Out" << endl;

		cin >> operation;

		switch (operation)
		{
		case '1': {																// вход в профиль
			if (users.size() < 1) { cout << "No users" << endl; return 1; }		// если пользователей в базе нет
			int i = 0;
			i = changeLogin();
			if (i != 255) {														// логин прошел проверку
				if (changePassword(i)) {										// пароль прошел проверку
					User::_curentId = ++i;										// текущий id	

					chatRun = true;
				}
			}

			else { cout << "Try again" << endl; }
			return 1;
		}
		case '2': {					// регистрация пользователя
			saveLogin();			// сохранить логин
			savePassword();			// сохранить пароль

			chatRun = true;
			return 1;

		}

		case '0': {					// выход из программы
			chatRun = false;
			return 0;
		}
		default: {
			cout << "no" << endl;	// не правильно введено значение
			return 1; }

		}

	}

	bool chat(/*char operation*/) {			// меню чата ( после входа в профиль
		char operation;
		cout << "1 - read, 2 - send,3 - send to all, 4 - delete mesanges, other - exit" << endl;
		cin >> operation;

		switch (operation)
		{
		case '1': {														// прочитать сообщения
			cout << "read messenge" << endl;

			for (unsigned int i = 0; i < mesanges_.size(); i++) {		// ищем все сообщения адресованные данному пользователю
				if (User::_curentName == mesanges_[i].getTo()) {
					cout << "from "
						<< mesanges_[i].getFrom() 
						<<": " << mesanges_[i].getText()
						<< endl;
				}
			}
			return 1;													// остаемся в меню чата
		}
		case '2': {														// отправить сообщение адресату
			cout << "send to: ";
			string nameTo;
			cin >> nameTo;

			if (!changeLoginTo(nameTo)) { return 1; }					// проверка адресата на наличие

			cout << "text: ";// << endl;
			string text;
			cin >> text;

			mesanges_.push_back(Mesange(nameTo, users[User::_curentId - 1].getLogin(), text));	// добавляем сообщение в конец вектора сообщений

			return 1;													// остаемся в меню чата
		}
		case '3': {														// сообщение всем пользователям
			cout << "text:";// << endl;
			string text;
			cin >> text;
			
			for (unsigned int i = 0; i < users.size(); i++) {			// проходим по списку пользователей
				if (User::_curentName== users[i].getLogin())continue;	// кроме себя

				mesanges_.push_back(Mesange(users[i].getLogin(),		// добавляем сообщение в конец вектора сообщений
					users[User::_curentId - 1].getLogin(), 
					text));
			}
			return 1;
		}

		case '4': {												// удаляем все сообщения пользователя
		
			for (int i = mesanges_.size()-1; i >=0 ; i--) {		// ищем сообщения в базе данного пользователя
				string name = mesanges_[i].getTo();
				if (User::_curentName == name) {				// имя найдено

					mesanges_.erase(mesanges_.begin()+i);		// удаляем 
				}
			}
			
			return 1;											// остаемся в меню чата

		}
		default:
			chatRun = false;
			return 0;											// покидаем чат
		}

	}

};

bool Menu::chatRun = 0;
