#include "pch.h"
#include "Admin.h"
#include "Manager.h"

//getters
string Admin::getUsername()
{
	return username;
}
string Admin::getPass()
{
	return password;
}
string Admin::getActiveLeague()
{
	return activeLeague;
}
stack<int> Admin::getRemovedFootballers()
{
	return removedFootballers;
}
stack<int> Admin::getRemovedFootballTeams()
{
	return removedFootballTeams;
}


void Admin::addFootballTeam(string name, string league)
{
	FootballTeam* FT = new FootballTeam(name, league);
	Manager::getInstance()->getFootballTeams()[FT->getId()] = FT;

}

void Admin::removeFootballTeam(int id)
{
	Manager::getInstance()->getFootballTeams().erase(id);
}

void Admin::updateFootballTeam(int id1, int id2)
{
	Footballer* footballer1 = Manager::getInstance()->getFootballers()[id1];
	Footballer* footballer2 = Manager::getInstance()->getFootballers()[id2];

	footballer1->setTeam(footballer2->getTeam());
	footballer1->setLeagueName(footballer2->getLeagueName());
	footballer2->setTeam(footballer1->getTeam());
	footballer2->setLeagueName(footballer1->getLeagueName());
}

void Admin:: updateMatchScore(int matchId, int htScore,int atScore )
{
	int gameWeek = Manager::getInstance()->getCurrentGw();
	Match match = *Manager::getInstance()->getMatches()[gameWeek][matchId];

	if (htScore > atScore)
	{
		match.getHomeTeam()->updatePoints('W');
	}

	if (htScore < atScore)
	{
		match.getAwayTeam()->updatePoints('W');
	}

	if (htScore = atScore)
	{
		match.getAwayTeam()->updatePoints('D');
		match.getHomeTeam()->updatePoints('D');
	}
}


	/* void Admin::updateMatchScorers(int matchId, vector <int> scorersGUI){}*/
