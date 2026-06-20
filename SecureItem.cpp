// SecureItem.cpp
#define _CRT_SECURE_NO_WARNINGS
#include "SecureItem.h"
#include <fstream>

SecureItem& SecureItem::getInstance() {
	static SecureItem instance;
	return instance;
}

SecureItem::~SecureItem() {
	logOut();
}

void SecureItem::signIn(string un, string pw) {
	ifstream userFile("users.dat", ios::binary);
	if (!userFile) {
		throw "Unable to open user data file.";
	}
	UserBinary user;

	while(userFile.read(reinterpret_cast<char*>(&user), sizeof(UserBinary))) {
		if (un == user.username && pw == user.password) {
			currentUser = make_unique<User>(un);
			return;
		}
	}

	throw "Invalid username or password.";
}

void SecureItem::signUp(string un, string pw) {
	ifstream userFile("users.dat", ios::binary);

	UserBinary user;

	while (userFile.read(reinterpret_cast<char*>(&user), sizeof(UserBinary))) {
		if (un == string(user.username)) {
			throw "User already exists.";
		}
	}

	UserBinary newUser;
	strncpy(newUser.username, un.c_str(), sizeof(newUser.username));
	strncpy(newUser.password, pw.c_str(), sizeof(newUser.password));

	ofstream outFile("users.dat", ios::binary | ios::app);
	if (!outFile) {
		throw "Unable to open user data file.";
	}
	outFile.write(reinterpret_cast<char*>(&newUser), sizeof(UserBinary));
}

void SecureItem::logOut() {
	currentUser = nullptr;
}

bool SecureItem::isLogged() {
	return currentUser != nullptr;
}

vector<VaultBinary> SecureItem::getUserData() {
	vector<VaultBinary> data;
	if (!isLogged()) {
		throw "No user is currently logged in.";
	}
	ifstream vaultFile("vault.dat", ios::binary);

	VaultBinary item;
	while (vaultFile.read(reinterpret_cast<char*>(&item), sizeof(VaultBinary))) {
		if (currentUser->getUsername() == string(item.owner)) {
			data.push_back(item);
		}
	}
	return data;
}

void SecureItem::saveOrUpdate(VaultBinary item, int index) {
	if (!isLogged()) {
		throw "No user is currently logged in.";
	}

	strncpy(item.owner, currentUser->getUsername().c_str(), sizeof(item.owner) - 1);
	item.owner[sizeof(item.owner) - 1] = '\0';

	if (index == -1) {
		ofstream outFile("vault.dat", ios::binary | ios::app);
		if (!outFile) {
			throw "Unable to open vault data file for writing.";
		}
		outFile.write(reinterpret_cast<const char*>(&item), sizeof(VaultBinary));
		outFile.close();
		return;
	}

	vector<VaultBinary> allItems;
	ifstream inFile("vault.dat", ios::binary);

	if (inFile) {
		VaultBinary temp;
		while (inFile.read(reinterpret_cast<char*>(&temp), sizeof(VaultBinary))) {
			allItems.push_back(temp);
		}
		inFile.close();
	}

	int currentUserItemCount = 0;
	bool found = false;

	for (size_t i = 0; i < allItems.size(); ++i) {
		if (string(allItems[i].owner) == currentUser->getUsername()) {
			if (currentUserItemCount == index) {
				allItems[i] = item;
				found = true;
				break;
			}
			currentUserItemCount++;
		}
	}

	if (!found) {
		throw "Record to update was not found.";
	}

	ofstream outFile("vault.dat", ios::binary | ios::trunc);
	if (!outFile) {
		throw "Unable to open vault data file for updating.";
	}

	for (const auto& entry : allItems) {
		outFile.write(reinterpret_cast<const char*>(&entry), sizeof(VaultBinary));
	}
	outFile.close();
}