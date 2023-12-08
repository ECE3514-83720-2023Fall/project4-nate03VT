////////////////////////////////////////////////////////
// ECE 3514, Project 4, Nathaniel Sawitzki
// File name: prefixTree.cpp 
// Description: prefix tree functions
// Date: 12/4/2023 

#include "prefixTree.h"
//#include "treeNode.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <iostream>
#include <iomanip>
#include <string>
#include <algorithm>
using namespace std;

prefixTree::prefixTree() 
{
	rootPtr = nullptr; //empty tree
}  // end default constructor

prefixTree::prefixTree(std::string filename) { //*****not finished
	rootPtr = nullptr;
	//open file for reading, and check that it has been opened
	std::ifstream inputFile(filename);
	if (!inputFile.is_open()) {
		std::cout << "Error, unable to open file: " << filename << std::endl;
	}
	else {

		std::string line;
		while (std::getline(inputFile, line)) {
			size_t delimiterPos = line.find(':');
			if (delimiterPos != std::string::npos) {
				std::string netId = line.substr(0, delimiterPos);
				int port = std::stoi(line.substr(delimiterPos + 1));

				// Add the routing entry to the prefix tree
				add(netId, port);
			}
		}

	}

	inputFile.close();
}



prefixTree::~prefixTree()
{
	//resets tree and deallocates all the trees memory
	clear();
}






bool prefixTree::add(const std::string netid, const int port) {
	
	//if empty create a new tree from root node

	if (rootPtr == nullptr) {
		rootPtr = make_shared<treeNode>(netid, port);
		return true;

	}

	if (netid == "") {
		rootPtr->setPort(port);
		return true;
	}
	


	return addHelper(rootPtr, netid, port);


}

bool prefixTree::addHelper(std::shared_ptr<treeNode> node, const std::string& netId, const int port) {
	
//SECTION 1: handles matching prefix case
	if (node->getNetId() == netId) { //if ip prefix already exists, update port number
		node->setPort(port);
		return true;
	}
	
	/*
//SECTION 2: handles stuck cases
	int leftChildlength = node->getLeftChildPtr()->getNetId().length();
	int rightChildlength = node->getRightChildPtr()->getNetId().length();
	bool leftChildValid;
	bool rightChildValid;
	

		if (node->getLeftChildPtr() == nullptr) leftChildValid = false;
		else leftChildValid = netId.substr(0, leftChildlength) == node->getLeftChildPtr()->getNetId();
		 
	if (node->getRightChildPtr() == nullptr) rightChildValid = false;
	else rightChildValid = netId.substr(0, rightChildlength) == node->getRightChildPtr()->getNetId();

//if neither left nor right child has a matching prefix to traverse into, we are stuck and need to insert a node
		bool stuck = (!leftChildValid && !rightChildValid) || ( (leftChildlength>netId.length()) && (rightChildlength > netId.length()));

		//this section checks if neither child prefix can be moved into
		if ( !leftChildValid && !rightChildValid) { //if child prefix is longer than netid
			return	insertNode( node, netId, port);
		}
		*/

//SECTION 3: Handles insertion into leafs
	int	nodeLength = node->getNetId().length();
		//checks if the netId is less than the current nodes 
	if (netId.substr(nodeLength, 1) == "0") { //case where we should move left
		if (node->getLeftChildPtr() == nullptr) {
			// Create a new node if the left child is null
			node->setLeftChildPtr(make_shared<treeNode>(netId, port));
					return true; // Added successfully
		}
		else {
			// Recursively traverse to the left subtree
			return addHelper(node->getLeftChildPtr(), netId, port);
		}
	}
	else { //case for inserting into right
		if (node->getRightChildPtr() == nullptr) {
			// Create a new node if the right child is null
			node->setRightChildPtr(make_shared<treeNode>(netId, port));
			return true; // Added successfully
		}
		else {
			// Recursively traverse to the left subtree
			return addHelper(node->getRightChildPtr(), netId, port);
		}
	}


}

