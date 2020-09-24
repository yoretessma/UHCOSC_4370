#include <iostream>
#include <fstream>
#include <cstdio>
#include <cassert>
using namespace std;

// We'll store image info as globals; not great programming practice
// but ok for this short program.
int size;
bool **image;

void renderPixel(int x, int y) {
    assert(x >= 0 && y >= 0 && x <= size && y <= size);
    image[x][y] = 1;

    // TODO:  light up the pixel's symmetric counterpart
    image[y][x] = 1;
}

void rasterizeArc(int radius) {
    // TODO:  rasterize the arc using renderPixel to light up pixels
    int x = 0;
    int y = radius;
    double d = 1 - radius;
    renderPixel(x,y);
    while(y>x){

        if(d<0) {
            d = d + 2 * x + 3;
        }
        else{
            d = d + 2 * (x - y) + 5;
            y--;
        }
        x++;
        renderPixel(x,y);
    }
}

// You shouldn't need to change anything below this point.

int main(int argc, char *argv[]) {


#ifdef _WIN32
    sscanf_s("200", "%d", &size);
#else
    sscanf("200", "%d", &size);
#endif
    if (size <= 0) {
        cout << "Image must be of positive size.\n";
        return 0;
    }

    // reserve image as 2d array
    image = new bool*[size+1];
    for (int i = 0; i <= size; i++) image[i] = new bool[size+1];

    rasterizeArc(100);
    rasterizeArc(150);

    char filename[50];
#ifdef _WIN32
    sprintf_s(filename, 50, "circle.ppm");
#else
    sprintf(filename, "circle.ppm");
#endif

    ofstream outfile(filename);
    outfile << "P3\n# " << filename << "\n";
    outfile << size+1 << ' ' << size+1 << ' ' << 1 << endl;

    for (int i = 0; i <= size; i++)
        for (int j = 0; j <= size; j++)
            outfile << image[size-i][j] << " 0 0\n";

    // delete image data
    for (int i = 0; i <= size; i++) delete [] image[i];
    delete [] image;

    return 0;
}
