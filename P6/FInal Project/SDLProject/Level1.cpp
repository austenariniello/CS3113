#include "Level1.h"

#define LEVEL1_WIDTH 10
#define LEVEL1_HEIGHT 50

#define LEVEL1_ENEMY_COUNT 11

unsigned int level1_data[] =
{
    50, 50, 50, 50, 50, 50, 50, 50, 50, 50,
    50, 50, 60, 50, 50, 50, 50, 50, 50, 50,
    50, 60, 48, 50, 50, 50, 50, 50, 50, 50,
    50, 50, 50, 50, 50, 50, 50, 50, 50, 50,
    50, 50, 50, 50, 50, 50, 50, 50, 50, 50,
    50, 50, 50, 50, 96, 96, 50, 60, 48, 50,
    50, 50, 50, 50, 50, 50, 50, 50, 60, 50,
    50, 50, 50, 50, 50, 50, 50, 50, 50, 50,
    50, 50, 60, 50, 50, 50, 50, 50, 50, 50,
    50, 48, 48, 60, 50, 50, 50, 50, 50, 50,
    50, 50, 60, 50, 50, 50, 50, 50, 50, 50,
    50, 50, 48, 50, 50, 50, 50, 50, 50, 50,
    50, 50, 60, 50, 50, 50, 50, 50, 50, 50,
    50, 50, 50, 50, 50, 50, 50, 50, 50, 50,
    50, 50, 50, 50, 50, 50, 50, 50, 50, 50,
    50, 50, 60, 50, 50, 50, 50, 50, 50, 50,
    50, 48, 48, 60, 50, 50, 50, 50, 60, 50,
    50, 60, 60, 50, 50, 50, 50, 60, 50, 50,
    50, 50, 50, 50, 50, 50, 50, 50, 50, 50,
    50, 50, 50, 50, 50, 50, 50, 50, 50, 50,
    50, 50, 50, 48, 50, 50, 50, 48, 50, 50,
    50, 50, 50, 50, 50, 50, 50, 50, 50, 50,
    50, 50, 50, 50, 50, 50, 50, 50, 50, 50,
    50, 50, 50, 50, 50, 50, 50, 50, 50, 50,
    50, 50, 50, 50, 50, 50, 50, 50, 50, 50,
    50, 50, 50, 50, 50, 50, 50, 50, 50, 50,
    60, 50, 50, 50, 50, 50, 50, 50, 50, 50,
    48, 60, 50, 50, 50, 50, 50, 50, 50, 50,
    48, 48, 60, 50, 50, 50, 50, 50, 50, 50,
    48, 60, 60, 50, 50, 50, 50, 50, 50, 50,
    60, 48, 60, 60, 50, 50, 50, 50, 50, 50,
    48, 48, 48, 60, 50, 50, 50, 50, 50, 50,
    60, 48, 48, 60, 50, 50, 50, 50, 50, 50,
    48, 60, 48, 60, 50, 50, 50, 50, 50, 50,
    48, 48, 60, 50, 50, 50, 50, 50, 50, 50,
    60, 60, 50, 50, 50, 50, 50, 50, 50, 50,
    60, 50, 50, 50, 50, 50, 50, 50, 50, 50,
    50, 50, 50, 50, 50, 50, 50, 50, 50, 50,
    50, 50, 50, 50, 50, 50, 50, 50, 50, 50,
    50, 50, 50, 50, 50, 50, 50, 50, 50, 50,
    50, 50, 50, 50, 50, 50, 50, 50, 50, 50,
    50, 50, 50, 50, 50, 50, 50, 50, 50, 50,
    50, 50, 50, 50, 50, 50, 50, 50, 50, 50,
    50, 60, 48, 50, 50, 50, 50, 50, 60, 50,
    50, 50, 50, 50, 50, 50, 50, 50, 50, 50,
    50, 50, 50, 50, 50, 50, 50, 50, 50, 50,
    50, 50, 60, 50, 50, 50, 50, 50, 50, 50,
    50, 50, 60, 50, 50, 50, 50, 48, 60, 50,
    50, 50, 50, 50, 50, 50, 50, 50, 50, 50,
    50, 50, 50, 50, 50, 50, 50, 50, 50, 50

};

