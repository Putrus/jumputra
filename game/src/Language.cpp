#include "../inc/Language.hpp"

#include <nlohmann/json.hpp>

#include <fstream>

namespace jp::game
{
   Language::Language(const std::string& language, const std::string& filename)
      : mLanguage(language), mFilename(filename)
   {
      mTexts.insert({ "play", "" });
      mTexts.insert({ "quit", "" });
      loadFromFile(filename);
   }

   void Language::loadFromJson(const nlohmann::json& json)
   {
      for (auto& text : mTexts)
      {
         text.second = json.at(mLanguage).at(text.first);
      }
   }

   const std::string& Language::getString(const std::string& text)
   {
      return mTexts.at(text);
   }

   void Language::setLanguage(const std::string& language)
   {
      mLanguage = language;
      loadFromFile(mFilename);
   }
}