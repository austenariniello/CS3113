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

ShaderProgram program;
glm::mat4 viewMatrix, modelMatrix, projectionMatrix;

// Start at 0, 0, 0
glm::vec3 player_position = glm::vec3(0, 0, 0);

// Don’t go anywhere (yet).
glm::vec3 player_movement = glm::vec3(0, 0, 0);

float player_speed = 1.0f;

GLuint playerTextureID;

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

float player_x = 0;
float lastTicks = 0.0f;
float player_rotate = 0;

void Initialize() {
    SDL_Init(SDL_INIT_VIDEO);
    displayWindow = SDL_CreateWindow("Lectures!", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 640, 480, SDL_WINDOW_OPENGL);
    SDL_GLContext context = SDL_GL_CreateContext(displayWindow);
    SDL_GL_MakeCurrent(displayWindow, context);
    
#ifdef _WINDOWS
    glewInit();
#endif
    
    glViewport(0, 0, 1280, 960);
    
    program.Load("shaders/vertex_textured.glsl", "shaders/fragment_textured.glsl");
    
    viewMatrix = glm::mat4(1.0f);
    modelMatrix = glm::mat4(1.0f);
    
    projectionMatrix = glm::ortho(-5.0f, 5.0f, -3.75f, 3.75f, -1.0f, 1.0f);
    
    program.SetProjectionMatrix(projectionMatrix);
    program.SetViewMatrix(viewMatrix);
    // program.SetColor(1.0f, 0.0f, 0.0f, 1.0f);
    
    glUseProgram(program.programID);
    
    glClearColor(1.0f, 0.769f, 0.922f, 1.0f);
    glEnable(GL_BLEND);
    
    // Good setting for transparency
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    
    playerTextureID = LoadTexture("ctg.png");
}

void ProcessInput() {
    
    player_movement = glm::vec3(0);
    
    SDL_Event event;
    while (SDL_PollEvent(&event)) {
        switch (event.type) {
            case SDL_QUIT:
            case SDL_WINDOWEVENT_CLOSE:
                gameIsRunning = false;
                break;

            case SDL_KEYDOWN:
                switch (event.key.keysym.sym) {
                    case SDLK_LEFT:
                        // Move the player left
                        break;

                    case SDLK_RIGHT:
                        // Move the player right
                        break;

                    case SDLK_SPACE:
                        // Some sort of action
                        break;
            }
            break; // SDL_KEYDOWN
        }
    }
    
    const Uint8 *keys = SDL_GetKeyboardState(NULL);
    
    if (keys[SDL_SCANCODE_LEFT]) {
        player_movement.x = -1.0f;
    }
    
    else if (keys[SDL_SCANCODE_RIGHT]) {
        player_movement.x = 1.0f;
    }
    
    if (keys[SDL_SCANCODE_UP]) {
        player_movement.y = 1.0f;
    }
    
    else if (keys[SDL_SCANCODE_DOWN]) {
        player_movement.y = -1.0f;
    }
    
    if (glm::length(player_movement) > 1.0f) {
        player_movement = glm::normalize(player_movement);
    }
}

bool moveLeft = false;

void Update() {
    float ticks = (float)SDL_GetTicks() / 1000.0f;
    float deltaTime = ticks - lastTicks;
    lastTicks = ticks;
    
    // Add (direction * units per second * elapsed time)
    player_position += player_movement * player_speed * deltaTime;
    
    modelMatrix = glm::mat4(1.0f);
    modelMatrix = glm::translate(modelMatrix, player_position);
}

/*
 
// Translation, Rotation, and Scaling Code

void Update() {
    float ticks = (float)SDL_GetTicks() / 1000.0f;
    float deltaTime = ticks - lastTicks;
    
    lastTicks = ticks;
    
    player_rotate += -90.0f * deltaTime;
    player_x += 1.0f *  deltaTime;
    
    modelMatrix = glm::mat4(1.0f);
    modelMatrix = glm::translate((modelMatrix), glm::vec3(player_x, 0.0f, 0.0f));
    modelMatrix = glm::rotate(modelMatrix, glm::radians(player_rotate), glm::vec3(0.0f, 0.0f, 1.0f));
    
    // modelMatrix = glm::mat4(1.0f);
    
    // Moving Vertically Up
    // modelMatrix = glm::translate(modelMatrix, glm::vec3(0.0f, 0.01f, 0.0f));
    
    // Rotating
    // modelMatrix = glm::rotate(modelMatrix, glm::radians(1.0f), glm::vec3(0.0f, 0.0f, 1.0f));
    
    // Scaling
    // modelMatrix = glm::scale(modelMatrix, glm::vec3(1.01f, 1.01f, 1.0f));
}

*/

void Render() {
    
    float vertices[] = { -0.5, -0.5, 0.5, -0.5, 0.5, 0.5, -0.5, -0.5, 0.5, 0.5, -0.5, 0.5 };
    float texCoords[] = { 0.0, 1.0, 1.0, 1.0, 1.0, 0.0, 0.0, 1.0, 1.0, 0.0, 0.0, 0.0 };
    
    glClear(GL_COLOR_BUFFER_BIT);
    
    glVertexAttribPointer(program.positionAttribute, 2, GL_FLOAT, false, 0, vertices);
    glEnableVertexAttribArray(program.positionAttribute);
    
    glVertexAttribPointer(program.texCoordAttribute, 2, GL_FLOAT, false, 0, texCoords);
    glEnableVertexAttribArray(program.texCoordAttribute);
    
    program.SetModelMatrix(modelMatrix);
    glBindTexture(GL_TEXTURE_2D, playerTextureID);
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
