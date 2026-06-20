// SecurItem.h
#pragma once

#include <iostream>
#include <string>
#include <memory>
#include <vector>
#include "User.h"

using namespace std;

class SecureItem {
private:
	unique_ptr<User> currentUser;
	SecureItem() = default;
public:
	static SecureItem& getInstance();
	void signIn(string un, string pw);
	void signUp(string un, string pw);
	void logOut(); // currentuser = nullptr
	bool isLogged(); // currentuse != nullptr
	vector<VaultBinary> getUserData(); // return vector of vault items for current user
	void saveOrUpdate(VaultBinary item, int index); // save or update vault item for current user
	~SecureItem();
};

