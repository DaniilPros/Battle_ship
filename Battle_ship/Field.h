#pragma once
#include <vector>
#include <functional>
#include <array>

namespace Model {
	class Ship;
	class Field;

	// Point on the game field
	struct Point {
		int x;
		int y;
		Point(int x = 0, int y = 0):x{x}, y{y} {}

		bool operator== (const Point& p) const {
			return x == p.x && y == p.y;
		}
	};

	// Model of a ship in the game
	class Ship {
	public:
		// Part of the ship
		// describes where does it located on the field
		// and its state (injured or not)
		struct Part {
			Part(bool injured, const Point& point)
				: injured{injured},
				point{point} {}

			bool injured;
			Point point;
		};

		// Orient describes orientation
		// of the ship relatively the field
		// on which it located
		enum class Orient {
			Horizontal,
			Vertical
		};

		using Parts = std::vector<Part>;

		/*
		Initialize the parts of the ship
		with all points between start_point and end_point.

		@param start_point the first point of the ship
		@param end_point the last point of the ship

		*/
		Ship(Point start_point, Point end_point);

		/*
		Initialize the parts of the ship with parts.

		Note: may be used as default constructor

		@param parts Parts of the ship
		@param center Index of the part that will be logical center
		*/
		explicit Ship(const Parts& parts = {}, const int& center = 0);

		/*
		Returns the killed field of the ship.

		@return the killed field
		*/
		bool is_killed();
		/*
		Sets on_kill event handler.

		on_kill event occurs after the last
		part of the ship has been injured.
		Handler gets all parts of the killed ship.

		@param on_kill Is event handler that called when the ship has been killed.
		*/
		void set_on_kill_handler(std::function<void(const Parts&)> on_kill);

		/*
		Sets on_injure event handler.

		on_injure event occurs after the
		part of the ship has been injured.
		Handler gets part that was injured.

		@param on_kill Is event handler that called when the ship has been injured.
		*/
		void set_on_injure_handler(std::function<void(const Point&)> on_injure);

		/*
		Finds part of the ship with  point equals to point
		and return the injured field of found part.
		If part wasn't found it returns false.

		@param point Is a point of the Field
		@return injured field of the part of the ship
		*/
		bool is_part_injured(const Point& point);

		/*
		Sets injured field of the part of
		the ship at the point to true.

		It also may call on_injure() and on_kill() event handlers.
		@param point Is a point of the Field where to injure the ship
		*/
		void injure_part(const Point& point);

		/*
		Returns parts of the ship
		@return Parts of teh ship
		*/
		Parts& get_parts();

		/*
		Sets parts of the ship to passed Parts

		@param p Parts that will be setted
		*/
		void set_parts(const Parts& p);

		/*
		Rotates the ship around the point at the center.
		The direction of rotating depends to the clockwise parameter.

		@param center Point around which the ship will be rotated.
		@param clockwise Flag that says in which direction the ship should be rotated.
		@return Reference to itself.
		*/
		Ship & rotate(const Point& center, bool clockwise);

		/*
		Shifts the ship by p.x and p.y

		@param p Is actuall offset which will be added to each part of the ship
		*/
		void shift(const Point& p);
		
		/*
		Moves the ship to p

		@param p Is a new position of the center of ship
		*/
		void set_center(const Point& center);

		/*
		Returns length of the ship

		@return Length of the ship
		*/
		size_t get_length() {
			return this->parts.size();
		}

	private:
		/*
		Finds the part with the point equals to a passed point.

		@param point Point which will be found.
		@return An iterator that points to the found part.
		*/
		Parts::iterator get_part(const Point& point);

		/*
		Looks through all parts and determine
		are all parts are injured.

		@return true if all parts are injured, false in other cases
		*/
		bool all_injured();

		/*
		Determine orientation of the ship.

		@return Orient object
		*/
		Orient orient();

		// Event handlers
		std::function<void(const Point&)> on_injure;
		std::function<void(const Parts&)> on_kill;

		bool killed;
		Parts parts;
		int center;
	};

	// Model of a field in the game
	class Field {
	public:
	
		Field();
		~Field();

		void add_primary_ship(const Ship& ship);
		//void set_

		void hit(const Point& p);
		void place_ship(const Ship& ship);


	private:
		std::function<void(const Point&)> on_miss;
		std::function<void(const Point&)> on_ship_injure;
		std::function<void(const Ship::Parts&)> on_ship_kill;
		
		struct Cell {
			Ship* ship = nullptr;
			bool used;
		};
		
		std::array<std::array<Cell,10>,10> field;
	};
}