void Level1::Initialize(int playerLives) {
    
    state.nextScene = -1;
    
    GLuint mapTextureID = Util::LoadTexture("tileset.png");
    state.map = new Map(LEVEL1_WIDTH, LEVEL1_HEIGHT, level1_data, mapTextureID, 1.0f, 12, 10);
    // Move over all of the player and enemy code from initialization.
    
    // Initialize Game Objects
    
    // Initialize Player
    state.player = new Entity();
    state.player->entityType = PLAYER;
    state.player->position = glm::vec3(5, -47, 0);
    state.player->startPosition = glm::vec3(5, -47, 0);
    state.player->velocity = glm::vec3(0, 1, 0);
    state.player->movement = glm::vec3(0);
    state.player->acceleration = glm::vec3(0);
    state.player->speed = 2.5f;
    state.player->textureID = Util::LoadTexture("ship_0000.png");
    
    state.player->height = 1;
    state.player->width = 1.0f;
    
    state.player->playerLives = playerLives;

    
    state.enemies = new Entity[LEVEL1_ENEMY_COUNT];
    GLuint enemyTextureID = Util::LoadTexture("ship_0001.png");
    
    for (int i = 0; i < LEVEL1_ENEMY_COUNT; i++) {
        state.enemies[i].entityType = ENEMY;
        state.enemies[i].textureID = enemyTextureID;
        state.enemies[i].acceleration = glm::vec3(0);
        
        state.enemies[i].aiType = STRAFER;
        state.enemies[i].aiState = STRAFERIGHT;
        state.enemies[i].speed = 1;
    }
    
    state.enemies[0].position = glm::vec3(4.5f, -44, 0);
    state.enemies[1].position = glm::vec3(4.5f, -37, 0);
    state.enemies[2].position = glm::vec3(4.5f, -36, 0);
    
    state.enemies[3].position = glm::vec3(8.0f, -27, 0);
    state.enemies[4].position = glm::vec3(6.0f, -29, 0);
    
    state.enemies[3].aiType = HOVER;
    state.enemies[3].aiState = IDLE;
    state.enemies[4].aiType = HOVER;
    state.enemies[4].aiState = IDLE;
    
    state.enemies[5].position = glm::vec3(4.5f, -21, 0);
    state.enemies[6].position = glm::vec3(4.5f, -18, 0);
    state.enemies[7].position = glm::vec3(4.5f, -13, 0);
    
    state.enemies[8].position = glm::vec3(8.0f, -10, 0);
    state.enemies[9].position = glm::vec3(9.0f, -9, 0);
    
    state.enemies[8].aiType = HOVER;
    state.enemies[8].aiState = IDLE;
    state.enemies[9].aiType = HOVER;
    state.enemies[9].aiState = IDLE;
    
    state.enemies[10].position = glm::vec3(4.5f, -7, 0);
}

void Level1::Update(float deltaTime) {
    state.player->Update(deltaTime, state.player, state.enemies, LEVEL1_ENEMY_COUNT, state.map);
    
    if ((state.player->position.y >= -6)) {
        state.nextScene = 2;
    }
    
    for (int i = 0; i < LEVEL1_ENEMY_COUNT; i++) {
        state.enemies[i].Update(deltaTime, state.player, state.enemies, LEVEL1_ENEMY_COUNT, state.map);
        
        
    }
}

void Level1::Render(ShaderProgram *program) {
    state.map->Render(program);
    state.player->Render(program);
    
    for (int i = 0; i < LEVEL1_ENEMY_COUNT; i++) {
        state.enemies[i].Render(program);
    }
}
