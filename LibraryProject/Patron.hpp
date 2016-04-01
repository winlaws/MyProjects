/********************************************************************* 
** Author: Spencer Winlaw	
** Date: March 15, 2015
** Description: Patron Header File
*********************************************************************/
#ifndef PATRON_HPP 
#define PATRON_HPP 

#include <iostream>
#include <vector> 

class LibraryItem; 

class Patron 
{
	private:
		std::string idNum; 
		std::string name; 
		std::vector<LibraryItem*> checkedOutItems;
		double fineAmount; 
	public: 
		Patron(); 
		Patron(std::string idn, std::string n); 
		std::string getIdNum();
		void setIdNum(std::string idn);
		std::string getName();
		void setName(std::string n);
		std::vector<LibraryItem*> getCheckedOutItems(); 
		void addLibraryItem(LibraryItem* b); 
		void removeLibraryItem(LibraryItem* b);
		double getFineAmount(); 
		void amendFine(double amount); 
};
#endif