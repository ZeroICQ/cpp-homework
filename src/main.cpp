#include <iostream>
#include "figures.h"
#include <vector>

int main() {
    std::cout << "main.cpp" << std::endl;

    std::vector<Figure> fgs;

    Circle c1(0, 2, 2);
    Circle c2(4, 2, 2);

    ((Figure) c1);

//    fgs.push_back(c1);
//    fgs.push_back(c2);

//    std::vector<Point>intrses(fgs[0].intersect(fgs[1]));

    return 0;
}