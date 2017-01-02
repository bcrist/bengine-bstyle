#include "token.hpp"
#include "document.hpp"
#include <cassert>

namespace be {
namespace bstyle {

///////////////////////////////////////////////////////////////////////////////
Token::Token()
   : id_(0),
     doc_(nullptr)
{ }

///////////////////////////////////////////////////////////////////////////////
Token::Token(const Token& other)
   : id_(other.id_),
     doc_(other.doc_)
{ }

///////////////////////////////////////////////////////////////////////////////
Token& Token::operator=(const Token& other) {
   id_ = other.id_;
   doc_ = other.doc_;
   return *this;
}

///////////////////////////////////////////////////////////////////////////////
Token::operator bool() const {
   return !!doc_;
}

///////////////////////////////////////////////////////////////////////////////
U32 Token::id() const {
   return id_;
}

///////////////////////////////////////////////////////////////////////////////
Token::operator const gsl::string_span<>() const {
   assert(doc_);
   assert(id_ < doc_->token_text_.size());
   return doc_->token_text_[id_];
}

///////////////////////////////////////////////////////////////////////////////
U32 Token::line() const {
   assert(doc_);
   assert(id_ < doc_->token_locations_.size());
   return doc_->token_locations_[id_].line;
}

///////////////////////////////////////////////////////////////////////////////
U32 Token::column() const {
   assert(doc_);
   assert(id_ < doc_->token_locations_.size());
   return doc_->token_locations_[id_].column;
}

///////////////////////////////////////////////////////////////////////////////
TokenType Token::type() const {
   assert(doc_);
   assert(id_ < doc_->token_types_.size());
   return get_token_type(doc_->token_types_[id_]);
}

///////////////////////////////////////////////////////////////////////////////
TokenSubtype Token::subtype() const {
   assert(doc_);
   assert(id_ < doc_->token_types_.size());
   return doc_->token_types_[id_];
}

///////////////////////////////////////////////////////////////////////////////
Scope Token::scope() const {
   assert(doc_);
   assert(id_ < doc_->token_scopes_.size());
   doc_->clean_tokens_();
   return doc_->token_scopes_[id_];
}

///////////////////////////////////////////////////////////////////////////////
TokenStatus Token::status() const {
   assert(doc_);
   assert(id_ < doc_->token_statuses_.size());
   return doc_->token_statuses_[id_];
}

///////////////////////////////////////////////////////////////////////////////
Token Token::prev() const {
   if (!doc_) {
      return Token();
   }
   doc_->clean_tokens_();
   U32 index = doc_->token_indices_[id_];
   if (index > 0) {
      return doc_->tokens_[index - 1];
   } else {
      return Token();
   }
}

///////////////////////////////////////////////////////////////////////////////
Token Token::prev_semantic() const {
   if (!doc_) {
      return Token();
   }
   doc_->clean_tokens_();
   U32 id = doc_->token_prev_semantic_tokens_[id_];
   if (id != U32(-1)) {
      return Token(*doc_, id);
   } else {
      return Token();
   }
}

///////////////////////////////////////////////////////////////////////////////
Token Token::prev_comment() const {
   if (!doc_) {
      return Token();
   }
   doc_->clean_tokens_();
   U32 id = doc_->token_prev_comments_[id_];
   if (id != U32(-1)) {
      return Token(*doc_, id);
   } else {
      return Token();
   }
}

///////////////////////////////////////////////////////////////////////////////
Token Token::start_of_line() const {
   if (!doc_) {
      return Token();
   }
   doc_->clean_tokens_();
   U32 id = doc_->token_start_of_lines_[id_];
   if (id != U32(-1)) {
      return Token(*doc_, id);
   } else {
      return Token();
   }
}

///////////////////////////////////////////////////////////////////////////////
Token Token::start_of_scope() const {
   if (!doc_) {
      return Token();
   }
   doc_->clean_tokens_();
   U32 id = doc_->token_start_of_scopes_[id_];
   if (id != U32(-1)) {
      return Token(*doc_, id);
   } else {
      return Token();
   }
}

///////////////////////////////////////////////////////////////////////////////
Token Token::start_of_statement() const {
   if (!doc_) {
      return Token();
   }
   doc_->clean_tokens_();
   U32 id = doc_->token_start_of_statements_[id_];
   if (id != U32(-1)) {
      return Token(*doc_, id);
   } else {
      return Token();
   }
}

///////////////////////////////////////////////////////////////////////////////
Token Token::next() const {
   if (!doc_) {
      return Token();
   }
   doc_->clean_tokens_();
   U32 index = doc_->token_indices_[id_];
   if (index < doc_->tokens_.size() - 1) {
      return doc_->tokens_[index + 1];
   } else {
      return Token();
   }
}

///////////////////////////////////////////////////////////////////////////////
Token Token::next_semantic() const {
   if (!doc_) {
      return Token();
   }
   doc_->clean_tokens_();
   U32 id = doc_->token_next_semantic_tokens_[id_];
   if (id != U32(-1)) {
      return Token(*doc_, id);
   } else {
      return Token();
   }
}

///////////////////////////////////////////////////////////////////////////////
Token Token::next_comment() const {
   if (!doc_) {
      return Token();
   }
   doc_->clean_tokens_();
   U32 id = doc_->token_next_comments_[id_];
   if (id != U32(-1)) {
      return Token(*doc_, id);
   } else {
      return Token();
   }
}

///////////////////////////////////////////////////////////////////////////////
Token Token::end_of_line() const {
   if (!doc_) {
      return Token();
   }
   doc_->clean_tokens_();
   U32 id = doc_->token_end_of_lines_[id_];
   if (id != U32(-1)) {
      return Token(*doc_, id);
   } else {
      return Token();
   }
}

///////////////////////////////////////////////////////////////////////////////
Token Token::end_of_scope() const {
   if (!doc_) {
      return Token();
   }
   doc_->clean_tokens_();
   U32 id = doc_->token_end_of_scopes_[id_];
   if (id != U32(-1)) {
      return Token(*doc_, id);
   } else {
      return Token();
   }
}

///////////////////////////////////////////////////////////////////////////////
Token Token::end_of_statement() const {
   if (!doc_) {
      return Token();
   }
   doc_->clean_tokens_();
   U32 id = doc_->token_end_of_statements_[id_];
   if (id != U32(-1)) {
      return Token(*doc_, id);
   } else {
      return Token();
   }
}

///////////////////////////////////////////////////////////////////////////////
Token::Token(const Document& doc, U32 token_id)
   : id_(token_id),
     doc_(&doc)
{ }

///////////////////////////////////////////////////////////////////////////////
bool operator==(const Token& a, const Token& b) {
   return a.doc_ == b.doc_ && a.id_ == b.id_;
}

///////////////////////////////////////////////////////////////////////////////
bool operator!=(const Token& a, const Token& b) {
   return !(a == b);
}

} // be::bstyle
} // be
