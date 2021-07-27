#include "Scene.h"

class Level2 : public Scene {

public:
    void Initialize(int playerLives) override;
    void Update(float deltaTime) override;
    void Render(ShaderProgram *program) override;
};
