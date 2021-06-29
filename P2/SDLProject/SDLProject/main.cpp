#define GL_SILENCE_DEPRECATION

#ifdef _WINDOWS
#include <GL/glew.h>
#endif

#define GL_GLEXT_PROTOTYPES 1
#include <SDL.h>
#include <SDL_opengl.h>
#include "glm/mat4x4.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "ShaderProgram.h"

#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

SDL_Window* displayWindow;
bool gameIsRunning = true;
int spacePressCount = 0;

ShaderProgram program;
glm::mat4 viewMatrix, player1Matrix, player2Matrix, eggMatrix, projectionMatrix;

glm::vec3 player1_position = glm::vec3(-4.5, 0, 0);
glm::vec3 player2_position = glm::vec3(4.5, 0, 0);
glm::vec3 egg_position = glm::vec3(0,0,0);

glm::vec3 player1_movement = glm::vec3(0, 0, 0);
glm::vec3 player2_movement = glm::vec3(0, 0, 0);
glm::vec3 egg_movement = glm::vec3(0,0,0);

glm::vec3 player1_dimensions = glm::vec3(1, 1, 0);
glm::vec3 player2_dimensions = glm::vec3(1, 1, 0);
glm::vec3 egg_dimensions = glm::vec3(0.5, 0.5, 0);

float player_speed = 2.0f;
float egg_speed = 2.5f;
int egg_direction;

GLuint player1TextureID, player2TextureID, eggTextureID;

bool HasCollided(glm::vec3 position1, glm::vec3 dimensions1, glm::vec3 position2, glm::vec3 dimensions2) {
    float xdist = fabs(position2.x - position1.x) - ((dimensions1.x + dimensions2.x) / 2.0f);
    float ydist = fabs(position2.y - position1.y) - ((dimensions1.y + dimensions2.y) / 2.0f);
    return (xdist < 0 && ydist < 0);
}

glm::vec3 EggPhysics(int direction) {
    /*
     Given an int 0-7, returns an egg movement vector corresponding to that direction
     0 : East
     1 : NorthEast
     2 : North
     3 : NorthWest
     4 : West
     5 : SouthWest
     6 : South
     7 : SouthEast
    */
    glm::vec3 movement;
    switch(direction) {
        case 0 :
            movement.x = 1.0f;
            break;
        case 1 :
            movement.x = 1.0f;
            movement.y = 1.0f;
            break;
        case 2 :
            movement.y = 1.0f;
            break;
        case 3 :
            movement.x = -1.0f;
            movement.y = 1.0f;
            break;
        case 4 :
            movement.x = -1.0f;
            break;
        case 5 :
            movement.x = -1.0f;
            movement.y = -1.0f;
            break;
        case 6 :
            movement.y = -1.0f;
            break;
        case 7 :
            movement.x = 1.0f;
            movement.y = -1.0f;
            break;
    }
    
    if (glm::length(movement) > 1.0f) {
        movement = glm::normalize(movement);
    }
    
    return movement;
}

GLuint LoadTexture(const char* filePath) {
    int w, h, n;
    unsigned char* image = stbi_load(filePath, &w, &h, &n, STBI_rgb_alpha);

    if (image == NULL) {
    std::cout << "Unable to load image. Make sure the path is correct\n";
    assert(false);
    }

    GLuint textureID;
    glGenTextures(1, &textureID);
    glBindTexture(GL_TEXTURE_2D, textureID);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, w, h, 0, GL_RGBA, GL_UNSIGNED_BYTE, image);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

    stbi_image_free(image);
    return textureID;
}

float lastTicks = 0.0f;

void Initialize() {
    SDL_Init(SDL_INIT_VIDEO);
    displayWindow = SDL_CreateWindow("Egg Toss!", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 640, 480, SDL_WINDOW_OPENGL);
    SDL_GLContext context = SDL_GL_CreateContext(displayWindow);
    SDL_GL_MakeCurrent(displayWindow, context);
    
#ifdef _WINDOWS
    glewInit();
#endif
    
    glViewport(0, 0, 1280, 960);
    
    program.Load("shaders/vertex_textured.glsl", "shaders/fragment_textured.glsl");
    
    viewMatrix = glm::mat4(1.0f);
    player1Matrix = glm::mat4(1.0f);
    player2Matrix = glm::mat4(1.0f);
    eggMatrix = glm::mat4(1.0f);
    
    projectionMatrix = glm::ortho(-5.0f, 5.0f, -3.75f, 3.75f, -1.0f, 1.0f);
    
    program.SetProjectionMatrix(projectionMatrix);
    program.SetViewMatrix(viewMatrix);
    
    glUseProgram(program.programID);
    
    glClearColor(1.0f, 0.769f, 0.922f, 1.0f);
    glEnable(GL_BLEND);
    
    // Good setting for transparency
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    
    player1TextureID = LoadTexture("mametchi.png");
    player2TextureID = LoadTexture("memetchi.png");
    eggTextureID = LoadTexture("egg.png");
}


void ProcessInput() {
    
    player1_movement = glm::vec3(0);
    player2_movement = glm::vec3(0);
    
    SDL_Event event;
    while (SDL_PollEvent(&event)) {
        switch (event.type) {
            case SDL_QUIT:
            case SDL_WINDOWEVENT_CLOSE:
                gameIsRunning = false;
                break;

            case SDL_KEYDOWN:
                switch (event.key.keysym.sym) {
                    case SDLK_SPACE:
                        if (spacePressCount < 1) {
                            egg_direction =(rand() % 8);
                            egg_movement = EggPhysics(egg_direction);
                        }
                        spacePressCount++;
                        break;
            }
            break; // SDL_KEYDOWN
        }
    }
    
    const Uint8 *keys = SDL_GetKeyboardState(NULL);
    
    if (keys[SDL_SCANCODE_W]) {
        player1_movement.y = 1.0f;
    }
    
    else if (keys[SDL_SCANCODE_S]) {
        player1_movement.y = -1.0f;
    }
    
    if (keys[SDL_SCANCODE_UP]) {
        player2_movement.y = 1.0f;
    }
    
    else if (keys[SDL_SCANCODE_DOWN]) {
        player2_movement.y = -1.0f;
    }
    
}

