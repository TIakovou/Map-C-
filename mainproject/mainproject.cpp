

#include "pch.h"
#include <iostream>
#include <map>
#include "methods.h" //the header file with the methods

int main()
{
	cus_map<int,int > map;

	//AN EXAMPLE OF HOW THE METHODS WORK
	//Insert Keys and Values in the map.
	map.insert(1,3);
	map.insert(2,5);
	map.insert(3,6);
	map.insert(4,8);
	
	map.show_all(); //show all the elements where are in the map.
	map.delete_element(3);//delete the third key of the map.
	map.show_all();//expecting to see three keys with there values.

	map.swap(2,4);
	map.show_all(); //swap between 2 and 4.

	map.clear();//Clear all the elements from the map.

return 0;
}









