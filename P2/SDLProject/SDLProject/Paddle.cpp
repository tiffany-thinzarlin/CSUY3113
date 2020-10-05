

#include "Paddle.hpp"

Paddle::Paddle()
{
position = glm::vec3(0);
speed = 0;
modelMatrix = glm::mat4(1.0f);
}

void Paddle::Update(float deltaTime)
{
    if(position[1]>=2.75){
        position[1] = 2.70;
    }
    else if(position[1]<=-2.75){
        position[1] = -2.70;
    }
    position += movement * speed * deltaTime;
    modelMatrix = glm::mat4(1.0f);
    modelMatrix = glm::translate(modelMatrix, position);
    
}


void Paddle::Render(ShaderProgram *program){
    program->SetModelMatrix(modelMatrix);
    float vertices[] = {-0.15,-1.0,0.15,-1.0,0.15,1.0,-0.15,-1.0,0.15,1.0,-0.15,1.0};
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
