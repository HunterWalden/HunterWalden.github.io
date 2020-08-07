#pragma once

#ifndef HEADER_H
#define HEADER_H

#include <algorithm>
#include <iostream>
#include <time.h>
#include <string>
#include <vector>
#include <fstream>
#include <stdlib.h>

#include "CSVparser.hpp"
#include "BinarySearchTree.h"
#include "Bid.h"
#include "sha256.h"
#include "UserDBHandler.h"

using namespace std;

// Global character limits
const int MAX_USERNAME_CHARACTERS = 16;
const int MAX_PASSWORD_CHARACTERS = 128;

/**
* Simple C function to convert a string to a double
* after stripping out unwanted char
*
* credit: http://stackoverflow.com/a/24875936
*
* @param str The string to modify
* @param ch The character to strip out
*
* @return A double version of the string without the char
*/
double stripCharStrToDouble(string str, char ch);

/**
* Load a CSV file containing bids into a container
*
* @param csvPath the path to the CSV file to load
* @param bst A pointer to the binary search tree that will hold the bids
*/
void loadBids(string csvPath, BinarySearchTree* bst);

/**
* Display a menu of user options
*
* @param username The current user's username
*/
void displayMenu(const string& username);

/**
* Read in a bid key from the user
*
* @return The bid key entered
*/
string getBidKey();

/**
* Read in a bid title from the user
*
* @return The bid title entered
*/
string getBidTitle();

/**
* Read in a bid fund from the user
*
* @return The bid fund entered
*/
string getBidFund();

/**
* Read in a bid amount from the user
*
* @return The bid amount entered
*/
double getBidAmount();

/**
* Read in .csv file name to read bids
*
* @return The file name entered
*/
string getFileName();

/**
* Check if a string contains only numbers
*
* @param str The string to check
*
* @return true if string is all numbers, otherwise false
*/
bool isNumeric(const string& str);

/**
* Read in a username string from the user
*
* @return The username entered
*/
string getUsername();

/**
* Read in a password string from the user
*
* @return The password entered
*/
string getPassword();

/**
* Check if the user entered valid credentials
*
* @param username The entered username
* @param password The entered password
*
* @return true if credentials match the database, otherwise false
*/
bool isValidLogin(const string& username, const string& password);

#endif 
