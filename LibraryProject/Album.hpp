/********************************************************************* 
** Author: Spencer Winlaw	
** Date: March 15, 2015
** Description: Album Header File
*********************************************************************/
#ifndef ALBUM_HPP
#define ALBUM_HPP

#include "LibraryItem.hpp"

class Album : public LibraryItem
{
	private:
		std::string artist;
	public:
		Album();
		Album(std::string a, std::string idc, std::string t);
		static const int CHECK_OUT_LENGTH;
		std::string getAuthor();
		void setArtist(std::string a);
		virtual int getCheckOutLength();
};
#endif