#pragma once
#include <SFML/Graphics.hpp>

using namespace sf;

class LevelManager
{
private:
    const int NUM_LEVELS = 4;

    float m_TimeModifier = 1;
    float m_BaseTimeLimit = 0;
    int m_CurrentLevel = 0;

    Vector2i m_LevelSize;
    Vector2f m_StartPosition;
public:
    const int TILE_SIZE = 50;
    const int VERTS_IN_QUAD = 4;

    float getTimeLimit();

    Vector2f getStartPosition();
    int** nextLevel(VertexArray& rVaLevel);
    
    Vector2i getLevelSize();
    int getCurrentLevel();
};
