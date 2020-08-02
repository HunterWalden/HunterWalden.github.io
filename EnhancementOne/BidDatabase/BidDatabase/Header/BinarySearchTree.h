#pragma once

#ifndef BINARY_SEARCH_TREE_H
#define BINARY_SEARCH_TREE_H

#include "Bid.h"

// Structure for holding tree nodes
struct Node
{
	Bid mData;
	Node* mLeft;
	Node* mRight;

	/**
	* Default constructor
	*/
	Node()
	{
		mData = Bid();
		mLeft = 0;
		mRight = 0;
	}
};

class BinarySearchTree
{
private:

	// Private member variables
	Node* mRoot;

	/**
	* Private member function to add a node to the tree
	*
	* @param node The new node to add
	* @param bid The bid data of the node
	*/
	void privateAddNode(Node* node, Bid bid);

	/**
	* Private member recursive function to display all tree nodes in order
	*
	* @param node The current node to display
	*/
	void privateDisplayAllNodes(Node* node);

	/**
	* Private member recursive function to remove a node from the tree
	*
	* @param node The current node to check for deletion
	* @param bidKey The key of the bid to delete
	*
	* @return A pointer to the next node to check or the deleted node itself (used as exit condition)
	*/
	Node* privateRemoveNode(Node* node, string bidKey);

	/**
	* Private member recursive function to delete every node on the tree
	*
	* @param node The current node to delete
	*/
	void deleteTree(Node* node);

public:

	/**
	* Default constructor
	*/
	BinarySearchTree();

	/**
	* Destructor
	*/
	~BinarySearchTree();

	/**
	* Add a new node to the tree
	*
	* @param bid The bid info to attach to the node
	*/
	void addNode(Bid bid);

	/**
	* Remove a node from the tree
	*
	* @param bidKey The key of the node to delete
	*/
	void removeNode(string bidKey);

	/**
	* Display every node on the tree in order
	*/
	void displayAllNodes();

	/**
	* Find a particular bid's data using its key
	*
	* @param bidKey The key of the bid to find
	*
	* @return The Bid object corresponding to the key (or an empty object if not found)
	*/
	Bid findBid(string bidKey);
};

#endif