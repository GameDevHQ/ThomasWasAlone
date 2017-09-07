#include "stdafx.h"
#include "Engine.h"


bool Engine::detectCollisions(PlayableCharacter& character)
{
    bool reachedGoal = false;
    FloatRect detectionZone = character.getPosition();

    FloatRect block;
    block.width = static_cast<float>(TILE_SIZE);
    block.height = static_cast<float>(TILE_SIZE);

    // Build a zone around thomas to detect collisions
    int startX = static_cast<int>(detectionZone.left / TILE_SIZE) - 1;
    int startY = static_cast<int>(detectionZone.top / TILE_SIZE) - 1;
    int endX = static_cast<int>(detectionZone.left / TILE_SIZE) + 2;
    int endY = static_cast<int>(detectionZone.top / TILE_SIZE) + 3;

    // Make ensure that the character is not out of the boundaries
    if (startX < 0)
        startX = 0;

    if (startY < 0)
        startY = 0;

    if (endX >= m_LevelManager.getLevelSize().x)
        endX = m_LevelManager.getLevelSize().x;

    if (endY >= m_LevelManager.getLevelSize().y)
        endY = m_LevelManager.getLevelSize().y;

    // Has the character fallen out of the map?
    FloatRect level(0.0f, 0.0f, 
        static_cast<float>(m_LevelManager.getLevelSize().x * TILE_SIZE),
        static_cast<float>(m_LevelManager.getLevelSize().y * TILE_SIZE)
    );
    // Shall we respawn the player at beginning of the game level?
    if (!character.getPosition().intersects(level))
    {
        character.spawn(m_LevelManager.getStartPosition(), static_cast<float>(GRAVITY));
    }

    for (int x = startX; x < endX; x++)
    {
        for (int y = startY; y < endY; y++)
        {
            // Initialize the starting position of the current block
            block.left = static_cast<float>(x * TILE_SIZE);
            block.top = static_cast<float>(y * TILE_SIZE);

            // Has character been burnt or drowned?
            // Use head as this allows him to sink a bit
            if (m_ArrayLevel[y][x] == 2 || m_ArrayLevel[y][x] == 3)
            {
                if (character.getHead().intersects(block))
                {
                    character.spawn(m_LevelManager.getStartPosition(), static_cast<float>(GRAVITY));

                    // Fire tile
                    if (m_ArrayLevel[y][x] == 2)
                    {
                        m_SoundManager.playFallInFire();
                    }
                    // Water tile
                    else                     
                    {
                        m_SoundManager.playFallInWater();
                    }
                }
            }


            // Is character colliding with a regular block
            if (m_ArrayLevel[y][x] == 1)
            {

                if (character.getRight().intersects(block))
                {
                    character.stopRight(block.left);
                }
                else if (character.getLeft().intersects(block))
                {
                    character.stopLeft(block.left);
                }

                if (character.getFeet().intersects(block))
                {
                    character.stopFalling(block.top);
                }
                else if (character.getHead().intersects(block))
                {
                    character.stopJump();
                }
            }

            // Has the character reached the goal?
            if (m_ArrayLevel[y][x] == 4)
            {
                reachedGoal = true;
            }
        }
    }

    return reachedGoal;
}
