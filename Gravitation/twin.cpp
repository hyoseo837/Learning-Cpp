#include <SFML/Graphics.hpp>

const float G = 6.67430e-11;
const float Pi = 3.14159;
const float ratio = 1e-6;


float pythago(float x, float y) {
    float value = sqrt(x * x + y * y);
    return value;
}

sf::Vector2f vec_mult(sf::Vector2f vector, float magnitude) {
    return vector * (magnitude / pythago(vector.x, vector.y));
}

// planet (id, radius, mass, position, color, velocity)
class planet
{
private:
    sf::Vector2f velocity = sf::Vector2f(0.f, 0.f);
    sf::Vector2f acceleration = sf::Vector2f(0.f, 0.f);
public:
    sf::Vector2f position;
    double radius;
    double mass;
    sf::CircleShape shape;

    planet(int id, double r, double m, sf::Vector2f pos, sf::Color clr, sf::Vector2f v) {
        const int ID = id;
        radius = r;
        mass = m;
        position = pos;
        shape = sf::CircleShape(radius * ratio);
        shape.setFillColor(clr);
        velocity = v;
    };
    ~planet() {};

    double field_strength(sf::Vector2f pos) {
        double d = pythago((pos - position).x, (pos - position).y);
        return G * mass / (d * d);
    }


    void update() {
        velocity += acceleration;
        position += velocity;
        shape.setPosition(sf::Vector2f(position.x - radius, position.y - radius) * ratio);
    }

    void net_force(planet a, planet b) {
        float dA = pythago((a.position - position).x, (a.position - position).y);
        float dB = pythago((b.position - position).x, (b.position - position).y);

        sf::Vector2f accA;
        sf::Vector2f accB;

        if (dA > radius + a.radius) {
            accA = vec_mult((a.position - position), a.field_strength(position));

        }
        else
        {
            accA = sf::Vector2f();
        }
        if (dB > radius + b.radius) {
            accB = vec_mult((b.position - position), b.field_strength(position));

        }
        else
        {
            accB = sf::Vector2f();
        }
        acceleration = accA + accB;


    }

};


int main()
{
    int t = 0;
    sf::RenderWindow window(sf::VideoMode(1000, 1000), "Hello SFML!");

    sf::Font open_sans;
    open_sans.loadFromFile("C://Users//효서//Documents//Fonts//Open_Sans//static//OpenSans//OpenSans-Bold.ttf");

    sf::Text tmp_text;
    tmp_text.setFont(open_sans);


    planet ash(1, 6.371e6, 5.972e24, sf::Vector2f(500.f / ratio + 100000000, 500.f / ratio), sf::Color(66, 164, 245, 255), sf::Vector2f());
    planet ember(1, 6.371e6, 5.972e24, sf::Vector2f(500.f / ratio - 100000000, 500.f / ratio), sf::Color(235, 64, 52, 255), sf::Vector2f());
    planet moon(1, 6.371e6, 5.972e24, sf::Vector2f(500.f / ratio, 500.f / ratio - 100000000), sf::Color(170, 66, 245, 255), sf::Vector2f());


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
        ash.update();
        ember.update();
        moon.update();
        ember.net_force(ash,moon);
        ash.net_force(ember, moon);
        moon.net_force(ember, ash);
        tmp_text.setString(std::to_string(t / 86400) + " days");

        if ((t / 3600) * 3600 == t) {
            window.clear();
            window.draw(tmp_text);
            window.draw(ember.shape);
            window.draw(ash.shape);
            window.draw(moon.shape);
            window.display();
        }
    }

    return 0;
}