#pragma once
#include <string> 

enum class ItemType{ Unknown,Potion, Weapon };

std::string item_type_to_string(ItemType type);
ItemType string_to_item_type(std::string type);
class Item{
    private:
        std::string name;
        ItemType type;
        int value;
    public:
        Item(std::string name, ItemType type,int value);
        std::string get_name() const;
        ItemType get_type() const;
        int get_value() const;
};