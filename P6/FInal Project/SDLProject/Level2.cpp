#include "Level2.h"

#define LEVEL2_WIDTH 10
#define LEVEL2_HEIGHT 50

#define LEVEL2_ENEMY_COUNT 15

#define LEVEL2_PROJECTILE_COUNT 20

unsigned int level2_data[] =
{
    56, 56, 56, 56, 56, 56, 56, 56, 56, 56,
    56, 56, 56, 56, 56, 56, 56, 56, 46, 68,
    56, 56, 56, 56, 56, 56, 56, 46, 69, 42,
    56, 56, 56, 56, 56, 56, 56, 57, 71, 42,
    56, 56, 56, 56, 102, 102, 56, 57, 42, 70,
    56, 56, 56, 56, 56, 56, 46, 69, 42, 42,
    68, 68, 47, 56, 46, 68, 69, 42, 42, 42,
    42, 42, 67, 68, 69, 42, 42, 42, 42, 42,
    42, 42, 42, 42, 42, 42, 42, 42, 70, 42,
    42, 42, 37, 39, 42, 42, 65, 42, 42, 42,
    42, 37, 53, 52, 38, 39, 42, 42, 64, 42,
    42, 61, 62, 41, 40, 63, 42, 42, 42, 42,
    42, 42, 42, 61, 63, 42, 42, 65, 42, 42,
    42, 42, 42, 42, 42, 42, 42, 42, 42, 42,
    42, 42, 42, 42, 42, 42, 42, 42, 42, 42,
    38, 39, 42, 42, 42, 42, 42, 42, 42, 42,
    50, 51, 42, 42, 42, 42, 42, 42, 37, 38,
    50, 52, 39, 42, 42, 42, 42, 42, 49, 50,
    50, 50, 52, 39, 42, 42, 42, 37, 53, 50,
    50, 50, 50, 52, 39, 42, 42, 49, 50, 50,
    50, 50, 50, 50, 52, 38, 38, 53, 50, 50,
    50, 50, 50, 50, 50, 50, 50, 50, 50, 50,
    50, 50, 50, 50, 50, 50, 50, 50, 50, 50,
    50, 50, 50, 50, 50, 50, 50, 50, 50, 50,
    50, 50, 50, 50, 50, 50, 50, 50, 50, 50,
    50, 50, 50, 50, 50, 50, 50, 50, 50, 60,
    50, 50, 50, 50, 50, 50, 50, 50, 48, 60,
    50, 50, 50, 50, 50, 50, 50, 50, 60, 60,
    50, 50, 50, 50, 50, 50, 48, 48, 60, 60,
    48, 50, 50, 50, 50, 60, 60, 60, 60, 60,
    60, 60, 50, 50, 50, 60, 60, 60, 60, 60,
    60, 48, 50, 50, 50, 48, 60, 60, 60, 60,
    60, 48, 50, 50, 50, 48, 60, 60, 60, 60,
    60, 48, 50, 50, 50, 60, 60, 60, 60, 60,
    60, 60, 50, 50, 50, 50, 60, 60, 60, 60,
    60, 60, 48, 50, 50, 50, 50, 48, 60, 60,
    60, 60, 60, 48, 50, 50, 50, 50, 60, 60,
    60, 60, 60, 60, 50, 50, 50, 50, 48, 60,
    60, 60, 48, 50, 50, 50, 50, 60, 48, 60,
    60, 60, 48, 50, 50, 50, 50, 48, 60, 60,
    60, 60, 60, 50, 50, 50, 50, 60, 60, 60,
    60, 48, 60, 50, 50, 50, 50, 48, 60, 60,
    60, 48, 50, 50, 50, 50, 50, 48, 60, 60,
    60, 48, 50, 50, 50, 50, 50, 48, 60, 60,
    60, 48, 50, 50, 50, 50, 50, 50, 60, 48,
    60, 48, 50, 50, 50, 50, 50, 50, 50, 50,
    48, 50, 50, 50, 50, 50, 50, 50, 50, 50,
    50, 50, 50, 50, 50, 50, 50, 50, 50, 50,
    50, 50, 50, 50, 50, 50, 50, 50, 50, 50,
    50, 50, 50, 50, 50, 50, 50, 50, 50, 50

};

