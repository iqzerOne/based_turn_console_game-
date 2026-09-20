#include "item.h"

std::string item_type_to_string(ItemType type) {
    if (type == ItemType::Potion) return "Potion";
    if (type == ItemType::Weapon) return "Weapon";
    return "Unknown";
}

ItemType string_to_item_type(std::string type) {
    if (type == "Potion") return ItemType::Potion;
    if (type == "Weapon") return ItemType::Weapon;
    return ItemType::Unknown;
}

Item::Item(std::string name, ItemType type, int value){
    this->name = name;
    this->type = type;
    this->value = value;
}

std::string Item::get_name() const {
    return name;
}

ItemType Item::get_type() const{
    return type;
}

int Item::get_value() const{
    return value;
}
