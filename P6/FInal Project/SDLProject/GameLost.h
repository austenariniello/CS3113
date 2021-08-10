#include "Scene.h"

class GameLost : public Scene {

public:
    void Initialize(int playerLives) override;
    void Update(float deltaTime) override;
    void Render(ShaderProgram *program) override;
};
