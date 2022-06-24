#include <SFML/Graphics.hpp>

int main()
{
    int t = 0;
    sf::RenderWindow window(sf::VideoMode(400, 400), "Hello SFML!");

    sf::Font open_sans;
    open_sans.loadFromFile("C://Users//효서//Documents//Fonts//Open_Sans//static//OpenSans//OpenSans-Bold.ttf");

    sf::Text tmp_text;
    tmp_text.setFont(open_sans);

    while (window.isOpen())
    {
        //window.setFramerateLimit(120);
        t++;

        sf::Vertex a(sf::Vector2f(100,100),sf::Color::White);

        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        if ((t / 3600) * 3600 == t) {
            window.clear();
            window.draw(&a, 1 , sf::Points);
            window.display();
        }
    }

    return 0;
}