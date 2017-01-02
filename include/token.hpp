#pragma once
#ifndef BE_BSTYLE_TOKEN_HPP_
#define BE_BSTYLE_TOKEN_HPP_

#include "token_data.hpp"

namespace be {
namespace bstyle {

///////////////////////////////////////////////////////////////////////////////
enum Scope {
   file_scope,
   namespace_scope,
   enum_scope,
   class_scope,
   function_scope,
   attribute_scope,

   count_
};

///////////////////////////////////////////////////////////////////////////////
enum class TokenStatus {
   unchanged,
   deleted,
   inserted,

   count_
};

class Document;

///////////////////////////////////////////////////////////////////////////////
class Token final {
   friend class Document;
   friend bool operator==(const Token&, const Token&);
public:
   Token();
   Token(const Token& other);
   Token& operator=(const Token& other);

   operator bool() const;
   U32 id() const;

   Token prev() const;
   Token prev_comment() const;
   Token prev_semantic() const;
   Token start_of_line() const;
   Token start_of_scope() const;
   Token start_of_statement() const;

   Token next() const;
   Token next_comment() const;
   Token next_semantic() const;
   Token end_of_line() const;
   Token end_of_scope() const;
   Token end_of_statement() const;

   // the following accessors assume a precondition of
   // operator bool() == true
   operator const gsl::string_span<>() const;
   U32 line() const;
   U32 column() const;
   TokenType type() const;
   TokenSubtype subtype() const;
   Scope scope() const;
   TokenStatus status() const;

private:
   Token(const Document& doc, U32 token_id); 

   U32 id_;
   const Document* doc_;
};

bool operator==(const Token& a, const Token& b);
bool operator!=(const Token& a, const Token& b);

} // be::bstyle
} // be

#endif
