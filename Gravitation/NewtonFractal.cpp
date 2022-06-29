#include <SFML/Graphics.hpp>
#include <iostream>

class complexNum 
{
private:
public:
    double real;
    double imaginary;
    complexNum (double realN, double imginN)
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
    complexNum foo(a.real * b, a.imaginary * b);
    return foo;
}
 
int coloring(double i, double j, double roots[3][2]) {

    double pos[2] = { i,j };
    double distances[3];
    for (int k = 0; k < 3; k++)
    {
        distances[k] = (roots[k][0] - i) * (roots[k][0] - i) + (roots[k][1] - j) * (roots[k][1] - j);
    }
    if (distances[0] < distances[1] and distances[0] < distances[2]) {
        return 50;
    }
    if (distances[1] < distances[0] and distances[1] < distances[2]) {
        return 150;
    }
    if (distances[2] < distances[0] and distances[2] < distances[1]) {
        return 250;
    }

    std::cout << std::to_string(i) + ",  " + std::to_string(j) + " : " + std::to_string(distances[0]) + "  " + std::to_string(distances[1]) + "  " + std::to_string(distances[2]) << std::endl;
    return 0;
}


int main()
{
    int t = 0;
    sf::RenderWindow window(sf::VideoMode(400, 400), "Newton's fractal!");
    int size = 400;
    complexNum one(1, 0);

    double roots[3][2] = { {1,0},{-0.5,sqrt(3)/2},{0.5,-sqrt(3)/2}};

    int pixels[400][400];
    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++)
        {
            complexNum z(static_cast<float>(i - 200)/200, static_cast<float>(j - 200)/200);
            complexNum grad(0,0);
            grad = Ctime(Csub(Ctime(Ctime(z,z),z),one),Creciprocal(Cmult(Ctime(z,z), 3)));
            z = Csub(z, grad);
            pixels[i][j] = coloring(z.real, z.imaginary, roots);

        }
    }

    sf::Image image;
    image.create(size, size, sf::Color::Yellow);

    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++)
        {
            image.setPixel(i, j, sf::Color(pixels[i][j], pixels[i][j], pixels[i][j], 255));
        }
    }
    image.setPixel(400, 200, sf::Color(255, 0, 0, 255));
    image.setPixel(100, 373, sf::Color(0, 255, 0, 255));
    image.setPixel(100, 27, sf::Color(0, 0, 255, 255));

    sf::Texture texture;
    texture.loadFromImage(image);

    sf::Sprite sprite;
    sprite.setTexture(texture);
    sprite.setPosition(0, 0);
    image.saveToFile("E:/sfmlimage.bmp");

    while (window.isOpen())
    {
        window.setFramerateLimit(1);
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