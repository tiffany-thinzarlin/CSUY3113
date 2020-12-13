 #include "Level1.h"
#define LEVEL1_WIDTH 14
#define LEVEL1_HEIGHT 8
#define LEVEL1_ENEMY_COUNT 1
#define LEVEL1_CAT_COUNT 1

GLuint fontTextureID1;
glm::vec3 randomvec1 = glm::vec3(1, -1, 0);
glm::vec3 randomvec7 = glm::vec3(5, -1, 0);
unsigned int level1_data[] =
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

void Level1::Initialize() {
    
    state.nextScene = -1;
    fontTextureID1 = Util::LoadTexture("font1.png");
    GLuint mapTextureID = Util::LoadTexture("rock.png");
    state.map = new Map(LEVEL1_WIDTH, LEVEL1_HEIGHT, level1_data, mapTextureID, 1.0f, 4, 1);
    // Move over all of the player and enemy code from initialization.
    
    
    // Initialize Game Objects
    
    // Initialize Player
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
    
    state.enemies = new Entity[LEVEL1_ENEMY_COUNT];
    GLuint enemyTextureID = Util::LoadTexture("alien.png");
    
    state.enemies[0].entityType = ENEMY;
    state.enemies[0].textureID = enemyTextureID;
    state.enemies[0].position = glm::vec3(3, -5 ,0);
    state.enemies[0].speed = 1;
    state.enemies[0].aiType = CIRCLE;
    state.enemies[0].aiState = LEFTCIRCLE;
    state.enemies[0].isActive = false;
    
    state.cat = new Entity[LEVEL1_CAT_COUNT];
    GLuint catTextureID = Util::LoadTexture("cat.png");
    state.cat[0].entityType = CAT;
    state.cat[0].textureID = catTextureID;
    state.cat[0].position = glm::vec3(8, -3 ,0);
    state.cat[0].speed = 0;
    state.cat[0].isActive = true;
}
int Level1::Update(float deltaTime, int playerLives) {
    state.player->Update(deltaTime, state.player, state.enemies, LEVEL1_ENEMY_COUNT, state.map);
    state.enemies[0].Update(deltaTime, state.player, state.enemies, LEVEL1_ENEMY_COUNT, state.map);
    state.cat[0].Update(deltaTime, state.player, state.enemies, LEVEL1_ENEMY_COUNT, state.map);

    if(state.player->EnemyEat(&state.enemies[0])==true){
        state.player->isActive=false;
    }
    if (state.player->position.y < -8){
        state.player->isActive=false;
    }
    if(state.player->EatCat(&state.cat[0])==true){
        state.cat[0].isActive=false;
    }
    if (state.player->isActive == false){
        playerLives = playerLives - 1;
        if (playerLives > 0){
            state.nextScene = 1;
        }
    }
    
    if (state.cat[0].isActive == false && playerLives > 0 && state.player->position.x > 11.0f && state.player->position.y<-6.0f) {
        state.nextScene = 2;
    }
    return playerLives;
}
void Level1::Render(ShaderProgram *program, int playerLives) {
    state.map->Render(program);
    state.player->Render(program);
    state.enemies[0].Render(program);
    state.cat[0].Render(program);
    if (playerLives == 1){
        Util::DrawText(program, fontTextureID1 , "Lives : 1", 0.8, -0.5f, randomvec1);
    }
    if (playerLives == 2){
        Util::DrawText(program, fontTextureID1 , "Lives : 2", 0.8, -0.5f, randomvec1);
    }
    if (playerLives == 3){
        Util::DrawText(program, fontTextureID1 , "Lives : 3", 0.8, -0.5f, randomvec1);
    }
    if (playerLives == 0){
        Util::DrawText(program, fontTextureID1 , "you lost :(", 0.8, -0.5f, randomvec7);
    }
    
    
}

