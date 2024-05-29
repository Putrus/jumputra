#include "../inc/Game.hpp"

#include <filesystem>

namespace jp::game
{
   Game::Game(Context& context)
      : mContext(context), logic::Engine(context.properties.logic)
   {
      load();
      updateView();
   }

   Game::~Game()
   {
      resetView();
   }

   void Game::draw(sf::RenderTarget& target, const sf::RenderStates& states) const
   {
      for (const auto& drawable : mDrawables)
      {
         target.draw(*drawable);
      }
   }

   void Game::event(const sf::Event& event)
   {
      if (mControlledCharacterId >= mCharacters.size())
      {
         return;
      }

      logic::Character& controlledCharacter = *mCharacters[mControlledCharacterId];

      if (event.type == sf::Event::KeyPressed)
      {
         switch (event.key.code)
         {
         case sf::Keyboard::Key::Left:
         case sf::Keyboard::Key::A:
            controlledCharacter.run(logic::CharacterDirection::Left);
            break;
         case sf::Keyboard::Key::Right:
         case sf::Keyboard::Key::D:
            controlledCharacter.run(logic::CharacterDirection::Right);
            break;
         case sf::Keyboard::Key::Space:
            controlledCharacter.squat();
            break;
         default:
            break;
         }
      }

      if (event.type == sf::Event::KeyReleased)
      {
         switch (event.key.code)
         {
         case sf::Keyboard::Key::Space:
            controlledCharacter.jump();
            break;
         case sf::Keyboard::Key::Left:
         case sf::Keyboard::Key::A:
            if (controlledCharacter.getDirection() == logic::CharacterDirection::Left)
            {
               controlledCharacter.stop();
            }
            break;
         case sf::Keyboard::Key::Right:
         case sf::Keyboard::Key::D:
            if (controlledCharacter.getDirection() == logic::CharacterDirection::Right)
            {
               controlledCharacter.stop();
            }
            break;
         case sf::Keyboard::Key::L:
            std::cout << "Log: " << std::endl;
            std::cout << "state: " << controlledCharacter.getState() << std::endl;
            std::cout << "acceleration: " << controlledCharacter.getAcceleration() << std::endl;
            std::cout << "velocity: " << controlledCharacter.getVelocity() << std::endl;
            std::cout << "runSpeed: " << controlledCharacter.getRunSpeed() << std::endl;
            std::cout << "statistics: " << mContext.statistics << std::endl;
            std::cout << std::endl;
            break;
         case sf::Keyboard::Key::S:
            save();
            break;
         default:
            break;
         }
      }
   }

   void Game::update(float dt)
   {
      updateView();
      logic::Engine::update(dt);
   }

   void Game::load()
   {
      std::string filename = std::string(SAVES_DIR) + mContext.world + ".json";
      if (!std::filesystem::exists(filename) || mContext.newGame)
      {
         filename = std::string(WORLDS_DIR) + mContext.world + ".json";
      }
      loadFromJsonFile(filename);
   }

   void Game::save() const
   {
      std::string filename = std::string(SAVES_DIR) + mContext.world + ".json";
      saveToJsonFile(filename);
   }

   void Game::setGoal(const std::shared_ptr<Goal>& goal)
   {
      mDrawables.push_back(goal);
      Engine::setGoal(goal);
   }

   void Game::addCharacter(const std::shared_ptr<Character>& character)
   {
      mDrawables.push_back(character);
      Engine::addCharacter(character);
   }

   void Game::addSegment(const std::shared_ptr<Segment>& segment)
   {
      mDrawables.push_back(segment);
      Engine::addSegment(segment->getLogicSegment());
   }

   void Game::addWind(const std::shared_ptr<Wind>& wind)
   {
      mDrawables.push_back(wind);
      Engine::addWind(wind);
   }

   void Game::resetView()
   {
      sf::View view = mContext.window.getView();
      view.setCenter(sf::Vector2f(static_cast<float>(mContext.properties.graphic.window.size.x / 2),
         static_cast<float>(mContext.properties.graphic.window.size.y / 2)));
      mContext.window.setView(view);
   }

   void Game::updateView()
   {
      if (mFollowedCharacterId < mCharacters.size())
      {
         const logic::Character& followedCharacter = *mCharacters[mFollowedCharacterId];
         float halfWindowHeight = mContext.properties.graphic.window.size.y / 2.f;
         sf::View view = mContext.window.getView();
         while(true)
         {
            if (followedCharacter.getPosition().y < mContext.window.getView().getCenter().y -
               halfWindowHeight - followedCharacter.getRect().height)
            {
               view.setCenter(sf::Vector2f(view.getCenter().x, view.getCenter().y - mContext.properties.graphic.window.size.y));
               mContext.window.setView(view);
            }
            else if (followedCharacter.getPosition().y > mContext.window.getView().getCenter().y + halfWindowHeight)
            {
               view.setCenter(sf::Vector2f(view.getCenter().x, view.getCenter().y + mContext.properties.graphic.window.size.y));
               mContext.window.setView(view);
            }
            else
            {
               break;
            }
         }
      }
   }

   void Game::setGoal(const nlohmann::json& json)
   {
      std::shared_ptr<Goal> goal = Goal::create(json);
      mDrawables.push_back(goal);
      mGoal = goal;
   }

   void Game::addCharacter(const nlohmann::json& json)
   {
      std::shared_ptr<Character> character = Character::create(json, mProperties, mStatistics, mSegments, mWinds);
      mDrawables.push_back(character);
      mCharacters.push_back(character);
   }

   void Game::addSegment(const math::Vector2<float>& a, const math::Vector2<float>& b,
      logic::SegmentSurface surface/* = SegmentSurface::Ordinary*/)
   {
      std::shared_ptr<Segment> segment = Segment::create(a, b, surface);
      mDrawables.push_back(segment);
      mSegments.push_back(segment->getLogicSegment());
   }

   void Game::addWind(const nlohmann::json& json)
   {
      std::shared_ptr<Wind> wind = Wind::create(json);
      mDrawables.push_back(wind);
      mWinds.push_back(wind);
   }
}