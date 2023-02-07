#include "Inventory.h"

Inventario::Inventario()
{
	this->cap = 5;
	this->nrOfItems = 0;
	this->itemArr = new Item*[cap];
	this->init();
}

Inventario::~Inventario()
{
	for (size_t i = 0; i < this->nrOfItems; i++)
	{
		delete this->itemArr[i];
	}
	delete[] this->itemArr;
}

Inventario::Inventario(const Inventario&obj)
{
	this->cap = obj.cap;
	this->nrOfItems = obj.nrOfItems;
	this->itemArr = new Item*[this->cap];

	for (size_t i = 0; i < this->nrOfItems; i++)
	{
		this->itemArr[i] = obj.itemArr[i]->clone();
	}

	init(this->nrOfItems);
}

Item& Inventario::operator[](const int index)
{
	if (index < 0 || index >= this->nrOfItems)
		throw("Indice incorrecto!");

	return *this->itemArr[index];
}

void Inventario::operator=(const Inventario&obj)
{
	for (size_t i = 0; i < this->nrOfItems; i++)
	{
		delete this->itemArr[i];
	}
	delete[] this->itemArr;

	this->cap = obj.cap;
	this->nrOfItems = obj.nrOfItems;
	this->itemArr = new Item*[this->cap];

	for (size_t i = 0; i < this->nrOfItems; i++)
	{
		this->itemArr[i] = obj.itemArr[i]->clone();
	}

	init(this->nrOfItems);
}

void Inventario::expand()
{
	this->cap *= 2;

	Item **tempArr = new Item*[this->cap];

	for (size_t i = 0; i < this->nrOfItems; i++)
	{
		tempArr[i] = this->itemArr[i];
	}

	delete[] this->itemArr;

	this->itemArr = tempArr;

	this->init(this->nrOfItems);
}

void Inventario::init(const int from)
{
	for (size_t i = from; i < cap; i++)
	{
		this->itemArr[i] = nullptr;
	}
}

void Inventario::addItem(const Item &item)
{
	if (this->nrOfItems >= this->cap)
	{
		expand();
	}

	this->itemArr[this->nrOfItems++] = item.clone();
}

void Inventario::removeItem(int index)
{
	if (index < 0 || index >= this->nrOfItems)
		throw("LIMITE EXCEDIDO, ELIMINAR ITEM");

	delete this->itemArr[index];
	this->itemArr[index] = this->itemArr[this->nrOfItems - 1];
	this->itemArr[--this->nrOfItems] = nullptr;
}