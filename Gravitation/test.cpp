#include <SFML/Graphics.hpp>

int main()
{
    int t = 0;
    sf::RenderWindow window(sf::VideoMode(400, 400), "Hello SFML!");
    int size = 400;

    sf::Font open_sans;
    open_sans.loadFromFile("C://Users//효서//Documents//Fonts//Open_Sans//static//OpenSans//OpenSans-Bold.ttf");

    sf::Text tmp_text;
    tmp_text.setFont(open_sans);
    int pixels[400][400];
    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++)
        {
            pixels[i][j] = i*j/628;
        }
    }

    sf::Image image;
    image.create(size, size, sf::Color::Yellow);

    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++)
        {
            image.setPixel(i, j, sf::Color(pixels[i][j], pixels[i][j], pixels[i][j],255));
        }
    }
    image.setPixel(100, 100, sf::Color(255, 0, 0, 255));
    
    sf::Texture texture;
    texture.loadFromImage(image);

    sf::Sprite sprite;
    sprite.setTexture(texture);
    sprite.setPosition(0, 0);
    image.saveToFile("E:/sfmlimage.bmp");

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

        if ((t / 36000) * 36000 == t) {
            window.clear();
            window.draw(sprite);
            window.display();
        }
    }

    return 0;
}