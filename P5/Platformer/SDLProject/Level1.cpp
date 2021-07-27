#include "Level1.h"

#define LEVEL1_WIDTH 30
#define LEVEL1_HEIGHT 8

#define LEVEL1_ENEMY_COUNT 2

unsigned int level1_data[] =
{
    38, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16,
    50, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16,
    50, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16,
    50, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 6, 8, 16, 16, 16, 16, 16, 16, 16, 16,
    50, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 6, 7, 7, 8, 16, 16, 6, 7, 7, 35, 20, 16, 16, 16, 42, 43, 43, 43, 44,
    50, 16, 16, 16, 16, 16, 6, 7, 8, 16, 16, 18, 19, 19, 20, 16, 16, 18, 19, 19, 19, 20, 16, 16, 16, 16, 16, 16, 16, 16,
    50, 7, 7, 7, 7, 7, 35, 19, 33, 7, 7, 35, 19, 19, 20, 16, 16, 18, 19, 19, 19, 20, 16, 16, 16, 16, 16, 16, 16, 16,
    50, 19, 19, 19, 19, 19, 19, 19, 19, 19, 19, 19, 19, 19, 20, 16, 16, 18, 19, 19, 19, 20, 16, 16, 16, 16, 16, 16, 16, 16,
};

void Level1::Initialize(int playerLives) {
    
    state.nextScene = -1;
    
    GLuint mapTextureID = Util::LoadTexture("tileset.png");
    state.map = new Map(LEVEL1_WIDTH, LEVEL1_HEIGHT, level1_data, mapTextureID, 1.0f, 12, 6);
    // Move over all of the player and enemy code from initialization.
    
    // Initialize Game Objects
    
    // Initialize Player
    state.player = new Entity();
    state.player->entityType = PLAYER;
    state.player->position = glm::vec3(3, 0, 0);
    state.player->startPosition = glm::vec3(3, 0, 0);
    state.player->movement = glm::vec3(0);
    state.player->acceleration = glm::vec3(0, -9.81f, 0);
    state.player->speed = 2.5f;
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
    state.player->width = 0.8f;
    
    state.player->jumpPower = 6.0f;
    
    state.player->playerLives = playerLives;
    
    state.enemies = new Entity[LEVEL1_ENEMY_COUNT];
    GLuint enemyTextureID = Util::LoadTexture("slime.png");
    
    for (int i = 0; i < LEVEL1_ENEMY_COUNT; i++) {
        state.enemies[i].entityType = ENEMY;
        state.enemies[i].textureID = enemyTextureID;
        state.enemies[i].acceleration = glm::vec3(0, -9.81f, 0);
        
        state.enemies[i].aiType = WAITANDGO;
        state.enemies[i].aiState = IDLE;
        state.enemies[i].speed = 1;
    }
    
    state.enemies[0].position = glm::vec3(8, -4, 0);
    state.enemies[1].position = glm::vec3(14, -3, 0);
}

void Level1::Update(float deltaTime) {
    state.player->Update(deltaTime, state.player, state.enemies, LEVEL1_ENEMY_COUNT, state.map);
    
    if (state.player->position.y <= -10) {
        state.player->PlayerHit();
    }
    else if ((state.player->position.x >= 27)) {
        state.nextScene = 2;
    }
    
    for (int i = 0; i < LEVEL1_ENEMY_COUNT; i++) {
        state.enemies[i].Update(deltaTime, state.player, state.enemies, LEVEL1_ENEMY_COUNT, state.map);
        
        if (state.enemies[i].position.y <= -10) {
            state.enemies[i].isActive = false;
        }
    }
}

void Level1::Render(ShaderProgram *program) {
    state.map->Render(program);
    state.player->Render(program);
    
    for (int i = 0; i < LEVEL1_ENEMY_COUNT; i++) {
        state.enemies[i].Render(program);
    }
}
