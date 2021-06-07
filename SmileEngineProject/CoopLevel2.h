#pragma once
#include <Scene.h>

namespace dae
{
    class CoopLevel2 final : public Scene
    {
    public:
        CoopLevel2(const GameSettings& gameSettings);
        void CreateScene() override;
        void OnSceneEnd() override;

    private:
        void CreateTilePositions(std::vector<glm::vec3>& tilePositions, float tileSize, int nrOfRows);
    };
}

