#pragma once

#include "Footballer.h"
#include <nlohmann/json.hpp>
#include "Manager.h"
#include <stack>

using json = nlohmann::json;
using namespace std;

class Footballer;

class PlayerTeam
{
private:
	unordered_map<int, pair<Footballer*, bool>> squad;
	Footballer* captain;
	Footballer* viceCaptain;
	stack<pair<Footballer*, int>> transferStack;
	int budget;
	map<int, int> points;

public:
	// Constructor
	PlayerTeam();
	PlayerTeam(unordered_map<int, pair<Footballer*, bool>>, Footballer*, Footballer*, int);

	// Getters
	unordered_map<int, pair<Footballer*, bool>> getSquad() const;
	const Footballer* getCaptain() const;
	const Footballer* getViceCaptain() const;
	int getBudget() const;
	const stack<pair<Footballer*, int>> getTransferStack() const;
	map<int, int> getPoints() const;

	// Setters
	void setSquad(const unordered_map<int, pair<Footballer*, bool>>& squad);
	void setCaptain(Footballer*);
	void setViceCaptain(Footballer*);
	void setBudget(int);
	void setPoints(map<int, int>);

	// Handles file serialization to and from JSON
	json toJson();
	void fromJson(json&);

	// Functionality methods
	bool addFootballer(Footballer*, const bool&);
	unordered_map<int, pair<Footballer*, bool>>::iterator findFootballer(const int&);
	bool removeFootballer(const int&);
	void swapFootballers(const int&, const int&);
	void transfer(const int&, Footballer*);
	bool confirmTransfers();
	void undoTransfer();
	void updatePoints(int);

};

