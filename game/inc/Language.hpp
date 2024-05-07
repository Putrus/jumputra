#pragma once

#include "../../logic/inc/Loadable.hpp"

#include <string>

namespace jp::game
{
   class Language : public logic::Loadable
   {
   public:
      Language(const std::string& language, const std::string& filename);

      void loadFromJson(const nlohmann::json& json) override;

      const std::string& getString(const std::string& text);

      void setLanguage(const std::string& language);

   private:
      std::string mLanguage;
      std::string mFilename;

      std::map<std::string, std::string> mTexts;
   };
}