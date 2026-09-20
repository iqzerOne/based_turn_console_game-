#include <iostream>
#include <string>
#include <vector>
#include <limits>
#include <fstream>
#include "constants.h"
#include "Character.h"
#include "Player.h"
#include "Enemy.h"
#include "item.h"
#include "inventory.h"

void save_game(const Player& hero,const std::vector<Enemy>& enemies, int wave){
    std::ofstream outFile("save.txt");
    if(outFile.is_open()){
        outFile << hero.get_hp() << "\n";
        outFile << hero.get_attack_damage() << "\n";
        outFile << hero.inventory_size() << "\n";
        for(int i = 0; i < hero.inventory_size(); i++){
            Item item = hero.use_item_player(i);
            outFile << item.get_name()<< " " << item_type_to_string(item.get_type())<< " " << item.get_value() << "\n";
        }
        outFile << wave << "\n";
        outFile << enemies.size() << "\n";
        for(int i = 0; i < enemies.size(); i++){
            outFile << enemies[i].get_name() << " " << enemies[i].get_hp() << " " << enemies[i].get_attack_damage() << "\n";
        }
        outFile.close(); 
        std::cout << "Game successfully saved!" << std::endl;
    }else{
        std::cout << "File not open" << std::endl;
    }
    
}

int load_game(Player& hero, std::vector<Enemy>& enemies, int wave){
    std::ifstream inFile("save.txt");
    if(inFile.is_open()){
        hero.clear_inventory_player();
        enemies.clear();
        int count_item = 0;
        int count_enemy = 0;
        int hp = 0;
        int dmg = 0;
        std::string type = "";
        std::string name = "";
        int value  = 0;
        inFile >> hp;
        inFile >> dmg; 
        inFile >> count_item;
        hero.set_hp(hp);
        hero.set_damage(dmg);
        for(int i = 0; i < count_item; i++){
            inFile >> name;
            inFile >> type; 
            inFile >> value;
            hero.add_item_player(Item(name, string_to_item_type(type), value));
        }
        inFile >> wave;
        inFile >> count_enemy;
        for(int i = 0; i < count_enemy; i++){
            inFile >> name;
            inFile >> hp;
            inFile >> dmg;
            enemies.push_back(Enemy(name,hp,dmg));
        }
        std::cout << "Hero loaded " << hero.get_hp() << " hp\n " << hero.get_attack_damage() << " damage\n" << std::endl;
        hero.print_inventory();
        inFile.close();
        return wave;
    }else{
        std::cout << "File not found" << std::endl;
        return wave;
    }
}

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

int input_choice(int min, int max){
    int choice = 0;
    while(true){
       while (!(std::cin >> choice)) {
            std::cout << "Err, pls input number: " << std::endl;
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        }
        if(choice < min || choice > max){
            std::cout << "Invalid choice" << std::endl;
        }else{
            return choice;
        }
    }
}

int check_inventory(Player& hero){
    hero.print_inventory();
    int choice = input_choice(1,hero.inventory_size());
    return choice;
}

int turn_hero(std::vector <Enemy>& enemies, Player& hero){
    hero.print_inventory();
    print_enemy(enemies);
    int choice = 0;
    while(!choice){
        std::cout << "Choice action (1-Attack, 2-Use item, 3-Skip turn, 4-Save/Load, 5-Exit): "  << std::endl;
        choice = input_choice(1,5);
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
        choice = input_choice(1,enemies.size());
        choice = check_enemy_hp(choice,enemies);
    }
    damage_character(enemies[choice-1],hero.get_attack_damage());
    return false;
}

void use_item(Player& hero){
    int index = check_inventory(hero) - 1;
    Item item = hero.use_item_player(index);
    if(item.get_type() == ItemType::Potion){
        hero.heal_hero(item.get_value());
    }else if(item.get_type() == ItemType::Weapon){
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

int save_load_game(Player& hero, std::vector<Enemy>& enemies, int wave){
    std::cout << "Choice 1-Save or 2-Load" << std::endl;
    int choice = input_choice(1,2);
    if(choice == 1){
        save_game(hero,enemies,wave);
    }else if(choice == 2){
        wave = load_game(hero,enemies,wave);
    }
    return wave;
}

std::string play_game(bool load){
    Player hero("Hero", Constants::HP_HERO,Constants::DAMAGE_HERO);
    std::vector<Enemy> enemies;
    bool turn = true;
    int wave = 1;
    if(load){
        wave = load_game(hero,enemies,wave);
    }else{
        hero.add_item_player(Item("Potion", ItemType::Potion, 20));
        hero.add_item_player(Item("Sword", ItemType::Weapon, 5));
        add_enemy(enemies,wave);
    }
    while (hero.get_hp() > 0 && check_lives_enemy(enemies)){
        if(turn){
            int choice_hero = turn_hero(enemies,hero);
            if(choice_hero == 1){
                turn = turn_hero_attack(enemies,hero);
            }else if(choice_hero == 2){
                turn = false;
                use_item(hero);
            }else if (choice_hero == 3) {
                // turn = defense_hero();
                turn = false;
            }else if(choice_hero == 4){
                wave = save_load_game(hero,enemies,wave);
            }else if(choice_hero == 5){
                return "main";
            }
        }else{
            turn = move_enemy(enemies,hero);
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
    if (hero.get_hp() > 0){
        std::cout << "Winner:" << std::endl;
        print_character(hero);
    }else{
        std::cout << "Player lose" << std::endl;
        for(int i = 0; i < enemies.size(); i++){
            print_character(enemies[i]);
        }
    }
    return "main";
}

std::string main_menu(){
    std::cout << "Choice number" << std::endl;
    std::cout << "1.Play\n2.Load\n3.Exit" << std::endl;
    int choice = input_choice(1,3);
    if(choice == 1){
        return "play";
    }else if(choice == 2){
        return "load";
    }else if(choice == 3){
        return "exit";
    }
    return "exit";
}

void start(){
    std::string state = "main";
    while(true){
        if(state == "main"){
            state = main_menu();
        }else if(state == "exit"){
            return;
        }else if(state == "play"){
            state = play_game(false);
        }else if(state == "load"){
            std::ifstream inFile("save.txt");
            if(inFile.is_open()){
                inFile.close();
                state = play_game(true);
            }else{
                std::cout << "Not found save game" << std::endl;
                state = "main";
            }
            
        }
    }
}


int main() {
    start();
}