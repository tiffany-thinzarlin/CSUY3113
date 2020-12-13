#include "Entity.hpp"

Entity::Entity()
{
    position = glm::vec3(0);
    speed = 0;
    movement = glm::vec3(0);
    acceleration = glm::vec3(0);
    velocity = glm::vec3(0);
    
    modelMatrix = glm::mat4(1.0f);
}

bool Entity::CheckCollision(Entity *other){
    if ((isActive == false) || other->isActive == false) return false;
    float xdist = fabs(position.x - other->position.x) - ((width + other->width)/2.0f);
    float ydist = fabs(position.y - other->position.y) - ((height + other->height)/2.0f);
    
    if (xdist < 0 && ydist < 0 ) return true;
    
    return false;
}

 void Entity::CheckCollisionsY(Entity *objects, int objectCount)
{
    for (int i = 0; i < objectCount; i++)
    {
        Entity *object = &objects[i];
        if (CheckCollision(object))
        {
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
        collidedTop = true;
    }
    else if (map->IsSolid(top_left, &penetration_x, &penetration_y) && velocity.y > 0) {
        position.y -= penetration_y;
        velocity.y = 0;
        collidedTop = true;
    }
    else if (map->IsSolid(top_right, &penetration_x, &penetration_y) && velocity.y > 0) {
        position.y -= penetration_y;
        velocity.y = 0;
        collidedTop = true;
    }
    if (map->IsSolid(bottom, &penetration_x, &penetration_y) && velocity.y < 0) {
        position.y += penetration_y;
        velocity.y = 0;
        collidedBottom = true;
    }
    else if (map->IsSolid(bottom_left, &penetration_x, &penetration_y) && velocity.y < 0) {
        position.y += penetration_y;
        velocity.y = 0;
        collidedBottom = true;
    }
    else if (map->IsSolid(bottom_right, &penetration_x, &penetration_y) && velocity.y < 0) {
    position.y += penetration_y;
    velocity.y = 0;
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
        collidedLeft = true;
}
    if (map->IsSolid(right, &penetration_x, &penetration_y) && velocity.x > 0) {
        position.x -= penetration_x;
        velocity.x = 0;
        collidedRight = true;
    }
    
}
    
void Entity::AIWalker(){
    switch (aiState){
        case HORIZONTAL:
            if (position.x < 3){
                movement = glm::vec3(1.0f,0,0);
                acceleration = glm::vec3(2.0f,0,0);
                }
            else if (position.x > 10){
                movement = glm::vec3(-1.0f,0,0);
                acceleration = glm::vec3(-2.0f,0,0);
                }
            break;
        case VERTICAL:
            if (position.y < -4){
                acceleration = glm::vec3(0,1,0);
            }
            else if (position.y > -2){
                acceleration = glm::vec3(0,-1,0);
            }
            break;


    }
}

void Entity::AICIRCLE(Entity *player){
    switch (aiState)
    {
        case LEFTCIRCLE:
            if(position.x <= 4.0f && position.y < -5){
                movement = glm::vec3{-1.0f, 1.0f, 0};
                velocity.y = 1.0f;
                acceleration = glm::vec3(-0.1f, 0.1f, 0);
            }
            else if(position.x <= 3.0f && position.y >= -4.0f){
                movement = glm::vec3{1.0f, 1.0f, 0};
                velocity.y = 1.0f;
                acceleration = glm::vec3(0.1f, 0.1f, 0);
            }
            else if(position.x > 4.0f && position.y>=-3.0f){
                movement = glm::vec3{1.0f, -1.0f, 0};
                velocity.y = -1.0f;
                acceleration = glm::vec3(0.1f, -0.1f, 0);
            }
            else if(position.x > 5.0f && position.y <-4.0f){
                movement = glm::vec3{-1.0f, -1.0f, 0};
                velocity.y = -1.0f;
                acceleration = glm::vec3(-0.1f, -0.1f, 0);
            }
            break;
        case RIGHTCIRCLE:
            if(position.x <= 9.0f && position.y < -5){
                movement = glm::vec3{-1.0f, 1.0f, 0};
                velocity.y = 1.0f;
                acceleration = glm::vec3(-0.1f, 0.1f, 0);
            }
            else if(position.x <= 8.0f && position.y >= -4.0f){
                movement = glm::vec3{1.0f, 1.0f, 0};
                velocity.y = 1.0f;
                acceleration = glm::vec3(0.1f, 0.1f, 0);
            }
            else if(position.x > 9.0f && position.y>=-3.0f){
                movement = glm::vec3{1.0f, -1.0f, 0};
                velocity.y = -1.0f;
                acceleration = glm::vec3(0.1f, -0.1f, 0);
            }
            else if(position.x > 10.0f && position.y <-4.0f){
                movement = glm::vec3{-1.0f, -1.0f, 0};
                velocity.y = -1.0f;
                acceleration = glm::vec3(-0.1f, -0.1f, 0);
            }
            break;
        case CENTERCIRCLE:
            if (position.x < 2){
                movement = glm::vec3(1,0,0);
            }
            else if (position.x > 5){
                movement = glm::vec3(-1,0,0);
            }
            break;
    }
}

void Entity::AI(Entity *player){
    switch(aiType) {
        case WALKER:
            AIWalker();
            break;
        case CIRCLE:
            AICIRCLE(player);
            break;
    }
}

bool Entity::CheckCollideTop(Entity *other){
    if(EnemyEat(other)){
        if (velocity.y < 0) {
            return true;

        }
    }
    return false;
}

bool Entity::EnemyEat(Entity *other){
    if ((isActive == false) || other->isActive == false) return false;
    float xdist = (fabs(position.x - other->position.x) - ((width + other->width)/2.0f))+0.7f;
    float ydist = fabs(position.y - other->position.y) - ((height + other->height)/2.0f)+0.7f;
    
    if (xdist < 0 && ydist < 0 ) return true;
    
    return false;
}

bool Entity::EatCat(Entity *other){
    if ((isActive == false) || other->isActive == false) return false;
    float xdist = (fabs(position.x - other->position.x) - ((width + other->width)/2.0f))+0.7f;
    float ydist = fabs(position.y - other->position.y) - ((height + other->height)/2.0f)+0.7f;
    
    if (xdist < 0 && ydist < 0 ){
        return true;
    }
    
    return false;
}

void Entity::Update(float deltaTime, Entity *player, Entity *objects, int objectCount, Map *map)
{
    if (isActive == false) return;
    
    collidedTop = false;
    collidedBottom = false;
    collidedLeft = false;
    collidedRight = false;
    
    if (entityType == ENEMY){
        AI(player);
        velocity.x = movement.x * speed;
        velocity += acceleration * deltaTime;
        
        position.y += velocity.y * deltaTime; // Move on Y
        CheckCollisionsY(map);
        
        position.x += velocity.x * deltaTime; // Move on X
        CheckCollisionsX(map);
        
        modelMatrix = glm::mat4(1.0f);
        modelMatrix = glm::translate(modelMatrix, position);
        modelMatrix = glm::scale(modelMatrix, glm::vec3(5.5f,5.5f,1.0f));
        
    }
    else if(entityType == CAT){
        velocity.x = movement.x * speed;
        velocity += acceleration * deltaTime;
        
        position.y += velocity.y * deltaTime; // Move on Y
        CheckCollisionsY(map);
        
        position.x += velocity.x * deltaTime; // Move on X
        CheckCollisionsX(map);
        
        modelMatrix = glm::mat4(1.0f);
        modelMatrix = glm::translate(modelMatrix, position);
        modelMatrix = glm::scale(modelMatrix, glm::vec3(0.7f,0.7f,1.0f));
    }
    else{
        if (jump){
            jump = false;
            velocity.y += jumpPower;
        }
    
        velocity.x = movement.x * speed;
        velocity += acceleration * deltaTime;
    
        position.y += velocity.y * deltaTime; // Move on Y
        CheckCollisionsY(map);
        //CheckCollisionsY(objects, objectCount); // Fix if needed
        position.x += velocity.x * deltaTime; // Move on X
        CheckCollisionsX(map);
        //CheckCollisionsX(objects, objectCount);// Fix if needed
    
        modelMatrix = glm::mat4(1.0f);
        modelMatrix = glm::translate(modelMatrix, position);
        modelMatrix = glm::scale(modelMatrix, glm::vec3(2.0f,2.0f,2.0f));
    }
}

void Entity::Render(ShaderProgram *program) {
    
    if (isActive == false) return;
    
    program->SetModelMatrix(modelMatrix);

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
