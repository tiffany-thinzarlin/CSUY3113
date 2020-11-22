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

void Menu::Initialize() {
    state.nextScene = -1;

    fontTextureID = Util::LoadTexture("font1.png");
    
    
}
int Menu::Update(float deltaTime, int playerLives) {
    return 3;
}
void Menu::Render(ShaderProgram *program, int playerLives) {
    Util::DrawText(program, fontTextureID , "Step On Em or Get Eaten!!!", 0.8, -0.5f, randomvec);
}
