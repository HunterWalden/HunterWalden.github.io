#include "BinarySearchTree.h"

BinarySearchTree::BinarySearchTree()
{
	mRoot = 0;
}

BinarySearchTree::~BinarySearchTree()
{
	// Ensure memory is freed when class is destroyed
	deleteTree(mRoot);
}

void BinarySearchTree::addNode(Bid bid)
{
	// Create a new node with the passed Bid
	Node* newNode = new Node();
	newNode->mData = bid;

	// Add it to the tree
	privateAddNode(newNode, bid);
}

void BinarySearchTree::removeNode(string bidKey)
{
	// Private removal function will return a new root when done
	mRoot = privateRemoveNode(mRoot, bidKey);
}

void BinarySearchTree::displayAllNodes()
{
	// Root is null, tree is empty
	if (mRoot == 0)
	{
		cout << "Database is empty" << endl;
		return;
	}

	// Traverse tree starting at the root
	privateDisplayAllNodes(mRoot);
}

Bid BinarySearchTree::findBid(string bidKey)
{
	// Start at the root and traverse the tree
	Node* current = mRoot;

	while (current != 0)
	{
		// If the current bid is correct, return it
		if (current->mData.getKey() == bidKey)
		{
			return current->mData;
		}
		// If the current bid's key is greater than the key to search for, traverse to the left
		else if (bidKey < current->mData.getKey())
		{
			current = current->mLeft;
		}
		// Otherwise traverse to the right
		else
		{
			current = current->mRight;
		}
	}

	// If the bid isn't found, return an empty one
	return Bid();
}

void BinarySearchTree::privateAddNode(Node* node, Bid bid)
{
	// if the root doesn't exist, the new bid becomes the root
	if (mRoot == 0)
	{
		mRoot = node;
		return;
	}

	// Start at the root and traverse the tree
	Node* current = mRoot;

	while (current != 0)
	{
		// If the bid key is less than the current node's key, then the bid belongs on the left side of the tree
		if (bid.getKey() < current->mData.getKey())
		{
			// If the current's left node doesn't exist, the bid is the new left node
			if (current->mLeft == 0)
			{
				current->mLeft = node;
				current = 0;
			}
			// Otherwise, keep traversing the left side
			else
			{
				current = current->mLeft;
			}
		}
		// Otherwise it belongs on the right
		else
		{
			// If the current's right node doesn't exist, the bid is the new right node
			if (current->mRight == 0)
			{
				current->mRight = node;
				current = 0;
			}
			// Otherwise, keep traversing the right side
			else
			{
				current = current->mRight;
			}
		}
	}
}

void BinarySearchTree::privateDisplayAllNodes(Node* node)
{
	// Recursively output each node's left, parent, and right, in order
	if (node != 0)
	{
		privateDisplayAllNodes(node->mLeft);
		node->mData.display();
		privateDisplayAllNodes(node->mRight);
	}
}

Node* BinarySearchTree::privateRemoveNode(Node* node, string bidKey)
{
	// Exit conditionn - if the node is null then stop recursion
	if (node == 0)
	{
		return node;
	}

	// If the bid is in the left subtree then traverse to the left
	if (bidKey < node->mData.getKey())
	{
		node->mLeft = privateRemoveNode(node->mLeft, bidKey);
	}
	// Or if the bid is in the right subtree then traverse right
	else if (bidKey > node->mData.getKey())
	{
		node->mRight = privateRemoveNode(node->mRight, bidKey);
	}
	// Otherwise, this bid is the bid we want
	else
	{
		// If this node as no children, just delete it
		if (node->mLeft == 0 && node->mRight == 0)
		{
			delete node;
			node = 0;
		}
		// If this node only has a right child, it moves up to the node's location
		else if (node->mLeft == 0 && node->mRight != 0)
		{
			Node* temp = node;
			node = node->mRight;
			delete temp;
		}
		// If this node only has a left child, it moves up to the node's location
		else if (node->mRight == 0 && node->mLeft != 0)
		{
			Node* temp = node;
			node = node->mLeft;
			delete temp;
		}
		else
		{
			// Find the successor (leftmost node of right subtree)
			Node* successor = node->mRight;
			while (successor->mLeft != 0)
			{
				successor = successor->mLeft;
			}

			// Replace the node to be deleted with the successor's data and delete the successor
			node->mData = successor->mData;
			node->mRight = privateRemoveNode(node->mRight, successor->mData.getKey());
		}
	}
	return node;
}

void BinarySearchTree::deleteTree(Node* node)
{
	// Recursive exit condition - stop when next node is null
	if (node == 0)
	{
		return;
	}

	// Delete left and right children from this node
	deleteTree(node->mLeft);
	deleteTree(node->mRight);

	// Then delete the node itself
	delete node;
}