bool prefixTree::insertNode( std::shared_ptr<treeNode> node, const std::string& netId, const int port) {
	//create the netid for the invalid node (has the opossite last bit of inserting node)
	string invalidId = netId;
	if (invalidId.back() == '1') invalidId.back() = '0';
	else invalidId.back() = '1';
	
	
	//create invalid node with proper netid
	shared_ptr<treeNode> invalidNode = make_shared<treeNode>(invalidId, -1) ;

	// invalid's children become the nodes children
	invalidNode->setLeftChildPtr(node->getLeftChildPtr());
	invalidNode->setRightChildPtr(node->getRightChildPtr());

	//make invalid node and the new node children of the node we are in
	if (invalidId.back() == '0') {
		node->setLeftChildPtr(invalidNode);
		node->setRightChildPtr(make_shared<treeNode>(netId, port));
	}
	else {
		node->setRightChildPtr(invalidNode);
		node->setLeftChildPtr(make_shared<treeNode>(netId, port));
	}
	return true;
}

int prefixTree::findPortHelper(shared_ptr<treeNode> node, std::string ipaddr) const {
	string rt = "5";
	string lt = "5";

	if(node->getRightChildPtr() != nullptr)  rt = node->getRightChildPtr()->getNetId();
	if (node->getLeftChildPtr() != nullptr)	lt = node->getRightChildPtr()->getNetId();

	//if you start and neither match then return -1
	if (node == rootPtr) {
		if ((rt != ipaddr.substr(0, rt.length())) && (lt != ipaddr.substr(0, lt.length()))) {
			return -1;
		}
	}
	


	// checks if either subtree can be moved into
	//if not then you have found the longest prefix match, so return the port
	if(node->getLeftChildPtr() != nullptr) {
		if ((lt == ipaddr.substr(0, lt.length())) && (node->getLeftChildPtr() != nullptr)) {
			return findPortHelper(node->getLeftChildPtr(), ipaddr);
		}
	}
	else if(node->getRightChildPtr() != nullptr) {
		if ((rt == ipaddr.substr(0, rt.length())) && (node->getRightChildPtr() != nullptr)) {
			return findPortHelper(node->getRightChildPtr(), ipaddr);
		}
	}
	else return node->getPort();



}

int prefixTree::findPort(std::string ipaddr) const
{
	if (rootPtr == nullptr) return -1;
	//begin at root pointer (top of tree)
	std::shared_ptr<treeNode> curr = rootPtr;

	//once the pointer hits a leaf, it has gone as far as possible 
	//(found the closest prefix). Or, the tree is empty. 

	
	return findPortHelper(curr, ipaddr);
	
}



bool prefixTree::remove(const std::string prefix)
{
	
	if (rootPtr == nullptr) return false;
	//begin at root pointer (top of tree)
	std::shared_ptr<treeNode> curr = rootPtr;

	
	return removeHelper(curr, prefix);
}

bool prefixTree::removeHelper(std::shared_ptr<treeNode> node, const std::string ipaddr) {

	string rt = "5";
	string lt = "5";
	return true;
	if (node->getRightChildPtr() != nullptr)  rt = node->getRightChildPtr()->getNetId();
	if (node->getLeftChildPtr() != nullptr)	lt = node->getRightChildPtr()->getNetId();

	//if you start and neither match then return -1
	if (node == rootPtr) {
		if ((rt != ipaddr.substr(0, rt.length())) && (lt != ipaddr.substr(0, lt.length()))) {
			return false;
		}
	}



	// checks if either subtree can be moved into
	//if not then you have found the longest prefix match, so return the port
	if (node->getLeftChildPtr() != nullptr) {
		if ((lt == ipaddr.substr(0, lt.length())) && (node->getLeftChildPtr() != nullptr)) {
			return removeHelper(node->getLeftChildPtr(), ipaddr);
		}
	}
	else if (node->getRightChildPtr() != nullptr) {
		if ((rt == ipaddr.substr(0, rt.length())) && (node->getRightChildPtr() != nullptr)) {
			return removeHelper(node->getRightChildPtr(), ipaddr);
		}
	}
	else return true;
}

void prefixTree::clearTreeHelper(std::shared_ptr<treeNode> subTreePtr) const {
	//if there are stuff left in the tree
	if (subTreePtr != nullptr) {
		//clear
		clearTreeHelper(subTreePtr->getLeftChildPtr());
		clearTreeHelper(subTreePtr->getRightChildPtr());
		//reset for next call
		subTreePtr.reset();
	}
}


