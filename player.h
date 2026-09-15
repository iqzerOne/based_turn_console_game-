#pragma once
#include "Character.h"
#include "Inventory.h"
#include <string> 

class Player : public Character{
    private:
        Inventory inventory;
    public:
        Player(std::string name, int hp, int damage);
        std::string get_type() const override;
        void add_item_player(const Item& item);
        void print_inventory() const;
        int inventory_size() const;
        Item use_item_player(int index) const;
        void remove_item_player(int index);
};