void Update() {
    float ticks = (float)SDL_GetTicks() / 1000.0f;
    float deltaTime = ticks - lastTicks;
    lastTicks = ticks;
    
    // Add (direction * units per second * elapsed time)
    player1_position += player1_movement * player_speed * deltaTime;
    player2_position += player2_movement * player_speed * deltaTime;
    
    if (player1_position.y > 3.25f) {
        player1_position.y = 3.25f;
    }
    
    else if (player1_position.y < -3.25f) {
        player1_position.y = -3.25f;
    }
    
    if (player2_position.y > 3.25f) {
        player2_position.y = 3.25f;
    }
    
    else if (player2_position.y < -3.25f) {
        player2_position.y = -3.25f;
    }

    egg_position += egg_movement * egg_speed * deltaTime;
    
    if (egg_position.y > 3.5f) {
        egg_position.y = 3.5f;
        if ((egg_direction == 1) || (egg_direction == 2)) {
            egg_direction = 7;
        }
        else if (egg_direction == 3)  {
            egg_direction = 5;
        }
        egg_movement = EggPhysics(egg_direction);
    }
    
    else if (egg_position.y < -3.5f) {
        egg_position.y = -3.5f;
        if ((egg_direction == 5) || (egg_direction == 6)) {
            egg_direction = 3;
        }
        else if (egg_direction == 7)  {
            egg_direction = 1;
        }
        egg_movement = EggPhysics(egg_direction);
    }
    
    if (egg_position.x > 4.75f) {
        egg_position.x = 4.75f;
        egg_speed = 0.0f;
        player_speed = 0.0f;
    }
    else if (egg_position.x < -4.75f) {
        egg_position.x = -4.75f;
        egg_speed = 0.0f;
        player_speed = 0.0f;
    }
    
    if (HasCollided(player1_position, player1_dimensions, egg_position, egg_dimensions)) {
        if (egg_direction == 3)  {
            egg_direction = 1;
        }
        else if (egg_direction == 4)  {
            if (player1_movement.y > 0) {
                egg_direction = 1;
            }
            else {
                egg_direction = 7;
            }
        }
        else if (egg_direction == 5)  {
            egg_direction = 7;
        }
        egg_speed += 0.1f;
        egg_movement = EggPhysics(egg_direction);
    }
    else if (HasCollided(player2_position, player2_dimensions, egg_position, egg_dimensions)) {
        if (egg_direction == 1)  {
            egg_direction = 3;
        }
        else if (egg_direction == 0)  {
            if (player2_movement.y > 0) {
                egg_direction = 3;
            }
            else {
                egg_direction = 5;
            }
        }
        else if (egg_direction == 7)  {
            egg_direction = 5;
        }
        egg_speed += 0.1f;
        egg_movement = EggPhysics(egg_direction);
        
    }
    
    player1Matrix = glm::mat4(1.0f);
    player1Matrix = glm::translate(player1Matrix, player1_position);
    
    player2Matrix = glm::mat4(1.0f);
    player2Matrix = glm::translate(player2Matrix, player2_position);
    
    eggMatrix = glm::mat4(1.0f);
    eggMatrix = glm::translate(eggMatrix, egg_position);
    eggMatrix = glm::scale(eggMatrix, glm::vec3(0.5f, 0.5f, 1.0f));
    
}

void Render() {
    
    float vertices[] = { -0.5, -0.5, 0.5, -0.5, 0.5, 0.5, -0.5, -0.5, 0.5, 0.5, -0.5, 0.5 };
    float texCoords[] = { 0.0, 1.0, 1.0, 1.0, 1.0, 0.0, 0.0, 1.0, 1.0, 0.0, 0.0, 0.0 };
    
    glClear(GL_COLOR_BUFFER_BIT);
    
    glVertexAttribPointer(program.positionAttribute, 2, GL_FLOAT, false, 0, vertices);
    glEnableVertexAttribArray(program.positionAttribute);
    
    glVertexAttribPointer(program.texCoordAttribute, 2, GL_FLOAT, false, 0, texCoords);
    glEnableVertexAttribArray(program.texCoordAttribute);
    
    program.SetModelMatrix(player1Matrix);
    glBindTexture(GL_TEXTURE_2D, player1TextureID);
    glDrawArrays(GL_TRIANGLES, 0, 6);
    
    program.SetModelMatrix(player2Matrix);
    glBindTexture(GL_TEXTURE_2D, player2TextureID);
    glDrawArrays(GL_TRIANGLES, 0, 6);
    
    program.SetModelMatrix(eggMatrix);
    glBindTexture(GL_TEXTURE_2D, eggTextureID);
    glDrawArrays(GL_TRIANGLES, 0, 6);
    
    glDisableVertexAttribArray(program.positionAttribute);
    glDisableVertexAttribArray(program.texCoordAttribute);

    SDL_GL_SwapWindow(displayWindow);
}

void Shutdown() {
    SDL_Quit();
}

int main(int argc, char* argv[]) {
    Initialize();
    
    while (gameIsRunning) {
        ProcessInput();
        Update();
        Render();
    }
    
    Shutdown();
    return 0;
}
