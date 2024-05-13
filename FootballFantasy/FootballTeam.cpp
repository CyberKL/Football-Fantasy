#include "pch.h"
#include "FootballTeam.h"

int FootballTeam::count = Manager::getInstance()->getCounts()["FootballTeam"];

// Constructors
FootballTeam::FootballTeam() {}
FootballTeam::FootballTeam(string name, string league)
	:name(name), league(league) {}
// Getters
int FootballTeam::getCount()
{
	return count;
}

string FootballTeam::getName() const
{
	return name;
}

int FootballTeam::getPoints() 
{
	return points;
}

int FootballTeam::getId()
{
	return id;
}

string FootballTeam::getLeague() const
{
	return league;
}

vector<Footballer*> FootballTeam::getFootballers()
{
	return footballers;
}


// update points of team 
void FootballTeam::updatePoints(char result)
{
	switch (result)
	{
	case 'W':
		points += 3;
	case 'D':
		points += 1;
	}
}

json FootballTeam::toJson()
{
	json j;
	j["_id"] = id;
	j["name"] = name;
	j["points"] = points;
	j["league"] = league;

	vector<Footballer*>::iterator it;
	int i = 0;
	for (it = footballers.begin(); it != footballers.end(); it++, i++)
	{
		j["footballers"][i] = (*it)->getId();
	}

	return j;
}

void FootballTeam::fromJson(json& j)
{
	id = j["_id"];
	name = j["name"];
	points = j["points"];
	league = j["league"];
}

void FootballTeam::loadFootballer(Footballer* footballer)
{
	footballers.push_back(footballer);
}
