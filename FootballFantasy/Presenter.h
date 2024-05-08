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
	int tempCaptainId;
	int tempViceCaptainId;
	bool squadEdited = false;
	bool captaincyEdited = false;

	Presenter(); // Private constructor to prevent instantiation

	// Delete copy constructor and assignment operator to prevent copying
	Presenter(Presenter const&) = delete;
	void operator=(Presenter const&) = delete;

public:
	static Presenter* getInstance();

	// Getters
	int getPressedFootballerControlId();
	int getTempCaptainId();
	int getTempViceCaptainId();
	bool getSquadEdited();
	bool getCaptaincyEdited();

	// Setters
	void setPressedFootballerControlId(int);
	void setTempSquad(unordered_map<int, bool>);
	void setTempCaptainId(int);
	void setTempViceCaptainId(int);
	void setSquadEdited(bool);
	void setCaptaincyEdited(bool);

	bool isUsernameDuplicate(const string&);
	void signUp(const string&, const string&);
	bool login(const string&, const string&);
	string budgetToString(int);
	PlayerTeam* getPlayerTeam();
	int getLoggedInPlayerBudget();
	Footballer getFootballer(int);
	string getFootballerNextMatch(int);
	void createPlayerTeam(unordered_set<int>, int);
	vector<Footballer> searchFootballersByPosition(string);
	unordered_map<int, struct UiFootballer> loadPickTeamPage();
	unordered_map<int, struct UiFootballer> loadTeamPointsPage();
	unordered_map<int, struct UiFootballer> loadTeamTransfersPage();
	unordered_map<int, struct UiFootballer> loadTempSquad();
	void getCaptainsIds(int&, int&);
	void confirmChangesInPickTeam();
	void confirmTransfersPage(stack<pair<int, int>>);
	void loadData();
	string getLoggedInPlayerPassword();
	string getLoggedInPlayerUsername();
	void changePassword(string password);
	void deleteAccount(int accountId);
	int getLoggedInPlayerID();
	map<int, vector<string>> getCurrentGwRankings();
	map<int, vector<string>> getTotalRankings();
	map<int, unordered_map<int, Match>> getMatches();
	int getCurrentGw();
	void logOut();
	void updateRate(double);
};

