/********************************************************************* 
** Author: Spencer Winlaw	
** Date: March 15, 2015
** Description: Displays Library Menu and Performs Selected Functions
*********************************************************************/
#include "Library.hpp"
#include "Patron.hpp"
#include "Book.hpp"
#include "Album.hpp"
#include "Movie.hpp"
#include <iostream>
#include <cstdlib>
#include <string>
using namespace std;

void displayMenu();
LibraryItem* getLibraryItem();
Patron* getMember();

int main()
{
	system("clear");
	
	int selection;
	string patronID,
		   itemID;
	double payment;
	Library library;
	
	do
	{
		displayMenu();
		cin >> selection;
		cin.ignore();

		system("clear");

		switch(selection)
		{
			// Add Library Item
			case 1 :library.addLibraryItem(getLibraryItem());
					break;
			// Add Member
			case 2 :library.addMember(getMember());
					break;
			// Check Out Lib Item
			case 3 :cout << "Input ID Number of Patron." << endl;
					getline(cin, patronID);
					cout << "Input ID Code of Library Item to be checked out." << endl;
					getline(cin, itemID);
					system("clear");
					library.checkOutLibraryItem(patronID, itemID);
					break;
			//Return Lib Item
			case 4 :cout << "Input ID Code of Library Item to be returned." << endl;
					getline(cin, itemID);
					system("clear");
					library.returnLibraryItem(itemID);
					break;
			//Request Lib Item
			case 5 :cout << "Input ID Number of Patron." << endl;
					getline(cin, patronID);
					cout << "Input ID Code of Library Item being requested." << endl;
					getline(cin, itemID);
					system("clear");
					library.requestLibraryItem(patronID, itemID);
					break;
			//Pay Fine
			case 6 :cout << "Input ID Number of Patron." << endl;
					getline(cin, patronID);
					cout << "Input the payment amount." << endl;
					cin >> payment;
					cin.ignore();
					system("clear");
					library.payFine(patronID, payment);
					break;
			//Increment Current Date
			case 7 :library.incrementCurrentDate();
					cout << "Date has been incremented" << endl;
					break;
			// View Patron Info
			case 8 :cout << "Input ID Number of Patron." << endl;
					getline(cin, patronID);
					system("clear");
					library.viewPatronInfo(patronID);
					break;
			//View Item Info
			case 9 :cout << "Input ID Code of Library Item." << endl;
					getline(cin, itemID);
					system("clear");
					library.viewItemInfo(itemID);
					break;
			//Quit
			case 10:break;
			default: cout << "Invalid selection" << endl; 
		}
		
		if(selection != 10)
		{
			cout << endl << "Press <Enter> to return to menu" << endl;
			cin.get();
			system("clear");
		}

	}while(selection != 10);

	return 0;
}

/********************************************************************* 
** Description: Displays Library Menu
** Parameters: None
*********************************************************************/
void displayMenu()
{
	cout << "Library Menu:" << endl
		 << "1) Add Library Item" << endl
		 << "2) Add Member" << endl
		 << "3) Check Out Library Item" << endl
		 << "4) Return Library Item" << endl
		 << "5) Request Library Item" << endl
		 << "6) Pay Fine" << endl
		 << "7) Increment Current Date" << endl
		 << "8) View Patron Information " << endl
		 << "9) View Item Information" << endl
		 << "10) Quit" << endl << endl
		 << "Enter selection from menu:" << endl;
}

/********************************************************************* 
** Description: Gets a Library Item from the user
** Parameters: none
*********************************************************************/
LibraryItem* getLibraryItem()
{
	int type;
	string itemID,
		   title,
		   author;
	LibraryItem* item;
	
	cout << "Input item type." << endl
		 << "Enter (1) for book, (2) for album, or (3) for movie." << endl;
	cin >> type;

	while(type < 1 || type > 3)
	{
		cout << endl << "ERROR: Invalid Input." << endl
			 << "Input item type." << endl
			 << "Enter (1) for book, (2) for album, or (3) for movie." << endl;
		cin >> type;
		
	}
	
	system("clear");
	cin.ignore();
	
	//gets book info
	if(type == 1)
	{
		cout << "Input the ID code for the book." << endl;
		getline(cin, itemID);
		cout << endl << "Input the title of the book." << endl;
		getline(cin, title);
		cout << endl << "Input the author of the book." << endl;
		getline(cin, author);

		item = new Book(author, itemID, title);
	}

	//gets album info
	else if(type == 2)
	{
		cout << "Input the ID code for the album." << endl;
		getline(cin, itemID);
		cout << endl << "Input the title of the album." << endl;
		getline(cin, title);
		cout << endl << "Input the artist of the album." << endl;
		getline(cin, author);

		item = new Album(author, itemID, title);
	}
	
	//gets movie info
	else
	{
		cout << "Input the ID code for the movie." << endl;
		getline(cin, itemID);
		cout << endl << "Input the title of the movie." << endl;
		getline(cin, title);
		cout << endl << "Input the director of the movie." << endl;
		getline(cin, author);

		item = new Movie(author, itemID, title);
	}

	return item;
}

/********************************************************************* 
** Description: Gets a Library Item from the user
** Parameters: none
*********************************************************************/
Patron* getMember()
{
	string patronID,
		   name;
	Patron* patron;
	
	cout << "Input ID Number of Patron." << endl;
	getline(cin, patronID);
	cout << endl << "Input the Name of Patron." << endl;
	getline(cin, name);

	patron = new Patron(patronID, name);

	return patron;
}