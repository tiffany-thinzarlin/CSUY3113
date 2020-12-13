#include "Scene.h"

class Level1 : public Scene {
public:
    void Initialize() override;
    int Update(float deltaTime, int playerlives) override;
    void Render(ShaderProgram *program, int playerLives) override;
};
