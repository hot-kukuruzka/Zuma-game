#include "snake.h"

void Snake::init() {
    ballBlue = LoadTexture("content/ball_blue.png");
    ballRed = LoadTexture("content/ball_red.png");
    ballGreen = LoadTexture("content/ball_green.png");
    ballYellow = LoadTexture("content/ball_yellow.png");
    hit = LoadSound("content/sounds/hit.mp3");
    collapse = LoadSound("content/sounds/collapse.mp3");
}


void Snake::initLevel(Level* level) {
    this->level = level;
    framesCounter = -1;
    counterHead = 0;
    counterTail = level->getSnakeLength();
    movementFrameCount = level->getMovementFrameCount();

    for (int i = 0; i < SNAKE_LENGTH; i++) {
        snake[i].position = level->getStartingPoint();
        snake[i].size = { SQUARE_SIZE, SQUARE_SIZE };
        snake[i].speed = level->getSnakeSpeed(i, snake[i].position);
        snake[i].speed.x /= movementFrameCount;
        snake[i].speed.y /= movementFrameCount;
       
        int x = GetRandomValue(1, 4);
        if (x == 1) snake[i].color = BLUE;
        else if (x == 2) snake[i].color = RED;
        else if (x == 3) snake[i].color = GREEN;
        else snake[i].color = YELLOW;
    }
}

void Snake::stepMove() {
    framesCounter++;

    if ((framesCounter % movementFrameCount) == 0) {
        // актуализация скорости
        for (int i = 0; i < SNAKE_LENGTH; i++) {
            snake[i].speed = level->getSnakeSpeed(i, snake[i].position);
            snake[i].speed.x /= movementFrameCount;
            snake[i].speed.y /= movementFrameCount;
        }
        /*
        for (int i = std::min(counterTail - 1, framesCounter / movementFrameCount); i >= 0; i--) {
            printf("%d %f %f %f\n", i, snake[i].position.x, snake[i].position.y, snake[i].position.x - snake[i + 1].position.x);
            printf("%d %f %f\n", i, snake[i].speed.x, snake[i].speed.y);
        }
        printf("COUNTER'S VALUE ---------------- %d %d\n", counterHead, counterTail);
        */
    }

    // перемещение змейки
    for (int i = 0; i < std::min(SNAKE_LENGTH, (framesCounter / movementFrameCount) + 1); i++) {
        snake[i].position.x += snake[i].speed.x;
        snake[i].position.y += snake[i].speed.y;
    }
}

// Столкновение змеи с лазером
int Snake::tryCollideWithLaser(Laser &laser) {
    for (int i = counterHead; i < counterTail; i++) {
        if (laser.checkPointInside(snake[i].position)) {
            PlaySound(hit);
            counterTail += 1;

            for (int j = SNAKE_LENGTH - 1; j > i; j--) {
                snake[j].color = snake[j - 1].color;
            }
            snake[i].color = laser.getColor();


            int begin = i, end = i;

            int knockedBalls = 0, knockStreakMult = 1;

            bool changed = false;
            do {
                begin = end;
                changed = false;
                while (begin > counterHead && ColorToInt(snake[begin].color) == ColorToInt(snake[begin - 1].color)) begin -= 1;
                while (end < counterTail - 1 && end < SNAKE_LENGTH - 1 && ColorToInt(snake[end].color) == ColorToInt(snake[end + 1].color)) end += 1;
                if (end - begin >= 2) {
                    PlaySound(collapse);
                    for (int j = begin - 1; j >= 0; j--) {
                        snake[j + (end - begin + 1)].color = snake[j].color;
                    }
                    counterHead += (end - begin + 1);
                    knockedBalls += (end - begin + 1) * knockStreakMult;
                    knockStreakMult *= 5;
                    //printf("%d %d - %d %d deletion \n", counterHead, counterTail, begin, end);
                    changed = true;
                }
            } while (changed and end >= counterHead);

            laser.setActive(false);
            return knockedBalls;
        }
    }

    return 0;
}

bool Snake::collidedWithWall() {
    return ((snake[counterHead].position.x) > (screenWidth - offset.x)) ||
        ((snake[counterHead].position.y) > (screenHeight - offset.y)) ||
        (snake[counterHead].position.x < 0) || (snake[counterHead].position.y < 0);
}

bool Snake::collidedWithHole(const Hole &hole) {
    return (snake[counterHead].position.x < (hole.position.x + hole.size.x) && (snake[counterHead].position.x + snake[counterHead].size.x) > hole.position.x) &&
        (snake[counterHead].position.y < (hole.position.y + hole.size.y) && (snake[counterHead].position.y + snake[counterHead].size.y) > hole.position.y);
}

bool Snake::isEmpty() {
    return counterTail == counterHead;
}

void Snake::draw() {
    // Рисовка змеи
    for (int i = std::min(counterTail - 1, framesCounter / movementFrameCount); i >= counterHead; i--) {    
        if (ColorToInt(snake[i].color) == ColorToInt(BLUE)) DrawTexture(ballBlue, snake[i].position.x, snake[i].position.y, WHITE);
        else if (ColorToInt(snake[i].color) == ColorToInt(RED)) DrawTexture(ballRed, snake[i].position.x, snake[i].position.y, WHITE);
        else if (ColorToInt(snake[i].color) == ColorToInt(GREEN)) DrawTexture(ballGreen, snake[i].position.x, snake[i].position.y, WHITE);
        else if (ColorToInt(snake[i].color) == ColorToInt(YELLOW)) DrawTexture(ballYellow, snake[i].position.x, snake[i].position.y, WHITE);
        //DrawText(std::to_string(i).c_str(), snake[i].position.x, snake[i].position.y, 30, BLACK);
    }
}

Snake::~Snake() {
    UnloadTexture(ballBlue);
    UnloadTexture(ballGreen);
    UnloadTexture(ballRed);
    UnloadTexture(ballYellow);
    UnloadSound(hit);
    UnloadSound(collapse);
}