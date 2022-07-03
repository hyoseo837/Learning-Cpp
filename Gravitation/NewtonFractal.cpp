#include <iostream>
#include "image.h"
#include <string>

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
 
int coloring(double i, double j, double roots[3][2], complexNum origin,float ratio) {

    double pos[2] = { i,j };
    double distances[3];
    double odistances[3];
    for (int k = 0; k < 3; k++)
    {
        distances[k] = (roots[k][0] - i) * (roots[k][0] - i) + (roots[k][1] - j) * (roots[k][1] - j);
    }
    for (int k = 0; k < 3; k++)
    {
        odistances[k] = (roots[k][0] - origin.real) * (roots[k][0] - origin.real) + (roots[k][1] - origin.imaginary) * (roots[k][1] - origin.imaginary);
    }
    if (odistances[0] < 5/(ratio*ratio) or odistances[1] < 5/(ratio*ratio) or odistances[2] < 5 / (ratio * ratio)){
        return 255;
    }
    if (distances[0] < distances[1] and distances[0] < distances[2]) {
        return 50;
    }
    if (distances[1] < distances[0] and distances[1] < distances[2]) {
        return 100;
    }
    if (distances[2] < distances[0] and distances[2] < distances[1]) {
        return 150;
    }

    std::cout << std::to_string(i) + ",  " + std::to_string(j) + " : " + std::to_string(distances[0]) + "  " + std::to_string(distances[1]) + "  " + std::to_string(distances[2]) << std::endl;
    return 0;
}


int main()
{

    // variables that you can change
    int size = 1000;
    int ratio = 300;
    int iteration = 50;
    float position[2] = {0.5,0.5};

    // system, constant
    int t = 0;
    const complexNum one(1, 0);

    double roots[3][2] = { {1,0},{-0.5,sqrt(3)/2},{-0.5,-sqrt(3)/2}};

    int* pixels = new int[1000000]; // should be square of size
    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++)
        {   
            complexNum z(static_cast<float>(i - (size * position[0])) / ratio, static_cast<float>(j - (size * position[1])) / ratio);
            complexNum o(z.real, z.imaginary);
            complexNum grad(0,0);
            for (int h = 0; h < iteration; h++) {
                grad = Ctime(Csub(Ctime(Ctime(z, z), z), one), Creciprocal(Cmult(Ctime(z, z), 3)));
                z = Csub(z, grad);
            }
           
            pixels[i*size+j] = coloring(z.real, z.imaginary, roots,o,ratio);
        }
        if (i % 50 == 0) {
            std::cout << std::to_string(i * 100 / size) + "% done " << std::endl;
        }
    }
    
    const int width = size;
    const int height = size;
    
    image image(width, height);
    for (int y = 0; y < height; y++) {
        for (int x = 0; x < width; x++) {

            image.SetColor(Color((float)pixels[x*size+y] / 255.f, (float)pixels[x * size + y] / 255.f, (float)pixels[x * size + y] / 255.f), x, y);
        }
    }

    image.Export("E:/testtest.bmp");
    
    return 0;
}