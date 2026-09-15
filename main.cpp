#include <iostream>
#include <string>
#include <vector>
#include <limits>
#include "constants.h"
#include "Character.h"
#include "Player.h"
#include "Enemy.h"
#include "item.h"
#include "inventory.h"

bool check_lives_enemy(const std::vector<Enemy>& enemy){
    for(int i = 0; i < enemy.size(); i++){
        if(enemy[i].get_hp() > 0){
            return true;
        }
    }
    return false;
}

int check_enemy_hp(int choice,const std::vector<Enemy>& enemy){
    if (choice < 1 || choice > (int)enemy.size()) {
        return 0;
    }
    if(enemy[choice-1].get_hp() > 0){
        return choice;
    }else{
        return 0;
    }
}

void add_enemy(std::vector<Enemy>& enemy,int wave){
    for(int i = 0; i < wave * 2; i++){
        enemy.push_back(Enemy("Goblin", Constants::HP_ENEMY * wave,wave * Constants::DAMAGE_ENEMY));
    }
}

void damage_character(Character& unit, int dmg){
    unit.take_damage(dmg);
}


void print_character(const Character& c){
    c.print_info();
}

void print_enemy(const std::vector<Enemy>& enemy){
    for(int i = 0; i < enemy.size(); i++){
        if(enemy[i].get_hp() > 0){
            std::cout << i + 1 << ": "; 
            print_character(enemy[i]);  
        }
    }
}

int check_inventory(Player& hero){
    int choice = 0;
    hero.print_inventory();
    while(!choice){
        std::cout << "Choice item (1-" << hero.inventory_size() << "): " << std::endl;
        while (!(std::cin >> choice)) {
            std::cout << "Err, pls input number: " << std::endl;
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        }
        if (choice <= 0 || choice > hero.inventory_size()){
            std::cout << "Inventory is not found, pls any more action" << std::endl;
            choice = 0;
        }
    }
    return choice;
}

int turn_hero(std::vector <Enemy>& enemies, Player& hero){
    hero.print_inventory();
    print_enemy(enemies);
    int choice = 0;
    while(!choice){
        std::cout << "Choice action (1-Attack, 2-Use item, 3-Skip turn): "  << std::endl;
        while (!(std::cin >> choice)) {
            std::cout << "Err, pls input number: " << std::endl;
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');  
        }
        if(choice <= 0 || choice > 3){
            choice = 0;
        }
        if(choice == 2){
            if(hero.inventory_size() <= 0){
                std::cout << "Inventory empty, pls any more action" << std::endl;
                choice = 0;
            }
        }
    }
    return choice;
}

bool turn_hero_attack(std::vector <Enemy>& enemies, Player& hero){
    int choice = 0;
    while(!choice){
        std::cout << "Choice enemy damage (1-" << enemies.size() << "): " << std::endl;
        while (!(std::cin >> choice)) {
            std::cout << "Err, pls input number: " << std::endl;
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');  
        }
        choice = check_enemy_hp(choice,enemies);
    }
    damage_character(enemies[choice-1],hero.get_attack_damage());
    return false;
}

void use_item(Player& hero){
    int index = check_inventory(hero) - 1;
    Item item = hero.use_item_player(index);
    if(item.get_type() == "potion"){
        hero.heal_hero(item.get_value());
    }else{
       hero.increase_damage(item.get_value());
    }
    hero.remove_item_player(index);
}

bool move_enemy(const std::vector <Enemy>& enemies, Player& hero){
    for(int i = 0; i < enemies.size(); i++){
        if(enemies[i].get_hp() > 0){
            damage_character(hero,enemies[i].get_attack_damage());
        }
    }
    print_character(hero);
    return true;
}

std::string play_game(){
    Player Hero("Hero", Constants::HP_HERO,Constants::DAMAGE_HERO);
    Hero.add_item_player(Item("Potion", "potion", 20));
    Hero.add_item_player(Item("Sword", "weapon", 5));
    std::vector<Enemy> enemies; 
    bool turn = true;
    int wave = 1;
    add_enemy(enemies,wave);
    while (Hero.get_hp() > 0 && check_lives_enemy(enemies)){
        if(turn){
            int choice_hero = turn_hero(enemies,Hero);
            if(choice_hero == 1){
                turn = turn_hero_attack(enemies,Hero);
            }else if(choice_hero == 2){
                turn = false;
                use_item(Hero);
            }else{
                // turn = defense_hero();
                turn = false;
            }
        }else{
            turn = move_enemy(enemies,Hero);
        }
        if(!check_lives_enemy(enemies)){
            wave += 1;
            if(wave <= 2){
                enemies.clear();
                add_enemy(enemies,wave);
                turn = true;
            }
        }
    }
    if (Hero.get_hp() > 0){
        std::cout << "Winner:" << std::endl;
        print_character(Hero);
    }else{
        std::cout << "Player lose" << std::endl;
        for(int i = 0; i < enemies.size(); i++){
            print_character(enemies[i]);
        }
    }
    return "main";
}

std::string main_menu(){
    int choice = 0;
    while(true){
        std::cout << "Choice number" << std::endl;
        std::cout << "1.Play\n2.Exit" << std::endl;
        while (!(std::cin >> choice)) {
            std::cout << "Err, pls input number: " << std::endl;
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        }
        if(choice == 1){
            return "play";
        }else if(choice == 2){
            return "exit";
        }else{
            std::cout << "invalid choice" << std::endl;
        }
    }    
}

void start(){
    std::string state = "main";
    while(true){
        if(state == "main"){
            state = main_menu();
        }else if(state == "exit"){
            return;
        }else if(state == "play"){
            state = play_game();
        }
    }
}

int main() {
    start();
}