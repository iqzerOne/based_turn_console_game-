#include "Enemy.h"
#include <iostream>

Enemy::Enemy(std::string name, int hp, int damage) : Character(name, hp, damage) {
}
std::string Enemy::get_type() const {
    return "Enemy";
}
