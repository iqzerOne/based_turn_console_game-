#include "Character.h"
#include "constants.h"
#include <iostream>

Character::Character(std::string name, int hp, int damage) {
    this->name = name;
    this->hp = hp;
    this->damage = damage;
}

std::string Character::get_type() const{
    return "Character";
}

int Character::get_attack_damage() const{
    return damage;
}

std::string Character::get_name() const {
    return name;
}

int Character::get_hp() const{
    return hp;
}

void Character::print_info() const{
    std::cout << "Name:" << name << std::endl;
    std::cout << "HP:" << hp << std::endl;
}

int Character::take_damage(int dmg){
    this->hp -= dmg;
    if(this->hp < 0){
        this->hp = 0;
    }
    return this->hp;
}

int Character::heal_hero(int heal){
    this->hp += heal;
    if(this->hp >= Constants::HP_HERO){
        this->hp = Constants::HP_HERO;
    }
    return this->hp;
}

int Character::increase_damage(int dmg){
    this->damage += dmg;
    return this->damage;
}

int Character::set_hp(int hp){
    this->hp = hp;
    return this->hp;
}

int Character::set_damage(int dmg){
    this->damage = dmg;
    return this->damage;
}