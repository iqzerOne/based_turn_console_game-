#pragma once
#include "Character.h"
#include <string> 

class Enemy : public Character{
    public:
        Enemy(std::string name, int hp, int damage);
        std::string get_type() const override;
};