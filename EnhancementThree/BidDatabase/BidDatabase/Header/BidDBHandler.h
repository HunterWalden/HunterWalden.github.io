#pragma once

#ifndef BID_DB_HANDLER_H
#define BID_DB_HANDLER_H

#include <sqlite3.h>
#include <vector>

#include "Bid.h"
#include "BinarySearchTree.h"

using namespace std;

// Global for database file name
const string BID_DB_FILE = "Bid.db";

// Class used to communicate with Bid database
class BidDBHandler
{
private:

	sqlite3* mDB;

public:

	/**
	* Default constructor
	*/
	BidDBHandler();

	/**
	* Destructor
	*/
	~BidDBHandler();

	/**
	* Add a new bid to the database
	*
	* @param bid The bid object to add
	*
	* @return true if added successfully
	*/
	bool addBid(Bid bid);

	/**
	* Remove a bid from the database
	*
	* @param key The key of the bid to remove
	*
	* @return true if removed successfully
	*/
	bool removeBid(const string& key);

	/**
	* Populate the binary tree by adding all database records
	*
	* @param bst A pointer to the binary tree to add to
	*
	* @return true if bids are added successfully
	*/
	bool populateBinaryTree(BinarySearchTree* bst);

	/**
	* Add multiple bids to the database
	*
	* @param bids A vector of bids to be added
	*
	* @return true if bids are added successfully
	*/
	bool addBids(vector<Bid> bids);
};

#endif
