//----------------------------------------------------------------------------
//	By: David Trinh
//	
//	BinTree.h
//	Description: BinTree header, contains the methods for BinTree.cpp
//	to include. This homework has a memory leak in the bstreeToArray method
//	and was not able to be fixed in time.
//
//	Assumptions: Lines from textfiles will be made of letters and the $ symbol
//	There will be no remove method. Sizing does not need to be checked for
//	bstreeToArray. Method to erase NodeData [] will be provided in main.
//----------------------------------------------------------------------------
#include "nodedata.h"

const int arraySize = 100;	//Fixed size for NodeData array

/*-----------------------------------BinTree--------------------------------*/
class BinTree {				
	//-------------------------------ostream----------------------------------
	// Takes a BinTree class and outputs data from Node in a line.
	friend ostream& operator<<(ostream&, const BinTree&);
	
public:
	BinTree();								// constructor
	BinTree(const BinTree &);				// copy constructor
	~BinTree();								// destructor, calls makeEmpty	
	bool isEmpty() const;			// Checks if tree is empty
	void makeEmpty();				// Deletes and clears memory from tree

	//------------------------------Equals Operator---------------------------
	// Empties current BinTree and copies BinTree in parameter to current tree
	BinTree& operator=(const BinTree &);    

	//------------------------------Compare Operator--------------------------
	//	Compares BinTree to another Bintree, returns true if variables
	//	are exactly the same.
	bool operator==(const BinTree &) const;

	//------------------------------Not Equals Operator-----------------------
	//	Compares BinTree to another BinTree, returns true if not equal
	bool operator!=(const BinTree &) const;

	//------------------------------Tree-To-Array-----------------------------
	//	Takes a binary tree and stores it into an array. Empties tree.
	void bstreeToArray(NodeData*[]);

	//------------------------------Array-To-Tree-----------------------------
	//	Takes a NodeData array and creates a tree from it. Clears array after
	void arrayToBSTree(NodeData*[]);

	//-------------------------------Insert-----------------------------------
	//	Inserts a new node into a tree
	bool insert(NodeData*);

	//-------------------------------Height-----------------------------------
	//	Finds the NodeData and returns the height in which it was found
	//	on the tree. Returns 0 if not found.
	int getHeight(const NodeData&);

	//-------------------------------Retrieve---------------------------------
	//	Searches tree for matching data, returns true if found and points the
	//	NodeData to its position.
	bool retrieve(const NodeData& match, NodeData*&) const;

	//-------------------------------DisplaySideways--------------------------
	//	provided below, displays the tree sideways
	void displaySideways() const;			
	
private:
	//-------------------------------Node-------------------------------------
	//	Used to create binary trees and arrays.
	struct Node {
		Node();								// Default constructor
		~Node();							// Destructor
		NodeData* data;						// pointer to data object
		Node* left;							// left subtree pointer
		Node* right;						// right subtree pointer
	};
	Node* root;								// root of the tree

	//--------------------------------Utility-Functions-----------------------
	void inorderHelper(ostream&) const;
	void copyHelper(Node *&, Node*);
	void sideways(Node*, int) const;		// helper for displaySideways()
	bool compareHelper(Node *, Node *) const;
	bool insertHelper(Node*&, NodeData*);
	bool retrieveHelper(const NodeData&, NodeData*&, Node*) const;
	void treeHelper(NodeData *data[], Node* curr, int& counter) const;
	void arrayToBSTreeHelper(NodeData *arr[], int min, int max);
	void privateOutputHelper(ostream& output, Node* printTree) const;
	int getHeightHelper(Node*, const NodeData&, int);
	void makeEmptyHelper(Node*);
};

