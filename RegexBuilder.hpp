
#ifndef REGEXBUILDER_REGEXBUILDER_HPP
#define REGEXBUILDER_REGEXBUILDER_HPP

#include <string>
#include <map>

class RegexBuilder
{
   private :
      std::string    nomPartieCourante_;
      std::string    regexCourante_;
      bool           dansSousExpr_;
      bool           dansRegex_;

      std::map< std::string, std::string >   mapSousExpr_;
      std::map< std::string, std::string >   mapRegex_;

      static std::string IdPartie_;
      static std::string IdSousExpr_;
      static std::string IdRegex_;
      static std::string IdVariable_;

   public :
      explicit RegexBuilder( const std::string & inCheminFichier );

      const std::string & getRegex( const std::string & inPartie );
};

#endif 
