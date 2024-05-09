#pragma once

#include "../../logic/inc/Jsonable.hpp"

#include <string>

namespace jp::game
{
   class Language : public logic::Jsonable
   {
   public:
      Language(const std::string& language, const std::string& filename);

      void fromJson(const nlohmann::json& json) override;
      nlohmann::json toJson() const override;

      const std::string& getString(const std::string& text);

      void setLanguage(const std::string& language);

   private:
      std::string mLanguage;
      std::string mFilename;

      std::map<std::string, std::string> mTexts;
   };
}