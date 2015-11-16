#pragma once
#include <vector>
#include <functional>
using namespace std;


class Field
{
	struct Point {
		int x;
		int y;
		bool operator==(const Point& p) const { return x == p.x && y == p.y; }
		//bool operator==(Point& p) const { return x == p.x && y == p.y; }
	};

	class Ship {
	public:
		struct Part {
			bool injured;
			Point point;
		};
		using Parts = vector<Part>;

		Ship(Point start_point, Point end_point);
		explicit Ship(Parts& parts);

		bool is_killed();

		void set_on_kill_handler(function<void(const Parts&)>  on_kill);
		void set_on_injure_handler(function<void(const Point&)> on_injure);

		bool is_part_injured(const Point& point);
		void injure_part(const Point& point);

		void rotate(Point center, bool clockwise);

		size_t get_length() { return this->parts.size(); }

		~Ship();
	private:
		//Parts::iterator& get_part(const Point& point);
		bool all_injured();

		function<void(const Point&)> on_injure;
		function<void(const Parts&)> on_kill;

		bool killed;
		Parts parts;
	};
public:
	Field();
	~Field();
};

