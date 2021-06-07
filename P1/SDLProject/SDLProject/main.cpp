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
glm::mat4 viewMatrix, tamaMatrix, pokeMatrix, projectionMatrix;

GLuint tamaTextureID;
GLuint pokeTextureID;

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

float tama_x = 0;
float lastTicks = 0.0f;
float poke_rotate = 0;

void Initialize() {
    SDL_Init(SDL_INIT_VIDEO);
    displayWindow = SDL_CreateWindow("2D Scene!", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 640, 480, SDL_WINDOW_OPENGL);
    SDL_GLContext context = SDL_GL_CreateContext(displayWindow);
    SDL_GL_MakeCurrent(displayWindow, context);
    
#ifdef _WINDOWS
    glewInit();
#endif
    
    glViewport(0, 0, 640, 480);
    
    program.Load("shaders/vertex_textured.glsl", "shaders/fragment_textured.glsl");
    
    viewMatrix = glm::mat4(1.0f);
    tamaMatrix = glm::mat4(1.0f);
    
    pokeMatrix = glm::mat4(1.0f);
    pokeMatrix = glm::translate((pokeMatrix), glm::vec3(0.0f, 1.0f, 0.0f));
    
    
    projectionMatrix = glm::ortho(-5.0f, 5.0f, -3.75f, 3.75f, -1.0f, 1.0f);
    
    program.SetProjectionMatrix(projectionMatrix);
    program.SetViewMatrix(viewMatrix);
    // program.SetColor(1.0f, 0.0f, 0.0f, 1.0f);
    
    glUseProgram(program.programID);
    
    glClearColor(0.2f, 0.2f, 0.2f, 1.0f);
    glEnable(GL_BLEND);
    
    // Good setting for transparency
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    
    tamaTextureID = LoadTexture("tamagotchi.png");
    pokeTextureID = LoadTexture("pokemon.png");
}

void ProcessInput() {
    SDL_Event event;
    while (SDL_PollEvent(&event)) {
        if (event.type == SDL_QUIT || event.type == SDL_WINDOWEVENT_CLOSE) {
            gameIsRunning = false;
        }
    }
}

bool moveLeft = false;

void Update() {
    float ticks = (float)SDL_GetTicks() / 1000.0f;
    float deltaTime = ticks - lastTicks;
    
    lastTicks = ticks;
    
    poke_rotate = 90.0f * deltaTime;
    
    if (tama_x > 4.0f) {
        moveLeft = true;
    }
    if (tama_x < -4.0f) {
        moveLeft = false;
    }
    
    if (moveLeft) {
        tama_x -= 1.0f * deltaTime;
    } else {
        tama_x += 1.0f * deltaTime;
    }
    
    tamaMatrix = glm::mat4(1.0f);
    tamaMatrix = glm::translate((tamaMatrix), glm::vec3(tama_x, 0.0f, 0.0f));
    
    pokeMatrix = glm::rotate(pokeMatrix, glm::radians(poke_rotate), glm::vec3(0.0f, 0.0f, 1.0f));
    
    
    // modelMatrix = glm::mat4(1.0f);
    
    /* // Moving Vertically Up
    modelMatrix = glm::translate(modelMatrix, glm::vec3(0.0f, 0.01f, 0.0f));
     */
    
    /* // Rotating
    modelMatrix = glm::rotate(modelMatrix, glm::radians(1.0f), glm::vec3(0.0f, 0.0f, 1.0f));
     */
    
    /* // Scaling
    modelMatrix = glm::scale(modelMatrix, glm::vec3(1.01f, 1.01f, 1.0f));
     */
}

void Render() {
    
    float vertices[] = { -0.5, -0.5, 0.5, -0.5, 0.5, 0.5, -0.5, -0.5, 0.5, 0.5, -0.5, 0.5 };
    float texCoords[] = { 0.0, 1.0, 1.0, 1.0, 1.0, 0.0, 0.0, 1.0, 1.0, 0.0, 0.0, 0.0 };
    
    glClear(GL_COLOR_BUFFER_BIT);
    
    glVertexAttribPointer(program.positionAttribute, 2, GL_FLOAT, false, 0, vertices);
    glEnableVertexAttribArray(program.positionAttribute);
    
    glVertexAttribPointer(program.texCoordAttribute, 2, GL_FLOAT, false, 0, texCoords);
    glEnableVertexAttribArray(program.texCoordAttribute);
    
    program.SetModelMatrix(tamaMatrix);
    glBindTexture(GL_TEXTURE_2D, tamaTextureID);
    glDrawArrays(GL_TRIANGLES, 0, 6);
    
    program.SetModelMatrix(pokeMatrix);
    glBindTexture(GL_TEXTURE_2D, pokeTextureID);
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
