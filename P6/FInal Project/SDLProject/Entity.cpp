#include "Entity.h"

Entity::Entity()
{
    position = glm::vec3(0);
    movement = glm::vec3(0);
    velocity = glm::vec3(0);
    acceleration = glm::vec3(0);
    speed = 0;
    
    modelMatrix = glm::mat4(1.0f);
}

bool Entity::CheckCollision(Entity *other) {
    
    if (other == this) return false;
    
    if ((this->entityType == PLAYER) && (other->entityType == PROJECTILE)) return false;
    
    if ((this->entityType == PROJECTILE) && (other->entityType == PLAYER)) return false;
    
    if (isActive == false || other->isActive == false) return false;
    
    float xdist = fabs(position.x - other->position.x) - ((width + other->width) / 2.0f);
    float ydist = fabs(position.y - other->position.y) - ((height + other->height) / 2.0f);
    
    return (xdist < 0 && ydist < 0);
}

void Entity::CheckCollisionsY(Entity *objects, int objectCount)
{
    for (int i = 0; i < objectCount; i++)
    {
        Entity *object = &objects[i];

        if (CheckCollision(object))
        {
            lastCollided = object;
            
            float ydist = fabs(position.y - object->position.y);
            float penetrationY = fabs(ydist - (height / 2.0f) - (object->height / 2.0f));
            
            if (velocity.y > 0) {
                position.y -= penetrationY;
                velocity.y = 0;
                collidedTop = true;
            }
            else if (velocity.y < 0) {
                position.y += penetrationY;
                velocity.y = 0;
                collidedBottom = true;
            }
        }
    }
}

void Entity::CheckCollisionsX(Entity *objects, int objectCount)
{
    for (int i = 0; i < objectCount; i++)
    {
        Entity *object = &objects[i];

        if (CheckCollision(object))
        {
            lastCollided = object;
            
            float xdist = fabs(position.x - object->position.x);
            float penetrationX = fabs(xdist - (width / 2.0f) - (object->width / 2.0f));
            
            if (velocity.x > 0) {
                position.x -= penetrationX;
                velocity.x = 0;
                collidedRight = true;
            }
            else if (velocity.x < 0) {
                position.x += penetrationX;
                velocity.x = 0;
                collidedLeft = true;
            }
        }
    }
}

void Entity::CheckCollisionsY(Map *map)
{
    // Probes for tiles
    glm::vec3 top = glm::vec3(position.x, position.y + (height / 2), position.z);
    glm::vec3 top_left = glm::vec3(position.x - (width / 2), position.y + (height / 2), position.z);
    glm::vec3 top_right = glm::vec3(position.x + (width / 2), position.y + (height / 2), position.z);

    glm::vec3 bottom = glm::vec3(position.x, position.y - (height / 2), position.z);
    glm::vec3 bottom_left = glm::vec3(position.x - (width / 2), position.y - (height / 2), position.z);
    glm::vec3 bottom_right = glm::vec3(position.x + (width / 2), position.y - (height / 2), position.z);

    float penetration_x = 0;
    float penetration_y = 0;
    
    if (map->IsSolid(top, &penetration_x, &penetration_y) && velocity.y > 0) {
        position.y -= penetration_y;
        velocity.y = 0;
        mapCollision = true;
        collidedTop = true;
    }
    
    else if (map->IsSolid(top_left, &penetration_x, &penetration_y) && velocity.y > 0) {
        position.y -= penetration_y;
        velocity.y = 0;
        mapCollision = true;
        collidedTop = true;
    }
    
    else if (map->IsSolid(top_right, &penetration_x, &penetration_y) && velocity.y > 0) {
        position.y -= penetration_y;
        velocity.y = 0;
        mapCollision = true;
        collidedTop = true;
    }
    
    if (map->IsSolid(bottom, &penetration_x, &penetration_y) && velocity.y < 0) {
        position.y += penetration_y;
        velocity.y = 0;
        mapCollision = true;
        collidedBottom = true;
    }
    
    else if (map->IsSolid(bottom_left, &penetration_x, &penetration_y) && velocity.y < 0) {
        position.y += penetration_y;
        velocity.y = 0;
        mapCollision = true;
        collidedBottom = true;
    }
    
    else if (map->IsSolid(bottom_right, &penetration_x, &penetration_y) && velocity.y < 0) {
        position.y += penetration_y;
        velocity.y = 0;
        mapCollision = true;
        collidedBottom = true;
    }
}

void Entity::CheckCollisionsX(Map *map)
{
    // Probes for tiles
    glm::vec3 left = glm::vec3(position.x - (width / 2), position.y, position.z);
    glm::vec3 right = glm::vec3(position.x + (width / 2), position.y, position.z);

    float penetration_x = 0;
    float penetration_y = 0;
    
    if (map->IsSolid(left, &penetration_x, &penetration_y) && velocity.x < 0) {
        position.x += penetration_x;
        velocity.x = 0;
        mapCollision = true;
        collidedLeft = true;
    }

    if (map->IsSolid(right, &penetration_x, &penetration_y) && velocity.x > 0) {
        position.x -= penetration_x;
        velocity.x = 0;
        mapCollision = true;
        collidedRight = true;
    }
}

void Entity::AIStrafer() {
    switch (aiState) {
        case IDLE:
            
            break;
        case STRAFERIGHT:
            if (position.x >= 9) {
                movement = glm::vec3(0);
                aiState =  STRAFELEFT;
            }
            else {
                movement = glm::vec3(1, 0, 0);
            }
            break;
        case STRAFELEFT:
            if (position.x <= 0) {
                movement = glm::vec3(0);
                aiState = STRAFERIGHT;
            }
            else {
                movement = glm::vec3(-1, 0, 0);
            }
            break;
        default:
            break;
    }
    
}

