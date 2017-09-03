#include "document.hpp"
#include "cxx_lexer.hpp"
#include <be/util/string_span.hpp>
#include <sstream>

namespace be {
namespace bstyle {

///////////////////////////////////////////////////////////////////////////////
Document::Document(Path path, S data)
   : path_(std::move(path)),
     data_(std::move(data)),
     tokens_dirty_(true)
{
   CxxLexer lexer(data_);
   lexer.lex_all();
   reserve_(lexer.tokens().size());
   for (const TokenData& t : lexer.tokens()) {
      TokenId id = TokenId(token_types_.size());
      assert(token_text_.size() == id);
      assert(token_locations_.size() == id);
      assert(token_statuses_.size() == id);
      assert(tokens_.size() == id);

      token_types_.push_back(t.type);
      token_text_.push_back(t.text);
      token_locations_.push_back(t.location);
      token_statuses_.push_back(TokenStatus::unchanged);
      tokens_.push_back(Token(*this, id));
   }
}

///////////////////////////////////////////////////////////////////////////////
Document::operator S() const {
   std::ostringstream oss;

   for (Token t : tokens_) {
      if (t.status() != TokenStatus::deleted) {
         oss << gsl::string_span<>(t);
      }
   }

   return oss.str();
}

///////////////////////////////////////////////////////////////////////////////
const Path& Document::path() const {
   return path_;
}

///////////////////////////////////////////////////////////////////////////////
void Document::path(Path path) {
   path_ = std::move(path);
}

///////////////////////////////////////////////////////////////////////////////
bool Document::empty() const {
   return tokens_.empty();
}

///////////////////////////////////////////////////////////////////////////////
std::size_t Document::size() const {
   return tokens_.size();
}

///////////////////////////////////////////////////////////////////////////////
Token Document::token(TokenId id) const {
   return id < token_types_.size() ? Token(*this, id) : Token();
}

///////////////////////////////////////////////////////////////////////////////
Document::const_iterator Document::iterator(TokenId id) const {
   clean_tokens_();
   assert(id < token_indices_.size());
   return tokens_.begin() + token_indices_[id];
}

///////////////////////////////////////////////////////////////////////////////
Document::const_iterator Document::iterator(Token token) const {
   assert(token.doc_ == this);
   return iterator(token.id());
}

///////////////////////////////////////////////////////////////////////////////
Document::const_iterator Document::begin() const {
   return tokens_.begin();
}

///////////////////////////////////////////////////////////////////////////////
Document::const_iterator Document::end() const {
   return tokens_.end();
}

///////////////////////////////////////////////////////////////////////////////
Token Document::operator[](std::size_t index) const {
   return tokens_[index];
}

///////////////////////////////////////////////////////////////////////////////
Document::const_iterator Document::insert(const_iterator before, TokenSubtype type, gsl::string_span<> text) {
   TokenId id = TokenId(token_types_.size());
   assert(token_text_.size() == id);
   assert(token_locations_.size() == id);
   assert(token_statuses_.size() == id);
   token_types_.push_back(type);
   token_text_.push_back(text);
   token_locations_.push_back({0, 0});
   token_statuses_.push_back(TokenStatus::inserted);
   tokens_dirty_ = true;
   return tokens_.insert(before, Token(*this, id));
}

///////////////////////////////////////////////////////////////////////////////
void Document::erase(Token token) {
   auto& status = token_statuses_[token.id()];
   if (status != TokenStatus::deleted) {
      token_statuses_[token.id()] = TokenStatus::deleted;
      tokens_dirty_ = true;
   }
}

///////////////////////////////////////////////////////////////////////////////
void Document::reserve_(std::size_t n_tokens) {
   tokens_.reserve(n_tokens);
   token_types_.reserve(n_tokens);
   token_text_.reserve(n_tokens);
   token_locations_.reserve(n_tokens);
   token_statuses_.reserve(n_tokens);
   token_indices_.reserve(n_tokens);
   token_scopes_.reserve(n_tokens);

   token_prev_comments_.reserve(n_tokens);
   token_prev_semantic_tokens_.reserve(n_tokens);
   token_start_of_lines_.reserve(n_tokens);
   token_start_of_scopes_.reserve(n_tokens);
   token_start_of_statements_.reserve(n_tokens);

   token_next_comments_.reserve(n_tokens);
   token_next_semantic_tokens_.reserve(n_tokens);
   token_end_of_lines_.reserve(n_tokens);
   token_end_of_scopes_.reserve(n_tokens);
   token_end_of_statements_.reserve(n_tokens);
}

///////////////////////////////////////////////////////////////////////////////
void Document::clean_tokens_() const {
   if (tokens_dirty_) {
      std::size_t n_tokens = token_types_.size();
      token_indices_.reserve(n_tokens);
      token_scopes_.reserve(n_tokens);

      token_prev_comments_.reserve(n_tokens);
      token_prev_semantic_tokens_.reserve(n_tokens);
      token_start_of_lines_.reserve(n_tokens);
      token_start_of_scopes_.reserve(n_tokens);
      token_start_of_statements_.reserve(n_tokens);

      token_next_comments_.reserve(n_tokens);
      token_next_semantic_tokens_.reserve(n_tokens);
      token_end_of_lines_.reserve(n_tokens);
      token_end_of_scopes_.reserve(n_tokens);
      token_end_of_statements_.reserve(n_tokens);

      calc_forward_adjacencies();
      calc_reverse_adjacencies();
      tokens_dirty_ = false;
   }
}

///////////////////////////////////////////////////////////////////////////////
void Document::calc_forward_adjacencies() const {
   std::size_t n_tokens = tokens_.size();
   token_indices_.resize(n_tokens);
   token_scopes_.resize(n_tokens);
   token_prev_comments_.resize(n_tokens);
   token_prev_semantic_tokens_.resize(n_tokens);
   token_start_of_lines_.resize(n_tokens);
   token_start_of_scopes_.resize(n_tokens);
   token_start_of_statements_.resize(n_tokens);

   U32 index = 0;

   TokenId comment = TokenId(-1);
   TokenId semantic = TokenId(-1);
   TokenId line_bound = TokenId(-1);

   Scope next_scope = Scope::file_scope;

   struct scope_data {
      TokenId scope_bound;
      TokenId stmt_bound;
      Scope scope;
   };

   std::vector<scope_data> scopes;
   scopes.push_back({ TokenId(-1), TokenId(-1), Scope::file_scope });

   for (Token t : tokens_) {
      TokenId id = t.id();

      token_indices_[id] = index;
      ++index;

      token_prev_comments_[id] = comment;
      token_prev_semantic_tokens_[id] = semantic;

      if (scopes.back().scope_bound == TokenId(-1)) {
         scopes.back().scope_bound = id;
      }

      if (scopes.back().stmt_bound == TokenId(-1)) {
         scopes.back().stmt_bound = id;
      }

      if (t.status() != TokenStatus::deleted) {
         switch (t.subtype()) {
            case TokenSubtype::scope_opener:
               scopes.push_back({ TokenId(-1), TokenId(-1), scopes.back().scope });
               break;

            case TokenSubtype::attribute_opener:
               next_scope = Scope::attribute_scope;
               scopes.push_back({ TokenId(-1), TokenId(-1), next_scope });
               break;

            case TokenSubtype::attribute_closer:
            case TokenSubtype::scope_closer:
               scopes.pop_back();
               if (scopes.empty()) {
                  scopes.push_back({ TokenId(-1), TokenId(-1), Scope::file_scope });
               }
               next_scope = Scope::count_;
               break;

            case TokenSubtype::terminator:
               scopes.back().stmt_bound = TokenId(-1);
               next_scope = scopes.back().scope;
               break;

            case TokenSubtype::kw_namespace:
               next_scope = Scope::namespace_scope;
               break;

            case TokenSubtype::kw_class:
            case TokenSubtype::kw_struct:
               if (next_scope != Scope::enum_scope) {
                  next_scope = Scope::class_scope;
               }
               break;

            case TokenSubtype::kw_enum:
               next_scope = Scope::enum_scope;
               break;

            case TokenSubtype::paren_closer:
               next_scope = Scope::function_scope;
               break;

            case TokenSubtype::op_comma:
               if (next_scope != Scope::class_scope) {
                  next_scope = scopes.back().scope;
               }
               break;
         }

         switch (t.type()) {
            case TokenType::comment: {
               gsl::cstring_span<> text = token_text_[id];
               if (std::find(text.begin(), text.end(), '\n') != text.end()) {
                  line_bound = id;
               }
               comment = id;
               break;
            }

            case TokenType::start_of_line:
               line_bound = id;
               break;

            case TokenType::end_of_line:
            case TokenType::whitespace:
            case TokenType::start_of_file:
            case TokenType::end_of_file:
            case TokenType::attribute_opener:
            case TokenType::attribute_closer:
               break;

            default:
               if (scopes.back().scope != Scope::attribute_scope) {
                  semantic = id;
               }
         }
      }

      bool found_scope = false;
      for (auto it = scopes.rbegin(); it != scopes.rend(); ++it) {
         if (it->scope_bound != TokenId(-1)) {
            token_scopes_[id] = it->scope;
            token_start_of_scopes_[id] = it->scope_bound;
            token_start_of_statements_[id] = it->stmt_bound;
            found_scope = true;
         }
      }
      if (!found_scope) {
         token_scopes_[id] = Scope::file_scope;
         token_start_of_scopes_[id] = TokenId(-1);
         token_start_of_statements_[id] = TokenId(-1);
      }

      token_start_of_lines_[id] = line_bound;
   }
}

///////////////////////////////////////////////////////////////////////////////
void Document::calc_reverse_adjacencies() const {
   std::size_t n_tokens = tokens_.size();
   token_next_comments_.resize(n_tokens);
   token_next_semantic_tokens_.resize(n_tokens);
   token_end_of_lines_.resize(n_tokens);
   token_end_of_scopes_.resize(n_tokens);
   token_end_of_statements_.resize(n_tokens);

   TokenId comment = TokenId(-1);
   TokenId semantic = TokenId(-1);
   TokenId line_bound = TokenId(-1);

   for (auto it = tokens_.rbegin(), end = tokens_.rend(); it != end; ++it) {
      Token t = *it;
      TokenId id = t.id();

      token_next_comments_[id] = comment;
      token_next_semantic_tokens_[id] = semantic;

      struct scope_data {
         TokenId scope_bound;
         TokenId stmt_bound;
      };

      std::vector<scope_data> scopes;
      scopes.push_back({ TokenId(-1), TokenId(-1) });

      if (scopes.back().scope_bound == TokenId(-1)) {
         scopes.back().scope_bound = id;
      }

      if (scopes.back().stmt_bound == TokenId(-1)) {
         scopes.back().stmt_bound = id;
      }

      if (t.status() != TokenStatus::deleted) {
         switch (t.subtype()) {
            case TokenSubtype::scope_closer:
            case TokenSubtype::attribute_closer:
               scopes.push_back({ TokenId(-1), TokenId(-1) });
               break;

            case TokenSubtype::scope_opener:
            case TokenSubtype::attribute_opener:
               scopes.pop_back();
               if (scopes.empty()) {
                  scopes.push_back({ TokenId(-1), TokenId(-1) });
               }
               break;

            case TokenSubtype::terminator:
               scopes.back().stmt_bound = TokenId(-1);
               break;
         }

         switch (t.type()) {
            case TokenType::comment: {
               gsl::cstring_span<> text = token_text_[id];
               if (std::find(text.begin(), text.end(), '\n') != text.end()) {
                  line_bound = id;
               }
               comment = id;
               break;
            }

            case TokenType::end_of_line:
               line_bound = id;
               break;

            case TokenType::start_of_line:
            case TokenType::whitespace:
            case TokenType::start_of_file:
            case TokenType::end_of_file:
            case TokenType::attribute_opener:
            case TokenType::attribute_closer:
               break;

            default:
               if (token_scopes_[id] != Scope::attribute_scope) {
                  semantic = id;
               }
         }
      }

      bool found_scope = false;
      for (auto it2 = scopes.rbegin(); it2 != scopes.rend(); ++it2) {
         if (it2->scope_bound != TokenId(-1)) {
            token_end_of_scopes_[id] = it2->scope_bound;
            token_end_of_statements_[id] = it2->stmt_bound;
            found_scope = true;
         }
      }
      if (!found_scope) {
         token_end_of_scopes_[id] = TokenId(-1);
         token_end_of_statements_[id] = TokenId(-1);
      }

      token_end_of_lines_[id] = line_bound;
   }
}

} // be::bstyle
} // be
