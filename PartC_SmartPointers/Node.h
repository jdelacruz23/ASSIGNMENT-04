//	Node.h
//  Created by Frank M. Carrano and Timothy M. Henry.
//	Updated by Duc Ta
//  Copyright (c) 2017 Pearson Education, Hoboken, New Jersey.

#pragma once
#include <memory>
#include <utility> // for ::move


template<typename ItemType>
class Node {
template<typename>
friend class LinkedBag;
public:
	Node();
	Node(const ItemType&);
	Node(const ItemType&, std::unique_ptr<Node<ItemType>>);
	void setItem(const ItemType&);
	void setNext(std::unique_ptr<Node<ItemType>>);
	ItemType getItem() const;
	Node<ItemType>* getNext() const;

private:
	ItemType        item{};			 // A data item
	std::unique_ptr<Node<ItemType>> next = nullptr; // Pointer to next node
};