#pragma once

#include <string>
#include "PlayerTeam.h"
#include <nlohmann/json.hpp>

using json = nlohmann::json;
using namespace std;

class PlayerTeam;

class Player
{
private:
    static int count;

	int id;
	string username;
	string password;
	PlayerTeam* team; // Pointer so it can be nullptr when a player signs up
	int totalPoints;

public:
    // Constructors
    Player();
    Player(const string&, const string&);
    Player(int, const string&, const string&, PlayerTeam*, int);

    // Getters
    static int getCount();
    int getId() const;
    string getUsername() const;
    string getPassword() const;
    PlayerTeam* getTeam() const;
    int getTotalPoints() const;

    // Setters
    static void setCount(int);
    void setUsername(const string& newUsername);
    void setPassword(const string& newPassword);
    void setTotalPoints(int newTotalPoints);
    void setTeam(PlayerTeam* team);

    // Handles file serialization to and from JSON
    json toJson();
    void fromJson(json&);

};

