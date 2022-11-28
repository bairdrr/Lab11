// LinkedList.cpp : Defines the exported functions for the DLL application.
//

#include "LinkedList.h"
#include <iostream>
#include <string>
#include <cmath>
#include <iomanip>
#include <sstream>

using namespace std;

ILinkedList::ILinkedList() : m_count(0)
{

}

/** Returns true if list is empty otherwise false */
bool ILinkedList::isEmpty() const
{
	if (m_count == 0){
		return true;
	}
	
	else {
	return false;
	};
}

Node::Node() : m_value(-1), m_next(nullptr)
{

}
Node::Node(int val) : m_value(val), m_next(nullptr)
{

}
Node::Node(int val, Node * nextNode) : m_value(val), m_next(nextNode)
{

}
void Node::setItem(const int& val)
{
	m_value = val;
}
void Node::setNext(Node* nextNodePtr)
{
	m_next = nextNodePtr;
}
int Node::getItem() const
{
	return m_value;
}
Node * Node::getNext() const
{
	return m_next;
}
Node::~Node()
{
	
	std::cout << "Deleting node with value " << m_value << std::endl;
}

PointerBasedLinkedList::PointerBasedLinkedList() : ILinkedList(), m_head(nullptr)
{

}

/** Adds a value to the LinkedList.  Return true if able to, otherwise false */
bool PointerBasedLinkedList::add(int val)
{
	Node* currPtr = m_head;
	Node* NewNodePtr = new Node;

	if (isEmpty() == true){
		m_head = new Node;
		m_tail = nullptr;
		
		NewNodePtr->setItem(val);
		m_head->setNext(NewNodePtr);
		NewNodePtr->setNext(m_tail);
		m_count++;

		return true;
	}	
	else{
		while (currPtr->getNext() != m_tail)
		{
			currPtr = currPtr->getNext();
		}
			NewNodePtr->setItem(val);
			currPtr->setNext(NewNodePtr);
			NewNodePtr->setNext(m_tail);			
			m_count++;
			return true;
		}
}
/** Remove a value to the LinkedList.  Return true if able to, otherwise false.
Will only remove one entry if there are multiple entries with the same value */
bool PointerBasedLinkedList::remove(int val)
{
	Node* currPtr = nullptr;
	Node* prevPtr = nullptr;
	if (m_head != nullptr) {
		currPtr = m_head->getNext();
		prevPtr = m_head;
	}
	bool found = false;
	int i = 0;

	if(isEmpty()==true){
		return found;
	}
	else{
		while (!found && currPtr != nullptr)
		{
			if (val == currPtr->getItem())
			{
				found = true;
				for (int j = 0; j < i; j++)
				{
					prevPtr = prevPtr->getNext();
				}
				prevPtr->setNext(currPtr->getNext());
				currPtr->setNext(nullptr);
				delete currPtr;
				currPtr = nullptr;
				m_count--;
				return found;
			}
			else {
				currPtr = currPtr->getNext();
				i++; 
			}
		}		
	}
		return found;	
}

/** Remove  all elements from LinkedList */
void PointerBasedLinkedList::clear()
{	
	Node* currPtr;
	Node* otherPtr;
	if (isEmpty()==false){
		currPtr = m_head->getNext();
	 	while (currPtr != nullptr)
		{	
			otherPtr = currPtr;
			currPtr = currPtr->getNext();
			otherPtr->setNext(nullptr);
			delete otherPtr;
		}
	}
	m_count = 0;
}
PointerBasedLinkedList::~PointerBasedLinkedList()
{
	clear();
}

std::string PointerBasedLinkedList::toString() const
{
	Node* currPtr;
	Node* NewNodePtr = new Node;
	string str = "";
	if (m_head != nullptr){
		currPtr = m_head->getNext();
		
	 	while (currPtr != nullptr)
		{
			str += to_string(currPtr->getItem()) + " ";
			currPtr = currPtr->getNext();
		}		
		str.resize(str.length()-1);	
	}
	return str;
}

ArrayBasedLinkedList::ArrayBasedLinkedList() : ILinkedList()
{
   	m_count = 0;
	// you got it for free :)
}

bool ArrayBasedLinkedList::add(int val)
{
	int length = end(m_values) - begin(m_values);
	if (m_count < length) {
		m_values[m_count] = val;
		m_count++;
		return true;
	}
	else{
		return false;
	}
}
bool ArrayBasedLinkedList::remove(int val)
{
	bool found = false;
	int counter = 0;
	int length = end(m_values) - begin(m_values);
	while (!found && counter < length) {
		if (m_values[counter] == val) {
			found = true;				
		}
		else{counter++;}
	}	
	if (!found)
		return found;
	for (int i = counter; i < length - 1; i++)
	{
		m_values[i] = m_values[i + 1];
	}
	m_values[length- 1] = 0;
	m_count--;
	return found;

}
void ArrayBasedLinkedList::clear()
{
	int length = end(m_values) - begin(m_values);
	for (int i = 0; i < length; i++)
	{
		m_values[i] = 0;
	}
	m_count = 0;
}
ArrayBasedLinkedList::~ArrayBasedLinkedList()
{
	clear();
}

std::string ArrayBasedLinkedList::toString() const
{
	string str = "";
	if(m_count == 0){
		return str;
	}
	for (int i = 0; i < m_count; i++)
	{
		str += to_string(m_values[i]) + " ";
	}
	str.resize(str.length()-1);

	return str;
}
