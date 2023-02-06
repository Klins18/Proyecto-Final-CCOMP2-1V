#pragma once

#include"STLINCLUDE.h"
#include"Weapon.h"
#include"Armor.h"

class Inventario
{
private:
	int cap;
	int nrOfItems;
	Item **itemArr;
	void expand();
	void init(const int from = 0);

public:
	Inventario();
	~Inventario();
	Inventario(const Inventario &obj);
	inline int size()const { return this->nrOfItems; };
	Item& operator[](const int index);
	void operator=(const Inventario &obj);
	void addItem(const Item &item);
	void removeItem(int index);
	inline void debugPrint() const
	{
		for (size_t i = 0; i < this->nrOfItems; i++)
		{
			std::cout << this->itemArr[i]->debugPrint() << std::endl;
		}
	}
};