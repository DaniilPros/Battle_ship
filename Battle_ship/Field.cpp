#include "Field.h"
#include <algorithm>

Field::Field ()
{
}


void Field::hit (const Point& p)
{
}

void Field::place_ship (const Ship& ship)
{
}

void Field::move_ship_by (const Point& p)
{
}

Field::~Field ()
{
}

Field::Ship::Ship (Point start_point, Point end_point) : Ship()
{
	if (start_point.x == end_point.x)
		for (auto i = start_point.y; i <= end_point.y; i++)
			this->parts.emplace_back(false, Point{start_point.x, i});
	else
		for (auto i = start_point.x; i <= end_point.x; i++)
			this->parts.emplace_back(false, Point{i, start_point.x});
}

Field::Ship::Ship (const Parts& parts) :
	on_injure{nullptr},
	on_kill{nullptr},
	killed{false},
	parts{parts}
{
}

bool Field::Ship::is_killed ()
{
	return this->killed;
}

void Field::Ship::set_on_kill_handler (std::function<void (const Parts&)> on_kill)
{
	this->on_kill = on_kill;
}

void Field::Ship::set_on_injure_handler (std::function<void (const Point&)> on_injure)
{
	this->on_injure = on_injure;
}

bool Field::Ship::is_part_injured (const Point& point)
{
	auto part = this->get_part(point);

	return part != this->parts.end() ? part->injured : false;
}

Field::Ship::Parts& Field::Ship::get_parts ()
{
	return this->parts;
}

void Field::Ship::set_parts (const Parts& p)
{
	this->parts = p;
}

void Field::Ship::injure_part (const Point& point)
{
	auto part = this->get_part(point);

	if (part != this->parts.end() && !part->injured)
	{
		part->injured = true;
		this->on_injure(point);

		if (this->all_injured())
		{
			this->killed = true;
			this->on_kill(this->parts);
		}
	}
}

Field::Ship & Field::Ship::rotate (Point center_point, bool clockwise)
{
	auto center = this->get_part(center_point);

	switch (this->orient())
	{
	case Orient::Horizontal:
		for (auto i = this->parts.begin(); i != this->parts.end(); ++i)
		{
			i->point.x = center->point.x;
			i->point.y += distance(i, center) * (clockwise ? -1 : 1);
		}
		break;
	case Orient::Vertical:
		for (auto i = this->parts.begin(); i != this->parts.end(); ++i)
		{
			i->point.y = center->point.y;
			i->point.x += distance(i, center) * (clockwise ? 1 : -1);
		}
		break;
	}
	return *this;
}

void Field::Ship::shift (const Point& p)
{
	for (auto& part : this->parts)
	{
		part.point.x += p.x;
		part.point.y += p.y;
	}
}

Field::Ship::Parts::iterator Field::Ship::get_part (const Point& point)
{
	return
			std::find_if(
				this->parts.begin(),
				this->parts.end(),

				[&](Part& p)
				{
					return p.point == point;
				}
			);
}

bool Field::Ship::all_injured ()
{
	return
			std::find_if_not(
				this->parts.begin(),
				this->parts.end(),

				[&](const Part& p)
				{
					return p.injured;
				}
			) != this->parts.end();
}

Field::Ship::Orient Field::Ship::orient ()
{
	return
			this->parts.front().point.x == this->parts.back().point.x ?
				Orient::Horizontal :
				Orient::Vertical;
}