#pragma once
#include "item.h"
#include <vector>

class Inventory {
private:
    std::vector<Item> items;
public:
    void add_item(const Item& item);
    void print_items() const;
    int size() const;
    Item get_item(int index) const;
    void remove_item(int index);
    void clear_inventory();
};