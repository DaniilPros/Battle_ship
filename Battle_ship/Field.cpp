#include "Field.h"
#include <algorithm>
Field::Field()
{
}


Field::~Field()
{
}
//
//void Field::Ship::set_on_kill_handler(function<void(const vector<Field::Ship::part>&)> on_kill) {
//	this->on_kill = on_kill;
//}
//
//void Field::Ship::set_on_injure_handler(function<void(const vector<Field::Ship::part>&)> on_injure) {
//	this->on_injure = on_injure;
//}
//
//vector<Field::Ship::part> Field::Ship::get_parts() {
//	return this->parts;
//}
//
//void Field::Ship::set_parts(vector<Field::Ship::part> parts) {
//	this->parts = parts;
//}
//
//void Field::Ship::add_part(Field::Ship::part part) {
//	this->parts.push_back(part);
//}
//
//void Field::Ship::delete_part(Field::Ship::part part) {
//	auto pos = find(this->parts.begin(), this->parts.end(), part);
//
//	if (pos != this->parts.end())
//		this->parts.erase(pos);
//}
//
//bool Field::Ship::is_part_injured(Field::Ship::pos pos_of_part) {
//	auto part = this->get_part(pos_of_part);
//
//	return part != this->parts.end() ? this->injured(*part) : false;
//}
//
//void Field::Ship::injure_part(Field::Ship::pos pos_of_part) {
//	auto part = this->get_part(pos_of_part);
//
//	if (part != this->parts.end() && !this->injured(*part)) {
//		this->injured(*part) = true;
//		if (this->on_injure)
//			on_injure(pos_of_part);
//		if (this->all_injured()) {
//			this->killed = true;
//			if (this->on_kill)
//				on_kill(this->parts);
//		}
//	}
//}
//
//void Field::Ship::rotate(Field::Ship::pos center_pos, bool clockwise) {
//	auto center = this->get_part(center_pos);
//
//	switch (this->orient()) {
//	case Orient::Horizontal:
//		for (auto i = this->parts.begin(); i != this->parts.end(); ++i) {
//			this->x(*i) = this->x(*center);
//			this->y(*i) += distance(i, center) * (clockwise ? -1 : 1);
//		}
//		break;
//	case Orient::Vertical:
//		for (auto i = this->parts.begin(); i != this->parts.end(); ++i) {
//			this->x(*i) += distance(i, center) * (clockwise ? 1 : -1);
//			this->y(*i) = this->y(*center);
//		}
//		break;
//	}
//}
//
//int Field::Ship::get_length() {
//	return this->parts.size();
//}
//
//Field::Ship::~Ship() {}
//
//vector<Field::Ship::part>::iterator Field::Ship::get_part(Field::Ship::pos pos) {
//	return find_if(this->parts.begin(), this->parts.end(), [&](const Field::Ship::part& p) {return p.second == pos; });
//}
//
//Field::Ship::Orient Field::Ship::orient() {
//	return
//		this->parts.front().second.first - this->parts.back().second.first == 0 ?
//		Field::Ship::Orient::Horizontal :
//		Field::Ship::Orient::Vertical;
//}
//
//bool Field::Ship::all_injured() {
//	return find_if_not(this->parts.begin(), this->parts.end(), [](Field::Ship::part& p) {return p.first; }) == this->parts.end();
//}

Field::Ship::Ship (Point start_point, Point end_point){
	if (start_point.x == end_point.x)
		for (size_t i = start_point.y; i <= end_point.y; i++)
			this->parts.emplace_back(start_point.x, int(i));
	else
		for (size_t i = start_point.x; i <= end_point.x; i++)
			this->parts.emplace_back(i, start_point.x);
}

Field::Ship::Ship (Parts& parts) : parts{parts}
{
}

bool Field::Ship::is_killed () {
	return this->killed;
}

void Field::Ship::set_on_kill_handler (function<void(const Parts&)> on_kill) {
	this->on_kill = on_kill;
}

void Field::Ship::set_on_injure_handler (function<void(const Point&)> on_injure) {
	this->on_injure = on_injure;
}

bool Field::Ship::is_part_injured (const Point& point) {
	/*auto part = this->get_part(point);
	
	return part != this->parts.end() ? part->injured : false;*/
	return false;
}

void Field::Ship::injure_part (const Point& point) {
}

void Field::Ship::rotate (Point center, bool clockwise) {
}

Field::Ship::~Ship () {
}
//
//Field::Ship::Parts::iterator& Field::Ship::get_part (const Point& point) {
//	auto x = find_if(this->parts.begin(), this->parts.end(), [&](Part& p) {return p.point == point; });
//	return x;
//}

bool Field::Ship::all_injured () {
}