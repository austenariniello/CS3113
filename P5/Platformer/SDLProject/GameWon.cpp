#include "GameWon.h"

#define GAMEWON_WIDTH 10
#define GAMEWON_HEIGHT 8


unsigned int gamewon_data[] =
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

void GameWon::Initialize(int playerLives) {
    
    state.nextScene = -1;
    
    GLuint mapTextureID = Util::LoadTexture("tileset.png");
    state.map = new Map(GAMEWON_WIDTH, GAMEWON_HEIGHT, gamewon_data, mapTextureID, 1.0f, 12, 6);
    
    state.player = new Entity();
    state.player->isActive = false;
}

void GameWon::Update(float deltaTime) {
    
}

void GameWon::Render(ShaderProgram *program) {
    state.map->Render(program);
    
    GLuint fontTextureID = Util::LoadTexture("font1.png");
    Util::DrawText(program, fontTextureID, "Game Won", 0.5f, -0.25f, glm::vec3(3.25f, -3.75f, 0));
}
