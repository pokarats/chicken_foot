/*
Summer 2017 - Assignment2 of Project 1 - CS261 - Noon Pokaratsiri
*/

#ifndef PLAYER_H
#define PLAYER_H

#include "hand.h"
#include "chickenYard.h"

class Player

{
public:
	Player();
	Player(char const * const name);
	~Player();
	bool 	drawBone(ChickenYard& deck);
	bool	addBone(Bone* returnedBone);
	bool 	playBone(Bone*& playedBone, const int& keyNum);
	bool 	playHighestDouble(Bone*& playedBone);
	int	 	getTotalScore() const;
	void 	displayPlayersHand() const;	
	Bone* 	getHighestDouble() const;
	bool 	hasDouble(Bone*& highestDouble) const;
	char* 	getPlayersName() const;
	bool	hasBones() const;
	Hand	getHand() const;

	Player(const Player& aPlayer);
	Player& operator=(const Player& aPlayer);

private:
	char*	name;
	Hand	hand;

// private functions:
	
	// dummy copy constructor and operator = overload for unintended future use 

};
#endif
