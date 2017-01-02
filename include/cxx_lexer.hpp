#pragma once
#ifndef BE_BSTYLE_CXX_LEXER_HPP_
#define BE_BSTYLE_CXX_LEXER_HPP_

#include "token_data.hpp"
#include <gsl/string_span>
#include <vector>

namespace be {
namespace bstyle {

///////////////////////////////////////////////////////////////////////////////
class CxxLexer final : Immovable {
public:
   CxxLexer(gsl::string_span<> input);

   void lex_all();
   const std::vector<TokenData>& tokens();

private:
   void t_(TokenSubtype type);
   void t_(TokenSubtype type, U32 line, U32 column, gsl::string_span<> text);
   void check_pp_identifier_();
   void check_comment_newlines_();
   void check_include_literal_();
   void check_generic_opener_();
   void check_generic_closer_();

   gsl::string_span<> input_;
   std::vector<TokenData> tokens_;
   char* ps_;
   char* p_;
   char* pe_;
   char* ts_;
   char* te_;
   char* ls_;
   U32 line_;
   bool in_attrib_;
   bool pp_include_;
   U16 unclosed_generics_;
};

} // be::bstyle
} // be

#endif
