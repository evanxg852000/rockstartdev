#ifndef PIPE_H
#define PIPE_H

#include <vector>
#include <algorithm>
#include <SFML/Graphics.hpp>

#include "./game.hpp"
#include "./definitions.hpp"

namespace evansofts {
    class Pipe {
    public:
        Pipe(GameDataRef data);
        void SpawnBottomPipe();
        void SpawnTopPipe();
        void SpawnInvisiblePipe();
        void SpawnScoringPipe();
        void MovePipes(float dt);
        void DrawPipes();
        void RandomisePipeOffset();
        const std::vector<sf::Sprite>& GetSprites() const;
        std::vector<sf::Sprite>& GetScoringSprites();
    
    private:
        GameDataRef _data;
        std::vector<sf::Sprite> _pipeSprites;
        std::vector<sf::Sprite> _scoringSprites;
        int _landHeight;
        int _pipeSpawnYOffset;
    };

}

#endif