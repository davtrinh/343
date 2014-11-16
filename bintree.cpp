//----------------------------------------------------------------------------
//	By: David Trinh
//	
//	BinTree.cpp
//	Description: This file contains implemtations for BinTree. There is a
//	memory leak in bstreeToArray. I understand that there will be deductions
//	as I was not able to fix it.
//	
//	Assumptions: 
//	- Nodedata array size will be fixed at 100, and no overflow checking will
//	be necessary. 
//	- Text files will be formatted correctly with only letters and $ symbols 
//	to indicate end of line or tree.
//	- lab2 will handle the deletion and initialization of NodeData array
//
//----------------------------------------------------------------------------
#include "bintree.h"

/*------------------------------Default Constructor---------------------------
 * @pre	 There must be no variables in the parameter
 * @post Variables will be initialized to NULL
 */
BinTree::BinTree(void) : root(NULL){ }

/*------------------------------Copy Constructor------------------------------
 * Calls on helper to copy other BinTree into this BinTree
 * @pre	 copyTree must not be empty, or else method will be returned.
 * @post CopyTree will be copied into this BinTree using CopyHelper
 */
BinTree::BinTree(const BinTree& copyTree) {
	root = NULL;
	copyHelper(root, copyTree.root);
}

/*------------------------------CopyHelper------------------------------------
 * Copies node values from other node to current tree
 * @pre	 curr must be empty and copyNode must not be empty
 * @post copyNode will copy its data into this Bintree to make a new tree
 */
void BinTree::copyHelper(Node *& curr,Node* copyNode) {
	if (curr != NULL || copyNode == NULL) return;
	
	curr = new Node();
	curr->data = new NodeData(*(copyNode->data)); 

	copyHelper(curr->left, copyNode->left);
	copyHelper(curr->right, copyNode->right);
}
/*------------------------------Destructor------------------------------------
 * @pre	None
 * @post Clears all memory from the tree
 */
BinTree::~BinTree(){
	makeEmpty();
}

/*------------------------------DestructorHelper------------------------------
 * @pre	None
 * @post Deletes root and sets it to NULL
 */
void BinTree::makeEmpty() { 
		delete root;
		root = NULL;
}

/*------------------------------EmptyCheck------------------------------------
 * @pre	None
 * @post Returns true if root is NULL, returns false if not NULL.
 */
bool BinTree::isEmpty() const {
	return (root == NULL);
}

/*------------------------------Default-Constructor---------------------------
 * @pre	 There must be only void in the parameters
 * @post All variables will be initialized to NULL
 */
BinTree::Node::Node(){
	data = NULL;
	left = NULL;
	right = NULL;
}
/*------------------------------Node-Destructor-------------------------------
 * Deletes node data as well as the whole tree
 * @pre	None
 * @post All nodes will be deleted and set to NULL
 */
BinTree::Node::~Node(void) {
		delete data;
		data = NULL;

		delete left;
		left = NULL;

		delete right;
		right = NULL;
}
/*------------------------------Operator Equal--------------------------------
 * Copies data from other tree to current tree
 * @pre	OtherTree must not be empty
 * @post Copies data from otherTree into this binTree
 */
BinTree& BinTree::operator=(const BinTree & otherTree) {
	if (this != &otherTree) {
		makeEmpty();						// Destructor
		copyHelper(root, otherTree.root);	// Recursive helper
	}
	return *this;
}

/*------------------------------Equality-Operator-----------------------------
 * Compares two trees
 *@pre	None
 *@post Returns true if both trees have the same data, otherwise returns false
 */
bool BinTree::operator==(const BinTree& otherTree)const {
	return compareHelper(root, otherTree.root);	//Recursive helper
}

/*------------------------------Inequality-Operator---------------------------
 * Compares two trees
 *@pre	None
 *@post Returns false if both trees have the same data, otherwise returns true
 */
bool BinTree::operator!=(const BinTree & otherTree) const {
	return (!(*this == otherTree));
}

