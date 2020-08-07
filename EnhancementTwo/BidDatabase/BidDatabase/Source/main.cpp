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
	bool isLoggedIn = false;

	// Create database handler class
	UserDBHandler* userDBHandler = new UserDBHandler();

	// Variables to read from user when adding a bid
	string key = "",
		title = "",
		fund = "";
	double amount = 0.00;

	// Continue program until the user exits
	do 
	{
		// Show menu and read user choice
		displayMenu(username);

		cout << "Enter choice: ";
		cin >> choice;

		// Ensure the user enters a valid menu option
		while (choice < 1 || choice > 8)
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
					loadBids(fileName, bst);
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
					// Create new bid object with input data and add it to the tree
					bid = Bid(key, title, fund, amount);
					bst->addNode(bid);
					cout << "Bid added successfully." << endl;
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

				bst->removeNode(bidKey);
				cout << "Bid removed successfully." << endl;
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
				if (isValidLogin(username, password))
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
		}
	} while (choice != 8);

	cout << "Goodbye." << endl;

	// Free memory
	delete userDBHandler;

	return 0;
}
