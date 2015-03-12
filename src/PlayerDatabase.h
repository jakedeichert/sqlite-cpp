#pragma once
#include "Database.h"
#include "StatList.h"

class PlayerDatabase
{
public:
	// Result codes used as return values.
	const enum Error {
		PLAYERDB_SUCCESS,
		PLAYERDB_CANNOT_CONNECT,
		PLAYERDB_CANNOT_DISCONNECT,
		PLAYERDB_CANNOT_UPDATE_VALUE,
		PLAYERDB_WRONG_USERNAME,
		PLAYERDB_WRONG_PASSWORD,
		PLAYERDB_NOT_LOGGED_IN,
		PLAYERDB_ALREADY_LOGGED_IN
	};

	PlayerDatabase();
	~PlayerDatabase();


	// Open a database connection.
	int Connect();


	// Close the database connection.
	int Disconnect();


	// Log in a player.
	// param:username-> The username of the player.
	// param:password-> The password of the player.
	int PlayerLogin(std::string username, std::string password);


	// Log out a player.
	// param:username-> The username of the player.
	int PlayerLogout(std::string username);


	// Get total kills from the database.
	// param:username-> The username of the player.
	int GetTotalKills(std::string username);


	// Get total deaths from the database.
	// param:username-> The username of the player.
	int GetTotalDeaths(std::string username);


	// Get total assists from the database.
	// param:username-> The username of the player.
	int GetTotalAssists(std::string username);


	// Update total kills for the player in the database.
	// param:username-> The username of the player to update.
	// param:increment-> The value to add to the stat.
	int UpdateTotalKills(std::string username, unsigned int increment);


	// Update total deaths for the player in the database.
	// param:username-> The username of the player to update.
	// param:increment-> The value to add to the stat.
	int UpdateTotalDeaths(std::string username, unsigned int increment);


	// Update total assists for the player in the database.
	// param:username-> The username of the player to update.
	// param:increment-> The value to add to the stat.
	int UpdateTotalAssists(std::string username, unsigned int increment);


	// Return whether the database is connected or not.
	bool GetIsConnected();
private:
	// The database.
	Database db;


	// Stats of the current player.
	StatList currentPlayerStats;


	// Map of players that are currently logged in.
	std::map<std::string, bool> playersLoggedIn;


	// Load the current stats for the specified player.
	// param:username-> The username of the player to load.
	int LoadPlayerStats(std::string username);
};
