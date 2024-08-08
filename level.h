#pragma once
#include "tools.h"

class Level {
public:
    virtual Vector2 getSnakeSpeed(int ind, const Vector2& position) = 0;
	virtual Vector2 getStartingPoint() = 0;
	virtual int getSnakeLength() = 0;
	virtual int getMovementFrameCount() = 0;
	virtual Vector2 getHolePoint() = 0;
	virtual Vector2 getFrogPoint() = 0;
	virtual ~Level() = default;
};

class Level1 : public Level {
	int way[SNAKE_LENGTH];
	int deltaHeight[SNAKE_LENGTH];
    Vector2 speed[SNAKE_LENGTH];
public:
    Level1() {
        for (int i = 0; i < SNAKE_LENGTH; i++) {
            way[i] = 1;
            deltaHeight[i] = 0;
            speed[i] = {SQUARE_SIZE, 0};
        }
    }

	Vector2 getSnakeSpeed(int ind, const Vector2& position) {
        if (screenWidth - position.x <= 2 * SQUARE_SIZE && way[ind] % 4 == 1) {
            speed[ind] = {0, SQUARE_SIZE};
            deltaHeight[ind] = position.y;
            way[ind] += 1;
        }
        else if (position.y - deltaHeight[ind] >= 2 * SQUARE_SIZE && way[ind] % 4 == 2) {
            speed[ind] = {-SQUARE_SIZE, 0};
            way[ind] += 1;
        }
        else if (position.x <= SQUARE_SIZE && way[ind] % 4 == 3) {
            speed[ind] = {0, SQUARE_SIZE};
            deltaHeight[ind] = position.y;
            way[ind] += 1;
        }
        else if (position.y - deltaHeight[ind] >= 2 * SQUARE_SIZE && way[ind] % 4 == 0) {
            speed[ind] = {SQUARE_SIZE, 0};
            way[ind] += 1;
        }

        return speed[ind];
    }

	Vector2 getStartingPoint() { return { offset.x / 2, SQUARE_SIZE + offset.y / 2 }; }
	int getSnakeLength() { return 75; }
	int getMovementFrameCount() { return 30; }
	Vector2 getHolePoint() { return { ((screenWidth / SQUARE_SIZE) - 1) * SQUARE_SIZE + offset.x / 2, ((screenHeight / SQUARE_SIZE) - 4) * SQUARE_SIZE + offset.y / 2 }; }
	Vector2 getFrogPoint() { return { screenWidth / 2, ((screenHeight / SQUARE_SIZE) - 2) * SQUARE_SIZE + offset.y / 2 }; }
};


class Level2 : public Level {
    int way[SNAKE_LENGTH];
    float koef_w1[SNAKE_LENGTH], koef_w2[SNAKE_LENGTH], koef_h[SNAKE_LENGTH];
    Vector2 speed[SNAKE_LENGTH];
public:
    Level2() {
        for (int i = 0; i < SNAKE_LENGTH; i++) {
            way[i] = 1;
            koef_w1[i] = 2;
            koef_w2[i] = 1;
            koef_h[i] = 2;
            speed[i] = { SQUARE_SIZE, 0 };
        }
    }

    Vector2 getSnakeSpeed(int ind, const Vector2& position) {
        if (screenWidth - position.x <= koef_w1[ind] * SQUARE_SIZE && way[ind] % 4 == 1) {
            speed[ind] = { 0, SQUARE_SIZE };
            koef_w1[ind] *= 5;
            way[ind] += 1;
        }
        else if (screenHeight - position.y <= koef_h[ind] * SQUARE_SIZE && way[ind] % 4 == 2) {
            speed[ind] = { -SQUARE_SIZE, 0 };
            koef_h[ind] *= 4;
            way[ind] += 1;
        }
        else if (position.x <= koef_w2[ind] * SQUARE_SIZE && way[ind] % 4 == 3) {
            speed[ind] = { 0, -SQUARE_SIZE };
            koef_w2[ind] *= 10;
            way[ind] += 1;
        }
        else if (position.y <= 6 * SQUARE_SIZE && way[ind] % 4 == 0) {
            speed[ind] = { SQUARE_SIZE, 0 };
            way[ind] += 1;
        }

        return speed[ind];
    }

