#include <SFML/Graphics.hpp>
#include <iostream>

class complexNum 
{
private:
public:
    float real;
    float imaginary;
    complexNum (float realN, float imginN)
    {
    real = realN;
    imaginary = imginN;
    }

    std::string print() {
        return std::to_string(real) + " + " + std::to_string(imaginary) + " i";
    }

};

complexNum Cadd(complexNum a, complexNum b) {
    complexNum foo(a.real + b.real, a.imaginary + b.imaginary);
    return foo;
}

complexNum Csub(complexNum a, complexNum b) {
    complexNum foo(a.real - b.real, a.imaginary - b.imaginary);
    return foo;
}

complexNum Creciprocal(complexNum a) {
    float dno = a.real * a.real + a.imaginary * a.imaginary;
    complexNum foo(a.real / dno, -a.imaginary / dno);
    return foo;
}

complexNum Ctime(complexNum a, complexNum b) {
    complexNum foo(a.real * b.real - a.imaginary * b.imaginary, a.imaginary * b.real + a.real * b.imaginary);
    return foo;
}

complexNum Cmult(complexNum a, float b) {
    complexNum foo(a.real*b, a.imaginary*b);
    return foo;
}

int coloring(int i, int j, int roots[3][2]) {

    int pos[2] = { i,j };
    int distances[3];
    for (int k = 0; k < 3; k++)
    {
        distances[k] = (roots[k][0] - i) * (roots[k][0] - i) + (roots[k][1] - j) * (roots[k][1] - j);
    }
    if (distances[0] < distances[1]) {
        if (distances[0] < distances[2]) {
            return 0;
        }
    }
    else
    {
        if (distances[1] < distances[2]) {
            return 128;
        }
    }
    return 245;
}


int main()
{
    int t = 0;
    sf::RenderWindow window(sf::VideoMode(400, 400), "Newton's fractal!");
    int size = 400;

    int roots[3][2] = { {100,200},{200,200},{300,200} };

    complexNum kkk(2, 2);
    complexNum ppp(1, 3);
    complexNum rrr(0, 0);
    rrr = Ctime(kkk,ppp);

    std::cout << kkk.print() << std::endl;
    std::cout << ppp.print() << std::endl;
    std::cout << rrr.print() << std::endl;

    /*int pixels[400][400];
    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++)
        {
            pixels[i][j] = coloring(i, j, roots);
        }
    }*/

    sf::Image image;
    image.create(size, size, sf::Color::Yellow);

    /*for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++)
        {
            image.setPixel(i, j, sf::Color(pixels[i][j], pixels[i][j], pixels[i][j], 255));
        }
    }*/
    image.setPixel(100, 200, sf::Color(255, 0, 0, 255));
    image.setPixel(200, 200, sf::Color(0, 255, 0, 255));
    image.setPixel(300, 200, sf::Color(0, 0, 255, 255));

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