#include "UserDBHandler.h"

UserDBHandler::UserDBHandler()
{
	db = 0;
}

UserDBHandler::~UserDBHandler()
{
}

/**
* Default callback function used when executing SQL statements
*
* @param data Data provided in the 4th argument of sqlite3_exec()
* @param argc The number of columns in row
* @param An array of strings representing fields in the row
* @param azColName An array of strings representing column names
*
* @return 0 if successful
*/
int callback(void *data, int argc, char **argv, char **azColName)
{
	return 0;
}

bool UserDBHandler::addUser(const string& username, const string& password, const string& salt)
{
	int result = 0;
	char *zErrMsg = 0;
	bool success = true;

	// Open database
	result = sqlite3_open(DB_FILE.c_str(), &db);

	// If db fails to open, show error and return
	if (exit)
	{
		cout << "Cannot open User database. Error: " << sqlite3_errmsg(db) << endl;
		return false;
	}

	// Query to add user
	string query = "INSERT INTO USER ('USERNAME', 'PASSWORD', 'SALT') " \
		"VALUES('" + username + "', '" + password + "', '" + salt + "');";

	// Execute query
	result = sqlite3_exec(db, query.c_str(), callback, 0, &zErrMsg);

	// Execution returned error
	if (result != SQLITE_OK) 
	{
		cout << "Cannot add user to table. Error: " << zErrMsg << endl;
		sqlite3_free(zErrMsg);
		success = false;
	}

	// Close database
	sqlite3_close(db);

	return success;
}