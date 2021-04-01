/*
Summer 2017 - Assignment2 of Project 1 - CS261 - Noon Pokaratsiri
*/

#include "player.h"
#include <iostream>
#include <cstring>

using namespace std;

Player::Player() : name{new char [strlen("No Name") + 1]}
{
	strcpy(this->name, "No Name");
}

Player::Player(char const * const name) : 
	name{new char [strlen(name) + 1]}
{
	strcpy(this->name, name);
}

Player::~Player()
{
//	cout << "Calling ~Player() " << endl;
	delete [] name;
}

// definition for the copy constructor
// there should not be a Player(anotherPlayer) copy in this program
Player::Player(const Player& aPlayer) :
	name{new char[strlen(aPlayer.name) + 1]},
	hand{aPlayer.hand}
{
	strcpy(this->name, aPlayer.name);
}

// definition for the assignment operator=
// define this function when needed
Player& Player:: operator=(const Player& aPlayer)
{
	if (this == &aPlayer)
		return *this;
	else
	{
		if (this->name)
			delete [] name;
		this->name = new char[strlen(aPlayer.getPlayersName()) + 1];
		strcpy(this->name, aPlayer.getPlayersName());
		
		this->hand = aPlayer.getHand();
	}
	return *this;
}

// drawBone takes info of aBone updated by removing/poping the top-most bone from
// the deck then add this to Hand class and returns true
bool Player::drawBone(ChickenYard& deck)
{
	Bone*	aBone;

	cout << "Drawing a bone from deck..." << endl;
	if (!deck.dealBone(aBone))
		return false;
//	cout << "Adding the bone to hand..." << endl;
	hand.addBone(aBone);

	return true;
}

// if bone played could not be played, add back to hand
bool Player::addBone(Bone* returnedBone)
{
	cout << "Returning " << returnedBone << " to hand!!!" << endl;
	if (hand.addBone(returnedBone))
		return true;
	return false;
}

bool Player::playBone(Bone*& playedBone, const int& keyNum)
{
	// if aBone containing keyNum is found in hand, remove aBone from Hand
	// if aBone is not found
	return hand.removeBone(playedBone, keyNum) ? true : false;
}

bool Player::playHighestDouble(Bone*& playedBone)
{
	if (!hand.removeExactBone(playedBone))
		return false;
	
	return true;
}

// player's TotalScore is the sum of bones in hand
int	 Player::getTotalScore() const
{
	return hand.getTotalScore();
}

// currently not in use; getHigestDouble is used intead
bool Player::hasDouble(Bone*& highestDouble) const
{
	cout << name << "'s ";
	return hand.containsDouble(highestDouble);
}

Bone* Player::getHighestDouble() const
{
	Bone* 	highestDouble{nullptr};

	cout << "Returning " << name << "'s Highest Double. ";
	
	hand.containsDouble(highestDouble);

	return highestDouble;	
}

char* Player::getPlayersName() const
{
	return name;
}

Hand Player::getHand() const
{
	return hand;
}

bool Player::hasBones() const
{
	return !hand.isEmpty();
}

void Player::displayPlayersHand() const
{
	cout << name << "'s Current Hand: " << endl;
	cout << hand << endl;
	cout << name << "'s Current Hand Contains " << hand.getSize() << " bones. " << endl;
	cout << name << "'s Current Hand Total Score: " << getTotalScore() << endl << endl;
}