    Vector2 getStartingPoint() { return { offset.x / 2, SQUARE_SIZE + offset.y / 2 }; }
    int getSnakeLength() { return 50; }
    int getMovementFrameCount() { return 25; }
    Vector2 getHolePoint() { return { SQUARE_SIZE * 9 + offset.x / 2, SQUARE_SIZE * 8 + offset.y / 2}; }
    Vector2 getFrogPoint() { return { screenWidth / 2 + offset.x / 2, screenHeight / 2 - SQUARE_SIZE + offset.y / 2 }; }
};


class Level3 : public Level {
    int way[SNAKE_LENGTH];
    Vector2 speed[SNAKE_LENGTH];
public:
    Level3() {
        for (int i = 0; i < SNAKE_LENGTH; i++) {
            way[i] = 1;
            speed[i] = { -SQUARE_SIZE, -SQUARE_SIZE };
        }
    }

    Vector2 getSnakeSpeed(int ind, const Vector2& position) {
        if (position.x <= SQUARE_SIZE && way[ind] % 4 == 1) {
            speed[ind] = {SQUARE_SIZE, -SQUARE_SIZE};
            way[ind] += 1;
        }
        else if (position.y <= SQUARE_SIZE && way[ind] % 4 == 2) {
            speed[ind] = {SQUARE_SIZE, SQUARE_SIZE};
            way[ind] += 1;
        }
        else if (screenHeight - position.y <= 2 * SQUARE_SIZE && way[ind] % 4 == 3) {
            speed[ind] = {SQUARE_SIZE, -SQUARE_SIZE};
            way[ind] += 1;
        }

        return speed[ind];
    }

    Vector2 getStartingPoint() { return { 10 * SQUARE_SIZE + offset.x / 2, screenHeight - SQUARE_SIZE - offset.y / 2 }; }
    int getSnakeLength() { return 15; }
    int getMovementFrameCount() { return 20; }
    Vector2 getHolePoint() { return { (screenWidth / SQUARE_SIZE - 1 ) * SQUARE_SIZE + offset.x / 2, SQUARE_SIZE * 11 + offset.y / 2 }; }
    Vector2 getFrogPoint() { return { (screenWidth / SQUARE_SIZE - 8) * SQUARE_SIZE + offset.x / 2, SQUARE_SIZE * 8 + offset.y / 2 }; }
};


class Level4 : public Level {
    int way[SNAKE_LENGTH];
    float deltaHeight[SNAKE_LENGTH], deltaWidth[SNAKE_LENGTH];
    Vector2 speed[SNAKE_LENGTH];
public:
    Level4() {
        for (int i = 0; i < SNAKE_LENGTH; i++) {
            way[i] = 1;
            deltaHeight[i] = 0;
            deltaWidth[i] = 0;
            speed[i] = { SQUARE_SIZE, 0 };
        }
    }

    Vector2 getSnakeSpeed(int ind, const Vector2& position) {
        if (position.x < screenWidth / 2) {
            if (position.x - deltaWidth[ind] >= SQUARE_SIZE / 2 * 3 && way[ind] % 2 == 1) {
                speed[ind] = { 0, SQUARE_SIZE };
                deltaWidth[ind] = position.x;
                way[ind] += 1;
            }
            else if (position.y - deltaHeight[ind] >= SQUARE_SIZE / 2 * 3 && way[ind] % 2 == 0) {
                speed[ind] = { SQUARE_SIZE, 0 };
                deltaHeight[ind] = position.y;
                way[ind] += 1;
            }
        }
        else {
            if (position.x - deltaWidth[ind] >= SQUARE_SIZE / 2 * 3 && way[ind] % 2 == 1) {
                speed[ind] = { 0, -SQUARE_SIZE };
                deltaWidth[ind] = position.x;
                way[ind] += 1;
            }
            else if (deltaHeight[ind] - position.y >= SQUARE_SIZE / 2 * 3 && way[ind] % 2 == 0) {
                speed[ind] = { SQUARE_SIZE, 0 };
                deltaHeight[ind] = position.y;
                way[ind] += 1;
            }
        }

        return speed[ind];
    }

    Vector2 getStartingPoint() { return { offset.x / 2, SQUARE_SIZE + offset.y / 2 }; }
    int getSnakeLength() { return 25; }
    int getMovementFrameCount() { return 15; }
    Vector2 getHolePoint() { return { (screenWidth / SQUARE_SIZE - 2) * SQUARE_SIZE + offset.x / 2, SQUARE_SIZE + offset.y / 2 }; }
    Vector2 getFrogPoint() { return { screenWidth / 2, screenHeight / 2 - 5 * SQUARE_SIZE}; }
};


