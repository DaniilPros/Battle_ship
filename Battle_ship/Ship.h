#pragma once
#include<vector>
using namespace std;
class Ship
{
	bool condition;
	vector<pair<bool, pair<int, int>>> coord_of_part;
public:
	Ship(initializer_list<pair<bool,pair<int,int>>> list = {});
	~Ship();
};