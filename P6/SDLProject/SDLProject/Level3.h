#include "Scene.h"

class Level3 : public Scene {
public:
    void Initialize() override;
    int Update(float deltaTime, int playerLives) override;
    void Render(ShaderProgram *program, int playerLives) override;
};
