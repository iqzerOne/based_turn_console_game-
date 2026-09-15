#include "item.h"

Item::Item(std::string name, std::string type, int value){
    this->name = name;
    this->type = type;
    this->value = value;
}

std::string Item::get_name() const {
    return name;
}

std::string Item::get_type() const{
    return type;
}

int Item::get_value() const{
    return value;
}

