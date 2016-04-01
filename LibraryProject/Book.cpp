/********************************************************************* 
** Author: Spencer Winlaw	
** Date: March 15, 2015
** Description: Book CPP File
*********************************************************************/
#include "Book.hpp"

const int Book::CHECK_OUT_LENGTH = 21;

Book::Book() : LibraryItem()
{
	setAuthor("");
}
Book::Book(std::string a, std::string idc, std::string t) : LibraryItem(idc, t)
{
	setAuthor(a);
}
std::string Book::getAuthor()
{
	return author;
}
void Book::setAuthor(std::string a)
{
	author = a;
}
int Book::getCheckOutLength()
{
	return Book::CHECK_OUT_LENGTH;
}