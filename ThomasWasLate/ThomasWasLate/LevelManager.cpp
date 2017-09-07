#include "stdafx.h"
#include "LevelManager.h"
#include <fstream>


float LevelManager::getTimeLimit()
{
    return m_BaseTimeLimit * m_TimeModifier;
}


Vector2f LevelManager::getStartPosition()
{
    return m_StartPosition;
}


int ** LevelManager::nextLevel(VertexArray & rVaLevel)
{
    m_LevelSize.x = 0;
    m_LevelSize.y = 0;

    // Get the next level
    m_CurrentLevel++;
    if (m_CurrentLevel > NUM_LEVELS)
    {
        m_CurrentLevel = 1;
        m_TimeModifier -= .1f;
    }

    // Load the appropriate level from a text file
    std::string levelToLoad;
    switch (m_CurrentLevel)
    {
        case 1:
            levelToLoad = "Resources/Levels/level1.txt";
            m_StartPosition.x = 100;
            m_StartPosition.y = 100;
            m_BaseTimeLimit = 30.0f;
            break;
        case 2:
            levelToLoad = "Resources/Levels/level2.txt";
            m_StartPosition.x = 100;
            m_StartPosition.y = 3600;
            m_BaseTimeLimit = 100.0f;
            break;
        case 3:
            levelToLoad = "Resources/Levels/level3.txt";
            m_StartPosition.x = 1250;
            m_StartPosition.y = 0;
            m_BaseTimeLimit = 30.0f;
            break;
        case 4:
            levelToLoad = "Resources/Levels/level4.txt";
            m_StartPosition.x = 50;
            m_StartPosition.y = 200;
            m_BaseTimeLimit = 50.0f;
            break;
    }

    std::ifstream inputFile(levelToLoad);
    std::string s;

    // Count the number of rows in the file
    while (getline(inputFile, s))
    {
        ++m_LevelSize.y;
    }
    // Store the length of the rows
    m_LevelSize.x = s.length();

    // Go back to the start of the file
    inputFile.clear();
    inputFile.seekg(0, std::ios::beg);

    // Prepare the 2d array to hold the int values from the file
    int** arrayLevel = new int*[m_LevelSize.y];
    for (int i = 0; i < m_LevelSize.y; ++i)
    {
        arrayLevel[i] = new int[m_LevelSize.x];
    }

    // Loop through the file and store all the values in the 2d array
    std::string row;
    int y = 0;
    while (inputFile >> row)
    {
        for (unsigned int x = 0; x < row.length(); x++) 
        {
            const char val = row[x];
            arrayLevel[y][x] = atoi(&val);
        }
        y++;
    }
    inputFile.close();

    rVaLevel.setPrimitiveType(Quads);
    rVaLevel.resize(m_LevelSize.x * m_LevelSize.y * VERTS_IN_QUAD);

    int currentVertex = 0;
    for (int x = 0; x < m_LevelSize.x; x++)
    {
        for (int y = 0; y < m_LevelSize.y; y++)
        {
            // Position each vertex in the current quad
            rVaLevel[currentVertex + 0].position = Vector2f(static_cast<float>(x * TILE_SIZE), static_cast<float>(y * TILE_SIZE));
            rVaLevel[currentVertex + 1].position = Vector2f(static_cast<float>((x * TILE_SIZE) + TILE_SIZE), static_cast<float>(y * TILE_SIZE));
            rVaLevel[currentVertex + 2].position = Vector2f(static_cast<float>((x * TILE_SIZE) + TILE_SIZE), static_cast<float>((y * TILE_SIZE) + TILE_SIZE));
            rVaLevel[currentVertex + 3].position = Vector2f(static_cast<float>((x * TILE_SIZE)), static_cast<float>((y * TILE_SIZE) + TILE_SIZE));

            // Which tile from the sprite sheet should we use
            int verticalOffset = arrayLevel[y][x] * TILE_SIZE;
            rVaLevel[currentVertex + 0].texCoords = Vector2f(0.0f, 0.0f + verticalOffset);
            rVaLevel[currentVertex + 1].texCoords = Vector2f(static_cast<float>(TILE_SIZE), 0.0f + verticalOffset);
            rVaLevel[currentVertex + 2].texCoords = Vector2f(static_cast<float>(TILE_SIZE), static_cast<float>(TILE_SIZE + verticalOffset));
            rVaLevel[currentVertex + 3].texCoords = Vector2f(0.0f, static_cast<float>(TILE_SIZE + verticalOffset));

            currentVertex = currentVertex + VERTS_IN_QUAD;
        }
    }

    return arrayLevel;
}


Vector2i LevelManager::getLevelSize()
{
    return m_LevelSize;
}


int LevelManager::getCurrentLevel()
{
    return m_CurrentLevel;
}
