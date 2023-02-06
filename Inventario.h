#pragma once
#include"Item.h"

class Inventario{
    private:
	    int cap;
	    int nrOfItems;
	    Item **itemArr;
	    void expand();
	    void initialize(const int from);
    public:
	    Inventario();
	    ~Inventario();
	    void addItem(const Item &item);
	    void removeItem(int index);
};
