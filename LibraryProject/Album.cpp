/********************************************************************* 
** Author: Spencer Winlaw	
** Date: March 15, 2015
** Description: Album CPP File
*********************************************************************/
#include "Album.hpp"

const int Album::CHECK_OUT_LENGTH = 14;

Album::Album() : LibraryItem()
{
	setArtist("");
}
Album::Album(std::string a, std::string idc, std::string t) : LibraryItem(idc, t)
{
	setArtist(a);
}
std::string Album::getAuthor()
{
	return artist;
}
void Album::setArtist(std::string a)
{
	artist = a;
}
int Album::getCheckOutLength()
{
	return Album::CHECK_OUT_LENGTH;
}