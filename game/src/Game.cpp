#include "../inc/Game.hpp"

#include "../../logic/inc/SegmentsLoader.hpp"
#include "../../logic/inc/WindsLoader.hpp"

namespace jp::game
{
   Game::Game(Context& context) : mContext(context), logic::Engine(context.properties.logic)
   {
      addCharacter(std::make_shared<Character>(math::Rect(10.f, 15100.f, 24.f, 24.f), mProperties, mSegments, mWinds));
      logic::SegmentsLoader<Segment> segmentsLoader;
      std::vector<std::shared_ptr<Segment>> segments = segmentsLoader.loadFromFile("data/jsons/segments.json");
      logic::WindsLoader<Wind> windsLoader;
      std::vector<std::shared_ptr<Wind>> winds = windsLoader.loadFromFile("data/jsons/winds.json");
      for (const auto& segment : segments)
      {
         addSegment(segment);
      }

      updateView();

      for (const auto& wind : winds)
      {
         addWind(wind);
      }
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
            controlledCharacter.run(logic::CharacterDirection::Left);
            break;
         case sf::Keyboard::Key::Right:
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
            if (controlledCharacter.getDirection() == logic::CharacterDirection::Left)
            {
               controlledCharacter.stop();
            }
            break;
         case sf::Keyboard::Key::Right:
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
            std::cout << "statistics: " << controlledCharacter.getStatistics() << std::endl;
            std::cout << std::endl;
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
      view.setCenter(sf::Vector2f(mContext.properties.graphic.window.size.x / 2, mContext.properties.graphic.window.size.y / 2));
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
}