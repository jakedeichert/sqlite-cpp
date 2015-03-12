#pragma once

struct StatList {
public:
	// Current stats of the player.
	int totalKills;
	int totalDeaths;
	int totalAssists;

	// Calculate the kill/death ratio.
	// param:kills-> The number of kills.
	// param:deaths-> The number of deaths.
	float GetKDRatio(unsigned int kills, unsigned int deaths);
};
