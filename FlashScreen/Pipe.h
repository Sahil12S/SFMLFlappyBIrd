#pragma once

#include <vector>
#include <SFML/Graphics.hpp>
#include "Game.h"
#include "DEFINITIONS.h"

namespace SSEngine
{
    class Pipe
    {
    public:
        Pipe( GameDataRef data);

        void SpawnBottomPipe();
        void SpawnTopPipe();

        // Invisible pipe helps in providing better movements.
        // Try removing this.
        void SpawnInvisiblePipe();

        void MovePipes( float dt );
        void DrawPipes();
        void RandomizePipeOffset();

        const std::vector<sf::Sprite>& GetSprites() const;

    private:
        GameDataRef m_Data;
        std::vector<sf::Sprite> m_PipeSprites;

        int m_LandHeight;
        int m_PipeSpawnYOffset;
    };
}