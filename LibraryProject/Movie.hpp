/********************************************************************* 
** Author: Spencer Winlaw	
** Date: March 15, 2015
** Description: Movie Header File
*********************************************************************/
#ifndef MOVIE_HPP
#define MOVIE_HPP

#include "LibraryItem.hpp"

class Movie : public LibraryItem
{
	private:
		std::string director;
	public:
		Movie();
		Movie(std::string d, std::string idc, std::string t);
		static const int CHECK_OUT_LENGTH;
		std::string getAuthor();
		void setDirector(std::string d);
		virtual int getCheckOutLength();
};
#endif