class Level5 : public Level {
    int way[SNAKE_LENGTH];
    int deltaWidth[SNAKE_LENGTH];
    Vector2 speed[SNAKE_LENGTH];
public:
    Level5() {
        for (int i = 0; i < SNAKE_LENGTH; i++) {
            way[i] = 1;
            deltaWidth[i] = 0;
            speed[i] = { 0, SQUARE_SIZE};
        }
    }

    Vector2 getSnakeSpeed(int ind, const Vector2& position) {
        if (screenHeight - position.y <= 2 * SQUARE_SIZE && way[ind] % 4 == 1) {
            speed[ind] = { SQUARE_SIZE, 0 };
            deltaWidth[ind] = position.x;
            way[ind] += 1;
        }
        else if (position.x - deltaWidth[ind] >= 1.5 * SQUARE_SIZE && way[ind] % 4 == 2) {
            speed[ind] = { 0, -SQUARE_SIZE };
            way[ind] += 1;
        }
        else if (position.y <= 2 * SQUARE_SIZE && way[ind] % 4 == 3) {
            speed[ind] = { SQUARE_SIZE, 0 };
            deltaWidth[ind] = position.x;
            way[ind] += 1;
        }
        else if (position.x - deltaWidth[ind] >= 1.5 * SQUARE_SIZE && way[ind] % 4 == 0) {
            speed[ind] = { 0, SQUARE_SIZE };
            way[ind] += 1;
        }

        return speed[ind];
    }

    Vector2 getStartingPoint() { return { offset.x / 2, SQUARE_SIZE + offset.y / 2 }; }
    int getSnakeLength() { return 40; }
    int getMovementFrameCount() { return 15; }
    Vector2 getHolePoint() { return { ((screenWidth / SQUARE_SIZE) - 5) * SQUARE_SIZE + offset.x / 2, ((screenHeight / SQUARE_SIZE) - 1) * SQUARE_SIZE + offset.y / 2 }; }
    Vector2 getFrogPoint() { return { ((screenWidth / SQUARE_SIZE) - 3) * SQUARE_SIZE + offset.y / 2, screenHeight / 2 }; }
};


class Level6 : public Level {
    int way[SNAKE_LENGTH];
    int deltaHeight[SNAKE_LENGTH];
    Vector2 speed[SNAKE_LENGTH];
public:
    Level6() {
        for (int i = 0; i < SNAKE_LENGTH; i++) {
            way[i] = 1;
            deltaHeight[i] = 0;
            speed[i] = { SQUARE_SIZE, 0 };
        }
    }

    Vector2 getSnakeSpeed(int ind, const Vector2& position) {
        if (screenWidth - position.x <= 2 * SQUARE_SIZE && way[ind] % 4 == 1) {
            speed[ind] = { 0, SQUARE_SIZE };
            deltaHeight[ind] = position.y;
            way[ind] += 1;
        }
        else if (position.y - deltaHeight[ind] >= 2 * SQUARE_SIZE && way[ind] % 4 == 2) {
            speed[ind] = { -SQUARE_SIZE, 0 };
            way[ind] += 1;
        }
        else if (position.x <= SQUARE_SIZE && way[ind] % 4 == 3) {
            speed[ind] = { 0, SQUARE_SIZE };
            deltaHeight[ind] = position.y;
            way[ind] += 1;
        }
        else if (position.y - deltaHeight[ind] >= 2 * SQUARE_SIZE && way[ind] % 4 == 0) {
            speed[ind] = { SQUARE_SIZE, 0 };
            way[ind] += 1;
        }

        return speed[ind];
    }

    Vector2 getStartingPoint() { return { offset.x / 2, SQUARE_SIZE + offset.y / 2 }; }
    int getSnakeLength() { return 30; }
    int getMovementFrameCount() { return 10; }
    Vector2 getHolePoint() { return { (screenWidth / SQUARE_SIZE - 1) * SQUARE_SIZE + offset.x / 2, (screenHeight / SQUARE_SIZE - 4) * SQUARE_SIZE + offset.y / 2 }; }
    Vector2 getFrogPoint() { return { screenWidth / 2, (screenHeight / SQUARE_SIZE - 2) * SQUARE_SIZE + offset.y / 2 }; }
};

