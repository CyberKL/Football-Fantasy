#include "pch.h"
#include "Match.h"

int Match::count = Manager::getInstance()->getCounts()["Match"];

// Constructors
Match::Match()
	: id(0), homeTeam(nullptr), awayTeam(nullptr), gw(0), league(""), score(""), played(false) { }

Match::Match(FootballTeam* homeTeam, FootballTeam* awayTeam, int gw, string league)
	: id(count), homeTeam(homeTeam), awayTeam(awayTeam), gw(gw), league(league), played(false) {
	count++;
}

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

vector<Footballer*> Match::getScorers() const
{
	return scorers;
}

bool Match::getPlayed() const
{
	return played;
}

void Match::setPlayed(bool played)
{
	this->played = played;
}

void Match::setScore(string score)
{
	this->score = score;
}

void Match::setScorers(vector<Footballer*>)
{
	this->scorers = scorers;
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
	
	for (int i = 0; i < scorers.size(); i++)
	{
		j["scorers"].push_back(scorers[i]->getId());
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
		scorers.push_back(footballer);
	}

	played = j["played"];
	
}