#include "pch.h"
#include "Player.h"

int Player::count = Manager::getInstance()->getCounts()["Player"];

// Constructors
Player::Player() : id(0), team(nullptr), totalPoints(0) {}

Player::Player(const string& username, const string& password)
    : id(count), username(username), password(password), team(nullptr), totalPoints(0) {
    count++;
}

Player::Player(int id, const string& username, const string& password, PlayerTeam* team, int totalPoints)
    : id(id), username(username), password(password), team(team), totalPoints(totalPoints) {}

// Getters
int Player::getCount() {
    return count;
}

int Player::getId() const {
    return id;
}

string Player::getUsername() const {
    return username;
}

string Player::getPassword() const {
    return password;
}

PlayerTeam* Player::getTeam() const {
     return team;
}

int Player::getTotalPoints() const {
    return totalPoints;
}

// Setters
void Player::setCount(int count) {
    Player::count = count;
}

void Player::setUsername(const std::string& newUsername) {
    username = newUsername;
}

void Player::setPassword(const std::string& newPassword) {
    password = newPassword;
}

void Player::setTotalPoints(int newTotalPoints) {
    totalPoints = newTotalPoints;
}

void Player::setTeam(PlayerTeam* team)
{
    this->team = team;
}


json Player::toJson() {
    json j;
    j["_id"] = id;
    j["username"] = username;
    j["password"] = password;
    j["team"] = team->toJson();
    j["totalPoints"] = totalPoints;
    return j;
}

void Player::fromJson(json& j) {
    id = j["_id"];
    username = j["uesrname"];
    password = j["password"];
    team = new PlayerTeam();
    team->fromJson(j["team"]);
    totalPoints = j["totalPoints"];
}