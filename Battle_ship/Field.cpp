#include "Field.h"
#include <algorithm>

Model::Field::Field ()
{
}


void Model::Field::hit (const Point& p)
{
}

void Model::Field::place_ship (const Ship& ship)
{
}

Model::Field::~Field ()
{
}

Model::Ship::Ship (Point start_point, Point end_point) : Ship()
{
	if (start_point.x == end_point.x)
		for (auto i = start_point.y; i <= end_point.y; i++)
			this->parts.emplace_back(false, Point{start_point.x, i});
	else
		for (auto i = start_point.x; i <= end_point.x; i++)
			this->parts.emplace_back(false, Point{i, start_point.x});
}

Model::Ship::Ship (const Parts& parts, const int& center) :
	on_injure{nullptr},
	on_kill{nullptr},
	killed{false},
	parts{parts},
	center{center}
{
}

bool Model::Ship::is_killed ()
{
	return this->killed;
}

void Model::Ship::set_on_kill_handler (std::function<void (const Parts&)> on_kill)
{
	this->on_kill = on_kill;
}

void Model::Ship::set_on_injure_handler (std::function<void (const Point&)> on_injure)
{
	this->on_injure = on_injure;
}

bool Model::Ship::is_part_injured (const Point& point)
{
	auto part = this->get_part(point);

	return part != this->parts.end() ? part->injured : false;
}

Model::Ship::Parts& Model::Ship::get_parts ()
{
	return this->parts;
}

void Model::Ship::set_parts (const Parts& p)
{
	this->parts = p;
}

void Model::Ship::injure_part (const Point& point)
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

Model::Ship & Model::Ship::rotate (const Point& center_point, bool clockwise)
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

void Model::Ship::shift (const Point& p)
{
	for (auto& part : this->parts)
	{
		part.point.x += p.x;
		part.point.y += p.y;
	}
}

Model::Ship::Parts::iterator Model::Ship::get_part (const Point& point)
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

bool Model::Ship::all_injured ()
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

Model::Ship::Orient Model::Ship::orient ()
{
	return
			this->parts.front().point.x == this->parts.back().point.x ?
				Orient::Horizontal :
				Orient::Vertical;
}