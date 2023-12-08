////////////////////////////////////////////////////////
// ECE 3514, Project 4, Nathaniel Sawitzki
// File name: hw4_main.cpp 
// Description: runs the tree traversal
// Date: 12/4/2023 


#include"treeNode.h"
#include"prefixTree.h"
#include "hw4_datarecord.h"
#include<iostream>
#include<memory>


void main() {
/*	prefixTree myTree("routing_table.txt");
	
	std::cout << "-------------Tree ----------------------\n\n";
	std::cout << myTree.postorderTraverse(visitNode) << std::endl;
	std::cout << "----------------------------------------------\n\n";
	

	std::cout<<"end of the program \n";
	std::cin.get();
	*/
	prefixTree myTree;

	myTree.add("", 0) ;
	myTree.add("", 1);
	
	myTree.add("0", 5);
	
	myTree.add("01", 6);
	myTree.add("010", 7);
	myTree.add("00", 2);
	myTree.add("1", 3);
	std::string result = myTree.postorderTraverse(visitNode);
	std::cout << result << std::endl;
	
}

