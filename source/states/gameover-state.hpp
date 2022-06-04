#pragma once

#include <application.hpp>
#include <systems/menu.hpp>
#include "../common/components/mesh-renderer.hpp"
#include <systems/movement.hpp>
#include <asset-loader.hpp>

class Gameoverstate : public our::State
{
    our::World world;
    our::ForwardRenderer renderer;
    our::FreeCameraControllerSystem cameraController;
    our::MovementSystem movementSystem;
    our::MenuSystem menuSystem;

    void onInitialize() override
    {
        auto &config = getApp()->getConfig()["scene"];

        if (config.contains("assets"))
            our::deserializeAllAssets(config["assets"]);

            

        if (config.contains("gameover"))
            world.deserialize(config["gameover"]);            

        cameraController.enter(getApp());
        auto size = getApp()->getFrameBufferSize();
        renderer.initialize(size, config["renderer"]);
    }

    void onDraw(double deltaTime) override
    {

        movementSystem.update(&world, (float)deltaTime);
        cameraController.update(&world, (float)deltaTime);
        renderer.render(&world);

    }

    void onDestroy() override
    {
        our::clearAllAssets();
    }
};