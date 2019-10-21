#include <iostream>

#include "./game.h" 
#include "./constants.h"
#include "../lib/glm/glm.hpp"
#include "./components/transformcomponent.h"
#include "./components/spritecomponent.h"
#include "./components/keyboardcomponent.h"
#include "./components/collidercomponent.h"
#include "./components/textlabelcomponent.h"
#include "./components/projectileemittercomponent.h"

SDL_Event Game::event{};
SDL_Rect Game::camera{0, 0, WINDOW_WIDTH, WINDOW_HEIGHT};
SDL_Texture* ColliderComponent::boundingBox{nullptr};


Game::Game(): ticksLastFrame{0}, running{false}, 
    window{nullptr}, renderer{nullptr} {
}

Game::~Game(){
    manager.clearData();
    if(map != NULL) delete map;
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
}

bool Game::isRunning() const noexcept {
    return this->running;
}


void Game::initialize(uint width, uint height) {
    if(SDL_Init(SDL_INIT_EVERYTHING) != 0) {
        std::cerr << "Error initializing SDL." << std::endl;
        return;
    }

    if(TTF_Init() != 0) {
        std::cerr << "Error initializing SDL TTF." << std::endl;
        return;
    } 

    window = SDL_CreateWindow(
        "Game", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 
        width, height, NULL
    );

    if(window == nullptr){
        std::cerr << "Error creating SDL window." << std::endl;
        return;
    }

    renderer = SDL_CreateRenderer(window, -1, 0 );
    if(renderer == nullptr){
        std::cerr << "Error creating SDL renderer." << std::endl;
        return; 
    }

    manager = EntityManager{};
    assetManager = AssetManager{renderer, manager};
    running = true;
    ticksLastFrame = 0;
    loadLevel(1);
}

void Game::loadLevel(int levelNumber) {
    sol::state lua;
    lua.open_libraries(sol::lib::base, sol::lib::os, sol::lib::math);
    std::string levelName = "Level"+ std::to_string(levelNumber);
    lua.script_file("./assets/scripts/" + levelName + ".lua");

    sol::table levelData = lua[levelName];
    sol::table levelAssets = levelData["assets"];

    uint idx = 0;
    while(true){
        sol::optional<sol::table> assetNode = levelAssets[idx];
        if(assetNode == sol::nullopt)
            break;
        sol::table asset = assetNode.value();
        std::string assetType = asset["type"];
        
        if(assetType == "texture")
            assetManager.addTexture(asset["id"], static_cast<std::string>(asset["file"]).c_str());

        if(assetType == "font")
            assetManager.addFont(
                asset["id"], 
                static_cast<std::string>(asset["file"]).c_str(),
                static_cast<int>(asset["fontSize"])
            );

        idx++;
    }

    sol::table levelMap = levelData["map"];
    std::string mapTextureId = levelMap["textureAssetId"];
    std::string mapFile = levelMap["file"];
    map = new Map{
        assetManager, 
        manager, 
        static_cast<int>(levelMap["scale"]), 
        static_cast<int>(levelMap["tileSize"])
    };
    map->loadMap(
        mapFile, 
        static_cast<int>(levelMap["mapSizeX"]), 
        static_cast<int>(levelMap["mapSizeY"])
    );

    

    
    // assetManager.addTexture("tank-image", "./assets/images/tank-big-right.png");
    // assetManager.addTexture("chopper-image", "./assets/images/chopper-spritesheet.png");
    // assetManager.addTexture("radar-image", "./assets/images/radar.png");
    // assetManager.addTexture("jungle-tiletexture", "./assets/tilemaps/jungle.png");
    // assetManager.addTexture("collider-box", "./assets/images/collision-texture.png");
    // assetManager.addTexture("heliport-image", "./assets/images/heliport.png");
    // assetManager.addTexture("projectile-image", "./assets/images/bullet-enemy.png");
    // assetManager.addFont("charriot-font", "./assets/fonts/charriot.ttf", 14);

    // map = new Map{assetManager, manager, 2, 32};
    // map->loadMap("./assets/tilemaps/jungle.map", 25, 20);

   // ColliderComponent::boundingBox = assetManager.getTexture("collider-box");
    
    // Entity& player{manager.addEntity("player", LayerType::Player)};
    // player.addComponent<TransformComponent>(240, 106, 0, 0, 32, 32, 1);
    // player.addComponent<SpriteComponent>(assetManager.getTexture("chopper-image"), 2, 90, true, false);
    // //player.addComponent<KeyboardComponent>("up", "right", "down", "left", "space");
    // player.addComponent<ColliderComponent>("PLAYER", 240, 106, 32, 32);

    // Entity& tankEntity{manager.addEntity("tank", LayerType::Enemy)};
    // tankEntity.addComponent<TransformComponent>(150, 495, 0, 0, 32, 32, 1);
    // tankEntity.addComponent<SpriteComponent>(assetManager.getTexture("tank-image"));
    // tankEntity.addComponent<ColliderComponent>("ENEMY", 150, 495, 32, 32);

    // Entity& projectile{manager.addEntity("projectile", LayerType::Projectile)};
    // projectile.addComponent<TransformComponent>(150+16, 495+16, 0, 0, 4, 4, 1);
    // projectile.addComponent<SpriteComponent>(assetManager.getTexture("projectile-image"));
    // projectile.addComponent<ColliderComponent>("PROJECTILE", 150+16, 495+16, 4,4);
    // projectile.addComponent<ProjectileEmitterComponent>(50, 270, 200, true);

    // Entity& heliportEntity{manager.addEntity("heliport", LayerType::Obstacle)};
    // heliportEntity.addComponent<TransformComponent>(470, 420, 0, 0, 32, 32, 1);
    // heliportEntity.addComponent<SpriteComponent>(assetManager.getTexture("heliport-image"));
    // heliportEntity.addComponent<ColliderComponent>("LEVEL_COMPLETE", 470, 420, 32, 32);

    // Entity& radarEntity{manager.addEntity("radar", LayerType::Ui)};
    // radarEntity.addComponent<TransformComponent>(720, 15, 0, 0, 64, 64, 1);
    // radarEntity.addComponent<SpriteComponent>(assetManager.getTexture("radar-image"), 8, 150, false, true);

    // Entity& labelLevelName{manager.addEntity("labelLevelName", LayerType::Ui)};
    // labelLevelName.addComponent<TextLabelComponent>(
    //     renderer, assetManager.getFont("charriot-font"), 
    //     10, 10, "First Level", "charriot-font", WHITE_COLOR
    // );

    

    //manager.listEntities();
    //std::cout<< tankEntity.hasComponent<SpriteComponent>() << std::endl;
}

