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
glm::mat4 viewMatrix, player1Matrix, player2Matrix, projectionMatrix;

// Start at 0, 0, 0
glm::vec3 player1_position = glm::vec3(0, 0, 0);
glm::vec3 player2_position = glm::vec3(0, 0, 0);

// Don’t go anywhere (yet).
glm::vec3 player1_movement = glm::vec3(0, 0, 0);
glm::vec3 player2_movement = glm::vec3(0, 0, 0);

float player_speed = 1.0f;
float player_x = 0;
float lastTicks = 0.0f;

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
    player1Matrix = glm::mat4(1.0f);
    player2Matrix = glm::mat4(1.0f);
    
    projectionMatrix = glm::ortho(-5.0f, 5.0f, -3.75f, 3.75f, -1.0f, 1.0f);
    
    program.SetProjectionMatrix(projectionMatrix);
    program.SetViewMatrix(viewMatrix);
    program.SetColor(1.0f, 0.0f, 0.0f, 1.0f);
    
    glUseProgram(program.programID);
    
    glClearColor(1.0f, 0.769f, 0.922f, 1.0f);
}

void ProcessInput() {
    
    player1_movement = glm::vec3(0);
    player2_movement = glm::vec3(0);
    
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

bool moveLeft = false;

void Update() {
    float ticks = (float)SDL_GetTicks() / 1000.0f;
    float deltaTime = ticks - lastTicks;
    lastTicks = ticks;
    
    // Add (direction * units per second * elapsed time)
    player1_position += player1_movement * player_speed * deltaTime;
    player2_position += player2_movement * player_speed * deltaTime;
    
    player1Matrix = glm::mat4(1.0f);
    player1Matrix = glm::translate(player1Matrix, player1_position);
    
    player2Matrix = glm::mat4(1.0f);
    player2Matrix = glm::translate(player2Matrix, player2_position);
}


void Render() {
    
    float vertices[] = { -0.5, -0.5, 0.5, -0.5, 0.5, 0.5, -0.5, -0.5, 0.5, 0.5, -0.5, 0.5 };
    
    glClear(GL_COLOR_BUFFER_BIT);
    
    program.SetModelMatrix(player1Matrix);
    glVertexAttribPointer(program.positionAttribute, 2, GL_FLOAT, false, 0, vertices);
    glEnableVertexAttribArray(program.positionAttribute);
    glDrawArrays(GL_TRIANGLES, 0, 3);
    glDisableVertexAttribArray(program.positionAttribute);

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
