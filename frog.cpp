#include "frog.h"

void Laser::init() {
    size = { SQUARE_SIZE, SQUARE_SIZE };
    color = RED;
    active = false;
    ballBlue = LoadTexture("content/ball_blue.png");
    ballRed = LoadTexture("content/ball_red.png");
    ballGreen = LoadTexture("content/ball_green.png");
    ballYellow = LoadTexture("content/ball_yellow.png");
}

void Laser::move(const Vector2& position) {
    this->position = position;
}

bool Laser::isActive() {
    return active;
}

void Laser::setActive(bool active) {
    this->active = active;
}

void Laser::setSpeed(const Vector2& speed) {
    this->speed = speed;
    this->speed.x *= speedCoef;
    this->speed.y *= speedCoef;
}

bool Laser::checkPointInside(const Vector2& point) {
    float deltaX = position.x - point.x;
    float deltaY = position.y - point.y;
    float len = deltaX * deltaX + deltaY * deltaY;

    return (len - SQUARE_SIZE * SQUARE_SIZE) < 0;
}

void Laser::update() {
    framesCounter++;

    if (IsMouseButtonPressed(MOUSE_BUTTON_RIGHT) && !active) {
        MouseRightCounter += 1;
        if (MouseRightCounter % 4 == 1) color = BLUE;
        else if (MouseRightCounter % 4 == 2) color = GREEN;
        else if (MouseRightCounter % 4 == 3) color = YELLOW;
        else if (MouseRightCounter % 4 == 0) color = RED;
    }

    if (active) {
        position.x += speed.x;
        position.y += speed.y;
    }

    // Пересечение со стенами
    if (((position.x) > (screenWidth - offset.x)) ||
        ((position.y) > (screenHeight - offset.y)) ||
        (position.x < 0) || (position.y < 0)) {
        active = false;
    }
}

void Laser::draw() {
    if (ColorToInt(color) == ColorToInt(BLUE)) DrawTexture(ballBlue, position.x - SQUARE_SIZE / 2, position.y - SQUARE_SIZE / 2, WHITE);
    else if (ColorToInt(color) == ColorToInt(RED)) DrawTexture(ballRed, position.x - SQUARE_SIZE / 2, position.y - SQUARE_SIZE / 2, WHITE);
    else if (ColorToInt(color) == ColorToInt(GREEN)) DrawTexture(ballGreen, position.x - SQUARE_SIZE / 2, position.y - SQUARE_SIZE / 2, WHITE);
    else if (ColorToInt(color) == ColorToInt(YELLOW)) DrawTexture(ballYellow, position.x - SQUARE_SIZE / 2, position.y - SQUARE_SIZE / 2, WHITE);
}

Laser::~Laser() {
    UnloadTexture(ballBlue);
    UnloadTexture(ballGreen);
    UnloadTexture(ballRed);
    UnloadTexture(ballYellow);
}

void Frog::init() {
    size = { 2 * SQUARE_SIZE, 2 * SQUARE_SIZE };
    color = DARKGREEN;
    frogImg = LoadTexture("content/frog.png");
    shot = LoadSound("content/sounds/shot.mp3");

    laser.init();
}

void Frog::initLevel(Level* level) {
    position = level->getFrogPoint();
}

float calcAngle(int x1, int y1, int x2, int y2) {
    float t = (x1 * x2 + y1 * y2) / (sqrt(x1 * x1 + y1 * y1) * sqrt(x2 * x2 + y2 * y2));
    if (t < -1) t = -1;
    else if (t > 1) t = 1;
    return acos(t) * 180 / PI;
}

void Frog::update() {
    if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT) && !laser.isActive()) {
        PlaySound(shot);
        Vector2 speed = { 0 };
        speed.x = GetMouseX() - position.x;
        speed.y = GetMouseY() - position.y;
        float len = sqrt(speed.x * speed.x + speed.y * speed.y) / SQUARE_SIZE;
        speed.x /= len;
        speed.y /= len;
        laser.setSpeed(speed);
        laser.setActive();
    }

    laser.update();
}

void Frog::draw() {
    DrawLine(position.x, position.y, GetMouseX(), GetMouseY(), BLACK);
    
    float rotation = calcAngle(0, -1, GetMouseX() - position.x, GetMouseY() - position.y);
    if (GetMouseX() < position.x) rotation *= -1;
    
    DrawTexturePro(frogImg, { 0.0f, 0.0f, (float)frogImg.width, (float)frogImg.height }, { position.x, position.y, (float)frogImg.width, (float)frogImg.height }, { (float)frogImg.width / 2, (float)frogImg.height / 2 }, rotation, WHITE);
    
    if (!laser.isActive()) {
        rotation = rotation / 180 * PI;
        laser.move({ position.x + SQUARE_SIZE * sin(rotation), position.y - SQUARE_SIZE * cos(rotation) });
    }

    laser.draw();
}

Frog::~Frog() {
    UnloadTexture(frogImg);
    UnloadSound(shot);
}