#include "stdafx.h"
#include "Engine.h"


void Engine::populateEmitters(std::vector<Vector2f>& vSoundEmitters, int** arrayLevel)
{
    vSoundEmitters.empty();

    // Keep track of the previous emitter, so we don't make too many
    FloatRect previousEmitter;

    // Search for fire in the level
    int levelWidth = static_cast<int>(m_LevelManager.getLevelSize().x);
    int levelHight = static_cast<int>(m_LevelManager.getLevelSize().y);

    for (int x = 0; x < levelWidth; x++)
    {
        for (int y = 0; y < levelHight; y++)
        {
            // Fire tile
            if (arrayLevel[y][x] == 2)
            {
                // Skip over any fire tiles too, near a previous emitter
                if (!FloatRect(
                    static_cast<float>(x * TILE_SIZE),
                    static_cast<float>(y * TILE_SIZE),
                    static_cast<float>(TILE_SIZE),
                    static_cast<float>(TILE_SIZE)).intersects(previousEmitter))
                {
                    // Add the coordiantes of this water block
                    vSoundEmitters.push_back(Vector2f(static_cast<float>(x * TILE_SIZE), static_cast<float>(y * TILE_SIZE)));

                    // Make a rectangle 6 blocks x 6 blocks, so we don't make any more emitters too close to this one
                    previousEmitter.left = static_cast<float>(x * TILE_SIZE);
                    previousEmitter.top = static_cast<float>(y * TILE_SIZE);
                    previousEmitter.width = static_cast<float>(TILE_SIZE * 6);
                    previousEmitter.height = static_cast<float>(TILE_SIZE * 6);
                }
            }
        }
    }
}
