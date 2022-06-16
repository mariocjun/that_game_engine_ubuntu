#include "SceneGame.hpp"

SceneGame::SceneGame(WorkingDirectory &workingDir, ResourceAllocator<sf::Texture> &textureAllocator, Window &window)
        : workingDir(workingDir), textureAllocator(textureAllocator), mapParser(textureAllocator), window(window) {}

void SceneGame::OnCreate() {
    std::shared_ptr<Object> player = std::make_shared<Object>();

    player->transform->SetPosition(100, 700);

    auto sprite = player->AddComponent<C_Sprite>();
    sprite->SetTextureAllocator(&textureAllocator);
    sprite->SetDrawLayer(DrawLayer::Entities);

    auto movement = player->AddComponent<C_KeyboardMovement>();
    movement->SetInput(&input);

    auto animation = player->AddComponent<C_Animation>();

    int vikingTextureID = textureAllocator.Add(workingDir.Get() + "Viking.png");

    const int frameWidth = 165;
    const int frameHeight = 145;

    std::shared_ptr<Animation> idleAnimation = std::make_shared<Animation>(FacingDirection::Right);
    const float idleAnimFrameSeconds = 0.2f;
    idleAnimation->AddFrame(vikingTextureID, 600, 0, frameWidth, frameHeight, idleAnimFrameSeconds);
    idleAnimation->AddFrame(vikingTextureID, 800, 0, frameWidth, frameHeight, idleAnimFrameSeconds);
    idleAnimation->AddFrame(vikingTextureID, 0, 145, frameWidth, frameHeight, idleAnimFrameSeconds);
    idleAnimation->AddFrame(vikingTextureID, 200, 145, frameWidth, frameHeight, idleAnimFrameSeconds);
    animation->AddAnimation(AnimationState::Idle, idleAnimation);

    std::shared_ptr<Animation> walkAnimation = std::make_shared<Animation>(FacingDirection::Right);
    const float walkAnimFrameSeconds = 0.15f;
    walkAnimation->AddFrame(vikingTextureID, 600, 290, frameWidth, frameHeight, walkAnimFrameSeconds);
    walkAnimation->AddFrame(vikingTextureID, 800, 290, frameWidth, frameHeight, walkAnimFrameSeconds);
    walkAnimation->AddFrame(vikingTextureID, 0, 435, frameWidth, frameHeight, walkAnimFrameSeconds);
    walkAnimation->AddFrame(vikingTextureID, 200, 435, frameWidth, frameHeight, walkAnimFrameSeconds);
    walkAnimation->AddFrame(vikingTextureID, 400, 435, frameWidth, frameHeight, walkAnimFrameSeconds);
    animation->AddAnimation(AnimationState::Walk, walkAnimation);

    auto collider = player->AddComponent<C_BoxCollider>();
    collider->SetSize(frameWidth * 0.4f, frameHeight * 0.5f);
    collider->SetOffset(0.f, 14.f);
    collider->SetLayer(CollisionLayer::Player);

    auto camera = player->AddComponent<C_Camera>();
    camera->SetWindow(&window);

    objects.Add(player);

    // You will need to play around with this offset until it fits the level in at your chosen resolution. This worls for 1920 * 1080.
    // In future we will remove this hardcoded offset when we look at allowing the player to change resolutions.
    sf::Vector2i mapOffset(-160, 180);
    //sf::Vector2i mapOffset(128, 128);
    std::vector<std::shared_ptr<Object>> levelTiles = mapParser.Parse(workingDir.Get() + "Test Map 1.tmx", mapOffset);

    objects.Add(levelTiles);
}

void SceneGame::OnDestroy() {

}

void SceneGame::ProcessInput() {
    input.Update();
}

void SceneGame::Update(float deltaTime) {
    objects.ProcessRemovals();
    objects.ProcessNewObjects();
    objects.Update(deltaTime);
    Debug::HandleCameraZoom(window, input);
}

void SceneGame::LateUpdate(float deltaTime) {
    objects.LateUpdate(deltaTime);
}

void SceneGame::Draw(Window &window) {
    objects.Draw(window);

    Debug::Draw(window);
}
