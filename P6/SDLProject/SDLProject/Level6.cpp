#include "Level6.h"
#define LEVEL6_WIDTH 14
#define LEVEL6_HEIGHT 8
#define LEVEL6_ENEMY_COUNT 6
#define LEVEL6_CAT_COUNT 6
GLuint fontTextureID6;
glm::vec3 randomvec16 = glm::vec3(1, -1, 0);
glm::vec3 randomvec66 = glm::vec3(5, -1, 0);
unsigned int level6_data[] =
{
    2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2,
    2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 2,
    2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 2,
    2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 2,
    2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 2,
    2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 2,
    2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 2,
    2, 2, 2, 0, 0, 0, 0, 0, 0, 0, 0, 2, 2, 2
};

void Level6::Initialize() {
    
    state.nextScene = -1;
    fontTextureID6 = Util::LoadTexture("font1.png");
    GLuint mapTextureID = Util::LoadTexture("rock.png");
    state.map = new Map(LEVEL6_WIDTH, LEVEL6_HEIGHT, level6_data, mapTextureID, 1.0f, 4, 1);

    state.player = new Entity();
    state.player->entityType = PLAYER;
    state.player->position = glm::vec3(1, -6, 0);
    state.player->movement = glm::vec3(0);
    state.player->acceleration = glm::vec3(0,-9.81f,0);
    state.player->speed = 5.0f;
    state.player->textureID = Util::LoadTexture("player.png");
    
    state.player->height = 0.8f;
    state.player->width = 0.8f;
    
    state.player->jumpPower = 5.0f;
    
    state.enemies = new Entity[LEVEL6_ENEMY_COUNT];
    GLuint enemyTextureID = Util::LoadTexture("alien.png");
    
    state.enemies[0].entityType = ENEMY;
    state.enemies[0].textureID = enemyTextureID;
    state.enemies[0].position = glm::vec3(9, -3 ,0);
    state.enemies[0].movement = glm::vec3(1,-1,0);
    state.enemies[0].acceleration = glm::vec3(0.5f,-0.5f,0);
    state.enemies[0].speed = 1;
    state.enemies[0].aiType = CIRCLE;
    state.enemies[0].aiState = RIGHTCIRCLE;
    state.enemies[0].isActive = true;
    
    state.enemies[1].entityType = ENEMY;
    state.enemies[1].textureID = enemyTextureID;
    state.enemies[1].position = glm::vec3(4, -5 ,0);
    state.enemies[1].movement = glm::vec3(-1,1,0);
    state.enemies[1].acceleration = glm::vec3(-0.5f,0.5f,0);
    state.enemies[1].speed = 1;
    state.enemies[1].aiType = CIRCLE;
    state.enemies[1].aiState = LEFTCIRCLE;
    state.enemies[1].isActive = true;
    
    state.enemies[2].entityType = ENEMY;
    state.enemies[2].textureID = enemyTextureID;
    state.enemies[2].position = glm::vec3(3, -3 ,0);
    state.enemies[2].movement = glm::vec3(0,1,0);
    state.enemies[2].acceleration = glm::vec3(0,0.5f,0);
    state.enemies[2].speed = 1;
    state.enemies[2].aiType = WALKER;
    state.enemies[2].aiState = VERTICAL;
    state.enemies[2].isActive = true;
    
    state.enemies[3].entityType = ENEMY;
    state.enemies[3].textureID = enemyTextureID;
    state.enemies[3].position = glm::vec3(10, -3 ,0);
    state.enemies[3].movement = glm::vec3(0,-1,0);
    state.enemies[3].acceleration = glm::vec3(0,-0.5f,0);
    state.enemies[3].speed = 1;
    state.enemies[3].aiType = WALKER;
    state.enemies[3].aiState = VERTICAL;
    state.enemies[3].isActive = true;
    
    state.enemies[4].entityType = ENEMY;
    state.enemies[4].textureID = enemyTextureID;
    state.enemies[4].position = glm::vec3(6, -6 ,0);
    state.enemies[4].movement = glm::vec3(1,0,0);
    state.enemies[4].acceleration = glm::vec3(0.5,0,0);
    state.enemies[4].speed = 1;
    state.enemies[4].aiType = WALKER;
    state.enemies[4].aiState = HORIZONTAL;
    state.enemies[4].isActive = true;
    
    state.enemies[5].entityType = ENEMY;
    state.enemies[5].textureID = enemyTextureID;
    state.enemies[5].position = glm::vec3(6, -1 ,0);
    state.enemies[5].movement = glm::vec3(-1,0,0);
    state.enemies[5].acceleration = glm::vec3(-0.5,0,0);
    state.enemies[5].speed = 1;
    state.enemies[5].aiType = WALKER;
    state.enemies[5].aiState = HORIZONTAL;
    state.enemies[5].isActive = true;
    
    state.cat = new Entity[LEVEL6_CAT_COUNT];
    GLuint catTextureID = Util::LoadTexture("cat.png");
    for (int i = 0; i < LEVEL6_CAT_COUNT; i++){
        state.cat[i].entityType = CAT;
        state.cat[i].textureID = catTextureID;
        state.cat[i].isActive = true;
    }
    
    state.cat[0].position = glm::vec3(4, -4,0);
    state.cat[1].position = glm::vec3(9, -4,0);
    state.cat[2].position = glm::vec3(6, -7,0);
    state.cat[3].position = glm::vec3(6, -1,0);
    state.cat[4].position = glm::vec3(3, -3,0);
    state.cat[5].position = glm::vec3(10, -3,0);

}
int Level6::Update(float deltaTime, int playerLives) {
    state.player->Update(deltaTime, state.player, state.enemies, LEVEL6_ENEMY_COUNT, state.map);
    for(int i = 0; i < LEVEL6_ENEMY_COUNT; i++){
        state.enemies[i].Update(deltaTime, state.player, state.enemies, LEVEL6_ENEMY_COUNT, state.map);
    }
    for(int i = 0; i < LEVEL6_CAT_COUNT; i++){
        state.cat[i].Update(deltaTime, state.player, state.enemies, LEVEL6_ENEMY_COUNT, state.map);
    }
    
    if(state.player->EnemyEat(&state.enemies[0])==true){
        state.player->isActive=false;
    }
    else if(state.player->EnemyEat(&state.enemies[1])==true){
       state.player->isActive=false;
    }
    else if(state.player->EnemyEat(&state.enemies[2])==true){
        state.player->isActive=false;
    }
    else if(state.player->EnemyEat(&state.enemies[3])==true){
        state.player->isActive=false;
    }
    else if(state.player->EnemyEat(&state.enemies[4])==true){
        state.player->isActive=false;
    }
    else if(state.player->EnemyEat(&state.enemies[5])==true){
        state.player->isActive=false;
    }

    if (state.player->position.y < -8){
        state.player->isActive=false;
    }
    for (int i = 0; i < LEVEL6_CAT_COUNT; i++){
        if(state.player->EatCat(&state.cat[i])==true){
            state.cat[i].isActive=false;
        }
    }

    if (state.player->isActive == false){
        playerLives = playerLives - 1;
        if (playerLives > 0){
            state.nextScene = 6;
        }
    }
    
    return playerLives;
}
void Level6::Render(ShaderProgram *program, int playerLives) {
    state.map->Render(program);
    state.player->Render(program);
    for(int i = 0; i < LEVEL6_ENEMY_COUNT; i++){
        state.enemies[i].Render(program);
    }
    
    for(int i = 0; i < LEVEL6_CAT_COUNT; i++){
        state.cat[i].Render(program);
    }
    if (state.cat[0].isActive == false && state.cat[1].isActive == false && state.cat[2].isActive == false && state.cat[3].isActive == false && state.cat[4].isActive == false && state.cat[5].isActive == false && playerLives > 0 && state.player->position.x > 11.0f && state.player->position.y<-6.0f) {
        Util::DrawText(program, fontTextureID6 , "YOU WIN!!!", 0.8, -0.5f, randomvec66);
       // playerLives = 5;
    }

    if (playerLives == 1){
        Util::DrawText(program, fontTextureID6 , "Lives : 1", 0.8, -0.5f, randomvec16);
    }
    if (playerLives == 2){
        Util::DrawText(program, fontTextureID6 , "Lives : 2", 0.8, -0.5f, randomvec16);
    }
    if (playerLives == 3){
        Util::DrawText(program, fontTextureID6 , "Lives : 3", 0.8, -0.5f, randomvec16);
    }
    if (playerLives == 0){
        Util::DrawText(program, fontTextureID6 , "you lost :(", 0.8, -0.5f, randomvec66);
    }
    
    
}

