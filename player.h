#pragma once
#include "Character.h"
#include <string> 

class Player : public Character{
    public:
        Player(std::string name, int hp, int damage);
        std::string get_type() const override;
};