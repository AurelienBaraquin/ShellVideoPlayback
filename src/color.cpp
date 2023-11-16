#include <cmath>
#include <tuple>
#include <vector>
#include "RGB.h"
#include <iostream>

    // init_pair(1, COLOR_WHITE, COLOR_BLACK);
    // init_pair(2, COLOR_WHITE, COLOR_RED);
    // init_pair(3, COLOR_WHITE, COLOR_GREEN);
    // init_pair(4, COLOR_WHITE, COLOR_YELLOW);
    // init_pair(5, COLOR_WHITE, COLOR_BLUE);
    // init_pair(6, COLOR_WHITE, COLOR_MAGENTA);
    // init_pair(7, COLOR_WHITE, COLOR_CYAN);
    // init_pair(8, COLOR_WHITE, COLOR_WHITE);

std::vector<std::pair<int, RGBColor>> ncursesColors = {
    {0, {0, 0, 0}},
    {1, {128, 0, 0}},
    {2, {0, 128, 0}},
    {3, {128, 128, 0}},
    {4, {0, 0, 128}},
    {5, {128, 0, 128}},
    {6, {0, 128, 128}},
    {7, {255, 255, 255}}
};

double colorDistance(const RGBColor& c1, const RGBColor& c2)
{
    return std::sqrt(
        std::pow(c1.r - c2.r, 2) + 
        std::pow(c1.g - c2.g, 2) + 
        std::pow(c1.b - c2.b, 2));
}

int getClosestNcursesColorIndex(const RGBColor& color)
{
    int closestIndex = 0;
    double closestDistance = std::numeric_limits<double>::max();

    for (const auto& ncursesColor : ncursesColors) {
        double distance = colorDistance(color, ncursesColor.second);
        if (distance < closestDistance) {
            closestDistance = distance;
            closestIndex = ncursesColor.first;
        }
    }

    return closestIndex;
}