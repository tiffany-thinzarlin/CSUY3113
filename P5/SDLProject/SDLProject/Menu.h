#include "Scene.h"

class Menu : public Scene {
public:
    void Initialize() override;
    int Update(float deltaTime, int playerLives) override;
    void Render(ShaderProgram *program, int playerLives) override;
};
