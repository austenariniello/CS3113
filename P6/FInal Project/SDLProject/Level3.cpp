#include "Level3.h"

#define LEVEL3_WIDTH 10
#define LEVEL3_HEIGHT 50

#define LEVEL3_ENEMY_COUNT 21

#define LEVEL3_PROJECTILE_COUNT 20

unsigned int level3_data[] =
{
    56, 56, 56, 56, 56, 56, 56, 56, 56, 56,
    56, 56, 56, 56, 56, 56, 56, 56, 56, 56,
    56, 56, 56, 54, 56, 56, 54, 56, 56, 56,
    56, 56, 66, 66, 56, 56, 56, 66, 56, 56,
    56, 56, 56, 56, 56, 56, 66, 56, 56, 56,
    56, 56, 56, 56, 56, 56, 56, 56, 56, 56,
    56, 56, 56, 56, 102, 102, 56, 56, 56, 56,
    56, 56, 56, 56, 56, 56, 56, 56, 56, 56,
    56, 56, 56, 56, 56, 56, 56, 56, 56, 56,
    56, 56, 56, 56, 56, 56, 56, 56, 56, 56,
    56, 56, 56, 56, 56, 56, 56, 56, 56, 56,
    56, 56, 56, 56, 56, 56, 56, 56, 56, 56,
    56, 56, 56, 56, 56, 56, 56, 56, 56, 56,
    56, 56, 56, 56, 56, 56, 56, 56, 56, 56,
    56, 56, 56, 56, 56, 56, 56, 56, 56, 56,
    56, 56, 56, 56, 56, 56, 56, 56, 56, 56,
    56, 56, 56, 56, 56, 56, 56, 56, 56, 56,
    56, 56, 56, 56, 56, 56, 56, 56, 56, 56,
    56, 56, 56, 56, 66, 54, 56, 56, 56, 56,
    56, 56, 56, 56, 56, 54, 56, 56, 56, 56,
    56, 56, 54, 56, 56, 66, 56, 56, 56, 56,
    56, 66, 66, 56, 56, 56, 56, 56, 56, 56,
    56, 56, 54, 56, 56, 56, 56, 56, 56, 56,
    56, 56, 56, 56, 56, 56, 56, 56, 56, 56,
    56, 56, 56, 56, 56, 56, 56, 56, 54, 56,
    56, 56, 56, 56, 56, 56, 56, 56, 54, 56,
    56, 56, 56, 54, 56, 56, 56, 54, 66, 56,
    56, 54, 66, 66, 56, 56, 56, 56, 56, 56,
    56, 56, 54, 56, 56, 56, 56, 56, 56, 56,
    56, 56, 56, 56, 56, 56, 56, 56, 56, 56,
    56, 56, 56, 56, 56, 56, 56, 56, 56, 56,
    56, 56, 56, 56, 56, 56, 56, 56, 56, 56,
    56, 56, 56, 56, 56, 56, 56, 56, 56, 54,
    56, 56, 56, 56, 56, 56, 56, 56, 54, 66,
    54, 56, 56, 56, 56, 56, 56, 56, 54, 66,
    66, 54, 54, 56, 56, 56, 56, 54, 66, 66,
    66, 66, 66, 54, 56, 56, 56, 54, 66, 66,
    66, 66, 66, 54, 56, 56, 56, 54, 66, 66,
    66, 66, 66, 54, 56, 56, 54, 66, 66, 66,
    66, 66, 66, 54, 56, 56, 54, 66, 66, 66,
    66, 66, 66, 54, 56, 56, 54, 66, 66, 66,
    66, 66, 66, 54, 56, 56, 54, 66, 66, 66,
    66, 66, 66, 54, 56, 56, 54, 66, 66, 66,
    66, 66, 54, 56, 56, 56, 54, 66, 66, 66,
    66, 54, 56, 56, 56, 56, 56, 54, 54, 66,
    66, 54, 56, 56, 56, 56, 56, 56, 56, 54,
    54, 56, 56, 56, 56, 56, 56, 56, 56, 54,
    56, 56, 56, 56, 56, 56, 56, 56, 56, 56,
    56, 56, 56, 56, 56, 56, 56, 56, 56, 56,
    56, 56, 56, 56, 56, 56, 56, 56, 56, 56
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
    
    state.enemies = new Entity[LEVEL3_ENEMY_COUNT];
    GLuint enemyTextureID = Util::LoadTexture("ship_0001.png");
    
    for (int i = 0; i < LEVEL3_ENEMY_COUNT; i++) {
        state.enemies[i].entityType = ENEMY;
        state.enemies[i].textureID = enemyTextureID;
        state.enemies[i].acceleration = glm::vec3(0);
        
        state.enemies[i].aiType = HOVER;
        state.enemies[i].aiState = IDLE;
        state.enemies[i].speed = 1;
    }
    
    state.enemies[0].position = glm::vec3(4, -41, 0);
    state.enemies[1].position = glm::vec3(5, -40, 0);
    state.enemies[2].position = glm::vec3(4, -39, 0);
    state.enemies[3].position = glm::vec3(5, -38, 0);
    state.enemies[4].position = glm::vec3(2, -25, 0);
    state.enemies[5].position = glm::vec3(6, -21, 0);
    state.enemies[6].position = glm::vec3(8, -19, 0);
    state.enemies[7].position = glm::vec3(1, -18, 0);
    state.enemies[8].position = glm::vec3(3, -17, 0);
    state.enemies[9].position = glm::vec3(7, -16, 0);
    state.enemies[10].position = glm::vec3(3, -13, 0);
    state.enemies[11].position = glm::vec3(6, -11, 0);
    state.enemies[12].position = glm::vec3(2, -9, 0);
    
    for (int i = 13; i < LEVEL3_ENEMY_COUNT; i++) {
        state.enemies[i].aiType = STRAFER;
        state.enemies[i].aiState = STRAFERIGHT;
    }
    
    state.enemies[13].position = glm::vec3(4, -30, 0);
    state.enemies[14].position = glm::vec3(5, -29, 0);
    state.enemies[15].position = glm::vec3(9, -23, 0);
    state.enemies[16].position = glm::vec3(3, -15, 0);
    state.enemies[17].position = glm::vec3(3, -14, 0);
    state.enemies[18].position = glm::vec3(5, -12, 0);
    state.enemies[19].position = glm::vec3(7, -10, 0);
    state.enemies[20].position = glm::vec3(2, -8, 0);
    
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
    
    if ((state.player->position.y >= -6)) {
        state.nextScene = 4;
    }
    
    for (int i = 0; i < LEVEL3_ENEMY_COUNT; i++) {
        state.enemies[i].Update(deltaTime, state.player, state.enemies, LEVEL3_ENEMY_COUNT, state.projectiles, LEVEL3_PROJECTILE_COUNT, state.map);
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
