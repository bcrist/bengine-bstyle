#pragma once
#ifndef BE_BSTYLE_DOCUMENT_HPP_
#define BE_BSTYLE_DOCUMENT_HPP_

#include "token.hpp"
#include <be/core/filesystem.hpp>
#include <vector>

namespace be {
namespace bstyle {

///////////////////////////////////////////////////////////////////////////////
class Document final : Immovable {
   using TokenId = U32;
   friend class Token;
public:
   using const_iterator = std::vector<Token>::const_iterator;

   Document(Path path, S data);
   operator S() const;

   const Path& path() const;
   void path(Path path);

   bool empty() const;
   std::size_t size() const;

   Token token(TokenId id) const;
   const_iterator iterator(TokenId id) const;
   const_iterator iterator(Token token) const;

   const_iterator begin() const;
   const_iterator end() const;
   
   Token operator[](std::size_t index) const;

   const_iterator insert(const_iterator before, TokenSubtype type, gsl::string_span<> text);
   void erase(Token token);

private:
   void reserve_(std::size_t n_tokens);
   void clean_tokens_() const;
   void calc_forward_adjacencies() const;
   void calc_reverse_adjacencies() const;

   Path path_;
   S data_;
   std::vector<Token> tokens_;
   mutable  bool tokens_dirty_;

   // TokenID is index for the following:
   std::vector<TokenSubtype> token_types_;
   std::vector<gsl::string_span<>> token_text_;
   std::vector<TokenLocation> token_locations_;
   std::vector<TokenStatus> token_statuses_;
   // these are calculated in clean_tokens_()
   mutable std::vector<U32> token_indices_;
   mutable std::vector<Scope> token_scopes_;

   mutable std::vector<TokenId> token_prev_comments_;
   mutable std::vector<TokenId> token_prev_semantic_tokens_; // any token which is not whitespace, comment, start/end-of-file/line, attribute-opener/closer, or a token enclosed by attribute opener/closers
   mutable std::vector<TokenId> token_start_of_lines_; // start-of-line
   mutable std::vector<TokenId> token_start_of_scopes_; // where the current scope was opened.
   mutable std::vector<TokenId> token_start_of_statements_; // where the current scope was opened, or closest previous terminator.

   mutable std::vector<TokenId> token_next_comments_;
   mutable std::vector<TokenId> token_next_semantic_tokens_; // any token which is not whitespace, comment, start/end-of-file/line, attribute-opener/closer, or a token enclosed by attribute opener/closers
   mutable std::vector<TokenId> token_end_of_lines_; // end-of-line
   mutable std::vector<TokenId> token_end_of_scopes_; // where the current scope will be closed.
   mutable std::vector<TokenId> token_end_of_statements_; // where the current scope will be closed, or closest upcoming terminator.
};

} // be::bstyle
} // be

#endif
