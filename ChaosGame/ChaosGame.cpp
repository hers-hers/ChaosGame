// Include important C++ libraries here
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <iostream>
#include <sstream>
#include <vector>
#include <ctime>

// Make the code easier to type with "using namespace"
using namespace sf;
using namespace std;

int main()
{
    // Seed the random number generator
    srand(static_cast<unsigned>(time(nullptr)));

    // Create a video mode object
    VideoMode vm(1920, 1080);
    // Create and open a window for the game
    RenderWindow window(vm, "Chaos Game!!", Style::Default);

    vector<Vector2f> vertices;
    vector<Vector2f> points;

    // Load a font for displaying instructions
    Font font;
    if (!font.loadFromFile("arial.ttf")) // Replace "arial.ttf" with your choice font file
    {
        cerr << "Error loading font\n";
        return -1;
    }

    // Create a Text object for instructions
    Text instructions;
    instructions.setFont(font);
    instructions.setString("Click three points to create a triangle, then click a fourth to start.");
    instructions.setCharacterSize(24);
    instructions.setFillColor(Color::Green);
    instructions.setPosition(10, 10);

    while (window.isOpen())
    {
        /*
        ****************************************
        Handle the players input
        ****************************************
        */
        Event event;
        while (window.pollEvent(event))
        {
            if (event.type == Event::Closed)
            {
                // Quit the game when the window is closed
                window.close();
            }
            if (event.type == sf::Event::MouseButtonPressed)
            {
                if (event.mouseButton.button == sf::Mouse::Left)
                {
                    std::cout << "the left button was pressed" << std::endl;
                    std::cout << "mouse x: " << event.mouseButton.x << std::endl;
                    std::cout << "mouse y: " << event.mouseButton.y << std::endl;

                    if (vertices.size() < 3)
                    {
                        vertices.push_back(Vector2f(event.mouseButton.x, event.mouseButton.y));
                    }
                    else if (points.size() == 0)
                    {
                        ///fourth click
                        ///push back to points vector
                        points.push_back(Vector2f(event.mouseButton.x, event.mouseButton.y));
                    }
                }
            }
        }

        if (Keyboard::isKeyPressed(Keyboard::Escape))
        {
            window.close();
        }

        /*
        ****************************************
        Update
        ****************************************
        */

        if (points.size() > 0)
        {
            ///Generate more point(s)
            for (int i = 0; i < 500; i++)    // i < x , where x is how fast it generates
            {                               // 10 was default, 500 would be very fast
                ///select random vertex
                int randomIndex = rand() % vertices.size(); // Random vertex index
                Vector2f randomVertex = vertices[randomIndex];

                // Get the last point
                Vector2f lastPoint = points.back();

                ///calculate midpoint between random vertex and the last point in the vector
                Vector2f newPoint((randomVertex.x + lastPoint.x) / 2,
                    (randomVertex.y + lastPoint.y) / 2);

                ///push back the newly generated coord.
                points.push_back(newPoint);
            }
        }

        /*
        ****************************************
        Draw
        ****************************************
        */
        window.clear();

        window.draw(instructions);

        for (int i = 0; i < vertices.size(); i++)
        {
            RectangleShape rect(Vector2f(10, 10));
            rect.setPosition(Vector2f(vertices[i].x, vertices[i].y));
            rect.setFillColor(Color::Red);
            window.draw(rect);
        }

        for (int i = 0; i < points.size(); i++)
        {
            RectangleShape point(Vector2f(2, 2));
            point.setPosition(Vector2f(points[i].x, points[i].y));
            point.setFillColor(Color::Green);
            window.draw(point);
        }

        window.display();
    }
}