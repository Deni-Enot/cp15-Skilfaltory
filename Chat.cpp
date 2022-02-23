#include<iostream>
#include"Chat.h"

void Chat::login()
{
	string login, password;
	int operation;

	do
	{
		cout << "login: ";
		cin >> login;
		cout << endl;
		cout << "password: ";
		cin >> password;

		currentUser_ = getUserByLogin(login);

		if (currentUser_ == nullptr || (password != currentUser_->getUserPassword()))
		{
			currentUser_ = nullptr;
			cout << "login failed..." << endl;
			cout << "(0) exit, or any key" << endl;
			cin >> operation;
			if (operation == 0)
				break;
		}
	} while (!currentUser_);
}

void Chat::signUp()
{
	string login, password, name;

	cout << "login: ";
	cin >> login;
	cout << endl;
	cout << "password: ";
	cin >> password;
	cout << endl;
	cout << "name: ";
	cin >> name;

	if (getUserByLogin(login) || login == "all")
	{
		throw UserLoginExp();
	}
	if (getUserByName(name) || name == "all")
	{
		throw UserNameExp();
	}

	User user = User(login, password, name);
	users_.push_back(user);
	currentUser_ = make_shared<User>(user);
}

void Chat::showChat() const
{
	string from; 
	string to;

	cout << "=== Chat ===" << endl;
	for (auto mess : messeges_)
	{
		if (currentUser_->getUserLogin() == mess.getFrom() || currentUser_->getUserLogin() == mess.getTo() || mess.getTo() == "all")
		{
			from = (currentUser_->getUserLogin() == mess.getFrom()) ? "me" : getUserByLogin(mess.getFrom())->getUserName();
			if (mess.getTo() == "all")
			{
				to = "(all)";
			}
			else
			{
				to = (currentUser_->getUserLogin() == mess.getTo()) ? "me" : getUserByLogin(mess.getTo())->getUserName();
			}
			cout << "Messege from " << from << "to " << to << endl;
			cout << "text " << mess.getText() << endl;
		}
	}
}

void Chat::showAllUsersName() const
{
	cout << "=== Users ===" << endl;
	for (auto& user : users_)
	{
		cout << user.getUserName() << endl;

		if (currentUser_->getUserLogin() == user.getUserLogin())
			cout << "me" << endl;
		cout << endl;
	}
	cout << "--------" << endl;
}

void Chat::addMessege()
{
	string to, text;
	cout << "to name or all: ";
	cin >> to;
	cout << " text " << endl;
	cin.ignore();
	getline(cin, text);

	if (!(to == "all" || getUserByName(to)))
	{
		cout << "error send messege: can't find " << to << endl;
		return;
	}
	
	if (to == "all")
		messeges_.push_back(Messege{ currentUser_->getUserLogin(), "all", text });
	else
		messeges_.push_back(Messege{ currentUser_->getUserLogin(), getUserByName(to)->getUserLogin(), text });
}

shared_ptr<User> Chat::getUserByLogin(const string& login) const
{
	for (auto& user : users_)
	{
		if (login == user.getUserLogin())
			return make_shared<User>(user);
	}
	return nullptr;
}

shared_ptr<User> Chat::getUserByName(const string& name) const
{
	for (auto &user : users_)
	{
		if (name == user.getUserName())
			return make_shared<User>(user);
	}
	return nullptr;
}

void Chat::start()
{
	isChatWork_ = true;
}

void Chat::showLoginMenu()
{
	currentUser_ = nullptr;
	int operation;
	do
	{
		cout << "[1] login " << endl;
		cout << "[2] SignUp" << endl;
		cout << "[0] Shotdown" << endl;
		cin >> operation;

		switch (operation)
		{
		case 1:
			login();
			break;
		case 2:
			try
			{
				signUp();
			}
			catch (const exception& e)
			{
				cout << e.what() << endl;
			}
			break;
		case 0:
			isChatWork_ = false;
			break;
		default:
			cout << "1 or 2" << endl;
			break;
		}

	} while (!currentUser_ && isChatWork_);
}

void Chat::showUserMenu()
{
	int operation;
	cout << "hi " << currentUser_->getUserName() << endl;

	while (currentUser_)
	{
		cout << "menu: 1 Show Chat, 2 Add messege, 3 users, 0 Logout" << endl;
		cin >> operation;
		switch (operation)
		{
		case 1:
			showChat();
			break;
		case 2:
			addMessege();
			break;
		case 3:
			showAllUsersName();
			break;
		case 0:
			currentUser_ = nullptr;
			break;
		default:
			cout << "Error: uncknow choice" << endl;
			break;
		}
	}
}
