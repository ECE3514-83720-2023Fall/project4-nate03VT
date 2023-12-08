
#define CATCH_CONFIG_MAIN			// this line tells Catch to provide a main() function
#define CATCH_CONFIG_COLOUR_NONE


#include "catch.hpp"
#include "prefixTree.h"
#include "treeNode.h"
#include "hw4_datarecord.h"

TEST_CASE("Test Creating an Empty Tree", "[constructor]") {
	
	


}

TEST_CASE("Testing tree nodes") {



	treeNode myNode0;
	myNode0.setNetId("");
	myNode0.setPort(1);
	CHECK(myNode0.getNetId() == "");
	CHECK(myNode0.getPort() == 1);


	treeNode  myNode = treeNode("0110", 5);
	CHECK(myNode.getNetId() == "0110");
	CHECK(myNode.getPort() == 5);


	std::shared_ptr<treeNode> nodePtr1 = std::make_shared<treeNode>("0101", 3);

	CHECK(nodePtr1->getNetId() == "0101");
	CHECK(nodePtr1->getPort() == 3);


	std::shared_ptr<treeNode> nodePtr2 = std::make_shared<treeNode>("010", -1);


	nodePtr2->setNetId("01000");
	nodePtr2->setPort(-79);
	CHECK(nodePtr2->getNetId() == "01000");
	CHECK(nodePtr2->getPort() == -79);



	CHECK(myNode.isLeaf() == true);

	myNode.setLeftChildPtr(nodePtr1);

	CHECK(myNode.isLeaf() == false);
	myNode.setRightChildPtr(nodePtr2);
	CHECK(myNode.isLeaf() == false);

	CHECK(nodePtr1 == myNode.getLeftChildPtr());
	CHECK(nodePtr2 == myNode.getRightChildPtr());

	RoutingEntry rtentry = nodePtr2->getRoutingEntry();
	CHECK(rtentry.netId == "01000");
	CHECK(rtentry.port == -79);

	CHECK(visitNode(nodePtr1) == "0101:3\n");
	CHECK(visitRoutingEntry(nodePtr1) == "0101:3\n");

	nodePtr1->setPort(-1);
	CHECK(visitNode(nodePtr1) == "0101:-1\n");
	CHECK(visitRoutingEntry(nodePtr1) == "");

}

TEST_CASE("Testing add") {


	prefixTree myTree;

	REQUIRE(myTree.add("", 0) == true);


	REQUIRE(myTree.isEmpty() == false);
	CHECK(myTree.getHeight() == 1);
	CHECK(myTree.getNumberOfNodes() == 1);

	REQUIRE(myTree.add("011", 2) == true);
	REQUIRE(myTree.add("1", 3) == true);
	REQUIRE(myTree.add("11", 4) == true);
	REQUIRE(myTree.add("111", 5) == true);
	REQUIRE(myTree.add("110", 6) == true);
	REQUIRE(myTree.add("0110", 7) == true);


	CHECK(myTree.getHeight() == 4);
	CHECK(myTree.getNumberOfNodes() == 7);

	std::string str1 = "011:2\n1:3\n:0\n";
	CHECK(str1.compare(myTree.postorderTraverse(visitNode)) == 1);

	REQUIRE(myTree.add("011", 4) == true);
	str1 = "011:4\n1:3\n:0\n";
	CHECK(str1.compare(myTree.postorderTraverse(visitNode)) == 1);

	REQUIRE(myTree.add("0001", 5) == true);
	CHECK(myTree.getHeight() == 4);
	




}

TEST_CASE("Test searching for port number based on IP address", "[search]") {
	using Catch::Matchers::Contains;
	prefixTree myTree1;

	CHECK(myTree1.findPort("01100110011001100110011001100110") == -1);


	REQUIRE(myTree1.add("", 0) == true);
	REQUIRE(myTree1.add("0", 2) == true);
	REQUIRE(myTree1.add("00", 3) == true);
	REQUIRE(myTree1.add("01", 5) == true);
	REQUIRE(myTree1.add("1001", 1) == true);

	CHECK(myTree1.findPort("01100110011001100110011001100110") == -1);
	CHECK(myTree1.findPort("11100110011001100110011001100110") == -1);
	CHECK(myTree1.findPort("10010110011001100110011001100110") == 53);
	CHECK(myTree1.findPort("00100110011001100110011001100110") == -1);



}