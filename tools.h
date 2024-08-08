#pragma once
#include <iostream>
#include <string>
#include <raylib.h>
#include <cmath>

constexpr int SQUARE_SIZE = 47;
constexpr int SNAKE_LENGTH = 256;

constexpr int zoom = 2; 
constexpr int screenWidth = 800 * zoom;
constexpr int screenHeight = 450 * zoom;
constexpr Vector2 offset = { screenWidth % SQUARE_SIZE, screenHeight % SQUARE_SIZE };