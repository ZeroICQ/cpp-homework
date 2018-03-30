#include <vector>
#include <algorithm>
#include "misc.h"
#include "figures.h"

bool misc::contains_point(const std::vector<Point> &vec, const Point &p)
{
    return std::find(vec.begin(), vec.end(), p) != vec.end();
}

