#include "../inc/Language.hpp"

#include <nlohmann/json.hpp>

#include <fstream>

namespace jp::game
{
   Language::Language(const std::string& language, const std::string& filename)
      : mLanguage(language), mFilename(filename)
   {
      loadFromJsonFile(filename);
   }

   void Language::fromJson(const nlohmann::json& json)
   {
      for (const auto& item : json.at(mLanguage).items())
      {
         mTexts[item.key()] = item.value();
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
      return mTexts.at(text);
   }

   void Language::setLanguage(const std::string& language)
   {
      mLanguage = language;
      loadFromJsonFile(mFilename);
   }
}