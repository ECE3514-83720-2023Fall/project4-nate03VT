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
	std::ifstream file(filename);
	if (!file.is_open()) {
		std::cout << "Error, unable to open file: " << filename << std::endl;
	}
	else {

		//read file

	}

	file.close();
}



prefixTree::~prefixTree()
{
	//resets tree and deallocates all the trees memory
	clear();
}






bool prefixTree::add(const std::string netid, const int port) {
	
	//if empty create a new tree from root node

	if (rootPtr == nullptr) {
		rootPtr = make_shared<treeNode>("", -1);
	}

	if (netid == "") {
		rootPtr->setPort(port);
		return true;
	}
	
	//new node to be inserted
	std::shared_ptr<treeNode> newNode; //will be the new node
	newNode->setNetId(netid);
	newNode->setPort(port);

	return true;


}

bool prefixTree::addHelper(std::shared_ptr<treeNode>& node, const std::string& netId, const int port) {
	
//SECTION 1: handles matching prefix case
	if (node->getNetId() == netId) { //if ip prefix already exists, update port number
		node->setPort(port);
		return true;
	}

//SECTION 2: handles stuck cases
	int leftChildlength = node->getLeftChildPtr()->getNetId().length();
	int rightChildlength = node->getRightChildPtr()->getNetId().length();
		bool leftChildValid = netId.substr(0, leftChildlength) == node->getLeftChildPtr()->getNetId(); 
		bool rightChildValid = netId.substr(0, rightChildlength) == node->getRightChildPtr()->getNetId();
//if neither left nor right child has a matching prefix to traverse into, we are stuck and need to insert a node
		bool stuck = (!leftChildValid && !rightChildValid) || ( (leftChildlength>netId.length()) && (rightChildlength > netId.length()));

		//this section checks if neither child prefix can be moved into
		if ( !leftChildValid && !rightChildValid) { //if child prefix is longer than netid
			return	insertNode(node, netId, port);
		}

//SECTION 3: Handles insertion into leafs


	if (netId < node->getNetId()) { //case where we should move left

	}
}

bool prefixTree::insertNode(std::shared_ptr<treeNode>& node, const std::string& netId, const int port) {

	return true;
}


int prefixTree::findPort(std::string ipaddr) const
{	//begin at root pointer (top of tree)
	std::shared_ptr<treeNode> curr = rootPtr;

	//once the pointer hits a leaf, it has gone as far as possible 
	//(found the closest prefix). Or, the tree is empty. 
	while (curr != nullptr) {
		
	



	}
	return 0;
	
}



bool prefixTree::remove(const std::string prefix)
{
	
	return false;
}

void prefixTree::clear()
{
	
	return;
}


std::string prefixTree::postorderTraverseHelper(std::string visit(std::shared_ptr<treeNode> NodePtr), std::shared_ptr<treeNode> treePtr) const
{
	
	return "";
}



RoutingEntry  prefixTree::getRoutingEntry(const std::string netId) const 
{

	return RoutingEntry{ "", -1 };
}

std::string prefixTree::postorderTraverse(std::string visit(std::shared_ptr<treeNode> NodePtr)) const {
	return "";
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