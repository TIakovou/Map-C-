#include "pch.h"
#include <iostream>
using namespace std;


 
template <typename T, typename N> //template map class
class cus_map
{
	
	 //brief Maximum number of items that the map can contain
	// before doubling its size.
	 
	int mnumberofitems = 10; //minimum number of items
	T* keys_ = nullptr; // Dynamic array of keys
	N* values_ = nullptr; //Dynamic array of values
	int curposs = 0;//Current possition of the array.

	void expand();
public: // the elements where are public in the map
	cus_map();
	~cus_map();
	void insert(T key, N value); //insert function
	void show_all(); //show_all function
	void delete_element(T key); //delete_element function
	void clear();//clear all function
	void swap(T key_01, T key_02); //swap function
};


 //Double the size of the arrays.
 
template <typename T, typename N>
void cus_map<T, N>::expand()
{
	const auto temp_number_of_items = mnumberofitems;
	mnumberofitems *= 2;
	T* new_keys = new T[mnumberofitems];
	N* new_values = new N[mnumberofitems];

	for (auto i = 0; i < temp_number_of_items; i++)
	{
		new_keys[i] = keys_[i];
		new_values[i] = values_[i];
	}

	delete[] keys_;
	delete[] values_;

	keys_ = new T[mnumberofitems];
	values_ = new N[mnumberofitems];

	for (auto i = 0; i < temp_number_of_items; i++)
	{
		keys_[i] = new_keys[i];
		values_[i] = new_values[i];
	}

	delete[] new_keys;
	delete[] new_values;
}



  //Free the allocated memory.
 
template <typename T, typename N>
cus_map<T, N>::cus_map()
{
	keys_ = new T[mnumberofitems];
	values_ = new N[mnumberofitems];
}


 //Map destructor which frees the allocated arrays.
 
template <typename T, typename N>
cus_map<T, N>::~cus_map()
{
	delete[] keys_; 
	delete[] values_;
}


//Insert an element in the container.
template <typename T, typename N>
void cus_map<T, N>::insert(T key, N value)
{
	// check if the key exists in the map , 
	//if the key exist in the map the program can not add key in the map,
	//otherwise if the key is not exist in the map the expand function double the size of the array
	//and we can insert key and value in the map.


	auto key_exists = false;
	for (auto index = 0; index < curposs; index++) 
	{
		if (keys_[index] == key) 
		{
			key_exists = true;
			break;
		}
	}

	if (key_exists)
	{
		cout << "Unable to insert the element [key: " << key << ", value: " << value << "]! Key [" << key << "] already exists!" << endl;
		return;
	}

	if (curposs >= mnumberofitems)
	{
		expand();
	}

	keys_[curposs] = key;
	values_[curposs] = value;
	++curposs;

	cout << "Inserted item [key: " << key << ", value: " << value << "]!" << endl;
}


//Check if the current possition is greater than the 0
//If the current possition is greater than 0, for loop all the elelemnts of the map and cout all the elements.
//Otherwise if the current position is less than 0 the program cout that map is empty.
 
template <typename T, typename N>
void cus_map<T, N>::show_all()
{
	if (curposs> 0) 
	{
		for (auto i = 0; i < curposs; i++) 
		{
			cout << "Item " << i << " [key: " << keys_[i] << ", value: " << values_[i] << "]!" << endl;
		}
	}
	else 
	{
		cout << "The container is empty!" <<endl;
	}

		cout << endl;
}

//Delete a spesific key for the map
template <typename T, typename N>
void cus_map<T, N>::delete_element(T key)
{
	// check if the key exists 
	auto key_exists = false;
	for (auto index = 0; index < curposs; index++)
	{
		if (keys_[index] == key)  
		{
			key_exists = true;
			break;
		}
	}
	
	if (!key_exists)
	{
		cout << "Unable to delete the element! Key [" << key << "] does not exist!" << endl;
		return;
	}

	// shift all keys to the left starting with the position of the key to delete
	auto shift_left = false;
	for (auto index = 0; index < curposs; index++)
	{
		if (keys_[index] == key)
		{
			shift_left = true;
		}

		if (shift_left)
		{
			keys_[index] = keys_[index + 1];
			values_[index] = values_[index + 1];
		}
	}

	// decrement current position
	curposs--;

	// clear memory in order to avoid memory leak
	memset(static_cast<void*>(keys_ + curposs), 0, sizeof(T));
	memset(static_cast<void*>(values_ + curposs), 0, sizeof(N));
}


 
 //Clear all the elements for the map(key and values)
template <typename T, typename N>
void cus_map<T, N>::clear() 
{
	mnumberofitems = 10;

	delete[] keys_; 
	delete[] values_;

	keys_ = new T[mnumberofitems]; 
	values_ = new N[mnumberofitems];
	cout << "Empty map" << std::endl;
}

//Swap the order of the 2 key in the keys array (and values as well).
template <typename T, typename N>
void cus_map<T, N>::swap(T key_01, T key_02)
{
	// check if you have the same key as arguments
	if (key_01 == key_02)
	{
		cout << "Unable to swap the requested keys! Keys are the same!" << endl;
		return;
	}

	// check if you have the requested keys in your container
	auto key_01_index = -1;
	auto key_02_index = -1;

	for (auto index = 0; index < curposs; index++)
	{
		if (key_01 == keys_[index])
		{
			key_01_index = index;
		}

		if (key_02 == keys_[index])
		{
			key_02_index = index;
		}

		if (key_01_index != -1 && key_02_index != -1)
		{
			break;
		}
	}

	if (key_01_index == -1 || key_02_index == -1)
	{
		cout << "Unable to swap the requested keys!" << endl;

		if (key_01_index == -1)
		{
		cout << "Key [" << key_01 << "] not found!" << endl;
		}

		if (key_02_index == -1)
		{
			cout << "Key [" << key_02 << "] not found!" << endl;
		}

		return;
	}

	// swap the 2 keys
	std::swap(keys_[key_01_index], keys_[key_02_index]);
	std::swap(values_[key_01_index], values_[key_02_index]);
}

