#include "pch.h"
#include "PlayerTeam.h"

int PlayerTeam::count = Manager::getInstance()->getCounts()["PlayerTeam"];

// Constructor
PlayerTeam::PlayerTeam()
	: id(0), captain(nullptr), viceCaptain(nullptr), budget(0.0) {}

PlayerTeam::PlayerTeam(unordered_map<int, pair<Footballer*, bool>> squad, Footballer* captain, Footballer* viceCaptain)
	: squad(squad), captain(captain), viceCaptain(viceCaptain), id(count), budget(100000.00), points() {
	count++;
}

PlayerTeam::PlayerTeam(int id, unordered_map<int, pair<Footballer*, bool>> squad, Footballer* captain, Footballer* viceCaptain, float budget, map<int, int> points)
	: squad(squad), captain(captain), viceCaptain(viceCaptain), id(id), budget(budget), points(points) {}


// Getters
int PlayerTeam::getCount() {
	return count;
}

int PlayerTeam::getId() const {
	return id;
}

unordered_map<int, pair<Footballer*, bool>> PlayerTeam::getSquad() const {
	return squad;
}

const Footballer* PlayerTeam::getCaptain() const {
	return captain;
}

const Footballer* PlayerTeam::getViceCaptain() const {
	return viceCaptain;
}

float PlayerTeam::getBudget() const {
	return budget;
}

const stack<pair<Footballer*, int>> PlayerTeam::getTransferStack() const {
	return transferStack;
}

map<int, int> PlayerTeam::getPoints() const {
	return points;
}


// Setters
void PlayerTeam::setCount(int count) {
	PlayerTeam::count;
}

void PlayerTeam::setSquad(const unordered_map<int, pair<Footballer*, bool>>& squad) {
	this->squad = squad;
}

void PlayerTeam::setCaptain(Footballer* captain) {
	this->captain = captain;
}

void PlayerTeam::setViceCaptain(Footballer* viceCaptain) {
	this->viceCaptain = viceCaptain;
}

void PlayerTeam::setBudget(float budget) {
	this->budget = budget;
}

void PlayerTeam::setPoints(map<int, int> points) {
	this->points = points;
}

json PlayerTeam::toJson() {
	json j;
	j["_id"] = id;
	
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
	id = j["_id"];

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

bool PlayerTeam::swapFootballers(const int& starterId, const int& benchedId) {
	unordered_map<int, pair<Footballer*, bool>>::iterator starterIt = findFootballer(starterId);
	unordered_map<int, pair<Footballer*, bool>>::iterator benchedIt = findFootballer(benchedId);
	
	// Chcek if the first footballers is starting and the second footballer is benched
	if (starterIt != squad.end() && benchedIt != squad.end() && starterIt->second.second == true && benchedIt->second.second == false) {
		starterIt->second.second = false;
		benchedIt->second.second = true;
		return true; // Swapped successfully
	}
	return false; // Both footballers were either both starting or both benched, or at least one wasn't in the squad (a player shouldn't be able to cause this)
}

void PlayerTeam::transfer(const int& out, Footballer* in)
{
	unordered_map<int, pair<Footballer*, bool>>::iterator outIt = findFootballer(out);
	Footballer* outFootballer = outIt->second.first;
	bool isStarting = outIt->second.second;
	removeFootballer(out);
	addFootballer(in, isStarting);
	transferStack.push(make_pair(outFootballer, in->getId()));
}

bool PlayerTeam::confirmTransfers()
{
	if (budget < 0.0)
		return false; // Negative budget
	
	// Clear the transfer stack
	stack<pair<Footballer*, int>> emptyStack;
	transferStack.swap(emptyStack);
	return true; // Transfers confirmed
}

void PlayerTeam::undoTransfer()
{
	Footballer* oldFootballer; // old is the footballer to be returned to the squad
	int newFootballerId;
	bool isStarting;

	oldFootballer = transferStack.top().first;
	newFootballerId = transferStack.top().second;
	isStarting = findFootballer(newFootballerId)->second.second;

	removeFootballer(newFootballerId);
	addFootballer(oldFootballer, isStarting);
	transferStack.pop();
}

void PlayerTeam::updatePoints(int gameweek)
{
	unordered_map<int, pair<Footballer*, bool>>::iterator it;
	points[gameweek] = 0;

	// Add all team footballers points
	for (it = squad.begin(); it != squad.end(); it++)
		points[gameweek] += it->second.first->getGwPoints()[gameweek];
}

