#pragma once

#ifndef BID_H
#define BID_H

#include <iostream>
#include <string>

using namespace std;

// Global character maximums
const int MAX_KEY_CHARACTERS = 10;
const int MAX_TITLE_CHARACTERS = 50;
const int MAX_FUND_CHARACTERS = 50;

class Bid
{
private:

	// Private member variables
	string mKey;
	string mTitle;
	string mFund;
	double mAmount;

public:

	/**
	* Constructor. Can be used as default or passed values
	*
	* @param key The key to assign this new Bid
	* @param title The title to assign this new Bid
	* @param fund The fund to assign this new Bid
	* @param amount The amount to assign this new Bid
	*/
	Bid(string key = "", string title = "", string fund = "", double amount = 0.0);

	/**
	* Destructor
	*/
	~Bid();

	/**
	* Change this bid's key value
	*
	* @param key New key to assign
	*/
	void setKey(const string& key);

	/**
	* Change this bid's title value
	*
	* @param title New title to assign
	*/
	void setTitle(const string& title);

	/**
	* Change this bid's fund value
	*
	* @param fund New fund to assign
	*/
	void setFund(const string& fund);

	/**
	* Change this bid's amount value
	*
	* @param amount New amount to assign
	*/
	void setAmount(const double& amount);

	/**
	* Get this bid's key value
	*
	* @return The bid's key
	*/
	const string getKey();

	/**
	* Get this bid's title value
	*
	* @return The bid's title
	*/
	const string getTitle();

	/**
	* Get this bid's fund value
	*
	* @return The bid's fund
	*/
	const string getFund();

	/**
	* Get this bid's amount value
	*
	* @return The bid's amount
	*/
	const double getAmount();

	/**
	* Display this bid's formatted information
	*/
	void display();
};

#endif