#pragma once

#include "Manager.h"

struct UiFootballer {
	int id;
	string name;
	string info;
	bool isStarting;
	string position;
};

class Presenter
{
private:
	static Presenter* instance;

	Player* loggedInPlayer;
	int pressedFootballerControlId;
	unordered_map<int, bool> tempSquad;
	bool squadEdited = false;

	Presenter(); // Private constructor to prevent instantiation

	// Delete copy constructor and assignment operator to prevent copying
	Presenter(Presenter const&) = delete;
	void operator=(Presenter const&) = delete;

public:
	static Presenter* getInstance();

	// Getters
	int getPressedFootballerControlId();
	bool getSquadEdited();

	// Setters
	void setPressedFootballerControlId(int);
	void setTempSquad(unordered_map<int, bool>);
	void setSquadEdited(bool);

	bool isUsernameDuplicate(const string&);
	void signUp(const string&, const string&);
	bool login(const string&, const string&);
	string budgetToString(int);
	PlayerTeam* getPlayerTeam();
	Footballer getFootballer(int);
	string getFootballerNextMatch(int);
	void createPlayerTeam(unordered_set<int>, int);
	vector<Footballer> searchFootballersByPosition(string);
	unordered_map<int, struct UiFootballer> loadPickTeamPage();
	unordered_map<int, struct UiFootballer> loadTempSquad();
	void confirmChangesInPickTeam();
	void loadData();
	string getLoggedInPlayerPassword();
	string getLoggedInPlayerUsername();
	void changePassword(string password);
	void deleteAccount(int accountId);
	int getLoggedInPlayerID();


};

