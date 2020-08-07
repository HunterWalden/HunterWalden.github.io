#pragma once

#ifndef USER_DB_HANDLER_H
#define USER_DB_HANDLER_H

#include <sqlite3.h>
#include <iostream>
#include <string>

using namespace std;

// Global for database file name
const string DB_FILE = "User.db";

// Class used to communicate with User database

class UserDBHandler
{
private:

	sqlite3* db;

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
	bool addUser(const string& username, const string& password, const string& salt);


};

#endif