#include "pch.h"
#include "League.h"

// Constructors
League::League() {}

League::League(string name)
	: name(name) {}

// Getters
string League::getName() 
{ 
	return name; 
}

map<int, vector<FootballTeam*>> League::getStandings() const
{
	return standings;
}

void League::updateStandingsPoints()
{
	if(!standings.empty()) standings.clear();

	unordered_map<int, FootballTeam*> teams = Manager::getInstance()->getFootballTeams();
	unordered_map<int, FootballTeam*>::iterator it;
	for (it = teams.begin(); it != teams.end(); it++)
	{
		if (it->second->getLeague() == name)
		{
			standings[it->second->getPoints()].push_back(it->second);
		}
	}
}


