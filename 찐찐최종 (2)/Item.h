#ifndef ITEM_H
#define ITEM_H
#include <string>

class Player;
class Monster;

class Item {
protected:
    int code;
    std::string name;
    int price;

public:
    Item(int code, std::string name, int price) : code(code), name(name), price(price) {}
    virtual ~Item() {}
    int getCode() const { return code; }
    std::string getName() const { return name; }
    int getPrice() const { return price; }
    virtual void Use(Player& player, Monster& monster) = 0;
    virtual Item* clone() const = 0;
};
#endif