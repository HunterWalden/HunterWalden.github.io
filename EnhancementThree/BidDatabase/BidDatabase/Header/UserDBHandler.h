#pragma once

#ifndef USER_DB_HANDLER_H
#define USER_DB_HANDLER_H

#include <sqlite3.h>
#include <iostream>
#include <string>
#include "sha256.h"
#include <random>

using namespace std;

// Global for database file name
const string USER_DB_FILE = "User.db";

// Global for size of salt strings
const int SALT_LENGTH = 32;

// Class used to communicate with User database
class UserDBHandler
{
private:

	sqlite3* mDB;

public:

	/**
	* Default constructor
	*/
	UserDBHandler();

	/**
	* Destructor
	*/
	~UserDBHandler();

	/**
	* Add a new row to the database
	* 
	* @param username Username to add to this row
	* @param password Password to add to this row
	* @param salt Password salt to add to this row
	*
	* @return true if added successfully
	*/
	bool addUser(const string& username, const string& password);

	/**
	* Validate entered username + password against the database
	*
	* @param username Entered username to check
	* @param password Entered password to check
	*
	* @return true if credentials are valid
	*/
	bool validateCredentials(const string& username, const string& password);

	/**
	* Create a pseudorandom salt for user passwords
	*
	* Created with help from https://stackoverflow.com/questions/56357869/how-to-generate-a-pseudorandom-32-byte-string-for-use-as-a-salt-in-a-cryptograph
	*
	* @return The generated salt
	*/
	string generateSalt();
};

#endif