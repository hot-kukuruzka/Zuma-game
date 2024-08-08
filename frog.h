#pragma once
#include "level.h"
#include "tools.h"

class Laser {
    int framesCounter = 0;
    int MouseRightCounter = 0;
    float speedCoef = 0.2f;

    Vector2 position;
    Vector2 size;
    Vector2 speed;
    bool active;
    Color color;
    Texture2D ballRed, ballYellow, ballBlue, ballGreen;

public:
    void init();

    void move(const Vector2& position);
    bool isActive();
    void setActive(bool active = true);
    void setSpeed(const Vector2& speed);
    Color getColor() { return color; }
    bool checkPointInside(const Vector2& position);
    void update();
    void draw();
    ~Laser();
};

class Frog {
    Vector2 position;
    Vector2 size;
    Color color;
    Laser laser;
    Texture2D frogImg;
    Sound shot;

public:
    void init();
    void initLevel(Level *level);
    void update();
    void draw();
    Laser& getLaser() { return laser; }
    ~Frog();
};