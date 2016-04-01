/********************************************************************* 
** Author: Spencer Winlaw	
** Date: March 15, 2015
** Description: Book Header File
*********************************************************************/
#ifndef BOOK_HPP
#define BOOK_HPP

#include "LibraryItem.hpp"

class Book : public LibraryItem
{
	private:
		std::string author;
	public:
		Book();
		Book(std::string a, std::string idc, std::string t);
		static const int CHECK_OUT_LENGTH;
		std::string getAuthor();
		void setAuthor(std::string a);
		virtual int getCheckOutLength();
};
#endif