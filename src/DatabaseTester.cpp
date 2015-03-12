#include "DatabaseTester.h"


DatabaseTester::DatabaseTester() {
	if (testConnect()) {

		// log in players
		int resultCode = db.PlayerLogin("jake", "1234");
		resultCode += db.PlayerLogin("ggg", "1234");
		resultCode += db.PlayerLogin("ender", "abcd1234");
		resultCode += db.PlayerLogin("asus", "abcd1234");


		// update stats, be careful!
		//resultCode += db.UpdateTotalKills("jake", 1);
		//resultCode += db.UpdateTotalDeaths("ender", 1);
		//resultCode += db.UpdateTotalAssists("ggg", 1);


		// if result code is still 0, no errors have occurred
		if (!resultCode) {
			printPlayers();
		} else {
			std::cout << "errors" << std::endl;
		}


		// log out players
		resultCode += db.PlayerLogout("jake");
		resultCode += db.PlayerLogout("ggg");
		resultCode += db.PlayerLogout("ender");
		resultCode += db.PlayerLogout("asus");



	}
	testDisconnect();
}

DatabaseTester::~DatabaseTester() {}


// Connect to the database.
bool DatabaseTester::testConnect() {
	std::cout << "=======================================================" << std::endl;
	if (db.Connect()) {
		std::cout << "DATABASE CONNECTION FAILED" << std::endl;
		return false;
	}
	std::cout << "DATABASE CONNECTION SUCCESSFUL" << std::endl;
	return true;
}


// Disconnect from the database.
bool DatabaseTester::testDisconnect() {
	std::cout << "=======================================================" << std::endl;

	if (db.Disconnect()) {
		std::cout << "DATABASE DISCONNECTION FAILED" << std::endl;
		return false;
	} else {
		std::cout << "DATABASE DISCONNECTION SUCCESSFUL" << std::endl;
		return true;
	}
}


// Print all player data from the database.
void DatabaseTester::printPlayers() {
	const int numPlayers = 4;
	std::string players[numPlayers];
	players[0] = "jake";
	players[1] = "ggg";
	players[2] = "ender";
	players[3] = "asus";

	for (int i = 0; i < numPlayers; i++) {
		std::cout << "=======================================================" << std::endl;
		std::cout << "player: " + players[i] << std::endl;
		std::cout << "----------------------" << std::endl;
		// get stats
		std::cout << "kills: " << db.GetTotalKills(players[i]) << std::endl;
		std::cout << "deaths: " << db.GetTotalDeaths(players[i]) << std::endl;
		std::cout << "assists: " << db.GetTotalAssists(players[i]) << std::endl;
	}
}
