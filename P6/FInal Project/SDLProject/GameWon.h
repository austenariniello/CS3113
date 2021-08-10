#include "Scene.h"

class GameWon : public Scene {

public:
    void Initialize(int playerLives) override;
    void Update(float deltaTime) override;
    void Render(ShaderProgram *program) override;
};
