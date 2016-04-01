/********************************************************************* 
** Author: Spencer Winlaw	
** Date: March 15, 2015
** Description: Patron CPP File
*********************************************************************/
#include "Patron.hpp"
#include "LibraryItem.hpp"

#include <iostream>
#include <string>
#include <vector>

Patron::Patron()
{
	setIdNum(""); 
	setName(""); 
	std::vector<LibraryItem*> checkedOutItems;
	fineAmount = 0; 
}
Patron::Patron(std::string idn, std::string n)
{
	setIdNum(idn); 
	setName(n); 
	std::vector<LibraryItem*> checkedOutItems;
	fineAmount = 0; 
}
std::string Patron::getIdNum()
{
	return idNum;
}
void Patron::setIdNum(std::string idn)
{
	idNum = idn;
}
std::string Patron::getName()
{
	return name;
}
void Patron::setName(std::string n)
{
	name = n;
}
std::vector<LibraryItem*> Patron::getCheckedOutItems()
{
	return checkedOutItems;
}
void Patron::addLibraryItem(LibraryItem* b)
{
	checkedOutItems.push_back(b);
}
void Patron::removeLibraryItem(LibraryItem* b)
{
	int place = 0;
	std::vector<LibraryItem*>::iterator iter = checkedOutItems.begin();
	while(checkedOutItems.at(place)->getIdCode() != b->getIdCode())
	{
		place++;
		iter++;
	}
	checkedOutItems.erase(iter);
}
double Patron::getFineAmount()
{
	return fineAmount;
}
void Patron::amendFine(double amount)
{
	fineAmount += amount;
}