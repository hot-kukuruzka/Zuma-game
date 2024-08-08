#include "game.h"
#include "menu.h"
#include "snake.h"
#include "hole.h"
#include "frog.h"

enum GameState {
    PLAY,
    PAUSE,
    WIN,
    LOSE
};

//------------------------------------------------------------------------------------
// Определения переменных
//------------------------------------------------------------------------------------

GameState gameState = PLAY;

Menu menu;
bool isInMenu = true;

Hole hole;
Frog frog;
Snake snake;

Level* level = nullptr;
int points = 0;

static Texture2D gameBackgroundTexture;
static Music music;
Sound win, loss;

//------------------------------------------------------------------------------------
// Определения функций
//------------------------------------------------------------------------------------

bool isGameOver() {
    return gameState == WIN || gameState == LOSE;
}

// Загрузка текстур
void InitGame() {
    menu.init();
    
    gameBackgroundTexture = LoadTexture("content/background_for_game.png");
    music = LoadMusicStream("content/sounds/zuma.mp3");
    win = LoadSound("content/sounds/win_sound.mp3");
    loss = LoadSound("content/sounds/loss_sound.mp3");
    PlayMusicStream(music);

    snake.init();
    frog.init();
    hole.init();
}

// Инициализация игровых переменных
void InitGameLevel() {
    gameState = PLAY;
    points = 0;
    
    snake.initLevel(level);
    frog.initLevel(level);
    hole.initLevel(level);
}

// Обновление игры (1 кадр)
void UpdateGame(void) {
    UpdateMusicStream(music);
    // Меню 
    if (isInMenu) {
        menu.update();

        if (!menu.isLevelSelected()) {
            return;
        }
        
        isInMenu = false;
        delete level;

        switch (menu.getSelectedLevel()) {
        case 1:
            level = new Level1();
            break;
        case 2:
            level = new Level2();
            break;
        case 3:
            level = new Level3();
            break;
        case 4:
            level = new Level4();
            break;
        case 5:
            level = new Level5();
            break;
        case 6:
            level = new Level6();
            break;
        default:
            exit(-1);
        }
        
        InitGameLevel();
    }

    if (isGameOver()) {
        if (IsKeyPressed(KEY_ENTER)) {
            menu.resetSelectedLevel();
            isInMenu = true;
        }

        return;
    }
    
    if (IsKeyPressed('P')) {
        gameState = (gameState == PAUSE ? PLAY : PAUSE);
    }

    if (IsKeyPressed('M')) {
        if (GetMasterVolume() == 0) SetMasterVolume(1); 
        else SetMasterVolume(0);        
    }

    if (IsKeyPressed('Q')) {
        menu.resetSelectedLevel();
        isInMenu = true;
    }

    if (gameState == PAUSE) {
        return;
    }

    // игра
    points += snake.tryCollideWithLaser(frog.getLaser());
    snake.stepMove();
    frog.update();

    if (snake.collidedWithWall() || snake.collidedWithHole(hole)) {
        PlaySound(loss);
        gameState = LOSE;
    }

    if (snake.isEmpty()) {
        PlaySound(win);
        gameState = WIN;
    }
}

void DrawBackground() {
    DrawTexture(gameBackgroundTexture, 0, 0, WHITE);

    // Рисовка сетки
    //for (int i = 0; i < screenWidth / SQUARE_SIZE + 1; i++) {
    //    DrawLine(SQUARE_SIZE * i + offset.x / 2, offset.y / 2, SQUARE_SIZE * i + offset.x / 2, screenHeight - offset.y / 2, LIGHTGRAY);
    //}
    //for (int i = 0; i < screenHeight / SQUARE_SIZE + 1; i++) {
    //    DrawLine(offset.x / 2, SQUARE_SIZE * i + offset.y / 2, screenWidth - offset.x / 2, SQUARE_SIZE * i + offset.y / 2, LIGHTGRAY);
    //}
}

// Рисовка игры (1 кадр)
void DrawGame() {
    BeginDrawing();
    if (isInMenu) {
        menu.draw();
        goto RETURN;
    }

    DrawBackground();
    frog.draw();
    hole.draw();
    snake.draw();
    DrawText("P - PAUSE", SQUARE_SIZE + offset.x, 20, 20, BLACK);
    DrawText("M - MUTE", SQUARE_SIZE * 4 + offset.x + MeasureText("P - PAUSE", 20), 20, 20, BLACK);
    DrawText("Q - QUIT", SQUARE_SIZE * 7 + offset.x + MeasureText("P - PAUSE", 20) + MeasureText("M - MUTE", 20), 20, 20, BLACK);
    DrawText("SCORE:", screenWidth - 200, 20, 20, BLACK);
    DrawText(std::to_string(points).c_str(), screenWidth - 100, 20, 20, BLACK);

    if (isGameOver()) {
        DrawRectangle(0, 0, screenWidth, screenHeight, { 100, 100, 100, 200 });
        if (gameState == WIN) {
            DrawText("YOU'RE WIN!!! PRESS [ENTER] TO RETURN TO THE MENU", GetScreenWidth() / 2 - MeasureText("YOU'RE WIN!!! PRESS [ENTER] TO RETURN TO THE MENU", 40) / 2, GetScreenHeight() / 2 - 50, 40, BLACK);
        }
        else {
            DrawText("YOU'RE LOSE... PRESS [ENTER] TO RETURN TO THE MENU", GetScreenWidth() / 2 - MeasureText("YOU'RE LOSE :( PRESS [ENTER] TO RETURN TO THE MENU", 40) / 2, GetScreenHeight() / 2 - 50, 40, BLACK);
        }
        goto RETURN;
    }

    if (gameState == PAUSE) DrawText("GAME PAUSED", screenWidth / 2 - MeasureText("GAME PAUSED", 40) / 2, screenHeight / 2 - 40, 40, BLACK);
    
RETURN:
    EndDrawing();
}

// Выгрузка игровых переменных
void UnloadGame() {
    UnloadTexture(gameBackgroundTexture);
    UnloadMusicStream(music);
    UnloadSound(win);
    UnloadSound(loss);
}

// Обновление и отрисовка (1 кадр)
void UpdateDrawFrame() {
    UpdateGame();
    DrawGame();
}