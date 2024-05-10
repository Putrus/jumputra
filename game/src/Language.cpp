#include "../inc/Language.hpp"

#include <nlohmann/json.hpp>

#include <fstream>

namespace jp::game
{
   void Language::fromJson(const nlohmann::json& json)
   {
      mAvailableLanguages.clear();
      for (const auto& language : json)
      {
         mAvailableLanguages.push_back(language.at("name"));
         if (language.at("name") == mLanguage)
         {
            for (const auto& item : language.at("texts").items())
            {
               mTexts[item.key()] = item.value();
            }
         }
      }
   }

   nlohmann::json Language::toJson() const
   {
      nlohmann::json json;
      for (auto& text : mTexts)
      {
         json[mLanguage][text.first] = text.second;
      }

      return json;
   }

   const std::string& Language::getString(const std::string& text)
   {
      if (mTexts.find(text) == mTexts.end())
      {
         throw std::runtime_error("jp::game::Language::getString - Translation for text \"" + text + "\" doesn't exist");
      }
      return mTexts.at(text);
   }

   const std::vector<std::string>& Language::getAvailableLanguages() const
   {
      return mAvailableLanguages;
   }

   void Language::setLanguage(const std::string& language)
   {
      mLanguage = language;
   }
}