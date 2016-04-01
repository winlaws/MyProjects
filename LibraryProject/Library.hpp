#ifndef LIBRARY_HPP
#define LIBRARY_HPP
/********************************************************************* 
** Author: Spencer Winlaw	
** Date: March 15, 2015
** Description: Library Header File
*********************************************************************/
#include "LibraryItem.hpp"
#include "Patron.hpp"
#include <iostream>
#include <vector> 

class Patron; 
class LibraryItem; 

class Library 
{ 
	private: 
		std::vector<LibraryItem*> holdings; 
		std::vector<Patron*> members; 
		int currentDate; 
	
	public: 
		Library();
		void addLibraryItem(LibraryItem*); 
		void addMember(Patron*); 
		void checkOutLibraryItem(std::string patronID, std::string ItemID); 
		void returnLibraryItem(std::string ItemID); 
		void requestLibraryItem(std::string patronID, std::string ItemID); 
		void incrementCurrentDate(); 
		void payFine(std::string patronID, double payment); 
		void viewPatronInfo(std::string patronID); 
		void viewItemInfo(std::string ItemID);
		LibraryItem* findItem(std::string ItemID);
		Patron* findPatron(std::string patronID);
};
#endif