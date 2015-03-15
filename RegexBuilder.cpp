
#include "RegexBuilder.hpp"

#include <iostream>
#include <fstream>

std::string RegexBuilder::IdPartie_    = "-partie:";
std::string RegexBuilder::IdSousExpr_  = "--sous-expr";
std::string RegexBuilder::IdRegex_     = "--regex";
std::string RegexBuilder::IdVariable_  = "@@";

RegexBuilder::RegexBuilder( const std::string & inCheminFichier )
   : nomPartieCourante_( "" ), regexCourante_( "" ),
     dansSousExpr_( false ), dansRegex_( false )
{
   std::ifstream  file( inCheminFichier.c_str() );

   if ( !file )
   {
      std::cerr << "Impossible d'ouvrir le fichier." << std::endl;
   }

   std::string    ligne = "";
   while ( !file.eof() )
   {
      getline( file, ligne );

      ligne.erase( 0, ligne.find_first_not_of( " " ) );
      ligne.erase( ligne.find_last_not_of( " " ) + 1, ligne.size() - ligne.find_last_not_of( " " ) - 1 );
      if ( ligne == "" || ligne[ 0 ] == '#' || ligne.substr( 0, 2 ) == "//" )
      {
         continue;
      }

      if ( ligne.find( IdPartie_ ) == 0 )
      {
         if ( nomPartieCourante_ != "" && regexCourante_ != "" )
         {
            mapRegex_[ nomPartieCourante_ ] = regexCourante_;
         }

         nomPartieCourante_   = ligne.substr( IdPartie_.size() );
         regexCourante_       = "";
         mapSousExpr_.clear();
         dansRegex_           = false;
         dansSousExpr_        = false;
         continue;
      }

      if ( ligne.find( IdSousExpr_ ) != std::string::npos )
      {
         dansSousExpr_  = true;
         continue;
      }

      if ( ligne.find( IdRegex_ ) != std::string::npos )
      {
         dansRegex_     = true;
         dansSousExpr_  = false;
         continue;
      }

      if ( dansSousExpr_ )
      {
         std::string    nomSousExpression    = ligne.substr( 0, ligne.find( "=" ) );
         std::string    valeurSousExpression = ligne.substr( ligne.find( "=" ) + 1, ligne.size() - ligne.find( "=" ) - 1 );

         mapSousExpr_[ nomSousExpression ] = valeurSousExpression;
         continue;
      }

      if ( dansRegex_ )
      {
         std::string    element  = "";
         size_t         pos      = -1;

         while ( ligne.size() != 0 )//pos != std::string::npos )
         {
            pos      = ligne.find( " " );

            element  = ligne.substr( 0, pos );
            if ( element.find( IdVariable_ ) == 0 )
            {
               element.erase( 0, IdVariable_.size() );
               regexCourante_ += mapSousExpr_[ element ];
            }
            else
            {
               regexCourante_ += element;
            }

            ligne.erase( 0, pos );
            ligne.erase( 0, ligne.find_first_not_of( " " ) );
            pos   = ligne.find( " " );
         }
      }
   }

   if ( nomPartieCourante_ != "" && regexCourante_ != "" )
   {
      mapRegex_[ nomPartieCourante_ ] = regexCourante_;
   }
}

const std::string & RegexBuilder::getRegex( const std::string & inPartie )
{
   return mapRegex_[ inPartie ];
}