void Level2::Initialize(int playerLives) {
    
    state.nextScene = -1;
    
    GLuint mapTextureID = Util::LoadTexture("tileset.png");
    state.map = new Map(LEVEL2_WIDTH, LEVEL2_HEIGHT, level2_data, mapTextureID, 1.0f, 12, 10);
    // Move over all of the player and enemy code from initialization.
    
    // Initialize Game Objects
    
    // Initialize Player
    state.player = new Entity();
    state.player->entityType = PLAYER;
    state.player->position = glm::vec3(4.5f, -47, 0);
    state.player->startPosition = glm::vec3(4.5f, -47, 0);
    state.player->velocity = glm::vec3(0, 1, 0);
    state.player->movement = glm::vec3(0);
    state.player->acceleration = glm::vec3(0);
    state.player->speed = 2.5f;
    state.player->textureID = Util::LoadTexture("ship_0000.png");
    
    state.player->height = 1;
    state.player->width = 1.0f;
    
    state.player->playerLives = playerLives;
    
    state.enemies = new Entity[LEVEL2_ENEMY_COUNT];
    GLuint enemyTextureID = Util::LoadTexture("ship_0001.png");
    
    for (int i = 0; i < LEVEL2_ENEMY_COUNT; i++) {
        state.enemies[i].entityType = ENEMY;
        state.enemies[i].textureID = enemyTextureID;
        state.enemies[i].acceleration = glm::vec3(0);
        
        state.enemies[i].aiType = HOVER;
        state.enemies[i].aiState = IDLE;
        state.enemies[i].speed = 1;
    }
    
    state.enemies[0].position = glm::vec3(3, -43, 0);
    state.enemies[1].position = glm::vec3(4, -39, 0);
    state.enemies[2].position = glm::vec3(6, -37, 0);
    state.enemies[3].position = glm::vec3(3, -33, 0);
    state.enemies[4].position = glm::vec3(1, -27, 0);
    state.enemies[5].position = glm::vec3(6, -26, 0);
    state.enemies[6].position = glm::vec3(2, -12, 0);
    state.enemies[7].position = glm::vec3(1, -6, 0);
    state.enemies[8].position = glm::vec3(8, -5, 0);
    
    for (int i = 9; i < LEVEL2_ENEMY_COUNT; i++) {
        state.enemies[i].aiType = STRAFER;
        state.enemies[i].aiState = STRAFERIGHT;
    }
    
    state.enemies[9].position = glm::vec3(4.5f, -24, 0);
    state.enemies[10].position = glm::vec3(2, -22, 0);
    state.enemies[11].position = glm::vec3(8, -18, 0);
    state.enemies[12].position = glm::vec3(2, -17, 0);
    state.enemies[13].position = glm::vec3(3, -14, 0);
    state.enemies[14].position = glm::vec3(4.5f, -10, 0);
    
    state.projectiles = new Entity[LEVEL2_PROJECTILE_COUNT];
    GLuint projectileTextureID = Util::LoadTexture("tile_0015.png");
    
    for (int i = 0; i < LEVEL2_PROJECTILE_COUNT; i++) {
        state.projectiles[i].entityType = PROJECTILE;
        state.projectiles[i].textureID = projectileTextureID;
        state.projectiles[i].velocity = glm::vec3(0, 1, 0);
        
        state.projectiles[i].speed = 7.0f;
        state.projectiles[i].isActive = false;
    }
}

void Level2::Update(float deltaTime) {
    state.player->Update(deltaTime, state.player, state.enemies, LEVEL2_ENEMY_COUNT, state.projectiles, LEVEL2_PROJECTILE_COUNT, state.map);
    
    if ((state.player->position.y >= -6)) {
        state.nextScene = 3;
    }
    
    for (int i = 0; i < LEVEL2_ENEMY_COUNT; i++) {
        state.enemies[i].Update(deltaTime, state.player, state.enemies, LEVEL2_ENEMY_COUNT, state.projectiles, LEVEL2_PROJECTILE_COUNT, state.map);
    }
    
    for (int i = 0; i < LEVEL2_PROJECTILE_COUNT; i++) {
        state.projectiles[i].Update(deltaTime, state.player, state.enemies, LEVEL2_ENEMY_COUNT, state.projectiles, LEVEL2_PROJECTILE_COUNT, state.map);
    }
}

void Level2::Render(ShaderProgram *program) {
    state.map->Render(program);
    state.player->Render(program);
    
    for (int i = 0; i < LEVEL2_ENEMY_COUNT; i++) {
        state.enemies[i].Render(program);
    }
    
    for (int i = 0; i < LEVEL2_PROJECTILE_COUNT; i++) {
        state.projectiles[i].Render(program);
    }
}
