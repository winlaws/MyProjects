/********************************************************************* 
** Author: Spencer Winlaw	
** Date: March 15, 2015
** Description: Library CPP File
*********************************************************************/
#include "Library.hpp"
#include <iostream>
#include <string>
#include <vector>
#include <iomanip>
using namespace std;


Library::Library()
{
	std::vector<LibraryItem*> holdings; 
	std::vector<Patron*> members; 
	int currentDate = 0; 
}
void Library::addLibraryItem(LibraryItem* item)
{
	holdings.push_back(item);
}
void Library::addMember(Patron* patron)
{
	members.push_back(patron);
}
void Library::checkOutLibraryItem(std::string patronID, std::string ItemID)
{
	LibraryItem *tempItem = findItem(ItemID);

	if(tempItem)
	{
		if(tempItem->getLocation() == CHECKED_OUT)
		{
			cout << tempItem->getTitle() << " is already checked out." << endl; 
		}
		else 
		{
			Patron *tempPatron = findPatron(patronID);

			if(tempPatron)
			{
				if(tempItem->getLocation() == ON_HOLD_SHELF)
				{
					if(tempItem->getRequestedBy() == tempPatron)
					{
						tempItem->setCheckedOutBy(tempPatron);
						tempItem->setDateCheckedOut(currentDate);
						tempItem->setLocation(CHECKED_OUT);
						tempItem->setRequestedBy(NULL);
						tempPatron->addLibraryItem(tempItem);
						cout << tempItem->getTitle() << " has been checked out by " << tempPatron->getName() << endl; 
					}
					else
					{
						cout << tempItem->getTitle() << " is on hold for another patron." << endl;
					}
				}
				else
				{
					tempItem->setCheckedOutBy(tempPatron);
					tempItem->setDateCheckedOut(currentDate);
					tempItem->setLocation(CHECKED_OUT);
					tempPatron->addLibraryItem(tempItem);
					cout << tempItem->getTitle() << " has been checked out by " << tempPatron->getName() << endl; //could put the due back date
				}
			}
			else
			{
				cout << "ERROR: Patron ID Number Does Not Match Any Library Members" << endl;
			}
			
		}
		

	}
	else
	{
		cout << "ERROR: Library Item ID Code Does Not Match Any Library Holdings." << endl;
	}
}
void Library::returnLibraryItem(std::string ItemID)
{
	LibraryItem *tempItem = findItem(ItemID);

	if(!tempItem)
	{
		cout << "ERROR: Library Item ID Code Does Not Match Any Library Holdings." << endl;
	}
	else if(tempItem->getLocation() != CHECKED_OUT)
	{
		cout << "ERROR: " << tempItem->getTitle() << " is not currently checked out" << endl;
	}
	else 
	{
		Patron *tempPatron = tempItem->getCheckedOutBy();
		tempPatron->removeLibraryItem(tempItem);
		if(tempItem->getRequestedBy())
		{
			tempItem->setLocation(ON_HOLD_SHELF);
		}
		else
		{
			tempItem->setLocation(ON_SHELF);
		}
		tempItem->setCheckedOutBy(NULL);
		cout << tempItem->getTitle() << " has been returned." << endl;
	}

}
void Library::requestLibraryItem(std::string patronID, std::string ItemID)
{
	LibraryItem *tempItem = findItem(ItemID);

	if(tempItem)
	{
		Patron *tempPatron = findPatron(patronID);

		if(tempPatron)
		{
			if(tempItem->getCheckedOutBy() && tempItem->getCheckedOutBy()->getIdNum() == tempPatron->getIdNum())
			{
					cout << tempItem->getTitle() << " is already checked out to " << tempPatron->getName() << "." << endl;
			}
			else if(tempItem->getRequestedBy())
			{
				if(tempItem->getRequestedBy()->getIdNum() == tempPatron->getIdNum())
				{
					cout << tempPatron->getName() << " has already requested " << tempItem->getTitle() << "." << endl;
				}
				else
				{
					cout << tempItem->getTitle() << " has already been requested by another patron." << endl;
				}

			}
			else
			{
				tempItem->setRequestedBy(tempPatron);
				if(tempItem->getLocation() == ON_SHELF)
				{
					tempItem->setLocation(ON_HOLD_SHELF);
				}
				cout << tempItem->getTitle() << " is on request for " << tempPatron->getName();
			}
		}
		else
		{
			cout << "ERROR: Patron ID Number Does Not Match Any Library Members" << endl;
		}
	}
	else
	{
		cout << "ERROR: Library Item ID Code Does Not Match Any Library Holdings." << endl;
	}
}
void Library::incrementCurrentDate()
{
	currentDate++;
	Patron *tempPatron;
	vector<LibraryItem*> checkedOut;
	double fines;
	int dueBack;

	for(int i = 0; i < members.size(); i++)
	{
		fines = 0;
		tempPatron = members.at(i);
		checkedOut = tempPatron->getCheckedOutItems();
		
		for(int j = 0; j < checkedOut.size(); j++)
		{
			dueBack = (checkedOut.at(j)->getDateCheckedOut() + checkedOut.at(j)->getCheckOutLength());
			if(dueBack < currentDate)
			{
				fines += (.10);
			}

		}

		tempPatron->amendFine(fines);
	}
}
void Library::payFine(std::string patronID, double payment)
{
	Patron *tempPatron = findPatron(patronID);

	if(tempPatron)
	{
		tempPatron->amendFine(-payment);
		cout << "The fines for " << tempPatron->getName() << " are now $" << fixed << setprecision(2) << tempPatron->getFineAmount() << endl;
	}
	else
	{
		cout << "ERROR: Patron ID Number Does Not Match Any Library Members" << endl;
	}
}
void Library::viewPatronInfo(std::string patronID)
{
	Patron *tempPatron = findPatron(patronID);

	if(tempPatron)
	{
		cout << tempPatron->getIdNum() << " - " << tempPatron->getName() << endl << endl
			 << "Currently Checked Out: " << endl << endl;
		
		vector<LibraryItem*> checkedOut = tempPatron->getCheckedOutItems();
		
		for(int i = 0; i < checkedOut.size(); i++)
		{
			cout << checkedOut.at(i)->getTitle() << endl;
		}
		
		cout << endl << "Current Fines: $" << fixed << setprecision(2) << tempPatron->getFineAmount() << endl;

	}
	else
	{
		cout << "ERROR: Patron ID Number Does Not Match Any Library Members" << endl;
	}
}
void Library::viewItemInfo(std::string ItemID)
{
	LibraryItem *tempItem = findItem(ItemID);
	
	if(tempItem)
	{
		cout << tempItem->getIdCode() << " - " << tempItem->getTitle() <<  " - " << tempItem->getAuthor() << endl << endl
			 << "Requested By: " ;
			 if(tempItem->getRequestedBy())
				 cout << tempItem->getRequestedBy()->getName();
		cout << endl << "Checked Out By: ";
			 if(tempItem->getCheckedOutBy())
				 cout << tempItem->getCheckedOutBy()->getName();
		cout << endl << endl << "Due Back: " ;
		
		int dueBack = tempItem->getDateCheckedOut() + tempItem->getCheckOutLength();
		
		if(!tempItem->getCheckedOutBy())
			cout << "Available" << endl;
		else if((dueBack - currentDate) == 0)	
			cout << "Today" << endl;
		else if((dueBack - currentDate) < 0)
			cout << "OVERDUE" << endl;
		else
			cout << (dueBack - currentDate) << " Days" << endl;
	}
	else
	{
		cout << "ERROR: Library Item ID Code Does Not Match Any Library Holdings." << endl;
	}
}

LibraryItem* Library::findItem(std::string ItemID)
{
	bool iFound = false;
	int hPos = 0;
	LibraryItem *tempItem = NULL;

	while(iFound == false && hPos < holdings.size())
	{
		if(holdings.at(hPos)->getIdCode() == ItemID)
		{
			tempItem = holdings.at(hPos);
			iFound = true;
		}
		hPos++;
	}

	return tempItem;
}

Patron* Library::findPatron(std::string patronID)
{
	bool pFound = false;
	int mPos = 0;
	Patron *tempPatron = NULL;

	while(pFound == false && mPos < members.size())
	{
		if(members.at(mPos)->getIdNum() == patronID)
		{
			tempPatron = members.at(mPos);
			pFound = true;
		}
		mPos++;
	}

	return tempPatron;
}