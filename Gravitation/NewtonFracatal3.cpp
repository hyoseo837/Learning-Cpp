#include <iostream>
#include "image.h"
#include <string>

class complexNum
{
private:
public:
    double real;
    double imaginary;
    complexNum(double realN, double imginN)
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

int coloring(double i, double j, double roots[4][2], complexNum origin, float ratio) {

    double pos[2] = { i,j };
    double distances[4];
    double odistances[4];
    for (int k = 0; k < 4; k++)
    {
        distances[k] = (roots[k][0] - i) * (roots[k][0] - i) + (roots[k][1] - j) * (roots[k][1] - j);
    }
    for (int k = 0; k < 4; k++)
    {
        odistances[k] = (roots[k][0] - origin.real) * (roots[k][0] - origin.real) + (roots[k][1] - origin.imaginary) * (roots[k][1] - origin.imaginary);
    }
    if (odistances[0] < 10 / (ratio * ratio) or odistances[1] < 10 / (ratio * ratio) or odistances[2] < 10 / (ratio * ratio) or odistances[3] < 10 / (ratio * ratio)) {
        return 0;
    }
    if (distances[0] < distances[1] && distances[0] < distances[2] && distances[0] < distances[3]) {
        return 1;
    }
    if (distances[1] < distances[0] && distances[1] < distances[2] && distances[1] < distances[3]) {
        return 2;
    }
    if (distances[2] < distances[0] && distances[2] < distances[1] && distances[2] < distances[3]) {
        return 3;
    }
    if (distances[3] < distances[0] && distances[3] < distances[1] && distances[3] < distances[2]) {
        return 4;
    }

    //std::cout << std::to_string(i) + ",  " + std::to_string(j) + " : " + std::to_string(distances[0]) + "  " + std::to_string(distances[1]) + "  " + std::to_string(distances[2]) << std::endl;
    return 0;
}


int main()
{

    // variables that you can change
    int size = 1000;
    int ratio = 200;
    int iteration = 10;
    float origin[2] = { 0.5,0.5 };
    Color color_list[5] = { Color(0,0,0),Color(0.9176,0.0,0.2157),Color(0.9686,0.8431,0.0863),Color(0.4471,0.7333,0.0588),Color(0.0,0.4863,0.9686) };

    // system, constant
    int t = 0;
    const complexNum one(1, 0);

    double roots[4][2] = { {1,0},{0,1},{-1,0},{0,-1} };

    int* pixels = new int[1000000]; // should be square of size
    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++)
        {
            complexNum z(static_cast<float>(i - (size * origin[0])) / ratio, static_cast<float>(j - (size * origin[1])) / ratio);
            complexNum o(z.real, z.imaginary);
            complexNum grad(0, 0);
            for (int h = 0; h < iteration; h++) {
                grad = Ctime(Cadd(Ctime(Ctime(Ctime(z, z), z), z),Cmult(one,-1)),Creciprocal(Ctime(Ctime(Cmult(z, 4), z), z)));

                z = Csub(z, grad);
            }

            pixels[i * size + j] = coloring(z.real, z.imaginary, roots, o, ratio);
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
            image.SetColor(color_list[pixels[x * size + y]], x, y);
        }
    }

    /* ------- draw grid ------- */
    int cnt = 25;
    for (int kkk = 0; kkk < size; kkk++)
    {
        image.SetColor(Color(1, 1, 1), kkk, 500);
        image.SetColor(Color(1, 1, 1), 500, kkk);
        if (cnt++ == 25) {
            image.SetColor(Color(1, 1, 1), kkk, 501);
            image.SetColor(Color(1, 1, 1), 501, kkk);
            image.SetColor(Color(1, 1, 1), kkk, 502);
            image.SetColor(Color(1, 1, 1), 502, kkk);
            image.SetColor(Color(1, 1, 1), kkk, 503);
            image.SetColor(Color(1, 1, 1), 503, kkk);
            image.SetColor(Color(1, 1, 1), kkk, 504);
            image.SetColor(Color(1, 1, 1), 504, kkk);
            cnt -= 25;
        }
    }
    /* ------------------------- */

    image.Export("C:/Users/효서/Desktop/Fractals/Newton.bmp");
    return 0;
}