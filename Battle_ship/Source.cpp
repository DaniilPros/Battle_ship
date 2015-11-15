#include <SFML/Window.hpp>
#include <SFML/OpenGL.hpp>
#include <SFML/Graphics.hpp>

using namespace sf;

int main()
{
	VideoMode videoMode(320, 240);
	RenderWindow window(videoMode, "KeyEvent Window");

	RectangleShape rectangle;
	rectangle.setPosition(30, 30);
	rectangle.setSize(Vector2f(50, 30));

	rectangle.setFillColor(Color::Yellow);
	rectangle.setOutlineColor(Color::Blue);
	rectangle.setOutlineThickness(3);

	while (window.isOpen())
	{
		window.clear();
		window.draw(rectangle);
		window.display();

		Event event;
		while (window.pollEvent(event))
		{
			if ((event.type == Event::Closed) ||
				((event.type == Event::KeyPressed) && (event.key.code == Keyboard::Escape)))
				window.close();
			else
			{
				if (event.type == Event::KeyPressed)
				{
					switch (event.key.code)
					{
					case Keyboard::Up: rectangle.move(0, -10);
						break;
					case Keyboard::Down: rectangle.move(0, 10);
						break;
					case Keyboard::Left: rectangle.move(-10, 0);
						break;
					case Keyboard::Right: rectangle.move(10, 0);
						break;
					}

				}
			}

		}
	}
	return EXIT_SUCCESS;
}