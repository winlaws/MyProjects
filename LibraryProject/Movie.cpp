/********************************************************************* 
** Author: Spencer Winlaw	
** Date: March 15, 2015
** Description: Movie CPP File
*********************************************************************/
#include "Movie.hpp"

const int Movie::CHECK_OUT_LENGTH = 7;

Movie::Movie() : LibraryItem()
{
	setDirector("");
}
Movie::Movie(std::string d, std::string idc, std::string t) : LibraryItem(idc, t)
{
	setDirector(d);
}
std::string Movie::getAuthor()
{
	return director;
}
void Movie::setDirector(std::string d)
{
	director = d;
}
int Movie::getCheckOutLength()
{
	return Movie::CHECK_OUT_LENGTH;
}