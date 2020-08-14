#include "BidDBHandler.h"

BidDBHandler::BidDBHandler()
{
	mDB = 0;
}

BidDBHandler::~BidDBHandler()
{
}

bool BidDBHandler::addBid(Bid bid)
{
	int result = 0;

	// Open database
	result = sqlite3_open(BID_DB_FILE.c_str(), &mDB);

	// If db fails to open, show error and return
	if (result != SQLITE_OK)
	{
		cout << "Cannot open Bid database. Error: " << sqlite3_errmsg(mDB) << endl;
		return false;
	}

	// Query to add bid
	string query = "INSERT INTO BID ('KEY', 'TITLE', 'FUND', 'AMOUNT') " \
		"VALUES ('" + bid.getKey() + "', '" + bid.getTitle() + "', '" + bid.getFund() + "', " + to_string(bid.getAmount()) + ");";

	// Create a prepared statement object to handle query result
	sqlite3_stmt *stmt = 0;

	// Prepare SQL for execution
	result = sqlite3_prepare_v2(mDB, query.c_str(), -1, &stmt, NULL);

	// Execution returned error
	if (result != SQLITE_OK)
	{
		cout << "Cannot add Bid to database. Error: " << sqlite3_errmsg(mDB) << endl;
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

bool BidDBHandler::removeBid(const string& key)
{
	int result = 0;

	// Open database
	result = sqlite3_open(BID_DB_FILE.c_str(), &mDB);

	// If db fails to open, show error and return
	if (result != SQLITE_OK)
	{
		cout << "Cannot open Bid database. Error: " << sqlite3_errmsg(mDB) << endl;
		return false;
	}

	// Query to remove bid
	string query = "DELETE FROM BID WHERE KEY = '" + key + "';";

	// Create a prepared statement object to handle query result
	sqlite3_stmt *stmt = 0;

	// Prepare SQL for execution
	result = sqlite3_prepare_v2(mDB, query.c_str(), -1, &stmt, NULL);

	// Execution returned error
	if (result != SQLITE_OK)
	{
		cout << "Cannot add Bid to database. Error: " << sqlite3_errmsg(mDB) << endl;
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

bool BidDBHandler::populateBinaryTree(BinarySearchTree* bst)
{
	int result = 0;

	// Open database
	result = sqlite3_open(BID_DB_FILE.c_str(), &mDB);

	// If db fails to open, show error and return
	if (result != SQLITE_OK)
	{
		cout << "Cannot open Bid database. Error: " << sqlite3_errmsg(mDB) << endl;
		return false;
	}

	// Query every record
	string query = "SELECT * FROM BID;";

	// Create a prepared statement object to handle query result
	sqlite3_stmt *stmt = 0;

	// Prepare SQL for execution
	result = sqlite3_prepare_v2(mDB, query.c_str(), -1, &stmt, NULL);

	// Execution returned error
	if (result != SQLITE_OK)
	{
		cout << "Cannot populate tree. Error: " << sqlite3_errmsg(mDB) << endl;
		sqlite3_close(mDB);
		return false;
	}

	// Continue stepping through database until there are no rows left
	while (sqlite3_step(stmt) == SQLITE_ROW)
	{
		// Get bid data from each column
		string key = string(reinterpret_cast<const char*>(sqlite3_column_text(stmt, 1)));
		string title = string(reinterpret_cast<const char*>(sqlite3_column_text(stmt, 2)));
		string fund = string(reinterpret_cast<const char*>(sqlite3_column_text(stmt, 3)));
		double amount = sqlite3_column_double(stmt, 4);

		// Create a bid object with data
		Bid bid(key, title, fund, amount);

		// Add bid to tree
		bst->addNode(bid);

	}

	// Finalize and close database
	sqlite3_finalize(stmt);
	sqlite3_close(mDB);

	return true;
}

bool BidDBHandler::addBids(vector<Bid> bids)
{
	int result = 0;

	// Open database
	result = sqlite3_open(BID_DB_FILE.c_str(), &mDB);

	// If db fails to open, show error and return
	if (result != SQLITE_OK)
	{
		cout << "Cannot open Bid database. Error: " << sqlite3_errmsg(mDB) << endl;
		return false;
	}

	// Construct query to add multiple bids
	string query = "INSERT INTO BID ('KEY', 'TITLE', 'FUND', 'AMOUNT') VALUES ";

	// Loop through the vector to add each bid to the query
	for (unsigned int i = 0; i < bids.size(); i++)
	{
		Bid currentBid = bids.at(i);
		query += "('" + currentBid.getKey() + "', '" +
			currentBid.getTitle() + "', '" +
			currentBid.getFund() + "', " +
			to_string(currentBid.getAmount()) + ")";

		// Add comma if not the last line, otherwise semicolon to finish statement
		if (i < (bids.size() - 1))
		{
			query += ", ";
		}
		else
		{
			query += ";";
		}
	}

	// Create a prepared statement object to handle query result
	sqlite3_stmt *stmt = 0;

	// Prepare SQL for execution
	result = sqlite3_prepare_v2(mDB, query.c_str(), -1, &stmt, NULL);

	// Execution returned error
	if (result != SQLITE_OK)
	{
		cout << "Cannot add Bid to database. Error: " << sqlite3_errmsg(mDB) << endl;
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