#include "pch.h"
#include "Match.h"

int Match::count = Manager::getInstance()->getCounts()["Match"];

// Constructors
Match::Match()
	: id(0), homeTeam(nullptr), awayTeam(nullptr), gw(0), league(""), score(""), played(false) { }

// Getters
int Match::getCount()
{
	return count;
}

int Match::getId() const
{
	return id;
}

FootballTeam* Match::getHomeTeam() const
{
	return homeTeam;
}

FootballTeam* Match::getAwayTeam() const
{
	return awayTeam;
}

int Match::getGw() const
{
	return gw;
}

string Match::getScore() const
{
	return score;
}

queue<Footballer*> Match::getScorers() const
{
	return scorers;
}

bool Match::getPlayed() const
{
	return played;
}

json Match::toJson()
{
	json j;
	j["_id"] = id;
	j["gw"] = gw;
	j["homeTeamId"] = homeTeam->getId();
	j["awayTeamId"] = awayTeam->getId();
	j["league"] = league;
	j["score"] = score;
	
	while (!scorers.empty())
	{
		j["scorers"].push_back(scorers.front()->getId());
		scorers.pop();
	}

	j["played"] = played;

	return j;
}

void Match::fromJson(json& j)
{
	id = j["_id"];
	gw = j["gw"];
	homeTeam = Manager::getInstance()->getFootballTeams()[j["homeTeamId"]];
	awayTeam = Manager::getInstance()->getFootballTeams()[j["awayTeamId"]];
	league = j["league"];
	score = j["score"];

	for (int id : j["scorers"])
	{
		Footballer* footballer = Manager::getInstance()->getFootballers()[id];
		scorers.push(footballer);
	}

	played = j["played"];
	
}