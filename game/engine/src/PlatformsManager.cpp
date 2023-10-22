#include "../inc/PlatformsManager.hpp"

#include "../../physics/inc/DiagonalPlatform.hpp"
#include "../../physics/inc/HorizontalPlatform.hpp"
#include "../../physics/inc/VerticalPlatform.hpp"

#include <fstream>

#include <nlohmann/json.hpp>

using json = nlohmann::json;

namespace jp::game::engine
{
    PlatformsManager::PlatformsManager(const std::string& filename) : mFilename(filename)
    {}

    std::vector<std::shared_ptr<physics::Platform>> PlatformsManager::load()
    {
        std::vector<std::shared_ptr<physics::Platform>> platforms;
        try
        {
            std::ifstream file("data/platforms.json");
            json j;
            if (!file.is_open())
                throw std::runtime_error("Failed to open file data/plaltforms.json");
            file >> j;
            for (const auto& jsonPlatform : j["platforms"])
            {
                if (jsonPlatform["type"] == "comment")
                    continue;

                physics::PlatformSurface surface = physics::PlatformSurface::Ordinary;
                if (jsonPlatform["surface"] == "slippery")
                {
                    surface = physics::PlatformSurface::Slippery;
                }
                else if (jsonPlatform["surface"] == "sticky")
                {
                    surface = physics::PlatformSurface::Sticky;
                }
                else if (jsonPlatform["surface"] != "ordinary")
                {
                    std::string strSurface = jsonPlatform["surface"];
                    throw std::runtime_error("Surface " + strSurface + " doesn't exist");
                }

                if (jsonPlatform["type"] == "points")
                {
                    const auto& jsonPoints = jsonPlatform["points"];
                    for (size_t i = 1; i < jsonPoints.size(); ++i)
                    {
                        math::Vector2<float> a(jsonPoints[i - 1]["x"], jsonPoints[i - 1]["y"]);
                        math::Vector2<float> b(jsonPoints[i]["x"], jsonPoints[i]["y"]);
                        platforms.push_back(createPlatform(a, b, surface));
                    }
                }
                else if (jsonPlatform["type"] == "segment")
                {
                    //to do
                }
                else if (jsonPlatform["type"] == "rectangle")
                {
                    math::Rect<float> rect(jsonPlatform["left"], jsonPlatform["top"],
                        jsonPlatform["width"], jsonPlatform["height"]);

                    platforms.push_back(createPlatform(rect.getLeftTop(), rect.getRightTop(), surface));
                    platforms.push_back(createPlatform(rect.getRightTop(), rect.getRightBottom(), surface));
                    platforms.push_back(createPlatform(rect.getLeftBottom(), rect.getRightBottom(), surface));
                    platforms.push_back(createPlatform(rect.getLeftTop(), rect.getLeftBottom(), surface));
                }
                else
                {
                    //nothing to do
                }
            }
            file.close();
        }
        catch (const std::exception& e)
        {
            //to do error handling
            std::cout << e.what() << std::endl;
        }
        return platforms;
    }


    std::shared_ptr<physics::Platform> PlatformsManager::createPlatform(const math::Vector2<float>& a,
        const math::Vector2<float>& b, physics::PlatformSurface surface)
    {
        math::Segment<float> segment(a, b);
        if (segment.isVertical())
        {
            return std::make_unique<physics::VerticalPlatform>(segment, surface);
        }
        else if (segment.isHorizontal())
        {
            return std::make_unique<physics::HorizontalPlatform>(segment, surface);
        }
        else if (segment.isDiagonal())
        {
            return std::make_unique<physics::DiagonalPlatform>(segment, surface);
        }
        else
        {
            throw std::runtime_error("Failed to create a platform. The platform is neither horizontal, nor vertical, nor diagonal");
        }
        return nullptr;
    }
}