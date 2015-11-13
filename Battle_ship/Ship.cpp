#include "Ship.h"
#include <algorithm>

Ship::Ship(initializer_list<Ship::part> list):
	on_injure{nullptr},
	on_kill{nullptr},
	killed{false},
	parts{list} {}

bool Ship::is_killed() {
	return this->killed;
}

void Ship::set_on_kill_handler(function<void(const vector<Ship::part>&)> on_kill) {
	this->on_kill = on_kill;
}

void Ship::set_on_injure_handler(function<void(const vector<Ship::part>&)> on_injure) {
	this->on_injure = on_injure;
}

vector<Ship::part> Ship::get_parts() {
	return this->parts;
}

void Ship::set_parts(vector<Ship::part> parts) {
	this->parts = parts;
}

void Ship::add_part(Ship::part part) {
	this->parts.push_back(part);
}

void Ship::delete_part(Ship::part part) {
	auto pos = find(this->parts.begin(), this->parts.end(), part);

	if (pos != this->parts.end())
		this->parts.erase(pos);
}

bool Ship::is_part_injured(Ship::pos pos_of_part) {
	auto part = this->get_part(pos_of_part);

	return part != this->parts.end() ? this->injured(*part) : false;
}

void Ship::injure_part(Ship::pos pos_of_part) {
	auto part = this->get_part(pos_of_part);

	if (part != this->parts.end() && !this->injured(*part)) {
		this->injured(*part) = true;
		if (this->on_injure)
			on_injure(pos_of_part);
		if (this->all_injured()) {
			this->killed = true;
			if (this->on_kill)
				on_kill(this->parts);
		}
	}
}

void Ship::rotate(Ship::pos center_pos, bool clockwise) {
	auto center = this->get_part(center_pos);

	switch (this->orient()) {
	case Orient::Horizontal:
		for (auto i = this->parts.begin(); i != this->parts.end(); ++i) {
			this->x(*i) = this->x(*center);
			this->y(*i) += distance(i, center) * (clockwise ? -1 : 1);
		}
		break;
	case Orient::Vertical:
		for (auto i = this->parts.begin(); i != this->parts.end(); ++i) {
			this->x(*i) += distance(i, center) * (clockwise ? 1 : -1);
			this->y(*i) = this->y(*center);
		}
		break;
	}
}

int Ship::get_length() {
	return this->parts.size();
}

Ship::~Ship() {}

vector<Ship::part>::iterator Ship::get_part(Ship::pos pos) {
	return find_if(this->parts.begin(), this->parts.end(), [&](const Ship::part& p) {return p.second == pos; });
}

Ship::Orient Ship::orient() {
	return
		this->parts.front().second.first - this->parts.back().second.first == 0 ?
		Ship::Orient::Horizontal :
		Ship::Orient::Vertical;
}

bool Ship::all_injured() {
	return find_if_not(this->parts.begin(), this->parts.end(), [](Ship::part& p) {return p.first; }) == this->parts.end();
}