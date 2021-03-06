#ifndef SceneGame_hpp
#define SceneGame_hpp

#include "Scene.hpp"
#include "Input.hpp"
#include "WorkingDirectory.hpp"
#include "Object.hpp"
#include "C_Sprite.hpp"
#include "C_KeyboardMovement.hpp"
#include "ResourceAllocator.hpp"
#include "ObjectCollection.hpp"
#include "TileMapParser.hpp"
#include "C_Animation.hpp"
#include "C_BoxCollider.hpp"
#include "Debug.hpp"
#include "C_Camera.hpp"

class SceneGame : public Scene {
public:
    SceneGame(WorkingDirectory &workingDir, ResourceAllocator<sf::Texture> &textureAllocator, Window &window);

    void OnCreate() override;

    void OnDestroy() override;

    void ProcessInput() override;

    void Update(float deltaTime) override;

    void LateUpdate(float deltaTime) override;

    void Draw(Window &window) override;

private:
    WorkingDirectory &workingDir;
    Input input;
    ResourceAllocator<sf::Texture> &textureAllocator;
    ObjectCollection objects;
    TileMapParser mapParser;
    Window &window;
};

#endif /* SceneGame_hpp */
