#include "Player.h"

Player::Player(std::string input_name) {
    name = input_name;
    level = 1;
    health = 10;
    max_health = 10;
    movement = 1;
    currentXp = 0;
    xpRequired = 2;
}

void Player::printDetails() {
    std::cout << name << ": L" << level << " (" << currentXp << "/" << xpRequired << ")" << '\n';
    std::cout << "Health: " << health << '/' << max_health << '\n';
    std::cout << "Movement: " << movement << "\n\n";
}

int Player::getMovement() {
    return this->movement;
}

void Player::takeDamage(int damage) {
    this->health -= damage;
}

void Player::heal() {
    this->health = this->max_health;
}


void Player::gainExperience(int xp) {
    currentXp += xp;
}