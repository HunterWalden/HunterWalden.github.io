#include "UserDBHandler.h"

UserDBHandler::UserDBHandler()
{
	mDB = 0;
}

UserDBHandler::~UserDBHandler()
{
}

bool UserDBHandler::addUser(const string& username, const string& password)
{
	int result = 0;
	string salt = "",
		hashedPassword = "";

	// Open database
	result = sqlite3_open(USER_DB_FILE.c_str(), &mDB);

	// If db fails to open, show error and return
	if (result != SQLITE_OK)
	{
		cout << "Cannot open User database. Error: " << sqlite3_errmsg(mDB) << endl;
		return false;
	}

	// First, query for username to see if it is taken
	string query = "SELECT * FROM 'USER' WHERE USERNAME = '" + username + "';";

	// Create a prepared statement object to handle query result
	sqlite3_stmt* stmt = 0;

	// Prepare SQL for execution
	result = sqlite3_prepare_v2(mDB, query.c_str(), -1, &stmt, NULL);

	// Execution returned error
	if (result != SQLITE_OK)
	{
		sqlite3_close(mDB);
		return false;
	}

	// If step is successful, username exists
	if (sqlite3_step(stmt) == SQLITE_ROW)
	{
		cout << "Username is already in use." << endl;
		sqlite3_close(mDB);
		return false;
	}

	// Clear prepared statement
	sqlite3_finalize(stmt);
	stmt = 0;

	// Generate salt for password
	salt = generateSalt();

	// Hash password with SHA-2 + salt
	hashedPassword = sha256(salt + password);

	// Query to add user
	query = "INSERT INTO USER ('USERNAME', 'PASSWORD', 'SALT') " \
		"VALUES ('" + username + "', '" + hashedPassword + "', '" + salt + "');";

	// Prepare SQL for execution
	result = sqlite3_prepare_v2(mDB, query.c_str(), -1, &stmt, NULL);

	// Execution returned error
	if (result != SQLITE_OK)
	{
		cout << "Cannot add User to database. Error: " << sqlite3_errmsg(mDB) << endl;
		sqlite3_close(mDB);
		return false;
	}

	// Step to execute query
	sqlite3_step(stmt);

	// Finalize and close database
	sqlite3_finalize(stmt);
	sqlite3_close(mDB);

	return true;
}

bool UserDBHandler::validateCredentials(const string& username, const string& password)
{
	int result = 0;
	string salt = "";

	// Open database
	result = sqlite3_open(USER_DB_FILE.c_str(), &mDB);

	// If db fails to open, show error and return
	if (result != SQLITE_OK)
	{
		cout << "Cannot open User database. Error: " << sqlite3_errmsg(mDB) << endl;
		return false;
	}

	// First, query for the username to ensure it exists + get salt
	string query = "SELECT * FROM 'USER' WHERE USERNAME = '" + username + "';";

	// Create a prepared statement object to handle query result
	sqlite3_stmt *stmt = 0;

	// Prepare SQL for execution
	result = sqlite3_prepare_v2(mDB, query.c_str(), -1, &stmt, NULL);

	// Execution returned error
	if (result != SQLITE_OK)
	{
		sqlite3_close(mDB);
		return false;
	}

	// If step is successful, result exists
	if (sqlite3_step(stmt) == SQLITE_ROW)
	{
		// Get user info from query results
		string hashedPassword = string(reinterpret_cast<const char*>(sqlite3_column_text(stmt, 2)));
		string salt = string(reinterpret_cast<const char*>(sqlite3_column_text(stmt, 3)));

		// Salt and hash the provided password to compare to the stored password
		if (sha256(salt + password) != hashedPassword)
		{
			// Incorrect password, return
			sqlite3_close(mDB);
			return false;
		}

	}
	// Step failed, username does not exist
	else
	{
		sqlite3_close(mDB);
		return false;
	}

	// Finalize and close database
	sqlite3_finalize(stmt);
	sqlite3_close(mDB);

	return true;
}

string UserDBHandler::generateSalt()
{
	// Random device + engine for creating salts
	std::random_device randomDevice;
	std::default_random_engine randomEngine(randomDevice());

	// String containing potential salt characters
	const string charset = "0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz";

	// Uniformly distribute characters
	std::uniform_int_distribution<int> randomNumber(0, charset.length() - 1);

	// Reserve 32 spaces for the salt
	string salt;
	salt.reserve(32);

	// Add random characters to the salt
	for (int i = 0; i < 32; i++) 
	{
		salt.push_back(charset[randomNumber(randomEngine)]);
	}

	return salt;
}