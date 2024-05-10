#pragma once

#include "../../core/inc/Jsonable.hpp"

#include <string>

namespace jp::game
{
   class Language : public core::Jsonable
   {
   public:
      void fromJson(const nlohmann::json& json) override;
      nlohmann::json toJson() const override;

      const std::string& getString(const std::string& text);
      const std::vector<std::string>& getAvailableLanguages() const;

      void setLanguage(const std::string& language);

   private:
      std::string mLanguage;
      std::string mFilename;

      std::map<std::string, std::string> mTexts;
      std::vector<std::string> mAvailableLanguages;
   };
}