#include <iostream>
#include "image.h"
#include <string>
#define _USE_MATH_DEFINES
#include <math.h>
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

int coloring(double i, double j, double roots[6][2], float ratio) {

    double pos[2] = { i,j };
    double distances[6];
    for (int k = 0; k < 6; k++)
    {
        distances[k] = (roots[k][0] - i) * (roots[k][0] - i) + (roots[k][1] - j) * (roots[k][1] - j);
    }

    if (distances[0] < distances[1] && distances[0] < distances[2] && distances[0] < distances[3] && distances[0] < distances[4] && distances[0] < distances[5]) {
        return 1;
    }
    if (distances[1] < distances[0] && distances[1] < distances[2] && distances[1] < distances[3] && distances[1] < distances[4] && distances[1] < distances[5]) {
        return 2;
    }
    if (distances[2] < distances[0] && distances[2] < distances[1] && distances[2] < distances[3] && distances[2] < distances[4] && distances[2] < distances[5]) {
        return 3;
    }
    if (distances[3] < distances[0] && distances[3] < distances[1] && distances[3] < distances[2] && distances[3] < distances[4] && distances[3] < distances[5]) {
        return 4;
    }
    if (distances[4] < distances[0] && distances[4] < distances[1] && distances[4] < distances[2] && distances[4] < distances[3] && distances[4] < distances[5]) {
        return 5;
    }
    if (distances[5] < distances[0] && distances[5] < distances[1] && distances[5] < distances[2] && distances[5] < distances[3] && distances[5] < distances[4]) {
        return 6;
    }

    //std::cout << std::to_string(i) + ",  " + std::to_string(j) + " : " + std::to_string(distances[0]) + "  " + std::to_string(distances[1]) + "  " + std::to_string(distances[2]) << std::endl;
    return 0;
}


int main()
{

    // variables that you can change
    int size = 2000;
    int ratio = 400;
    int iteration = 50;
    float origin[2] = { 0.5,0.5 };
    Color color_list[2] = { Color(1,1,1), Color(0,0,0) };

    // system, constant
    int t = 0;
    const complexNum one(1, 0);

    double roots[6][2] = { {1,0}, {0.5,sqrt(3) / 2} , {-0.5,sqrt(3) / 2},{-1,0} , {-0.5,-sqrt(3) / 2} , {0.5,-sqrt(3) / 2}};


    int* pixels = new int[6250000]; // should be square of size
    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++)
        {
            complexNum z(static_cast<float>(i - (size * origin[0])) / ratio, static_cast<float>(j - (size * origin[1])) / ratio);
            complexNum o(z.real, z.imaginary);
            complexNum grad(0, 0);
            for (int h = 0; h < iteration; h++) {
                grad = Ctime(Cadd(Ctime(Ctime(Ctime(Ctime(Ctime(z,z), z), z), z), z), Cmult(one, -1)),
                    Creciprocal(Ctime(Ctime(Ctime(Ctime(Cmult(z, 6), z), z), z),z)));

                z = Csub(z, grad);
            }

            pixels[i * size + j] = coloring(z.real, z.imaginary, roots, ratio);
        }
        if (i % (size / 20) == 0) {
            std::cout << std::to_string(i * 100 / size) + "% done " << std::endl;
        }
    }

    const int width = size / 2;
    const int height = size / 2;
    int blk_count = 0;

    image image(width, height);
    for (int y = 0; y < height; y++) {
        for (int x = 0; x < width; x++) {
            if (pixels[2 * x * size + 2 * y] == pixels[(2 * x + 1) * size + (2 * y)] &&
                pixels[2 * x * size + 2 * y] == pixels[(2 * x) * size + (2 * y + 1)] &&
                pixels[2 * x * size + 2 * y] == pixels[(2 * x + 1) * size + (2 * y + 1)]) {
                image.SetColor(color_list[0], x, y);
            }
            else {
                blk_count++;
                image.SetColor(color_list[1], x, y);
            }

        }
    }


    image.Export("C:/Users/효서/Desktop/Fractals/Newton_dimension_6roots_1.bmp");
    std::cout << std::to_string(blk_count) + " pixels " << std::endl;

    return 0;
}