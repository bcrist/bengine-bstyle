#pragma once
#ifndef BE_BSTYLE_RULE_BASE_HPP_
#define BE_BSTYLE_RULE_BASE_HPP_

#include "all_rules.hpp"

namespace be {
namespace bstyle {
namespace detail {

///////////////////////////////////////////////////////////////////////////////
inline S strip_namespace(S qualified_name) {
   S test = "be::bstyle::rules::";
   if (std::equal(test.begin(), test.end(), qualified_name.begin(), qualified_name.end())) {
      qualified_name.erase(0, test.length());
   }

   // collapse any remaining :: into :
   bool last_was_colon = false;
   for (auto it = qualified_name.begin(); it != qualified_name.end();) {
      bool found_colon = *it == ':';
      if (last_was_colon && found_colon) {
         it = qualified_name.erase(it);
      } else {
         ++it;
      }
      last_was_colon = found_colon;
   }
}

///////////////////////////////////////////////////////////////////////////////
std::vector<S> tags_from_id(S id) {
   // any namespaces inside ::be::bstyle::rules:: become tags
   std::vector<S> tags;
   auto begin = id.begin();
   for (auto it = begin, end = id.end(); it != end; ++it) {
      if (*it == ':') {
         if (begin != it) {
            tags.push_back(S(begin, it));
         }
         begin = it + 1;
      }
   }
   return tags;
}

} // be::bstyle::detail

///////////////////////////////////////////////////////////////////////////////
template <typename Derived>
class RuleBase {
public:
   using s_il = std::initializer_list<S>;
   using token_type_il = std::initializer_list<TokenType>;
   using token_subtype_il = std::initializer_list<TokenSubtype>;

   const S& id() const {
      return Derived::id;
   }

   std::size_t size() const {
      return Derived::tags.size();
   }

   const S& operator[](std::size_t index) const {
      return Derived::tags[index];
   }

   bool applies_to(const Path& path) const {
      Path ext = path.extension();
      auto& t = Derived::file_extensions;
      return std::find(std::begin(t), std::end(t), ext.generic_string()) != std::end(t);
   }

   bool applies_to(TokenSubtype subtype) const {
      auto& t = Derived::token_types;
      auto& st = Derived::token_subtypes;
      return std::find(std::begin(st), std::end(st), subtype) != std::end(st) ||
         std::find(std::begin(t), std::end(t), get_token_type(subtype)) != std::end(t);
   }

   U8 strictness() const {
      return Derived::strictness_level;
   }

   U32 priority() const {
      return Derived::priority;
   }

   //void operator()(Document& document, Token token) const;

   static const S id;
   static const std::vector<S> tags;
   static const s_il extensions;
   static const std::array<TokenType, 0> token_types;
   static const std::array<TokenSubtype, 0> token_subtypes;
   static const U8 strictness = 1;
   static const U32 priority = 0;

private:
   static const Nil init_;
};

//////////////////////////////////////////////////////////////////////////////
template <typename Derived>
const S RuleBase<Derived>::id = detail::strip_namespace(type_name<Derived>());

///////////////////////////////////////////////////////////////////////////////
template <typename Derived>
const std::vector<S> RuleBase<Derived>::tags = detail::tags_from_id(detail::strip_namespace(type_name<Derived>()));

//////////////////////////////////////////////////////////////////////////////
template <typename Derived>
const std::initializer_list<S> RuleBase<Derived>::extensions = { ".hpp", ".inl", ".cpp" };

//////////////////////////////////////////////////////////////////////////////
template <typename Derived>
const std::array<TokenType, 0> RuleBase<Derived>::token_types;

//////////////////////////////////////////////////////////////////////////////
template <typename Derived>
const std::array<TokenSubtype, 0> RuleBase<Derived>::token_subtypes;

//////////////////////////////////////////////////////////////////////////////
template <typename Derived>
const Nil RuleBase<Derived>::init_ = detail::init_rule(Derived());

} // be::bstyle
} // be

#endif
