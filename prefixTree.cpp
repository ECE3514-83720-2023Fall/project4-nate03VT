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
	std::shared_ptr<treeNode> current = rootPtr;
	std::shared_ptr<treeNode> newNode = nullptr; //will be the new node
	newNode->setNetId(netid);
	newNode->setPort(port);

	//tree empty (left or right tree empty)
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
	while (current != nullptr) {

		//checks the digit
		if (rootPtr->getLeftChildPtr()) {

		}


	}


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



int prefixTree::getHeightHelper(std::shared_ptr<treeNode> subTreePtr) const
{
	return -1;
}

int prefixTree::getNumberOfNodesHelper(std::shared_ptr<treeNode> subTreePtr) const
{
	return -1;
}





bool prefixTree::isEmpty() const {
	return true;
}

int prefixTree::getHeight() const
{
	return 0;
}

int prefixTree::getNumberOfNodes() const
{
	return 0;
}


