/*
Summer 2017 - Assignment2 of Project 1 - CS261 - Noon Pokaratsiri
*/

#ifndef GAME_H
#define	GAME_H

#include "bone.h"
#include "chickenYard.h"
#include "player.h"
#include "field.h"
#include "freeList.h"

class Game
{
public:
	static const char	MY_NAME[];	// print programmer'name
	static const int	INIT_BONES;	// number of Bones players are dealt initially
	static const int	NUM_PLAYERS; // numer of players allowed

	Game();			// constructor
	~Game();		// destructor

	void initDeck();		// start game by shuffling the deck
	void initPlayers(); 	// deal cards to player1 and player2
	void startGame(); 		// start playing the game
	
private:
	Player*			player1;
	Player*			player2;
	ChickenYard*	deck;
	Field*			field;

// private fucntions:
	void 	showDeckStatus();
	void 	showHandStatus();
	void	controlGame();
	void	playGame(Player* aPlayer);
	void 	endGame();
	void 	swapPlayer(Player*& aPlayer);
	Player* startPlayer();

	// dummy copy constructor and operator = overload for unintended future use 
	Game(const Game& aGame);
	Game& operator=(const Game& aGame);

};
#endif
