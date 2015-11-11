#pragma once
#include<vector>
using namespace std;
class Ship
{
	bool condition;//condition of the ship
	vector<pair<bool, pair<int, int>>> parts;//positions and conditions of parts of the ship

public:
	Ship(initializer_list<pair<bool,pair<int,int>>> list = {});//constructor with list of arguments which has pairs of conditions and positions of parts

	bool get_condition();//return condition of the ship
	void set_condition(bool condition);//set condition of the ship
	void change_condition();//change condition of the ship on the opposite

	vector<pair<bool, pair<int, int>>> get_parts();//return all the parts of the ship
	void set_parts(vector<pair<bool, pair<int, int>>> parts);//set parts of the ship

	pair<bool, pair<int, int>> get_part(int index_of_part);//return a part of the ship by index
	void set_part(int index_of_part, pair<bool, pair<int, int>> part);//set a part of the ship by index
	void add_part(pair<bool, pair<int, int>> part);//add a part of the ship
	
	bool get_condition_of_part(int index_of_part);//return condition of part by index
	void set_condition_of_part(int index_of_part, bool condition);//set condition of part by index
	void change_condition_of_part(int index_of_part);//change condition of part by index on the opposite
	
	pair<int, int> get_position_of_part(int index_of_part);//return position of part by index
	void set_position_of_part(int index_of_part, pair<int, int>);//set position of part by index

	int get_length();//return length of the ship

	~Ship();//destructor of the ship
};