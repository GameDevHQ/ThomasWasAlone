#pragma once
#include "SFML/Graphics.hpp"
#include "TextureManager.h"
#include "Thomas.h"
#include "Bob.h"
#include "LevelManager.h"


using namespace sf;


class Engine
{
private:
    const int TILE_SIZE = 50;
    const int VERTS_IN_QUAD = 4;

    const int GRAVITY = 300;

    TextureManager& m_TextureManager;
    RenderWindow m_Window;

    // Game characters;
    Thomas m_Thomas;
    Bob m_Bob;

    LevelManager m_LevelManager;

    // Game views (for a few players too)
    View m_MainView;
    View m_LeftView;
    View m_RightView;

    // Three views for the background
    View m_BGMainView;
    View m_BGLeftView;
    View m_BGRightView;

    // Game HUD
    View m_HudView;

    // Declare a sprite and a texture for the background
    Sprite m_BackgroundSprite;
    Texture m_BackgroundTexture;

    // Is the game currently playing?
    bool m_Playing = false;

    // Is character 1 or 2 the current focus?
    bool m_Character1 = true;

    // Start in fullscreen mode
    bool m_SplitScreen = false;

    // How much time is left in the current level
    float m_TimeRemaining = 10;
    Time m_GameTimeTotal;

    // Is it time for a new/first level?
    bool m_NewLevelRequired = true;

    VertexArray m_VALevel;       // The vertex array for the level tiles
    int** m_ArrayLevel = NULL;   // The 2d array with the map for the level
    Texture m_TextureTiles;      // Texture for the level tiles

    // Private functions for internal use only
    void input();
    void update(float timedelta);
    void draw();
    void loadLevel();
public:
    Engine();
    void run();
};
