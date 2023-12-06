

#include "treeNode.h"



treeNode::treeNode() {
	rtEntry.netId = "";
	rtEntry.port = -1;
	leftChildPtr = nullptr;
	rightChildPtr = nullptr;
}

treeNode::treeNode(const std::string netId_in,  int port_in) {
	rtEntry.netId = netId_in;
	rtEntry.port = port_in;
	leftChildPtr = nullptr;
	rightChildPtr = nullptr;
}

void treeNode::setNetId(const std::string netId_in) {
	rtEntry.netId = netId_in;
	}

void treeNode::setPort(const int port_in) {
	rtEntry.port = port_in;
	
}



std::string treeNode::getNetId() const {
	
	return rtEntry.netId;
}
 int treeNode::getPort() const {
	 return rtEntry.port;
	
}
 RoutingEntry treeNode::getRoutingEntry() const
 {
	  return rtEntry;
 }
bool treeNode::isLeaf() const {
	
	return (leftChildPtr == nullptr  &&  rightChildPtr == nullptr);

}

std::shared_ptr<treeNode> treeNode::getLeftChildPtr() const {

	return leftChildPtr;
	
}
std::shared_ptr<treeNode>  treeNode::getRightChildPtr() const {
	return rightChildPtr;
}

void treeNode::setLeftChildPtr(std::shared_ptr<treeNode> leftPtr) {
	leftChildPtr = leftPtr;
}

void treeNode::setRightChildPtr(std::shared_ptr<treeNode> rightPtr) {
	rightChildPtr = rightPtr;

}