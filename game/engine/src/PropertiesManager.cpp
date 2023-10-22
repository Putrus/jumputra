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
            physicsProperties.setBounceFactor(j["physics"]["bounce"]);
            physicsProperties.setCheckCollisionDistance(j["physics"]["collision"]);
            physicsProperties.setFallVelocity(j["physics"]["fall"]);
            physicsProperties.setFriction(j["physics"]["friction"]);
            physicsProperties.setGravity(j["physics"]["gravity"]);
            physicsProperties.setEntitySize(math::Vector2<float>(j["physics"]["entity"]["size"]["x"],
                j["physics"]["entity"]["size"]["y"]));
            physicsProperties.setWindAcceleration(math::Vector2<float>(j["physics"]["wind"]["acceleration"], 0.f));
            physicsProperties.setWindFactor(j["physics"]["wind"]["factor"]);
            physicsProperties.setWindMaxVelocity(math::Vector2<float>(j["physics"]["wind"]["max"], 0.f));


            //character properties
            characterProperties.setJumpGain(math::Vector2<float>(j["character"]["jump"]["gain"]["x"],
                j["character"]["jump"]["gain"]["y"]));
            characterProperties.setJumpMax(math::Vector2<float>(j["character"]["jump"]["max"]["x"],
                j["character"]["jump"]["max"]["y"]));
            characterProperties.setRunVelocity(j["character"]["run"]);
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