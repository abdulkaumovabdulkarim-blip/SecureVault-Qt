// User.h
#pragma once

#include <iostream>
#include <string>

using namespace std;

struct UserBinary {
	char username[40];
	char password[30];
};

struct VaultBinary {
	char owner[40];
	char website[50];
	char password[30];
	char note[100];
};

class User {
private:
	string username;
public:
	User() = default;
	User(string username) : username(username) {}
	string getUsername() const { return username; }
};