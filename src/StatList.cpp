#include "StatList.h"

// Calculate the kill/death ratio.
// param:kills-> The number of kills.
// param:deaths-> The number of deaths.
float StatList::GetKDRatio(unsigned int kills, unsigned int deaths){
	return (float)kills/(float)deaths;
}
