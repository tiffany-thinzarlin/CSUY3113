  #include "Level3.h"
 #define LEVEL3_WIDTH 14
 #define LEVEL3_HEIGHT 8
 #define LEVEL3_ENEMY_COUNT 4
 #define LEVEL3_CAT_COUNT 2
 GLuint fontTextureID3;
 glm::vec3 randomvec3 = glm::vec3(1, -1, 0);
 glm::vec3 randomvec5 = glm::vec3(5, -1, 0);
 unsigned int level3_data[] =
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

 void Level3::Initialize() {
     
     state.nextScene = -1;
     fontTextureID3 = Util::LoadTexture("font1.png");
     GLuint mapTextureID = Util::LoadTexture("rock.png");
     state.map = new Map(LEVEL3_WIDTH, LEVEL3_HEIGHT, level3_data, mapTextureID, 1.0f, 4, 1);

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
     
     state.enemies = new Entity[LEVEL3_ENEMY_COUNT];
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
     
     state.cat = new Entity[LEVEL3_CAT_COUNT];
     GLuint catTextureID = Util::LoadTexture("cat.png");
     state.cat[0].entityType = CAT;
     state.cat[0].textureID = catTextureID;
     state.cat[0].position = glm::vec3(4, -4,0);
     state.cat[0].speed = 0;
     state.cat[0].isActive = true;
     
     state.cat[1].entityType = CAT;
     state.cat[1].textureID = catTextureID;
     state.cat[1].position = glm::vec3(9, -4,0);
     state.cat[1].speed = 0;
     state.cat[1].isActive = true;
 }
 int Level3::Update(float deltaTime, int playerLives) {
     state.player->Update(deltaTime, state.player, state.enemies, LEVEL3_ENEMY_COUNT, state.map);
     for(int i = 0; i < LEVEL3_ENEMY_COUNT; i++){
         state.enemies[i].Update(deltaTime, state.player, state.enemies, LEVEL3_ENEMY_COUNT, state.map);
     }
     for(int i = 0; i < LEVEL3_CAT_COUNT; i++){
         state.cat[i].Update(deltaTime, state.player, state.enemies, LEVEL3_ENEMY_COUNT, state.map);
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
     if (state.player->position.y < -8){
         state.player->isActive=false;
     }
     if(state.player->EatCat(&state.cat[0])==true){
         state.cat[0].isActive=false;
     }
     if(state.player->EatCat(&state.cat[1])==true){
         state.cat[1].isActive=false;
     }
     if (state.player->isActive == false){
         playerLives = playerLives - 1;
         if (playerLives > 0){
             state.nextScene = 3;
         }
     }
     
     if (state.cat[0].isActive == false && state.cat[1].isActive == false && playerLives > 0 && state.player->position.x > 11.0f && state.player->position.y<-6.0f) {
         state.nextScene = 4;
     }
     return playerLives;
 }
 void Level3::Render(ShaderProgram *program, int playerLives) {
     state.map->Render(program);
     state.player->Render(program);
     for(int i = 0; i < LEVEL3_ENEMY_COUNT; i++){
         state.enemies[i].Render(program);
     }
     for(int i = 0; i < LEVEL3_CAT_COUNT; i++){
         state.cat[i].Render(program);
     }
     if (playerLives == 1){
         Util::DrawText(program, fontTextureID3 , "Lives : 1", 0.8, -0.5f, randomvec3);
     }
     if (playerLives == 2){
         Util::DrawText(program, fontTextureID3 , "Lives : 2", 0.8, -0.5f, randomvec3);
     }
     if (playerLives == 3){
         Util::DrawText(program, fontTextureID3 , "Lives : 3", 0.8, -0.5f, randomvec3);
     }
     if (playerLives == 0){
         Util::DrawText(program, fontTextureID3 , "you lost :(", 0.8, -0.5f, randomvec5);
     }
     
     
 }

