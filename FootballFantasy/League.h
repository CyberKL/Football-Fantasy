#pragma once

#include "Footballer.h"
#include "FootballTeam.h"
#include "Match.h"
#include <unordered_set>

using namespace std;

class League
{
private:
	string name;
	map<int, vector<FootballTeam*>> standings;
	
public:
	// Constructors
	League();
	League(string);

	// Getters
	string getName();
	map<int, vector<FootballTeam*>> getStandings() const;

	void updateStandingsPoints();

};

