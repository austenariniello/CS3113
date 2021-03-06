#include "Menu.h"

#define MENU_WIDTH 10
#define MENU_HEIGHT 8


unsigned int menu_data[] =
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

void Menu::Initialize(int playerLives) {
    
    state.nextScene = -1;
    
    GLuint mapTextureID = Util::LoadTexture("tileset.png");
    state.map = new Map(MENU_WIDTH, MENU_HEIGHT, menu_data, mapTextureID, 1.0f, 12, 6);
    
    state.player = new Entity();
    state.player->playerLives = playerLives;
    state.player->isActive = false;
}

void Menu::Update(float deltaTime) {
    
}

void Menu::Render(ShaderProgram *program) {
    state.map->Render(program);
    
    GLuint fontTextureID = Util::LoadTexture("font1.png");
    Util::DrawText(program, fontTextureID, "Press Enter", 0.5f, -0.25f, glm::vec3(3.25f, -3.75f, 0));
}
