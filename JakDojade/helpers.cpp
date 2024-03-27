#include "helpers.h"

int pointToInt(int x, int y, int width)
{
    return x * width + y;
}

pairInt intToPoint(int value, int width)
{
    pairInt result;
    result.second = value % width;
    result.first = (value - value % width) / width;
    return result;
}
