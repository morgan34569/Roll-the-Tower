#ifndef INVENTORY_H
#define INVENTORY_H

#include <vector>

class Item;
class Player;
class Monster;

class Inventory {
private:
    std::vector<Item*> items;

public:
    Inventory();
    ~Inventory();

    void addItem(Item* item);
    void show(const Player& player) const;
    void open(Player& player);

    bool useItem(int index, Player& player, Monster& target);

    void showPotionNamesWithCount() const;
    int getPotionCount() const;
    int getCount() const;
    Item* getItem(int index) const;
};

#endif