/*------------------------------CompareHelper---------------------------------
 * Description: Recursive Helper. Checks two trees to see if both are equal
 * @pre	 None
 * @post Returns true if both trees or equal, else returns false
 */
bool BinTree::compareHelper(Node *curr, Node *other) const { 
	if (curr == NULL && other == NULL) return true;
	else
	if (curr == NULL || other == NULL) return true;
	bool check = ((*curr->data) == *(other->data)) 
		&& compareHelper(curr->left, other->left)
		&& compareHelper(curr->right, other->right);
	return check;
}

/*------------------------------bstreeToArray---------------------------------
 * Calls on recursiveHelper to move data from tree to array, then deletes tree
 * @pre	NodeData array must be empty
 * @post Binary tree will be emptied and data will be moved to NodeData array
 */
void BinTree::bstreeToArray(NodeData *data[]) {
	int currIndex = 0;					// Starting index for array
	treeHelper(data, root, currIndex);	// Recursive Helper
	makeEmpty();						// Destructor
}

/*------------------------------TreeHelper------------------------------------
 * Copies data from tree into NodeData array
 * @pre	 Current Node in param must not be empty
 * @post NodeData array will be filled with data from the binary tree.
 * @param index: The index for which the data will be placed into the array
 * @param curr:  The node that will be moved from the tree to the array
 * @param data[]: Array that is to be filled with data from bsTree
 */
void BinTree::treeHelper(NodeData *data[], Node* curr, int& index) const {
	if (curr == NULL) return; 

	treeHelper(data, curr->left, index);
	data[index++] = new NodeData (*(curr->data));
	treeHelper(data, curr->right, index);
}

/*------------------------------ArrayToBSTree---------------------------------
 * Calls on recursive helper to move array data into a binary search tree
 * @pre	 NodeData array must not be empty
 * @post Method will call recursive helper to create a tree with data from arr
 */
void BinTree::arrayToBSTree(NodeData *treeArray[]) {
	int maxSize;
	for (maxSize = 0; maxSize < arraySize; maxSize++)
		if (treeArray[maxSize] == NULL) break;
		if (maxSize == 0) return;
		arrayToBSTreeHelper(treeArray, 0, maxSize);
}

/*------------------------------ArrayHelper-----------------------------------
 * Description: This helper takes two integers, the first index and the last
 *				of the array to find middle index to insert into the tree.
 *				Method will continue searching each middle term until there
 *				are none left.
 * @pre	 Integer min must not be greater than integer max.
 * @post A tree will be created with data from NodeData array
 * @param arr[]: NodeData array that contains data to be used to create a tree
 * @param min:   Bottom section of that part of the array
 * @param max:	 Highest index for that section of the array
 */
void BinTree::arrayToBSTreeHelper(NodeData *arr[], int min, int max) {
	if (min > max) return;	// No more nodes to insert in this section

	insert(arr[((min + max) / 2)]);	// Insert into tree

	arrayToBSTreeHelper(arr, min, (((min + max) / 2) - 1)); //Left part of arr
	arrayToBSTreeHelper(arr, (((min + max) / 2) + 1), max);//Right part of arr
}

/*------------------------------Insert----------------------------------------
 * Calls recursive helper to inserts Node into tree
 * @pre	NodeData must not be NULL
 * @post NodeData will be inserted into tree and return true, else return
 *		 false if NodeData is a duplicate or NULL.
 */
bool BinTree::insert(NodeData* newData) {
	return (insertHelper(root, newData)); //Recursive Helper Below
}

/*------------------------------InsertHelper----------------------------------
 * Finds correct spot to insert Node into tree
 * Description: Puts nodes in order to create a binary search tree
 * @pre	NodeData must not be NULL
 * @post NodeData will be inserted into tree and return true, else return
 *		 false if NodeData is a duplicate or NULL.
 */
