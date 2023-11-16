#pragma once

struct RGBColor {
    int r, g, b;
};

int getClosestNcursesColorIndex(const RGBColor& color);
