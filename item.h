#pragma once
#include <string> 

class Item{
    private:
        std::string name;
        std::string type;
        int value;
    public:
        Item(std::string name, std::string type,int value);
        
        std::string get_name() const;
        std::string get_type() const;
        int get_value() const;
};