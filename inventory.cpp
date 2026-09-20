#include "item.h"
#include "inventory.h"
#include <iostream>
#include <vector>

void Inventory::add_item(const Item& item){
    items.push_back(item);
}

int Inventory::size()const{
    return items.size();
}



void Inventory::print_items()const{
    if(items.size() > 0){
        for(int i = 0; i < items.size(); i++){
            std::cout << "Name: "<< items[i].get_name()<<" Type: "<< item_type_to_string(items[i].get_type()) <<" Value: " << items[i].get_value() << std::endl;
        }
    }
}

Item Inventory::get_item(int index) const{
    return items[index];
}

void Inventory::remove_item(int index){
    if(index < 0 || index >= items.size()){
        std::cout << "Item not found" << std::endl;
        return;
    }
    items.erase(items.begin() + index);
}

void Inventory::clear_inventory(){
    if(items.size() > 0){
        items.clear();
    }
}