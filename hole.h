#pragma once
#include "level.h"
#include "tools.h"

struct Hole {
    Vector2 position;
    Vector2 size;
    Texture2D holeImg;

    void init();
    void initLevel(Level* level);
    void draw();
    ~Hole();
}; 