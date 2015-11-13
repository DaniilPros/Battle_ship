#pragma once
#include <vector>
#include <functional>
using namespace std;

class Ship
{
public:
	using pos = pair<int, int>;
	using part = pair<bool, Ship::pos>;

	enum class Orient { Horizontal, Vertical };

	/*
	Copies the list of arguments to the Ship::parts
	
	@param list of the parts of the ship
	*/
	Ship(initializer_list<Ship::part> list = {});
	
	/*
	Returns the killed flag of the ship

	@return Ship::killed 
	*/
	bool is_killed();

	void set_on_kill_handler(function<void(const vector<Ship::part>&)>  on_kill);
	void set_on_injure_handler(function<void(const vector<Ship::part>&)> on_injure);

	vector<Ship::part> get_parts();// return all the parts of the ship
	void set_parts(vector<Ship::part> parts);// set parts of the ship
	
	void add_part (Ship::part part); // add "part" to "this->parts"
	void delete_part (Ship::part part); // erase "part" from "this->parts"

	// return the boolean value of "part" at the "position"
	bool is_part_injured(Ship::pos pos_of_part);
	
	// set "part::first" to true of part at "pos_of_part"
	void injure_part(Ship::pos pos_of_part);
	
	void rotate(Ship::pos center, bool clockwise);

	int get_length();// return length of the ship

	~Ship();// destructor of the ship
private:
	// retutn an iterator of Ship::parts that points to the "part" with specified "pos"
	vector<Ship::part>::iterator get_part(Ship::pos pos);

	Ship::Orient orient();

	int& x(Ship::part& part) { return part.second.first; }
	int& y(Ship::part& part) { return part.second.second; }
	bool& injured(Ship::part& part) { return part.first; }

	bool all_injured();

	function<void(const Ship::pos&)> on_injure;
	function<void(const vector<Ship::part>&)> on_kill;

	bool killed;// killed of the ship
	vector<Ship::part> parts;// positions and conditions of parts of the ship
};