void Entity::AIHover() {
    switch (aiState) {
        case IDLE:
            
            break;
            
        default:
            break;
    }
}

void Entity::AI(Entity *player) {
    switch (aiType) {
        case STRAFER:
            AIStrafer();
            break;
            
        case HOVER:
            AIHover();
            break;
            
        default:
            break;
    }
}

void Entity::PlayerHit() {
    position = startPosition;
    velocity = glm::vec3(0, 1, 0);
    playerLives -= 1;
    
}

void Entity::Update(float deltaTime, Entity *player, Entity *enemies, int enemyCount, Entity *projectiles, int projectileCount, Map *map)
{
    if (isActive == false) return;
    
    collidedTop = false;
    collidedBottom = false;
    collidedLeft = false;
    collidedRight = false;
    mapCollision = false;
    
    if (entityType == ENEMY) {
        AI(player);
    }
    
    if (animIndices != NULL) {
        if (glm::length(movement) != 0) {
            animTime += deltaTime;

            if (animTime >= 0.25f)
            {
                animTime = 0.0f;
                animIndex++;
                if (animIndex >= animFrames)
                {
                    animIndex = 0;
                }
            }
        } else {
            animIndex = 0;
        }
    }
    
    if (shoot) {
        shoot = false;
        
        int freeProjectile = 0;
        
        for (int i = 0; i < projectileCount; i++) {
            if (not projectiles[i].isActive) {
                freeProjectile = i;
                break;
            }
        }
        
        projectiles[freeProjectile].position = position;
        projectiles[freeProjectile].position.y += 1;
        projectiles[freeProjectile].lastCollided = NULL;
        projectiles[freeProjectile].isActive = true;
        
        projectiles[freeProjectile].velocity.y = 7;
    }
    
    velocity.x = movement.x * speed;
    velocity += acceleration * deltaTime;
    
    position.x += velocity.x * deltaTime;   // Move on X
    position.y += velocity.y * deltaTime;   // Move on Y
    
    CheckCollisionsX(enemies, enemyCount); // Fix if needed
    CheckCollisionsX(projectiles, projectileCount);
    CheckCollisionsX(map);
       
    CheckCollisionsY(enemies, enemyCount); // Fix if needed
    CheckCollisionsY(projectiles, projectileCount);
    CheckCollisionsY(map);
    
    if (entityType ==  PLAYER) {
        if ((collidedTop) || (collidedBottom) || (collidedLeft) || (collidedRight)) {
            PlayerHit();
        }
    }
    
    if (entityType == PROJECTILE) {
        if ((collidedTop) || (collidedBottom) || (collidedLeft) || (collidedRight)) {
            if (not mapCollision) {
                lastCollided->isActive = false;
            }
            isActive = false;
        }
        
        if ((position.y - player->position.y) >= 7.5) {
            isActive = false;
        }
    }

    modelMatrix = glm::mat4(1.0f);
    modelMatrix = glm::translate(modelMatrix, position);
}

void Entity::DrawSpriteFromTextureAtlas(ShaderProgram *program, GLuint textureID, int index)
{
    float u = (float)(index % animCols) / (float)animCols;
    float v = (float)(index / animCols) / (float)animRows;
    
    float width = 1.0f / (float)animCols;
    float height = 1.0f / (float)animRows;
    
    float texCoords[] = { u, v + height, u + width, v + height, u + width, v,
        u, v + height, u + width, v, u, v};
    
    float vertices[]  = { -0.5, -0.5, 0.5, -0.5, 0.5, 0.5, -0.5, -0.5, 0.5, 0.5, -0.5, 0.5 };
    
    glBindTexture(GL_TEXTURE_2D, textureID);
    
    glVertexAttribPointer(program->positionAttribute, 2, GL_FLOAT, false, 0, vertices);
    glEnableVertexAttribArray(program->positionAttribute);
    
    glVertexAttribPointer(program->texCoordAttribute, 2, GL_FLOAT, false, 0, texCoords);
    glEnableVertexAttribArray(program->texCoordAttribute);
    
    glDrawArrays(GL_TRIANGLES, 0, 6);
    
    glDisableVertexAttribArray(program->positionAttribute);
    glDisableVertexAttribArray(program->texCoordAttribute);
}

void Entity::Render(ShaderProgram *program) {
    if (isActive == false) return;
    program->SetModelMatrix(modelMatrix);
    
    if (animIndices != NULL) {
        DrawSpriteFromTextureAtlas(program, textureID, animIndices[animIndex]);
        return;
    }
    
    float vertices[]  = { -0.5, -0.5, 0.5, -0.5, 0.5, 0.5, -0.5, -0.5, 0.5, 0.5, -0.5, 0.5 };
    float texCoords[] = { 0.0, 1.0, 1.0, 1.0, 1.0, 0.0, 0.0, 1.0, 1.0, 0.0, 0.0, 0.0 };
    
    glBindTexture(GL_TEXTURE_2D, textureID);
    
    glVertexAttribPointer(program->positionAttribute, 2, GL_FLOAT, false, 0, vertices);
    glEnableVertexAttribArray(program->positionAttribute);
    
    glVertexAttribPointer(program->texCoordAttribute, 2, GL_FLOAT, false, 0, texCoords);
    glEnableVertexAttribArray(program->texCoordAttribute);
    
    glDrawArrays(GL_TRIANGLES, 0, 6);
    
    glDisableVertexAttribArray(program->positionAttribute);
    glDisableVertexAttribArray(program->texCoordAttribute);
}
