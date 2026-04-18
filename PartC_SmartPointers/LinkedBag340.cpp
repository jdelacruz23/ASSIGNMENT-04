//	LinkedBag340.cpp
//	Created by: CSC340

#include <cstdlib> // for rand
#include "LinkedBag.h"
#include "Node.h"


/*
* 1.
removeSecondNode340 would:
- Check first node if it exists, if it does then go to second node then delete it
- Reconnect nodes after deletion
- If getNext() == nullptr meaning "second pointer is empty" then return false
- Reduce itemCount by 1 for getSize
- If no nodes exists; return false otherwise true
*/
template<typename ItemType>
bool LinkedBag<ItemType>::removeSecondNode340() {
    //base case 
    if (headPtr == nullptr || headPtr->getNext() == nullptr) {
        return false;
    }

    Node<ItemType>* nodeToDelete = headPtr->getNext();
    headPtr->setNext(nodeToDelete->getNext());
    nodeToDelete->setNext(nullptr);
    delete nodeToDelete;
    itemCount--;
    return true;
}

/*
* 2.
addEnd340 would: 
First: check the if the bag is empty and if yes, then make that the FIRST node and make it headPtr
- If there is already items inside the bag then iterate through to reach last node and add it there 
then update pointers
- increase itemCount by 1 for getSize
- return true if valid otherwise false
*/
template<typename ItemType>
bool LinkedBag<ItemType>::addEnd340(const ItemType& newEntry) {
    Node<ItemType>* newNodePtr = new Node<ItemType>(newEntry);
    if (headPtr == nullptr) {
        headPtr = newNodePtr;
    }else {
        Node<ItemType>* curPtr = headPtr;
        while (curPtr->getNext() != nullptr) {
            curPtr = curPtr->getNext();
        }
        curPtr->setNext(newNodePtr);
    }
    itemCount++;
    return true;
}

/*
* 3.
getCurrentSize340Iterative would:
- ITERATIVELY traverse the bag and then returns a count of the bag size when it reaches nullptr
- returns bagSizeIterative value
*/
template<typename ItemType>
int LinkedBag<ItemType>::getCurrentSize340Iterative() const {
    int bagSizeIterative = 0;
    Node<ItemType>* curPtr = headPtr; //set curPtr at the head.
    while (curPtr != nullptr) {
        curPtr = curPtr->getNext();
        bagSizeIterative++;
    }
    return bagSizeIterative;
}

/*
* 4.
getCurrentSize340RecursiveHelper would:
- Help getCurrentSize340Recursive function
- Uses curPtr to traverse until nullptr is found
- Calls itself until nullptr
*/
template<typename ItemType>
int LinkedBag<ItemType>::getCurrentSize340RecursiveHelper(Node<ItemType>* curPtr) const {
    // base case
    if (curPtr == nullptr) { 
        return 0;
    }
    // 1 + node(s) found
    return 1 + getCurrentSize340RecursiveHelper(curPtr->getNext());
}

/*
* 4.
getCurrentSize340Recursive would: 
- start the recursive counting
- uses headPtr
- calls getCurrentSize340RecursiveHelper
*/
template<typename ItemType>
int LinkedBag<ItemType>::getCurrentSize340Recursive() const {
    return getCurrentSize340RecursiveHelper(headPtr);
}

/*
* 5.
getCurrentSize340RecursiveNoHelper would:
- Traverse through the bag recursively WITHOUT any helper functions and returns the size.
- base case would be bag is 0
- Deletes nodes until empty
*/
template<typename ItemType>
int LinkedBag<ItemType>::getCurrentSize340RecursiveNoHelper() const {
    if (headPtr == nullptr) {
        return 0;
    }
    // can't do return 1 + helper because no helper
    // creates a smallerBag object basically same as helper above but just within
    LinkedBag<ItemType> smallerBag(*this); //copying current bag
    Node<ItemType>* nodeToDelete = smallerBag.headPtr;
    smallerBag.headPtr = smallerBag.headPtr->getNext();
    nodeToDelete->setNext(nullptr);
    delete nodeToDelete;
    return 1 + smallerBag.getCurrentSize340RecursiveNoHelper();
}

/*
* 6.
getFrequencyOf340RecursiveHelper and getFrequencyOf340Recursive would:
- Get the frequency of the node that matches "target"
getFrequencyOf340RecursiveHelper would:
- Check if curPtr == target then count++;
- If bag is traversed and nothing matches return 0
*/
template<typename ItemType>
int LinkedBag<ItemType>::getFrequencyOf340RecursiveHelper(Node<ItemType>* curPtr, const ItemType& target) const {
    // base case
    if (curPtr == nullptr) {
        return 0;
    }
    if (curPtr->getItem() == target) {
        return 1 + getFrequencyOf340RecursiveHelper(curPtr->getNext(), target);
    }
    return getFrequencyOf340RecursiveHelper(curPtr->getNext(), target);
}

/*
* 6.
- starts the recursive frequency counting
- call the helper with headPtr
*/
template<typename ItemType>
int LinkedBag<ItemType>::getFrequencyOf340Recursive(const ItemType& target) const {
    return getFrequencyOf340RecursiveHelper(headPtr, target);
}

/*
getFrequencyOf340RecursiveNoHelper would:
- Get the frequency of the node that matches "target" with no helper function
- returns the frequency of nodes
*/
template<typename ItemType>
int LinkedBag<ItemType>::getFrequencyOf340RecursiveNoHelper(const ItemType& target) const {
    if (headPtr == nullptr) {
        return 0;
    }
    LinkedBag<ItemType> smallerBag(*this); //copying current bag
    //same behavior as the one above
    Node<ItemType>* nodeToDelete = smallerBag.headPtr;
    smallerBag.headPtr = smallerBag.headPtr->getNext();
    nodeToDelete->setNext(nullptr);
    delete nodeToDelete;
    smallerBag.itemCount--;
    if (headPtr->getItem() == target) {
        return 1 + smallerBag.getFrequencyOf340RecursiveNoHelper(target);
    }
    return smallerBag.getFrequencyOf340RecursiveNoHelper(target);
}

 /*
 removeRandom340 would:
- delete a random node based on a formula
- re-assigns pointers to avoid memory leaks
- returns the removedItem
*/
template<typename ItemType>
ItemType LinkedBag<ItemType>::removeRandom340() {
    int randomIndex = rand() % itemCount;
    Node<ItemType>* nodeToDelete = headPtr;
    Node<ItemType>* prevPtr = nullptr;
    // base case
    if (headPtr == nullptr || itemCount == 0) {
        return ItemType();
    }
    for (int i = 0; i < randomIndex; i++) {
        prevPtr = nodeToDelete;
        nodeToDelete = nodeToDelete->getNext();
    }
	// Save the item from the node being removed, then update links:
	// if deleting the head, move headPtr forward; otherwise, link the previous node to the next node.
    ItemType removedItem = nodeToDelete->getItem();

    if (prevPtr == nullptr) {
        headPtr = headPtr->getNext();
    }else {
        prevPtr->setNext(nodeToDelete->getNext());
    }

    nodeToDelete->setNext(nullptr);
    delete nodeToDelete;
    itemCount--;

    return removedItem;
}

