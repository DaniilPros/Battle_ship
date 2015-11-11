#include "Ship.h"


Ship::Ship(initializer_list<pair<bool, pair<int, int>>> list)
{
	this->parts.insert(this->parts.end(), list.begin(), list.end());
	this->condition = true;
}

bool Ship::get_condition()
{
	return this->condition;
}

void Ship::set_condition(bool condition)
{
	this->condition = condition;
}

void Ship::change_condition()
{
	this->condition = this->condition ? false : true;
}

vector<pair<bool, pair<int, int>>> Ship::get_parts()
{
	return this->parts;
}

void Ship::set_parts(vector<pair<bool, pair<int, int>>> parts)
{
	this->parts = parts;
}

pair<bool, pair<int, int>> Ship::get_part(int index_of_part)
{
	return parts[index_of_part];
}

void Ship::set_part(int index_of_part, pair<bool, pair<int, int>> part)
{
	this->parts[index_of_part] = part;
}

void Ship::add_part(pair<bool, pair<int, int>> part)
{
	this->parts.push_back(part);
}

bool Ship::get_condition_of_part(int index_of_part)
{
	return this->parts[index_of_part].first;
}

void Ship::set_condition_of_part(int index_of_part, bool condition)
{
	this->parts[index_of_part].first = condition;
}

void Ship::change_condition_of_part(int index_of_part)
{
	this->parts[index_of_part].first = this->parts[index_of_part].first ? false : true;
}

pair<int, int> Ship::get_position_of_part(int index_of_part)
{
	return this->parts[index_of_part].second;
}

void Ship::set_position_of_part(int index_of_part, pair<int, int> position_of_part)
{
	this->parts[index_of_part].second = position_of_part;
}

int Ship::get_length()
{
	return this->parts.size();
}

Ship::~Ship()
{
}
