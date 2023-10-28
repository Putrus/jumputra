#include "../inc/PropertiesManager.hpp"

#include <fstream>

#include <nlohmann/json.hpp>

using json = nlohmann::json;

namespace jp::game::engine
{
    PropertiesManager::PropertiesManager(const std::string& filename) : mFilename(filename)
    {
        load();
    }

    void PropertiesManager::load()
    {
        try
        {
            std::ifstream file(mFilename);
            if (!file.is_open())
                throw std::runtime_error("Failed to open file " + mFilename);
            json j;
            file >> j;

            //physics properties
            physicsProperties.bounceFactor = j["physics"]["bounce"];
            physicsProperties.checkCollisionDistance = j["physics"]["collision"];
            physicsProperties.fallVelocity = j["physics"]["fall"];
            physicsProperties.friction = j["physics"]["friction"];
            physicsProperties.gravity = j["physics"]["gravity"];
            physicsProperties.entitySize = math::Vector2<float>(j["physics"]["entity"]["size"]["x"],
                j["physics"]["entity"]["size"]["y"]);
            physicsProperties.wind.acceleration = j["physics"]["wind"]["acceleration"], 0.f;
            physicsProperties.wind.factor = j["physics"]["wind"]["factor"];
            physicsProperties.wind.maxVelocity =  j["physics"]["wind"]["max"];
            physicsProperties.wind.startPosition = j["physics"]["wind"]["position"]["start"];
            physicsProperties.wind.endPosition = j["physics"]["wind"]["position"]["end"];


            //character properties
            characterProperties.jumpGain = math::Vector2<float>(j["character"]["jump"]["gain"]["x"],
                j["character"]["jump"]["gain"]["y"]);
            characterProperties.jumpMax = math::Vector2<float>(j["character"]["jump"]["max"]["x"],
                j["character"]["jump"]["max"]["y"]);
            characterProperties.runVelocity = j["character"]["run"];
            file.close();
        }
        catch (const std::exception& e)
        {
            //to do error handling
            std::cout << e.what() << std::endl;
        }
    }

    void PropertiesManager::save()
    {

    }
}