bool BinTree::insertHelper(Node *&curr, NodeData* newData) {

	if (newData == NULL)	// Empty data
		return false;

	if (curr == NULL) {		// Found correct position, puts in new data
		curr = new Node();	
		curr->data = newData;
		return true;
	}
	//	Finds the correct position of new data
	else if (*newData < *(curr->data)) 
		return insertHelper(curr->left, newData);
	else if (*newData > *(curr->data))
		return insertHelper(curr->right, newData);
	else
		return false; // Node must equal another node and will not be added

	return true;
}

/*------------------------------Retrieve--------------------------------------
 * @pre	NodeData being matched must not be empty. Root must not be empty.
 * @post Method will return true and pointer will point to found NodeData 
 *		if NodeData is found. If Nodedata is not found, return false.
 */
bool BinTree::retrieve(const NodeData& match, NodeData*& pointer) const{
	return retrieveHelper(match, pointer, root);
}
/*------------------------------RetrieveHelper--------------------------------
 * @pre	NodeData being matched must not be empty. Root must not be empty.
 * @post Method will return true and pointer will point to found NodeData
 *		if NodeData is found. If Nodedata is not found, return false.
 */
bool BinTree::retrieveHelper(const NodeData& match, NodeData *& pointer, Node *curr) const{
	if (curr == NULL) return false;
	if (match == *curr->data) {	//Found a match
		pointer = curr->data;
		return true;
	}
	// Not found, continue looking through tree
	else if (match < *curr->data)
		return retrieveHelper(match, pointer, curr->left);
	else if (match > *curr->data)
		return retrieveHelper(match, pointer, curr->right);
	return true;
}

/*------------------------------getHeight-------------------------------------
 * Calls on recursive helper to find the height of a Nodedata
 * @pre	None
 * @post BinTree unchanged
 * @return height of Nodedata in tree, or 0 if not found
 */
int BinTree::getHeight(const NodeData& match) {
	int startingHeight = 1;
	return getHeightHelper(root, match, startingHeight);
}
/*------------------------------getHeight-------------------------------------
 * Searches for matching NodeData in the tree
 * @pre	None
 * @post BinTree unchanged
 * @return height of Nodedata in tree, or 0 if not found
 */
int BinTree::getHeightHelper(Node* curr, const NodeData& match, int height) {
	if (curr == NULL) return 0;
	if (match == *curr->data) // Found match
		return height;

	height++; //Integer used to keep track of height on one route

	// Continues down checking left tree Node
	int tempCheckHeight = getHeightHelper(curr->left, match, height);

	// If nodedata is found, temp will not be 0
	if (tempCheckHeight != 0) return tempCheckHeight;

	//Contiues checking down the right tree node
	return getHeightHelper(curr->right, match, height);
}
ostream& operator<<(ostream& output, const BinTree& printTree){
	
	if (printTree.isEmpty()) return output;
	
	printTree.inorderHelper(output);
	output << endl;
	return output;
}
void BinTree::inorderHelper(ostream &output) const {
	privateOutputHelper(output, root);
}
void BinTree::privateOutputHelper(ostream& output, Node* printTree) const{
	if (printTree == NULL) return;
	privateOutputHelper(output, printTree->left);
	output << *printTree->data << " ";
	privateOutputHelper(output, printTree->right);

}
//------------------------- displaySideways ---------------------------------
// Displays a binary tree as though you are viewing it from the side;
// hard coded displaying to standard output.
// Preconditions: NONE
// Postconditions: BinTree remains unchanged.
void BinTree::displaySideways() const {
	sideways(root, 0);
}

//---------------------------- Sideways -------------------------------------
// Helper method for displaySideways
// Preconditions: NONE
// Postconditions: BinTree remains unchanged.
void BinTree::sideways(Node* current, int level) const {
	if (current != NULL) {
		level++;
		sideways(current->right, level);

		// indent for readability, 4 spaces per depth level 
		for (int i = level; i >= 0; i--) {
			cout << "    ";
		}

		cout << *current->data << endl;        // display information of object
		sideways(current->left, level);
	}
}

