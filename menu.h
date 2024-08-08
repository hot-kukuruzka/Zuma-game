#pragma once
#include "tools.h"
#include <functional>

class Menu {
    class Button {
        enum ButtonState {
            NORMAL,
            HOVER,
            PRESSED
        };
        
        Texture2D images[3];
        Vector2 position;
        ButtonState state = NORMAL;
        Rectangle bounds;
        Sound clicked;
        std::function<void()> action;
    public:
        void init(const std::string &textureUriPrefix, const Vector2 &pos);
        void setAction(std::function<void()> cb);
        void update(const Vector2 &mousePoint);
        void draw();
        ~Button();
    };

    enum State {
        MAIN,
        LEVEL
    };

    Button play, mute, quit, l1, l2, l3, l4, l5, l6, back;
    Texture2D backgroundTexture, backgroundTexture2, zumaLogoTexture;

    State state = MAIN; 

    static const int LEVEL_NOT_SELECTED = -1;

    int selectedLevel = LEVEL_NOT_SELECTED;
public:
    void init();
    void update();
    void draw();

    void resetSelectedLevel();
    bool isLevelSelected();
    int getSelectedLevel();

    ~Menu();
};