void prefixTree::clear()
{
	clearTreeHelper(rootPtr);
	rootPtr = nullptr;
}



std::string prefixTree::postorderTraverseHelper(std::string visit(std::shared_ptr<treeNode> NodePtr), std::shared_ptr<treeNode> treePtr) const
{
	if (treePtr == nullptr) {
		// Base case: an empty subtree, return an empty string
		return "";
	}
	else {
		// Recursive case: concatenate the results of postorder traversal on left and right subtrees
		std::string result = "";
		result += postorderTraverseHelper(visit, treePtr->getLeftChildPtr());
		result += postorderTraverseHelper(visit, treePtr->getRightChildPtr());

		// Append the result of processing the current node using the visit function
		result += visit(treePtr);

		return result;
	}
}



RoutingEntry  prefixTree::getRoutingEntry(const std::string netId) const 
{

	return RoutingEntry{ "", -1 };
}






std::string prefixTree::postorderTraverse(std::string visit(std::shared_ptr<treeNode> NodePtr)) const {

	return postorderTraverseHelper(visit, rootPtr);
}



int prefixTree::getNumberOfNodesHelper(std::shared_ptr<treeNode> subTreePtr) const
{
	if (subTreePtr == nullptr) {
		// Base case: an empty subtree has zero nodes
		return 0;
	}
	else {
		// Recursive case: number of nodes is 1 plus the sum of nodes in the left and right subtrees
		return 1 + getNumberOfNodesHelper(subTreePtr->getLeftChildPtr()) +
			getNumberOfNodesHelper(subTreePtr->getRightChildPtr());
	}
}

int prefixTree::getNumberOfNodes() const
{
	return getNumberOfNodesHelper(rootPtr);
}

int prefixTree::getHeightHelper(std::shared_ptr<treeNode> subTreePtr) const
{
	if (subTreePtr == nullptr) {
		// Base case: height of an empty tree is 0
		return 0;
	}
	else {
		// Recursive case: height is 1 plus the maximum height of the left and right subtrees
		int leftHeight = getHeightHelper(subTreePtr->getLeftChildPtr());
		int rightHeight = getHeightHelper(subTreePtr->getRightChildPtr());
		return std::max(leftHeight, rightHeight) + 1;
	}
}


int prefixTree::getHeight() const
{
	int height = getHeightHelper(rootPtr);
	return height;
}






bool prefixTree::isEmpty() const {
	return (rootPtr==nullptr );
}







/*std::shared_ptr<treeNode> current = rootPtr;
	std::shared_ptr<treeNode> newNode; //will be the new node
	newNode->setNetId(netid);
	newNode->setPort(port);
	

	
	//BASECASE
	//tree with no subtree (left or right tree empty)
	if (rootPtr->getLeftChildPtr() ==nullptr ) {
		//check if id starts with 0, if so, set left child = new node
		if (netid.substr(0, 1) == "0") {
			current->setLeftChildPtr(newNode);
		}

	}
	else if (rootPtr->getRightChildPtr() == nullptr) {
		//check if id starts with 1, if so, set right child = new node
		if (netid.substr(0, 1) == "1") {
			current->setRightChildPtr(newNode);
		}
	}

	//traverse tree to find most identical prefix
	//if no prefix is found and at leaf node, add
	//if no prefix found and stuck, record position to make new tree.
	while (current->getNetId() != netid) {//*** bad logic
		std::shared_ptr<treeNode> parent = current; //will hold the parent node to the current node
		string leftchildstr = current->getLeftChildPtr()->getNetId(); //grabs theleft child netID
		string rightchildstr = current->getRightChildPtr()->getNetId(); //grabs theleft child netID

		//checks if the string is equal
		
		if (netid.substr(0,leftchildstr.length()) == leftchildstr) {
			
			//check if netids are equal, if so, replace the port
			if (current->getNetId() == netid) {
				current->setPort(port);
				return true;
			}



			current = current->getLeftChildPtr();
			if( (current->getLeftChildPtr()->isLeaf()) && true  ){}//checks if therer is a leaf and ofm
		}
		else if (netid.substr(0, rightchildstr.length()) == rightchildstr) {//check right
			current = current->getRightChildPtr();
		}

		//check if at leaf
			}
	//if at leaf then insert

	
	return true;
	
*/