/********************************************************************* 
** Author: Spencer Winlaw	
** Date: March 15, 2015
** Description: LibraryItem Header File
*********************************************************************/
#include "LibraryItem.hpp"

LibraryItem::LibraryItem()
{
	setIdCode(""); 
	setTitle(""); 
	setLocation(ON_SHELF); 
	setCheckedOutBy(NULL); 
	setRequestedBy(NULL); 
	setDateCheckedOut(NULL); 
}
LibraryItem::LibraryItem(std::string idc, std::string t) 
{
		setIdCode(idc); 
		setTitle(t); 
		setLocation(ON_SHELF); 
		setCheckedOutBy(NULL); 
		setRequestedBy(NULL);
		setDateCheckedOut(NULL); 
}
std::string LibraryItem::getIdCode()
{
	return idCode;
}
void LibraryItem::setIdCode(std::string idc)
{
	idCode = idc;
}
std::string LibraryItem::getTitle()
{
	return title;
}
void LibraryItem::setTitle(std::string t)
{
	title = t;
}
Locale LibraryItem::getLocation() 
{
	return location;
}
void LibraryItem::setLocation(Locale lo)
{
	location = lo;
}
Patron* LibraryItem::getCheckedOutBy()
{
	return checkedOutBy;
}
void LibraryItem::setCheckedOutBy(Patron* p)
{
	checkedOutBy = p;
}
Patron* LibraryItem::getRequestedBy()
{
	return requestedBy;
}
void LibraryItem::setRequestedBy(Patron* p)
{
	requestedBy = p;
}
int LibraryItem::getDateCheckedOut() 
{
	return dateCheckedOut;
}
void LibraryItem::setDateCheckedOut(int d)
{
	dateCheckedOut = d;
}