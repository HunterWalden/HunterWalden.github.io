#include "Header.h"

double stripCharStrToDouble(string str, char ch)
{
	str.erase(remove(str.begin(), str.end(), ch), str.end());
	return atof(str.c_str());
}

void loadBids(string csvPath, BinarySearchTree* bst, vector<Bid>& bids)
{
	cout << "Loading CSV file " << csvPath << endl;

	// Initialize the CSV Parser using the given path
	csv::Parser file = csv::Parser(csvPath);

	// Read and display header row
	vector<string> header = file.getHeader();
	for (auto const& c : header) 
	{
		cout << c << " | ";
	}
	cout << "" << endl;

	try 
	{
		// Loop to read rows of a CSV file
		for (unsigned int i = 0; i < file.rowCount(); i++) 
		{
			// Create a Bid structure and add to the collection of bids
			Bid bid;
			bid.setKey(file[i][1]); // Bid key located in row 2
			bid.setTitle(file[i][0]); // Bid title located in row 1
			bid.setFund(file[i][8]); // Bid fund located in row 9
			bid.setAmount(stripCharStrToDouble(file[i][4], '$')); // Bid amount located in row 5

			// Add to the tree
			bst->addNode(bid);

			// Add bid to the vector
			bids.push_back(bid);
		}
	}
	catch (csv::Error &e) 
	{
		cerr << e.what() << endl;
	}
}

void displayMenu(const string& username)
{
	cout << "Welcome " << (username.empty() ? "Guest" : username) << endl;
	cout << "Please choose a menu option:" << endl;
	cout << "  1. Load Bids From File" << endl;
	cout << "  2. Display All Bids" << endl;
	cout << "  3. Find Bid" << endl;
	cout << "  4. Add Bid" << endl;
	cout << "  5. Remove Bid" << endl;
	cout << "  6. Log In" << endl;
	cout << "  7. Log Out" << endl;
	cout << "  8. Create Account" << endl;
	cout << "  9. Exit" << endl;
}

string getBidKey()
{
	string bidKey = "";

	// Flush newline from cin
	cin.ignore();

	cout << "Enter bid key: ";
	getline(cin, bidKey);

	// Bid keys must be numeric and less than character limit
	while (!isNumeric(bidKey) || bidKey.length() > MAX_KEY_CHARACTERS)
	{
		cout << "Invalid bid key! Please try again: ";
		getline(cin, bidKey);
	}

	return bidKey;
}

string getBidTitle()
{
	string bidTitle = "";

	cout << "Enter bid title: ";
	getline(cin, bidTitle);

	// Make sure title does not exceed character limit
	while (bidTitle.length() > MAX_TITLE_CHARACTERS)
	{
		cout << "Bid titles cannot exceed " << MAX_TITLE_CHARACTERS << " characters. Please try again: ";
		getline(cin, bidTitle);
	}

	return bidTitle;
}

string getBidFund()
{
	string bidFund = "";

	cout << "Enter bid fund: ";
	getline(cin, bidFund);

	// Make sure fund does not exceed character limit
	while (bidFund.length() > MAX_FUND_CHARACTERS)
	{
		cout << "Bid funds cannot exceed " << MAX_FUND_CHARACTERS << " characters. Please try again: ";
		getline(cin, bidFund);
	}

	return bidFund;
}

double getBidAmount()
{
	string amountStr = "";
	double amount = 0.0;

	cout << "Enter amount: ";
	// Read in as string for easier checking
	getline(cin, amountStr);

	// Make sure a number is entered
	while (!isNumeric(amountStr))
	{
		cout << "Amount must be a number. Try again: ";
		getline(cin, amountStr);
	}

	// String is all numbers, convert to double
	try
	{
		amount = stod(amountStr);
	}
	// If the string amount is out of possible range for a double, catch error
	catch (out_of_range e)
	{
		cout << "Input is too large." << endl;
		return -1.0;
	}

	return amount;
}

string getFileName()
{
	string fileName = "";
	bool success = true;

	// Flush newline from cin
	cin.ignore();
	cout << "Enter file name: ";
	getline(cin, fileName);

	// File name is too short
	if (fileName.length() < 5)
	{
		cout << "Invalid file name." << endl;
		return "";
	}

	// Check if string ends in ".csv"
	if (fileName.substr(fileName.length() - 4, fileName.length() - 1) != ".csv")
	{
		cout << "Input must be a .csv file." << endl;
		return "";
	}
	
	// Make sure file exists
	ifstream inFile;
	inFile.open(fileName);
	if (!inFile.good())
	{
		cout << "File not found." << endl;
		inFile.close();
		return "";
	}
	inFile.close();

	return fileName;
}

bool isNumeric(const string& str)
{
	// Loop through each character and check if it's a digit
	for (unsigned int i = 0; i < str.length(); i++)
	{
		// Not a digit, string not numeric
		if (!isdigit(str[i]))
		{
			return false;
		}
	}

	return true;
}

string getUsername()
{
	string username = "";

	cout << "Enter username: ";
	getline(cin, username);

	// Make sure input does not exceed character limit or contain illegal characters
	while (username.length() > MAX_USERNAME_CHARACTERS || containsIllegalCharacters(username))
	{
		cout << "Invalid username. Please try again: ";
		getline(cin, username);
	}

	return username;
}

string getPassword()
{
	string password = "";

	cout << "Enter password: ";
	getline(cin, password);

	// Make sure input does not exceed character limit
	while (password.length() > MAX_PASSWORD_CHARACTERS)
	{
		cout << "Invalid password. Please try again: ";
		getline(cin, password);
	}

	// Once valid password is entered, hash it with SHA-2
	// TODO: Generate and add a salt to be saved to the database
	password = sha256(password);

	return password;
}

bool containsIllegalCharacters(const string& str)
{
	// String containing illegal characters
	string illegalChars = ",.<>'\"\\/[]{}()!@#$%^&*`~|+=?;:";

	// Loop through illegal string to check each element
	for (unsigned int i = 0; i < illegalChars.length(); i++)
	{
		// String contains this char, return true
		if (str.find(illegalChars[i]) != string::npos)
		{
			return true;
		}
	}

	return false;
}