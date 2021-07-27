#include "Level3.h"

#define LEVEL3_WIDTH 14
#define LEVEL3_HEIGHT 8

#define LEVEL3_ENEMY_COUNT 1

unsigned int level3_data[] =
{
    3, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16,
    3, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16,
    3, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16,
    3, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16,
    3, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16,
    3, 16, 16, 16, 16, 16, 16, 16, 16, 1, 1, 1, 1, 1,
    3, 1, 1, 1, 1, 1, 1, 16, 16, 2, 2, 2, 2, 2,
    3, 2, 2, 2, 2, 2, 2, 16, 16, 2, 2, 2, 2, 2
};

void Level3::Initialize(int playerLives) {
    
    state.nextScene = -1;
    
    GLuint mapTextureID = Util::LoadTexture("tileset.png");
    state.map = new Map(LEVEL3_WIDTH, LEVEL3_HEIGHT, level3_data, mapTextureID, 1.0f, 12, 6);
    // Move over all of the player and enemy code from initialization.
    
    // Initialize Game Objects
    
    // Initialize Player
    state.player = new Entity();
    state.player->entityType = PLAYER;
    state.player->position = glm::vec3(5, 0, 0);
    state.player->movement = glm::vec3(0);
    state.player->acceleration = glm::vec3(0, -9.81f, 0);
    state.player->speed = 2.0f;
    state.player->textureID = Util::LoadTexture("player.png");
    
    state.player->animRight = new int[6] {0, 1, 2, 3, 4, 5};
    state.player->animLeft = new int[6] {6, 7, 8, 9, 10, 11};

    state.player->animIndices = state.player->animRight;
    state.player->animFrames = 4;
    state.player->animIndex = 0;
    state.player->animTime = 0;
    state.player->animCols = 6;
    state.player->animRows = 2;
    
    state.player->height = 1;
    state.player->width = 0.8;
    
    state.player->jumpPower = 6.0f;
    
    state.player->playerLives = playerLives;
    
    state.enemies = new Entity[LEVEL3_ENEMY_COUNT];
    GLuint enemyTextureID = Util::LoadTexture("slime.png");
    
    for (int i = 0; i < LEVEL3_ENEMY_COUNT; i++) {
        state.enemies[i].entityType = ENEMY;
        state.enemies[i].textureID = enemyTextureID;
        state.enemies[i].position = glm::vec3(9 + i, -4, 0);
        state.enemies[i].acceleration = glm::vec3(0, -9.81f, 0);
        
        state.enemies[i].aiType = WAITANDGO;
        state.enemies[i].aiState = IDLE;
        state.enemies[i].speed = 1;
    }
}

void Level3::Update(float deltaTime) {
    state.player->Update(deltaTime, state.player, state.enemies, LEVEL3_ENEMY_COUNT, state.map);
    
    if (state.player->position.x >= 12) {
        state.nextScene = 4;
    }
    
    for (int i = 0; i < LEVEL3_ENEMY_COUNT; i++) {
        state.enemies[i].Update(deltaTime, state.player, state.enemies, LEVEL3_ENEMY_COUNT, state.map);
    }
}

void Level3::Render(ShaderProgram *program) {
    state.map->Render(program);
    state.player->Render(program);
    
    for (int i = 0; i < LEVEL3_ENEMY_COUNT; i++) {
        state.enemies[i].Render(program);
    }
}
