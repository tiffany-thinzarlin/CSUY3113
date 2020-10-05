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
#include "Paddle.hpp"
#include "Ball.hpp"

#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

struct GameState{
    Paddle *player1;
    Paddle *player2;
    Ball *ball;
};
GameState state;

SDL_Window* displayWindow;
bool gameIsRunning = true;

ShaderProgram program;
glm::mat4 viewMatrix, modelMatrix, projectionMatrix;
//paddle1Matrix, paddle2Matrix;

bool initialKey = false;
float lastMovementX = -1.0f;
float lastMovementY = 1.0f;

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
 

void Initialize() {
    SDL_Init(SDL_INIT_VIDEO);
    displayWindow = SDL_CreateWindow("my second project!", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 640, 480, SDL_WINDOW_OPENGL);
    SDL_GLContext context = SDL_GL_CreateContext(displayWindow);
    SDL_GL_MakeCurrent(displayWindow, context);
    
#ifdef _WINDOWS
    glewInit();
#endif
    
    glViewport(0, 0, 640, 480);
    
    program.Load("shaders/vertex_textured.glsl", "shaders/fragment_textured.glsl");
    
    viewMatrix = glm::mat4(1.0f);
    //paddle1Matrix = glm::mat4(1.0f);
    //paddle2Matrix = glm::mat4(1.0f);

    modelMatrix = glm::mat4(1.0f);

    projectionMatrix = glm::ortho(-5.0f, 5.0f, -3.75f, 3.75f, -1.0f, 1.0f);
    
    program.SetProjectionMatrix(projectionMatrix);
    program.SetViewMatrix(viewMatrix);
    program.SetColor(1.0f, 0.0f, 0.0f, 1.0f); /*set the color to red*/
    
    glUseProgram(program.programID);
    
    glClearColor(0.2f, 0.2f, 0.2f, 1.0f);
    
    glEnable(GL_BLEND);

    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    
     state.player1 = new Paddle();
     state.player1->position = glm::vec3(0);
     state.player1->movement = glm::vec3(0);
     state.player1->speed = 1.0f;
    state.player1->textureID = LoadTexture("white_bar.png");
    state.player1->position = glm::vec3(-4.75f, 0.0f, 0.0f);
    
    state.player2 = new Paddle();
     state.player2->position = glm::vec3(0);
     state.player2->movement = glm::vec3(0);
     state.player2->speed = 1.0f;
    state.player2->textureID = LoadTexture("white_bar.png");
    state.player2->position = glm::vec3(4.75f, 0.0f, 0.0f);
    
    state.ball = new Ball();
     state.ball->position = glm::vec3(0);
     state.ball->movement = glm::vec3(0);
     state.ball->speed = 1.0f;
    state.ball->textureID = LoadTexture("white_bar.png");

}

void ProcessInput() {
        state.player1->movement = glm::vec3(0);
        state.player2->movement = glm::vec3(0);
        state.ball->movement = glm::vec3(0);
    
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
                            //player_movement.x = 1.0f;
                            
                            break;
                        case SDLK_SPACE:
                            // Some sort of action
                            break;
                    }
                    break; // SDL_KEYDOWN
                }
        }
         
         const Uint8 *keys = SDL_GetKeyboardState(NULL);
    if(keys[SDL_SCANCODE_SPACE]){
        initialKey = true;
    }

        if (keys[SDL_SCANCODE_W]) {
            state.player2->movement.y = 1.0f;
        }
        else if (keys[SDL_SCANCODE_S]) {
        state.player2->movement.y = -1.0f;
        }
         //can hold only up or down
         if (keys[SDL_SCANCODE_UP]) {
             state.player1->movement.y = 1.0f;
         }
         else if (keys[SDL_SCANCODE_DOWN]) {
             state.player1->movement.y = -1.0f;
         }
         
         if(glm::length(state.player1->movement) > 1.0f){
             state.player1->movement = glm::normalize(state.player1->movement);
         }
        if(glm::length(state.player2->movement) > 1.0f){
        state.player2->movement = glm::normalize(state.player2->movement);
        }
    if(glm::length(state.player2->movement) > 1.0f){
    state.ball->movement = glm::normalize(state.player2->movement);
    }

    }

float lastTicks = 0.0f;


void Update() {
    float ticks = (float)SDL_GetTicks() / 1000.0f;
    float deltaTime = ticks - lastTicks;
    lastTicks = ticks;
    
    if(state.ball->position[0]<=-4.80 || state.ball->position[0]>=4.80){
        deltaTime = 0;
    }
    state.ball->movement.x = lastMovementY;
    state.ball->movement.y = lastMovementY;
    
    float xdist1 = fabs((state.ball->position.x)-(state.player1->position.x))-(0.3f);
    float xdist2 = fabs((state.ball->position.x)-(state.player2->position.x))-(0.3f);
    float ydist1 = fabs((state.ball->position.y)-(state.player1->position.y))-(1.15f);
    float ydist2 = fabs((state.ball->position.y)-(state.player2->position.y))-(1.15f);
    
    if(xdist1<0 && ydist1<0){
        state.ball->movement.x = 1.0f;
        lastMovementX = 1.0f;
        state.ball->movement.y = lastMovementY;
    }
    else if(xdist2<0 && ydist2<0){
        state.ball->movement.x = -1.0f;
        lastMovementX = -1.0f;
        state.ball->movement.y = lastMovementY;
    }
    else if(state.ball->position[1]>=3.65){
        state.ball->movement.x = lastMovementX;
        state.ball->movement.y = -1.0f;
        lastMovementY = -1.0f;
    }
    else if(state.ball->position[1]<=-3.65){
        state.ball->movement.x = lastMovementX;
        state.ball->movement.y = 1.0f;
        lastMovementY = 1.0f;
    }
    else{
        state.ball->movement.x = lastMovementX;
        state.ball->movement.y = lastMovementY;
    }
    state.player1->Update(deltaTime);
    state.player2->Update(deltaTime);
    if (initialKey == true){
        state.ball->Update(deltaTime);
    }
    
    
}

void Render() {
    
    glClear(GL_COLOR_BUFFER_BIT);

    state.player1->Render(&program);

    state.player2->Render(&program);
    
    state.ball->Render(&program);
    
    
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


