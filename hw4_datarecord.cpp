#include "hw4_datarecord.h"
#include <string>

std::string visitNode(std::shared_ptr<treeNode> nodePtr) { 

    if (nodePtr) {
             return nodePtr->getNetId() + ":" + std::to_string(nodePtr->getPort()) + "\n";
    }
    else {
        return "";
    }

	
}

std::string visitRoutingEntry(std::shared_ptr<treeNode> nodePtr) {
    if (nodePtr) {
           RoutingEntry entry = nodePtr->getRoutingEntry();
        if (entry.port == -1)
            return "";
        else
            return entry.netId + ":" + std::to_string(entry.port) + "\n";
    }
    else {
        return "";
    }

}