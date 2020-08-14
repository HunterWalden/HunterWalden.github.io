#include "Header.h"

int main(int argc, char* argv[]) 
{
	// Local variables
	string bidKey = "";
	BinarySearchTree* bst = new BinarySearchTree();
	string fileName = "";
	Bid bid = Bid();
	int choice = 0;
	string username = "", password = "";
	string newUsername = "", newPassword = "";
	bool isLoggedIn = false;
	vector<Bid> bids = vector<Bid>();

	// Create database handler classes
	UserDBHandler* userDBHandler = new UserDBHandler();
	BidDBHandler* bidDBHandler = new BidDBHandler();

	// Variables to read from user when adding a bid
	string key = "",
		title = "",
		fund = "";
	double amount = 0.00;

	// Popuate the tree with database records
	if (!bidDBHandler->populateBinaryTree(bst))
	{
		cout << "Failed to read bids from database." << endl;
	}

	// Continue program until the user exits
	do 
	{
		// Show menu and read user choice
		displayMenu(username);

		cout << "Enter choice: ";
		cin >> choice;

		// Ensure the user enters a valid menu option
		while (choice < 1 || choice > 9)
		{
			cout << "Invalid menu choice! Please try again: ";
			cin >> choice;
		}

		switch (choice) 
		{
			// Read in bids from a file
			case 1:
				// Admin operation: check login
				if (!isLoggedIn)
				{
					cout << "Please log in to perform this action." << endl;
					break;
				}

				fileName = getFileName();

				// Make sure valid file name is received before reading
				if (!fileName.empty())
				{
					// Read the file
					loadBids(fileName, bst, bids);

					// Pass the vector to the database to add each new bid
					if (!bidDBHandler->addBids(bids))
					{
						cout << "Failed to add bids to the database." << endl;
					}
				}

				break;

			// Display all bids
			case 2:
				bst->displayAllNodes();
				break;

			// Search for a bid
			case 3:
				bidKey = getBidKey();

				// Locate the bid
				bid = bst->findBid(bidKey);

				// Ensure bid is valid then display data
				if (!bid.getKey().empty()) 
				{
					bid.display();
				}
				// Otherwise show an error
				else 
				{
					cout << "Bid with key " << bidKey << " not found." << endl;
				}

				break;

			// Add a bid
			case 4:
				// Admin operation: check login
				if (!isLoggedIn)
				{
					cout << "Please log in to perform this action." << endl;
					break;
				}

				// Get bid data from user
				cout << "Enter new bid information" << endl;
				key = getBidKey();
				title = getBidTitle();
				fund = getBidFund();
				amount = getBidAmount();

				// Amount input failed, do not add bid
				if (amount < 0)
				{
					cout << "Bid failed to be added. Please try again." << endl;
				}
				else
				{
					// Create new bid object with input data
					bid = Bid(key, title, fund, amount);

					// Attempt to add to db
					if (bidDBHandler->addBid(bid))
					{
						bst->addNode(bid);
						cout << "Bid added successfully." << endl;
					}
					// Add failed, show error
					else
					{
						cout << "Bid failed to be added. Please try again." << endl;
					}
				}

				break;

			// Remove a bid
			case 5:
				// Admin operation: check login
				if (!isLoggedIn)
				{
					cout << "Please log in to perform this action." << endl;
					break;
				}

				bidKey = getBidKey();

				// Attempt to remove from db
				if (bidDBHandler->removeBid(bidKey))
				{
					bst->removeNode(bidKey);
					cout << "Bid removed successfully." << endl;
				}
				// Remove failed, show error
				else
				{
					cout << "Bid failed to be removed. Please try again." << endl;
				}

				break;

			// Admin login
			case 6:
				// Make sure users cannot login twice
				if (isLoggedIn)
				{
					cout << "You are currently logged in as " << username << ". Please log out first to change accounts." << endl;
					break;
				}

				// Flush newline from cin
				cin.ignore();

				// Get login info from user
				username = getUsername();
				password = getPassword();

				// Validate credentials and start login session if successful
				if (userDBHandler->validateCredentials(username, password))
				{
					isLoggedIn = true;
					cout << "Logged in successfully." << endl;
				}
				else
				{
					username = "";
					password = "";
					cout << "Login failed." << endl;
				}
				
				break;

			// Log out
			case 7:
				// Cannot log out unless logged in
				if (!isLoggedIn)
				{
					cout << "You are not currently logged in!" << endl;
					break;
				}

				// Clear login info
				username = "";
				password = "";
				isLoggedIn = false;

				cout << "Logged out successfully." << endl;

				break;

			// Create account
			case 8:
				// Cannot create account unless logged in
				if (!isLoggedIn)
				{
					cout << "You must be logged in to create a new account." << endl;
					break;
				}

				// Flush newline from cin
				cin.ignore();

				// Get account info from user
				newUsername = getUsername();
				newPassword = getPassword();

				// Add to database, if true then success
				if (userDBHandler->addUser(newUsername, newPassword))
				{
					cout << "Account created successfully." << endl;
				}
				else
				{
					cout << "Account creation failed." << endl;
				}

				break;
		}
	} while (choice != 9);

	cout << "Goodbye." << endl;

	// Free memory
	delete userDBHandler;
	delete bidDBHandler;
	delete bst;

	return 0;
}
