#ifndef ITEMSTORAGE_H
#define ITEMSTORAGE_H
#include <vector>
#include "Item.h"

class ItemStorage {
private:
    std::vector<Item*> items;
public:
    ItemStorage();
    ~ItemStorage();
    void addItem(Item* item);
    int getCount() const;
    Item* getItem(int index) const;
    Item* findByCode(int code) const;
};
#endif