void Game::processInput(){
    SDL_PollEvent(&event);
    switch (event.type){
        case SDL_QUIT:{
            running = false;
            break;
        }
        case SDL_KEYDOWN: {
            if(event.key.keysym.sym == SDLK_ESCAPE)
                running = false;
            break;
        }
        default:{
            break;
        }
    }
}

void Game::update(){
    // Wait until 16ms has ellapsed since the last frame
    while (!SDL_TICKS_PASSED(SDL_GetTicks(), ticksLastFrame + FRAME_TARGET_TIME));
    
    // Delta time is the difference in ticks from last frame converted to secomds
    float deltaTime = (SDL_GetTicks() - ticksLastFrame) / 1000.0f;

    // Clamp deltaTime to a maximum value
    deltaTime = (deltaTime > 0.05f) ? 0.05f : deltaTime;

    // Sets the new ticks for the current frame to be used in the next pass
    ticksLastFrame = SDL_GetTicks();

    manager.update(deltaTime);

    handleCameraMovement();

    checkCollisions();
}

void Game::render(){
    SDL_SetRenderDrawColor(renderer, 21, 21, 21, 255);
    SDL_RenderClear(renderer);

    if(manager.hasNoEntity())
        return;

    manager.render(renderer);
    
    SDL_RenderPresent(renderer);
}

void Game::handleCameraMovement(){
    Entity* player = manager.getEntity("player");
    if(player == NULL) return;

    TransformComponent* transform = player->getComponent<TransformComponent>();
    camera.x = transform->position.x - (WINDOW_WIDTH / 2);
    camera.y = transform->position.y - (WINDOW_HEIGHT / 2);

    camera.x = (camera.x < 0)? 0 : camera.x;
    camera.y = (camera.y < 0)? 0 : camera.y;
    camera.x = (camera.x > WINDOW_WIDTH)? WINDOW_WIDTH : camera.x;
    camera.y = (camera.y > WINDOW_HEIGHT)? WINDOW_HEIGHT : camera.y;
}

void Game::checkCollisions(){
    CollisionType collisionType = manager.checkEntityCollisions();
    if(collisionType == CollisionType::PlayerEnemy)
        processGameOver();

    if(collisionType == CollisionType::PlayerProjectile)
        processGameOver();
    
    if(collisionType == CollisionType::PlayerLevelComplete)
        processNextLevel();
}

void Game::processNextLevel(){
    std::cout << "Next Level" << std::endl;
    running = false;
}

void Game::processGameOver(){
    std::cout << "Game Over" << std::endl;
    running = false;
}



// Not needed: void Game::destroy() { }