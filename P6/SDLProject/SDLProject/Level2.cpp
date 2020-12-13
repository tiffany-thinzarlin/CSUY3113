  #include "Level2.h"
 #define LEVEL2_WIDTH 14
 #define LEVEL2_HEIGHT 8
 #define LEVEL2_ENEMY_COUNT 2
 #define LEVEL2_CAT_COUNT 2
 GLuint fontTextureID2;
 glm::vec3 randomvec2 = glm::vec3(1, -1, 0);
 glm::vec3 randomvec6 = glm::vec3(5, -1, 0);
 unsigned int level2_data[] =
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

 void Level2::Initialize() {
     
     state.nextScene = -1;
     fontTextureID2 = Util::LoadTexture("font1.png");
     GLuint mapTextureID = Util::LoadTexture("rock.png");
     state.map = new Map(LEVEL2_WIDTH, LEVEL2_HEIGHT, level2_data, mapTextureID, 1.0f, 4, 1);
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
     
     state.enemies = new Entity[LEVEL2_ENEMY_COUNT];
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
     
     state.cat = new Entity[LEVEL2_CAT_COUNT];
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
 int Level2::Update(float deltaTime, int playerLives) {
     state.player->Update(deltaTime, state.player, state.enemies, LEVEL2_ENEMY_COUNT, state.map);
     state.enemies[0].Update(deltaTime, state.player, state.enemies, LEVEL2_ENEMY_COUNT, state.map);
     state.enemies[1].Update(deltaTime, state.player, state.enemies, LEVEL2_ENEMY_COUNT, state.map);
     state.cat[0].Update(deltaTime, state.player, state.enemies, LEVEL2_ENEMY_COUNT, state.map);
     state.cat[1].Update(deltaTime, state.player, state.enemies, LEVEL2_ENEMY_COUNT, state.map);
     //if(state.player->CheckCollideTop(&state.enemies[0])==true){
         //state.enemies[0].isActive = false;
     //}
     if(state.player->EnemyEat(&state.enemies[0])==true){
         state.player->isActive=false;
     }
        else if(state.player->EnemyEat(&state.enemies[1])==true){
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
             state.nextScene = 2;
         }
     }
     
     if (state.cat[0].isActive == false && state.cat[1].isActive == false && playerLives > 0 && state.player->position.x > 11.0f && state.player->position.y<-6.0f) {
         state.nextScene = 3;
     }
     return playerLives;
 }
 void Level2::Render(ShaderProgram *program, int playerLives) {
     state.map->Render(program);
     state.player->Render(program);
     state.enemies[0].Render(program);
     state.enemies[1].Render(program);
     state.cat[0].Render(program);
     state.cat[1].Render(program);
     if (playerLives == 1){
         Util::DrawText(program, fontTextureID2 , "Lives : 1", 0.8, -0.5f, randomvec2);
     }
     if (playerLives == 2){
         Util::DrawText(program, fontTextureID2 , "Lives : 2", 0.8, -0.5f, randomvec2);
     }
     if (playerLives == 3){
         Util::DrawText(program, fontTextureID2 , "Lives : 3", 0.8, -0.5f, randomvec2);
     }
     if (playerLives == 0){
         Util::DrawText(program, fontTextureID2 , "you lost :(", 0.8, -0.5f, randomvec6);
     }
     
     
 }

