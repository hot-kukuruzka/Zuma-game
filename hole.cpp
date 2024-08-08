#include "hole.h"

void Hole::init() {
    size = { SQUARE_SIZE, SQUARE_SIZE };
    holeImg = LoadTexture("content/hole.png");
}

void Hole::initLevel(Level* level) {
    position = level->getHolePoint();
}

void Hole::draw() {
    DrawTextureV(holeImg, position, WHITE);
}

Hole::~Hole() {
    UnloadTexture(holeImg);
}