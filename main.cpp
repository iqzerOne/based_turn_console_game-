#include <iostream>
#include <string>
#include <vector>
#include <limits>
#include "constants.h"
#include "Character.h"
#include "Player.h"
#include "Enemy.h"

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
        return choice ;
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

bool turn_hero(std::vector <Enemy>& enemies, Player& hero){
    int choice = 0;
    print_enemy(enemies);
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
    print_enemy(enemies);
    return false;
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
    std::vector<Enemy> enemies; 
    bool turn = true;
    int wave = 1;
    add_enemy(enemies,wave);
    while (Hero.get_hp() > 0 && check_lives_enemy(enemies)){
        if(turn){
            turn = turn_hero(enemies,Hero);
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