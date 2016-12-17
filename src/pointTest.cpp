
#include <stdio.h>
#include <iostream>
#include <cmath>
#include "Point.h"

using namespace std;

int run()
{
    Point p = Point(3.0, 2.0);
    cout << "x: " << p.getPoint()[0] << " y: " << p.getPoint()[1] << "\n";

    Point q = Point(0, 0);
    cout << "distance p->q: " << p.getDistance(q) << "\n";

}
