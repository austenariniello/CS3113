#include "GameLost.h"

#define GAMELOST_WIDTH 10
#define GAMELOST_HEIGHT 8


unsigned int gamelost_data[] =
{
    13, 13, 13, 13, 13, 13, 13, 13, 13, 13,
    13, 13, 13, 13, 13, 13, 13, 13, 13, 13,
    13, 13, 13, 13, 13, 13, 13, 13, 13, 13,
    13, 13, 13, 13, 13, 13, 13, 13, 13, 13,
    13, 13, 13, 13, 13, 13, 13, 13, 13, 13,
    13, 13, 13, 13, 13, 13, 13, 13, 13, 13,
    13, 13, 13, 13, 13, 13, 13, 13, 13, 13,
    13, 13, 13, 13, 13, 13, 13, 13, 13, 13
};

void GameLost::Initialize(int playerLives) {
    
    state.nextScene = -1;
    
    GLuint mapTextureID = Util::LoadTexture("tileset.png");
    state.map = new Map(GAMELOST_WIDTH, GAMELOST_HEIGHT, gamelost_data, mapTextureID, 1.0f, 12, 6);
    
    state.player = new Entity();
    state.player->isActive = false;
}

void GameLost::Update(float deltaTime) {
    
}

void GameLost::Render(ShaderProgram *program) {
    state.map->Render(program);
    
    GLuint fontTextureID = Util::LoadTexture("font1.png");
    Util::DrawText(program, fontTextureID, "Game Lost", 0.5f, -0.25f, glm::vec3(3.25f, -3.75f, 0));
    Util::DrawText(program, fontTextureID, "Press Enter To Restart", 0.5f, -0.25f, glm::vec3(1.75f, -4.75f, 0));
}
