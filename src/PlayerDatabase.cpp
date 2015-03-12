#include "PlayerDatabase.h"



PlayerDatabase::PlayerDatabase() {}
PlayerDatabase::~PlayerDatabase() {
	Disconnect();
}



// Open a database connection.
int PlayerDatabase::Connect() {
	// try to connect to the player table in the database
	if (db.Connect("players", "username")) return PLAYERDB_CANNOT_CONNECT;
	return PLAYERDB_SUCCESS;
}



// Close the database connection.
int PlayerDatabase::Disconnect() {
	// try to disconnect from the database
	if (db.Disconnect()) return PLAYERDB_CANNOT_DISCONNECT;
	return PLAYERDB_SUCCESS;
}



// Log in a player.
// param:username-> The username of the player.
// param:password-> The password of the player.
int PlayerDatabase::PlayerLogin(std::string username, std::string password) {
	// check if the player is already logged in
	if (playersLoggedIn.count(username)) return PLAYERDB_ALREADY_LOGGED_IN;

	// check if the username exists in the database
	int resultCode = db.CheckPrimaryKeyValueExists(username);
	if (resultCode) return PLAYERDB_WRONG_USERNAME;

	// check if the password is correct
	if (password != db.GetCellString(username, "password")) return PLAYERDB_WRONG_PASSWORD;

	// try to update the logged in value to true
	if (db.UpdateCell(username, "logged_in", "true")) return PLAYERDB_CANNOT_UPDATE_VALUE;

	// add the player to the map of logged in players
	playersLoggedIn[username] = true;

	return PLAYERDB_SUCCESS;
}



// Log out a player.
// param:username-> The username of the player.
int PlayerDatabase::PlayerLogout(std::string username) {
	// check if player is logged in before continuing
	if (!playersLoggedIn.count(username)) return PLAYERDB_NOT_LOGGED_IN;

	// try to update the logged in value to false
	if (db.UpdateCell(username, "logged_in", "false")) return PLAYERDB_CANNOT_UPDATE_VALUE;

	// remove the player from the map since they are no longer being used
	playersLoggedIn.erase(username);

	return PLAYERDB_SUCCESS;
}



// Get total kills from the database.
// param:username-> The username of the player.
int PlayerDatabase::GetTotalKills(std::string username) {
	int resultCode = LoadPlayerStats(username);

	// if there is an error, return -1
	// else return the stat
	if (resultCode) return -1;
	else return currentPlayerStats.totalKills;
}



// Get total deaths from the database.
// param:username-> The username of the player.
int PlayerDatabase::GetTotalDeaths(std::string username) {
	int resultCode = LoadPlayerStats(username);

	// if there is an error, return -1
	// else return the stat
	if (resultCode) return -1;
	else return currentPlayerStats.totalDeaths;
}



// Get total assists from the database.
// param:username-> The username of the player.
int PlayerDatabase::GetTotalAssists(std::string username) {
	int resultCode = LoadPlayerStats(username);

	// if there is an error, return -1
	// else return the stat
	if (resultCode) return -1;
	else return currentPlayerStats.totalAssists;
}



// Update total kills for the player in the database.
// param:username-> The username of the player to update.
// param:increment-> The value to add to the stat.
int PlayerDatabase::UpdateTotalKills(std::string username, unsigned int increment) {
	// add the increment to the current value
	int newValue = increment + GetTotalKills(username);

	// if the update fails, return the result code
	if (db.UpdateCell(username, "total_kills", newValue)) return PLAYERDB_CANNOT_UPDATE_VALUE;

	// otherwise, return success
	return PLAYERDB_SUCCESS;
}



// Update total deaths for the player in the database.
// param:username-> The username of the player to update.
// param:increment-> The value to add to the stat.
int PlayerDatabase::UpdateTotalDeaths(std::string username, unsigned int increment) {
	// add the increment to the current value
	int newValue = increment + GetTotalDeaths(username);

	// if the update fails, return the result code
	if (db.UpdateCell(username, "total_deaths", newValue)) return PLAYERDB_CANNOT_UPDATE_VALUE;

	// otherwise, return success
	return PLAYERDB_SUCCESS;
}



// Update total assists for the player in the database.
// param:username-> The username of the player to update.
// param:increment-> The value to add to the stat.
int PlayerDatabase::UpdateTotalAssists(std::string username, unsigned int increment) {
	// add the increment to the current value
	int newValue = increment + GetTotalAssists(username);

	// if the update fails, return the result code
	if (db.UpdateCell(username, "total_assists", newValue)) return PLAYERDB_CANNOT_UPDATE_VALUE;

	// otherwise, return success
	return PLAYERDB_SUCCESS;
}



// Load the current stats for the specified player.
// param:username-> The username of the player to load.
int PlayerDatabase::LoadPlayerStats(std::string username) {
	// check if the player is logged in
	if (!playersLoggedIn.count(username)) return PLAYERDB_NOT_LOGGED_IN;

	// grab the stats from the database
	currentPlayerStats.totalKills = db.GetCellInt(username, "total_kills");
	currentPlayerStats.totalDeaths = db.GetCellInt(username, "total_deaths");
	currentPlayerStats.totalAssists = db.GetCellInt(username, "total_assists");
	return PLAYERDB_SUCCESS;
}



// Return whether the database is connected or not.
bool PlayerDatabase::GetIsConnected() {
	return db.GetIsConnected();
}
