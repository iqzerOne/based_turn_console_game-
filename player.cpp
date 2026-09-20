#include "Player.h"
#include "item.h"
#include <iostream>

Player::Player(std::string name, int hp, int damage) : Character(name, hp, damage) {
}
std::string Player::get_type() const {
        return "Player";
}

void Player::add_item_player(const Item& item) {
        inventory.add_item(item);
}

void Player::print_inventory() const{
        inventory.print_items();
}

int Player::inventory_size() const{
        return inventory.size();
}

Item Player::use_item_player(int index) const{
        return inventory.get_item(index);
}

void Player::remove_item_player(int index) {
        inventory.remove_item(index);
}

void Player::clear_inventory_player(){
        inventory.clear_inventory();
}