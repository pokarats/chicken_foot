/*
CS 261 - Summer 2017 - Assignment 2 of Project 1 - Noon Pokaratsiri
*/

#include <iostream>
#include "playedList.h"

using namespace std;

PlayedList::PlayedList() :
	head{nullptr},
	length{0}
{
}

PlayedList::~PlayedList()
{
//	cout << "Calling ~PlayedList()" << endl;
	deleteNode(head);
}



PlayedList::Node::Node() : // initialization list for Node without parameters
	nodeData{nullptr},
	chickenFoot{false},
	freeEnd{ChickenYard::MIN_NUM - 1},
	next1{nullptr},
	next2{nullptr},
	next3{nullptr}
{
}

PlayedList::Node::Node(Bone* aBonePtr, int aFreeEnd) :// initialization list for Node with Bone* as parameter
	nodeData{aBonePtr},
	chickenFoot{false},
	freeEnd{aFreeEnd},
	next1{nullptr},
	next2{nullptr},
	next3{nullptr}
{
}

// copy constructor for struct Node 
PlayedList::Node::Node(const Node& sNode) :
	nodeData{new Bone(sNode.nodeData->getNum1(), sNode.nodeData->getNum2())},
	chickenFoot{sNode.chickenFoot},
	freeEnd{sNode.freeEnd},
	next1{sNode.next1},
	next2{sNode.next2},
	next3{sNode.next3}
{
}

// assignment operator for struct Node, overload
PlayedList::Node& PlayedList::Node::operator=(const Node& node2)
{
	if (this == &node2)
		return *this;
	else
	{
		this->nodeData = new Bone(node2.nodeData->getNum1(), node2.nodeData->getNum2());
		this->chickenFoot = node2.chickenFoot;
		this->freeEnd = node2.freeEnd;
		this->next1 = node2.next1;
		this->next2 = node2.next2;
		this->next3 = node2.next3;
	}
	return *this;
}

PlayedList::Node::~Node()		
{
//	cout << "Trying to delete node" << endl;
	if (nodeData)
	{
//		cout << "Deleting nodeData...(aBone)" << endl;
		delete nodeData;
		nodeData = nullptr;
	}
}

// recursively traverse the list to deallocate each node 
// in post order
// private
void PlayedList::deleteNode(Node*& aHead)
{
	Node* curr{aHead};
	
//	cout << length << " Nodes." << endl;
	if (curr)
	{
		deleteNode(curr->next3);
		deleteNode(curr->next2);
		deleteNode(curr->next1);
		delete curr;
		curr = nullptr;
		length--;
//		cout << length << " left after deleting." << endl;
	}
}

// public add, call recursive add
bool PlayedList::add(Bone* playedBone, const int& newFree, const int& keyNum)
{
	// adding first node in the list
	if (head == nullptr)
	{
		Node*	newNode{makeNewNode(playedBone, newFree)};

		head = newNode;
		length++;
		return true;
	}
	else
	{
	// subsequent nodes
		if (recursiveAdd(head, playedBone, newFree, keyNum))
		{
			length++;
			return true;
		}
		else
			// could not add, i.e. keyNum was not found in any freeEnds
			return false;
	}
}

// private add, starting at head, traverse through next1, next2, and next3
// to find a match for key with the existing freeEnd,
bool PlayedList::recursiveAdd(Node* aHead, Bone* playedBone, const int& newFree, const int& key)
{
	if (aHead)
	{
		if (aHead->freeEnd == key)
		{
			Node* newNode{makeNewNode(playedBone, newFree)};

			if (aHead->chickenFoot)
			{
				cout << "Adding to a double/Chicken Foot..." << endl;
				if (aHead->next1 == nullptr)
					aHead->next1 = newNode;
				else if (aHead->next2 == nullptr)
					aHead->next2 = newNode;
				else // next3 is nullptr
				{
					aHead->next3 = newNode;
					aHead->freeEnd = (ChickenYard::MIN_NUM - 1);
					aHead->chickenFoot = false;
					// after chickenFoot is filled, so won't priority adding to this.
					cout << "Chicken Foot is now filled. " << endl;
				}
			}	
			else
			{
				if (aHead->next1 == nullptr)
				{
					cout << "Adding to a regular free end..." << endl;
					aHead->next1 = newNode;
					aHead->freeEnd = (ChickenYard::MIN_NUM - 1);
				}
				else
				{
					cout << "Something is wrong..." << endl;
					delete newNode;
					newNode = nullptr;
					return false;
				}
			}
			return true;
		}
		else if (recursiveAdd(aHead->next1, playedBone, newFree, key))
			return true;
		else if (recursiveAdd(aHead->next2, playedBone, newFree, key))
			return true;
		else if (recursiveAdd(aHead->next3, playedBone, newFree, key))
			return true;
		else
			return false;
	}
	return false;
}

PlayedList::Node* PlayedList::makeNewNode(Bone* playedBone, const int& newFree)
{
	PlayedList::Node*	aNode{new Node(playedBone, newFree)};
		
	if (aNode->nodeData->isDouble())
		aNode->chickenFoot = true;
	
	return aNode;
}

// private, called by public hasChickenFoot()
bool PlayedList::findChickenFoot(Node* aHead) const
{
	if (aHead)
	{
		if (aHead->chickenFoot)
			return true;
		else if (findChickenFoot(aHead->next1))
			return true;
		else if (findChickenFoot(aHead->next2))
			return true;
		else if (findChickenFoot(aHead->next3))
			return true;
		else
			return false;
	}
	else
		return false;
}

bool PlayedList::isEmpty() const
{
	return (head) ? false : true;
}

bool PlayedList::hasChickenFoot() const
{
	if (findChickenFoot(head))
		return true;
	else
		return false;
}

// public access display, calls private display to recursively display the list
void PlayedList::display() const
{
	displayList(head, 0);
	cout << "\nThis side contains: " << length << " bones. " << endl << endl;
}

// printing spacers, this is so that the different brances of any chickenFoot
// can be visually followed and the columns will lined up
void PlayedList::printLevelSpacers(ostream& out, int spacers) const
{
	int i{0};

	for (i = 0; i < spacers; i++)
	{
		// space is 11 char long, based on cout in bone class, adjust as desired
		out << "           ";
	}

}
// private display
// this function and printLevelSpacers are adapted from display functions
// in sample code bst.cpp from Trigaboff, M's Spring 2017 CS260 Class.
void PlayedList::displayList(Node* aHead, int level) const
{
	if (aHead)
	{
		printLevelSpacers(cout, level -1);
		if (level)
			cout << "|->";
		cout << aHead->nodeData << endl;
		if (aHead->next1 || aHead->next2 || aHead->next3)
		{
			if (aHead->next1)
				displayList(aHead->next1, level + 1);
			else
			{
				printLevelSpacers(cout, level);
				cout << "|*" << endl;
			}
			if (aHead->next2)
				displayList(aHead->next2, level + 1);
			else
			{
				printLevelSpacers(cout, level);
				cout << "|**" << endl;
			}
			if (aHead->next3)
				displayList(aHead->next3, level + 1);
			else
			{
				printLevelSpacers(cout, level);
				cout << "|***" << endl;
			}
		}
	}
}

// overload operator<< to cout PlayedList
ostream& operator<<(ostream& out, PlayedList* aPlayedList)
{

	aPlayedList->display();

	return out;
}

