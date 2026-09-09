#include "Player.h"
#include <iostream>

Player::Player(std::string name, int hp, int damage) : Character(name, hp, damage) {
}
std::string Player::get_type() const {
        return "Player";
}