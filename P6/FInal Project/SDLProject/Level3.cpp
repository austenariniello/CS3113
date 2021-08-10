#include "Level3.h"

#define LEVEL3_WIDTH 30
#define LEVEL3_HEIGHT 8

#define LEVEL3_ENEMY_COUNT 1

#define LEVEL3_PROJECTILE_COUNT 20

unsigned int level3_data[] =
{
    38, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16,
    50, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16,
    50, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16,
    50, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16,
    50, 16, 16, 16, 16, 16, 16, 16, 16, 54, 55, 55, 56, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 42, 43, 44,
    50, 16, 16, 16, 16, 54, 56, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 54, 56, 16, 16, 16, 16, 16, 16, 16, 16,
    50, 16, 54, 56, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 54, 56, 16, 16, 16, 16, 54, 56, 16, 16, 16, 16, 16,
    50, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16,
};

void Level3::Initialize(int playerLives) {
    
    state.nextScene = -1;
    
    GLuint mapTextureID = Util::LoadTexture("tileset.png");
    state.map = new Map(LEVEL3_WIDTH, LEVEL3_HEIGHT, level3_data, mapTextureID, 1.0f, 12, 10);
    // Move over all of the player and enemy code from initialization.
    
    // Initialize Game Objects
    
    // Initialize Player
    state.player = new Entity();
    state.player->entityType = PLAYER;
    state.player->position = glm::vec3(2.5, 0, 0);
    state.player->startPosition = glm::vec3(2.5, 0, 0);
    state.player->movement = glm::vec3(0);
    state.player->acceleration = glm::vec3(0, -9.81f, 0);
    state.player->speed = 2.7f;
    state.player->textureID = Util::LoadTexture("ship_0000.png");
    
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
    
    state.player->playerLives = playerLives;
    
    state.enemies = new Entity[LEVEL3_ENEMY_COUNT];
    GLuint enemyTextureID = Util::LoadTexture("ship_0001.png");
    
    for (int i = 0; i < LEVEL3_ENEMY_COUNT; i++) {
        state.enemies[i].entityType = ENEMY;
        state.enemies[i].textureID = enemyTextureID;
        state.enemies[i].position = glm::vec3(12 + i, -3, 0);
        state.enemies[i].acceleration = glm::vec3(0, -9.81f, 0);
        
        state.enemies[i].aiType = HOVER;
        state.enemies[i].aiState = IDLE;
        state.enemies[i].speed = 1;
    }
    
    state.enemies[0].position = glm::vec3(12, -3, 0);
    
    state.projectiles = new Entity[LEVEL3_PROJECTILE_COUNT];
    GLuint projectileTextureID = Util::LoadTexture("tile_0015.png");
    
    for (int i = 0; i < LEVEL3_PROJECTILE_COUNT; i++) {
        state.projectiles[i].entityType = PROJECTILE;
        state.projectiles[i].textureID = projectileTextureID;
        state.projectiles[i].velocity = glm::vec3(0, 1, 0);
        
        state.projectiles[i].speed = 7.0f;
        state.projectiles[i].isActive = false;
    }
}

void Level3::Update(float deltaTime) {
    state.player->Update(deltaTime, state.player, state.enemies, LEVEL3_ENEMY_COUNT, state.projectiles, LEVEL3_PROJECTILE_COUNT, state.map);
    
    if (state.player->position.y <= -10) {
        state.player->PlayerHit();
    }
    else if (state.player->position.x >= 28) {
        state.nextScene = 4;
    }
    
    for (int i = 0; i < LEVEL3_ENEMY_COUNT; i++) {
        state.enemies[i].Update(deltaTime, state.player, state.enemies, LEVEL3_ENEMY_COUNT, state.projectiles, LEVEL3_PROJECTILE_COUNT, state.map);
        
        if (state.enemies[i].position.y <= -10) {
            state.enemies[i].isActive = false;
        }
    }
    
    for (int i = 0; i < LEVEL3_PROJECTILE_COUNT; i++) {
        state.projectiles[i].Update(deltaTime, state.player, state.enemies, LEVEL3_ENEMY_COUNT, state.projectiles, LEVEL3_PROJECTILE_COUNT, state.map);
    }
}

void Level3::Render(ShaderProgram *program) {
    state.map->Render(program);
    state.player->Render(program);
    
    for (int i = 0; i < LEVEL3_ENEMY_COUNT; i++) {
        state.enemies[i].Render(program);
    }
    
    for (int i = 0; i < LEVEL3_PROJECTILE_COUNT; i++) {
        state.projectiles[i].Render(program);
    }
}