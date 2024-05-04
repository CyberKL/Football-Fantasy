#include "pch.h"
#include "Footballer.h"
#include <sstream>
#include <iomanip>

int Footballer::count = Manager::getInstance()->getCounts()["Footballer"];

// Constructor
Footballer::Footballer()
	: id(0), leagueName(""), price(0.0f) {}

// Getters
int Footballer::getCount()
{
	return count;
}

string Footballer::getName() const
{
	return name;
}

int Footballer::getId() const
{
	return id;
}

string Footballer::getLeagueName() const
{
	return leagueName;
}

int Footballer::getPrice() const
{
	return price;
}

map<int, int> Footballer::getGwPoints() const
{
	return gwPoints;
}

int Footballer::getTotalPoints() const
{
	return totalPoints;
}

string Footballer::getPosition() const
{
	return position;
}

FootballTeam* Footballer::getTeam() const
{
	return team;
}

// Setters
void Footballer::setTeam(FootballTeam& team)
{
	this->team = &team;
}


// update points of footballer
void Footballer:: updatePoints(int goals)
{
	int gw = Manager::getInstance()->getCurrentGw();
	if (position == "Goalkeeper" || position == "Defender")
		gwPoints[gw] += 6 * goals;

	else if (position == "Midfielder")
		gwPoints[gw] += 5 * goals;

	else if (position == "Forward")
		gwPoints[gw] += 4 * goals;
}

//update price of footballer
void Footballer:: updatePrice()
{
	int gw = Manager::getInstance()->getCurrentGw();
	price = gwPoints[gw] * 10 ;
}

string Footballer::priceToString() const
{
	float newPrice = static_cast<float>(price) / 1000;
	ostringstream oss;
	oss << fixed << setprecision(1) << newPrice;
	string priceString = oss.str() + 'K';
	return priceString;
}

// Saving and loading
json Footballer::toJson()
{
	json j;
	j["_id"] = id;
	j["name"] = name;
	j["team"] = team->getName();
	j["league"] = leagueName;
	j["position"] = position;
	j["totalPoints"] = totalPoints;

	for (map<int, int>::iterator it = gwPoints.begin(); it != gwPoints.end(); it++) {
		int key = it->first;
		int value = it->second;
		j["gwPoints"][key] = value;
	}

	j["price"] = price;
	return j;
}

void Footballer::fromJson(json& j)
{
	id = j["_id"];
	name = j["name"];
	
	int teamId = j["teamId"];
	FootballTeam* footballTeam = Manager::getInstance()->getFootballTeams()[teamId];
	team = footballTeam;

	leagueName = j["league"];
	position = j["position"];
	totalPoints = j["totalPoints"];

	for (json::iterator it = j["gwPoints"].begin(); it != j["gwPoints"].end(); it++)
		gwPoints[stoi(it.key())] = it.value();

	price = j["price"];
}