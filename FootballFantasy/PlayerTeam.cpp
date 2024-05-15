#include "pch.h"
#include "PlayerTeam.h"

// Constructor
PlayerTeam::PlayerTeam()
	: captain(nullptr), viceCaptain(nullptr), budget(0.0) { }

PlayerTeam::PlayerTeam(unordered_map<int, pair<Footballer*, bool>> squad, Footballer* captain, Footballer* viceCaptain, int budget)
	: squad(squad), captain(captain), viceCaptain(viceCaptain), budget(budget) { }


// Getters
unordered_map<int, pair<Footballer*, bool>> PlayerTeam::getSquad() const {
	return squad;
}

const Footballer* PlayerTeam::getCaptain() const {
	return captain;
}

const Footballer* PlayerTeam::getViceCaptain() const {
	return viceCaptain;
}

int PlayerTeam::getBudget() const {
	return budget;
}

const stack<pair<Footballer*, int>> PlayerTeam::getTransferStack() const {
	return transferStack;
}

map<int, int> PlayerTeam::getPoints() const {
	return points;
}


// Setters
void PlayerTeam::setSquad(const unordered_map<int, pair<Footballer*, bool>>& squad) {
	this->squad = squad;
}

void PlayerTeam::setCaptain(Footballer* captain) {
	this->captain = captain;
}

void PlayerTeam::setViceCaptain(Footballer* viceCaptain) {
	this->viceCaptain = viceCaptain;
}

void PlayerTeam::setBudget(int budget) {
	this->budget = budget;
}

void PlayerTeam::setPoints(map<int, int> points) {
	this->points = points;
}

json PlayerTeam::toJson() {
	json j;

	for (unordered_map<int, pair<Footballer*, bool>>::iterator it = squad.begin(); it != squad.end(); it++) {
		int key = it->first;
		bool value = it->second.second;
		j["squad"][key] = value;
	}
	j["captain"] = captain->getId();
	j["viceCaptain"] = viceCaptain->getId();
	j["budget"] = budget;

	for (map<int, int>::iterator it = points.begin(); it != points.end(); it++) {
		int key = it->first;
		int value = it->second;
		j["points"][key] = value;
	}
	return j;
}

void PlayerTeam::fromJson(json& j) {

	// Load the Squad map
	for (json::iterator it = j["squad"].begin(); it != j["squad"].end(); it++) {
		int footballerId = stoi(it.key());
		bool isStarting = it.value();
		Footballer* footballer = Manager::getInstance()->getFootballers()[footballerId];
		squad[footballerId] = make_pair(footballer, isStarting);
	}

	captain = Manager::getInstance()->getFootballers()[j["captain"]];
	viceCaptain = Manager::getInstance()->getFootballers()[j["viceCaptain"]];
	budget = j["budget"];

	// Load points map
	for (json::iterator it = j["points"].begin(); it != j["points"].end(); it++)
		points[stoi(it.key())] = it.value();
}

// Find the pair with the given footballer
unordered_map<int, pair<Footballer*, bool>>::iterator PlayerTeam::findFootballer(const int& footballerId) {
	unordered_map<int, pair<Footballer*, bool>>::iterator it;
	for (it = squad.begin(); it != squad.end(); it++) {
		if (it->first == footballerId) {
			return it; // Found the footballer in the squad
		}
	}
	return squad.end(); // Footballer not found in the squad
}

// Add Footballer
bool PlayerTeam::addFootballer(Footballer* footballer, const bool& isStarting) {
	unordered_map<int, pair<Footballer*, bool>>::iterator it = findFootballer(footballer->getId());
	if (it != squad.end())
		return false; // There is already this footballer in the squad
	squad[footballer->getId()] = make_pair(footballer, isStarting); // Footballer added successfully
	budget -= footballer->getPrice(); // Update budget
	return true;
}

// Remove the given footballer's pair from the vector
bool PlayerTeam::removeFootballer(const int& footballerId) {
	unordered_map<int, pair<Footballer*, bool>>::iterator it = findFootballer(footballerId);

	if (it == squad.end())
		return false; // Footballer not found (a player shouldn't be able to cause this)

	// Footballer found and removed
	budget += it->second.first->getPrice(); // Update budget
	squad.erase(it);
	return true;
}

void PlayerTeam::transfer(const int& out, Footballer* in)
{
	unordered_map<int, pair<Footballer*, bool>>::iterator outIt = findFootballer(out);
	Footballer* outFootballer = outIt->second.first;
	bool isStarting = outIt->second.second;
	removeFootballer(out);
	addFootballer(in, isStarting);
	if (outFootballer == captain)
		captain = in;
	else if (outFootballer == viceCaptain)
		viceCaptain = in;
}

void PlayerTeam::updatePoints(int gameweek)
{
	unordered_map<int, pair<Footballer*, bool>>::iterator it;
	points[gameweek] = 0;

	// Add all team footballers points
	for (it = squad.begin(); it != squad.end(); it++)
	{
		if (it->second.second)
		{
			if (it->second.first == captain)
				points[gameweek] += it->second.first->getGwPoints()[gameweek] * 2;
			else
				points[gameweek] += it->second.first->getGwPoints()[gameweek];
		}
	}
}

