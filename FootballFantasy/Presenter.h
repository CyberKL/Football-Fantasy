#pragma once

#include "Manager.h"

struct UiFootballer {
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

	Presenter(); // Private constructor to prevent instantiation

	// Delete copy constructor and assignment operator to prevent copying
	Presenter(Presenter const&) = delete;
	void operator=(Presenter const&) = delete;

public:
	static Presenter* getInstance();

	bool isUsernameDuplicate(const string&);
	void signUp(const string&, const string&);
	bool login(const string&, const string&);
	string getLoggedInPlayerBudget();
	PlayerTeam* getPlayerTeam();
	Footballer getFootballer(int);
	string getFootballerNextMatch(int);
	void createPlayerTeam(unordered_set<int>);
	vector<Footballer> searchFootballersByPosition(string);
	vector<struct UiFootballer> loadPickTeamPage();
	void loadData();
};

