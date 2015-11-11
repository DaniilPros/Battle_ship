#include <SFML/Window.hpp>
#include<iostream>
using namespace sf;
int main()
{
	sf::Window window(sf::VideoMode(800, 600), "My window",sf::Style::Close|sf::Style::Resize);
	window.setVerticalSyncEnabled(true);
	window.setFramerateLimit(60);
	while (window.isOpen())
	{
		Event event1;
		while (window.pollEvent(event1))
		{
			if (event1.type == Event::Closed)
				window.close();
			else if (event1.type == Event::Resized)
				window.hasFocus();
		}
	}
		return 0;
}