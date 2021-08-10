#include "Menu.h"

#define MENU_WIDTH 10
#define MENU_HEIGHT 8


unsigned int menu_data[] =
{
    1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
    1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
    1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
    1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
    1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
    1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
    1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
    1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
};

void Menu::Initialize(int playerLives) {
    
    state.nextScene = -1;
    
    GLuint mapTextureID = Util::LoadTexture("tileset.png");
    state.map = new Map(MENU_WIDTH, MENU_HEIGHT, menu_data, mapTextureID, 1.0f, 12, 10);
    
    state.player = new Entity();
    state.player->playerLives = playerLives;
    state.player->isActive = false;
}

void Menu::Update(float deltaTime) {
    
}

void Menu::Render(ShaderProgram *program) {
    state.map->Render(program);
    
    GLuint fontTextureID = Util::LoadTexture("font1.png");
    Util::DrawText(program, fontTextureID, "Plane Old Shmup", 0.75f, -0.25f, glm::vec3(1.125f, -0.75f, 0));
    Util::DrawText(program, fontTextureID, "Avoid Trees and Enemy Planes", 0.5f, -0.25f, glm::vec3(1.125f, -2.75f, 0));
    Util::DrawText(program, fontTextureID, "Press Space To Shoot", 0.5f, -0.25f, glm::vec3(2.125f, -4.75f, 0));
    Util::DrawText(program, fontTextureID, "Press Enter To Begin", 0.5f, -0.25f, glm::vec3(2.125f, -5.75f, 0));
}
