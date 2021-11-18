#include "minCircle.h"

bool Circle::contains(const Point &p) const {
    return center.distance(p) <= r * MULTIPLICATIVE_EPSILON;
}

bool Circle::contains(const vector<Point> &ps) const {
    for (const Point &p : ps) {
        if (!contains(p))
            return false;
    }
    return true;
}


Circle Circle:: findMinCircle(Point** points,size_t size){

}