#include "menu.h"
#include <string>


// инициализация кнопки
void Menu::Button::init(const std::string &textureUriPrefix, const Vector2 &pos) {
    for (int i = 0; i < sizeof(images) / sizeof(images[0]); i++) {
        std::string textureUri = textureUriPrefix + std::to_string(i + 1) + ".png";
        images[i] = LoadTexture(textureUri.c_str());
    }

    position = pos;
    bounds = { 
        position.x, 
        position.y, 
        static_cast<float>(images[0].width), 
        static_cast<float>(images[0].height)
    };
    clicked = LoadSound("content/sounds/button_pressed.mp3");
}

void Menu::Button::setAction(std::function<void()> action) {
    this->action = action;
}

void Menu::Button::update(const Vector2 &mousePoint) {
    if (CheckCollisionPointRec(mousePoint, bounds)) {
        if (IsMouseButtonDown(MOUSE_BUTTON_LEFT)) {
            state = PRESSED;
            PlaySound(clicked);
        }
        else state = HOVER;

        if (IsMouseButtonReleased(MOUSE_BUTTON_LEFT)) {
            //WaitTime(0.5);
            action();
        }
    }
    else state = NORMAL;
}

void Menu::Button::draw() {
    DrawTextureV(images[state], position, WHITE);
}

Menu::Button::~Button() {
    for (int i = 0; i < sizeof(images) / sizeof(images[0]); i++) {
        UnloadTexture(images[0]);
    }
    UnloadSound(clicked);
}

void Menu::init() {
    backgroundTexture = LoadTexture("content/menu.png");
    backgroundTexture2 = LoadTexture("content/menu_2.png");
    zumaLogoTexture = LoadTexture("content/logoZuma.png");

    play.init("content/button_play_", { screenWidth / 8.5 * 5, screenHeight / 10 * 4 });
    play.setAction([this]() { state = LEVEL; });

    mute.init("content/button_mute_", { screenWidth / 8.5 * 5, screenHeight / 10 * 6 });
    mute.setAction([]() {if (GetMasterVolume() == 0) SetMasterVolume(1); else SetMasterVolume(0); });

    quit.init("content/button_quit_", { screenWidth / 8.5 * 5, screenHeight / 10 * 8 });
    quit.setAction([]() { exit(0); });

    // init level selector buttons
    l1.init("content/button_1_", { screenWidth / 7, screenHeight / 5 });
    l1.setAction([this]() { selectedLevel = 1; });

    l2.init("content/button_2_", { screenWidth / 7 * 3, screenHeight / 5 });
    l2.setAction([this]() { selectedLevel = 2; });

    l3.init("content/button_3_", { screenWidth / 7 * 5, screenHeight / 5 });
    l3.setAction([this]() { selectedLevel = 3; });

    l4.init("content/button_4_", { screenWidth / 7, screenHeight / 2 });
    l4.setAction([this]() { selectedLevel = 4; });

    l5.init("content/button_5_", { screenWidth / 7 * 3, screenHeight / 2 });
    l5.setAction([this]() { selectedLevel = 5; });

    l6.init("content/button_6_", { screenWidth / 7 * 5, screenHeight / 2 });
    l6.setAction([this]() { selectedLevel = 6; });

    back.init("content/button_back_", { screenWidth / 20, screenHeight / 5 * 4 });
    back.setAction([this]() { state = MAIN; });
}

void Menu::update() {
    Vector2 mousePoint = GetMousePosition();

    if (state == MAIN) {
        play.update(mousePoint);
        mute.update(mousePoint);
        quit.update(mousePoint);
    }
    else if (state == LEVEL) {
        // update level selector buttons
        l1.update(mousePoint);
        l2.update(mousePoint);
        l3.update(mousePoint);
        l4.update(mousePoint);
        l5.update(mousePoint);
        l6.update(mousePoint);
        back.update(mousePoint);
    }
}

void Menu::draw() {
    if (state == MAIN) {
        DrawTexture(backgroundTexture, 0, 0, WHITE);
        DrawTexture(zumaLogoTexture, screenWidth / 2, screenHeight / 10, WHITE);

        play.draw();
        mute.draw();
        quit.draw();
    }
    else if (state == LEVEL) {
        // draw level selector
        DrawTexture(backgroundTexture2, 0, 0, WHITE);

        l1.draw();
        l2.draw();
        l3.draw();
        l4.draw();
        l5.draw();
        l6.draw();
        back.draw();
    }
}

bool Menu::isLevelSelected() {
    return selectedLevel != LEVEL_NOT_SELECTED;
}

int Menu::getSelectedLevel() {
    return selectedLevel;
}

void Menu::resetSelectedLevel() {
    selectedLevel = LEVEL_NOT_SELECTED;
}

Menu::~Menu() {
    UnloadTexture(backgroundTexture);
    UnloadTexture(backgroundTexture2);
    UnloadTexture(zumaLogoTexture);
}