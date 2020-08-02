#include "Header.h"

int main(int argc, char* argv[]) 
{
	// Local variables
	string bidKey = "";
	BinarySearchTree* bst = new BinarySearchTree();
	string fileName = "";
	Bid bid = Bid();
	int choice = 0;

	// Variables to read from user when adding a bid
	string key = "",
		title = "",
		fund = "";
	double amount = 0.00;

	// Continue program until the user exits
	do 
	{
		// Show menu and read user choice
		displayMenu();

		cout << "Enter choice: ";
		cin >> choice;

		// Ensure the user enters a valid menu option
		while (choice < 1 || choice > 6)
		{
			cout << "Invalid menu choice! Please try again: ";
			cin >> choice;
		}

		switch (choice) 
		{
			// Read in bids from a file
			case 1:
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
				bidKey = getBidKey();

				bst->removeNode(bidKey);
				cout << "Bid removed successfully." << endl;
				break;
		}
	} while (choice != 6);

	cout << "Goodbye." << endl;

	return 0;
}
