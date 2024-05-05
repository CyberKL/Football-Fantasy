#pragma once
#include "pch.h"
#include "Admin.h"
#include "Footballer.h"
	class Admin
	{

		string username;
		string password;
		string activeLeague;
		//int for the id 
		stack<int>removedFootballers;
		stack<int>removedFootballTeams;

		//default constructor
		Admin();

		string getUsername();
		string getPass();
		string getActiveLeague();
		stack<int> getRemovedFootballers();
		stack<int> getRemovedFootballTeams();

		//add Football team function
		void addFootballTeam(string, string);

		//remove Football team function

		void removeFootballTeam(int id);

		//update football team = swap footballers
		void updateFootballTeam(int player1, int player2);

		//update Match Score
		void updateMatchScore(int matchId, int htScore, int atScore);

		//update Match Scorers for latest 
		void updateMatchScorers(int matchId, vector <int> scorers);

	};
