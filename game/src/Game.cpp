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

   void Game::draw(sf::RenderTarget& target, sf::RenderStates states) const
   {
      for (const auto& drawable : mDrawables)
      {
         target.draw(*drawable);
      }
   }

   void Game::event(const std::optional<sf::Event>& event)
   {
      if (const auto* keyReleased = event->getIf<sf::Event::KeyReleased>())
      {
         switch (keyReleased->scancode)
         {
         case sf::Keyboard::Scancode::V:
            mViewFollowCharacter = mViewFollowCharacter ? false : true;
            break;
         case sf::Keyboard::Scancode::Numpad8:
            if (!mViewFollowCharacter)
            {
               changeView(-static_cast<float>(mContext.properties.graphic.window.size.y));
            }
            break;
         case sf::Keyboard::Scancode::Numpad2:
            if (!mViewFollowCharacter)
            {
               changeView(mContext.properties.graphic.window.size.y);
            }
         default:
            break;
         }
      }

      if (mContext.algorithm == algorithm::AlgorithmName::Human)
      {
         humanCharacterControl(event);
      }      
   }

   void Game::update(float dt)
   {
      updateView();
      logic::Engine::update(dt);
   }

   void Game::addCharacter(const math::Rect<float>& rect)
   {
      std::shared_ptr<Character> character = std::make_shared<Character>(rect, mProperties, mStatistics, mSegments, mWinds);
      mDrawables.push_back(character);
      mCharacters.push_back(character);
   }

   void Game::addCharacterCopy(const logic::Character& character)
   {
      std::shared_ptr<Character> newCharacter = std::make_shared<Character>(character);
      mDrawables.push_back(newCharacter);
      mCharacters.push_back(newCharacter);
   }

   void Game::removeCharacter(const std::shared_ptr<logic::Character>& character)
   {
      mDrawables.erase(std::remove_if(mDrawables.begin(), mDrawables.end(), [&character](const auto& drawable)
         {
            return dynamic_cast<game::Character*>(character.get()) == dynamic_cast<game::Character*>(drawable.get());
         }), mDrawables.end());
      mCharacters.erase(std::find(mCharacters.begin(), mCharacters.end(), character));
   }

   void Game::removeAllCharacters()
   {
      while (!mCharacters.empty())
      {
         removeCharacter(mCharacters.front());
      }
   }

   void Game::removeAllCharactersExcept(const std::shared_ptr<logic::Character>& character)
   {
      while (mCharacters.size() > 1)
      {
         if (mCharacters.front() == character)
         {
            removeCharacter(mCharacters.back());
         }
         else
         {
            removeCharacter(mCharacters.front());
         }
      }
   }

   void Game::load()
   {
      std::string filename = makeSavePath();
      if (!std::filesystem::exists(filename) || mContext.newGame)
      {
         filename = std::string(WORLDS_DIR) + mContext.world + ".json";
      }
      
      loadFromJsonFile(filename);
   }

   void Game::save() const
   {
      if (!std::filesystem::exists(SAVES_DIR))
      {
         std::filesystem::create_directory(SAVES_DIR);
      }
      saveToJsonFile(std::string(SAVES_DIR) + mContext.world + ".json");
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
      if (mCharacters.empty() || !mViewFollowCharacter)
      {
         return;
      }

      auto followedCharacterIt = std::min_element(mCharacters.begin(), mCharacters.end(),
         [](const auto& lhs, const auto& rhs)
         {
            return lhs->getPosition().y < rhs->getPosition().y;
         });
      const logic::Character& followedCharacter = **followedCharacterIt;

      float halfWindowHeight = mContext.properties.graphic.window.size.y / 2.f;
      while(true)
      {
         if (followedCharacter.getPosition().y < mContext.window.getView().getCenter().y -
            halfWindowHeight - followedCharacter.getRect().height)
         {
            changeView(-static_cast<float>(mContext.properties.graphic.window.size.y));
         }
         else if (followedCharacter.getPosition().y > mContext.window.getView().getCenter().y + halfWindowHeight)
         {
            changeView(mContext.properties.graphic.window.size.y);
         }
         else
         {
            break;
         }
      }
   }

   void Game::removeRedundantDrawables()
   {
         mDrawables.erase(std::remove_if(mDrawables.begin(), mDrawables.end(), [](const auto& drawable)
         {
            return dynamic_cast<Character*>(drawable.get()) != nullptr && drawable.use_count() <= 1;
         }), mDrawables.end());
   }

   void Game::humanCharacterControl(const std::optional<sf::Event>& event)
   {
      if (mCharacters.empty())
      {
         return;
      }

      logic::Character& controlledCharacter = *mCharacters.at(0);
      if (const auto* keyPressed = event->getIf<sf::Event::KeyPressed>())
      {
         switch (keyPressed->scancode)
         {
         case sf::Keyboard::Scancode::Left:
         case sf::Keyboard::Scancode::A:
            controlledCharacter.run(logic::CharacterDirection::Left);
            break;
         case sf::Keyboard::Scancode::Right:
         case sf::Keyboard::Scancode::D:
            controlledCharacter.run(logic::CharacterDirection::Right);
            break;
         case sf::Keyboard::Scancode::Space:
            controlledCharacter.squat();
            break;
         default:
            break;
         }
      }
      
      if (const auto* keyReleased = event->getIf<sf::Event::KeyReleased>())
      {
         switch (keyReleased->scancode)
         {
         case sf::Keyboard::Scancode::Space:
            controlledCharacter.jump();
            break;
         case sf::Keyboard::Scancode::Left:
         case sf::Keyboard::Scancode::A:
            if (controlledCharacter.getDirection() == logic::CharacterDirection::Left)
            {
               controlledCharacter.stop();
            }
            break;
         case sf::Keyboard::Scancode::Right:
         case sf::Keyboard::Scancode::D:
            if (controlledCharacter.getDirection() == logic::CharacterDirection::Right)
            {
               controlledCharacter.stop();
            }
            break;
         case sf::Keyboard::Scancode::L:
            std::cout << "Log: " << std::endl;
            std::cout << "position: " << controlledCharacter.getPosition() << std::endl;
            std::cout << "state: " << controlledCharacter.getState() << std::endl;
            std::cout << "acceleration: " << controlledCharacter.getAcceleration() << std::endl;
            std::cout << "velocity: " << controlledCharacter.getVelocity() << std::endl;
            std::cout << "runSpeed: " << controlledCharacter.getRunSpeed() << std::endl;
            std::cout << "statistics: " << mContext.statistics << std::endl;
            std::cout << "visited segments: " << controlledCharacter.getVisitedSegments().size() << std::endl;
            for (const auto& segment : controlledCharacter.getVisitedSegments())
            {
               std::cout << *segment << std::endl;
            }
            std::cout << std::endl;
            break;
         default:
            break;
         }
      }
   }

   void Game::changeView(float y)
   {
      sf::View view = mContext.window.getView();
      view.setCenter(sf::Vector2f(view.getCenter().x, view.getCenter().y + y));
      mContext.window.setView(view);
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

   std::string Game::makeSavePath() const
   {
      return std::string(SAVES_DIR) + mContext.world + ".json";
   }
}
