#include "game.h"
#include "tools.h"

int main() {
    // Инициализация
    InitWindow(screenWidth, screenHeight, "Zuma");
    InitAudioDevice();
    InitGame();
    SetTargetFPS(60);

    // Основной игровой цикл
    while (!WindowShouldClose()) {
        // Обновление и отрисовка
        UpdateDrawFrame();
    }

    // Деинициализация  
    // Выгрузка загруженных данных (текстуры, звуки, модели...)  
    UnloadGame();
    CloseAudioDevice();
    CloseWindow();
    return 0;
}