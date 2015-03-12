#pragma once
#include "PlayerDatabase.h"
#include <iostream>

class DatabaseTester
{
public:
	DatabaseTester();
	~DatabaseTester();
private:
	// The database.
	PlayerDatabase db;


	// Connect to the database.
	bool testConnect();


	// Disconnect from the database.
	bool testDisconnect();


	// Print all player data from the database.
	void printPlayers();
};
