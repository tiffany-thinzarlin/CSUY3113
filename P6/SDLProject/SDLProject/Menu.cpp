//
//  Menu.cpp
//  SDLProject
//
//  Created by Tiffany Yan on 11/22/20.
//  Copyright © 2020 ctg. All rights reserved.
//

#include "Menu.h"
GLuint fontTextureID;
glm::vec3 randomvec = glm::vec3(-4.25f, 3, 0);
glm::vec3 randomvec22 = glm::vec3(-4.25f, -2, 0);
glm::vec3 randomvec20 = glm::vec3(-4.25f, -3, 0);

void Menu::Initialize() {
    state.nextScene = -1;

    fontTextureID = Util::LoadTexture("font1.png");
    
    
}
int Menu::Update(float deltaTime, int playerLives) {
    return 3;
}
void Menu::Render(ShaderProgram *program, int playerLives) {
    Util::DrawText(program, fontTextureID , "Collect da Kittens, not Aliens!", 0.8, -0.5f, randomvec);
    Util::DrawText(program, fontTextureID , "And land da spaceship on", 0.8, -0.5f, randomvec22);
    Util::DrawText(program, fontTextureID , "the other platform!", 0.8, -0.5f, randomvec20);
}
