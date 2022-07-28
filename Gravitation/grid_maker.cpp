#include "image.h"

#include <iostream>
#include <fstream>

int size = 1000;
const int width = size;
const int height = size;


int main() {
    image image(width, height);
    for (int y = 0; y < height/25; y++) {
        for (int x = 0; x < width/25; x++) {
            image.SetColor(Color(1,1,1), x*25, y*25);
        }
    }
    
    image.Export("D:/images/grid.png");

}