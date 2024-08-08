#pragma once
#include "level.h"
#include "tools.h"
#include "hole.h"
#include "frog.h"

class Snake {
    struct SnakeBall {
        Vector2 position;
        Vector2 size;
        Vector2 speed;
        Color color;
    };
    
    int counterTail;
    int counterHead;
    int movementFrameCount;
    int framesCounter;
    Level* level;
    SnakeBall snake[SNAKE_LENGTH];
    Texture2D ballRed, ballYellow, ballBlue, ballGreen;
    Sound hit, collapse;
public:
    void init();
    void initLevel(Level* level);
    void stepMove();
    int tryCollideWithLaser(Laser& laser);
    bool collidedWithWall();
    bool collidedWithHole(const Hole &hole);
    bool isEmpty();
    void draw();
    ~Snake();
};