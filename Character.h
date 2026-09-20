#pragma once
#include <string> 

class Character{
    private:
        std::string name;
        int hp;
        int damage;
    public:
        Character(std::string name, int hp, int damage);
        virtual ~Character() = default;
        virtual std::string get_type()const;

        std::string get_name() const;
        int get_hp()const;
        int get_attack_damage() const;

        void print_info() const;
        int take_damage(int dmg);
        int heal_hero(int heal);
        int increase_damage(int dmg);
        int set_hp(int hp);
        int set_damage(int dmg);
        
};