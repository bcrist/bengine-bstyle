#include "token_type.hpp"
#include <stdexcept>

namespace be {
namespace bstyle {

///////////////////////////////////////////////////////////////////////////////
const char* get_name(TokenType type) {
   using T = TokenType;
   switch (type) {
      case T::start_of_file:           return "start_of_file";
      case T::end_of_file:             return "end_of_file";
      case T::start_of_line:           return "start_of_line";
      case T::end_of_line:             return "end_of_line";
      case T::whitespace:              return "whitespace";
      case T::comment:                 return "comment";
      case T::preprocessor_directive:  return "preprocessor_directive";
      case T::attribute_opener:        return "attribute_opener";
      case T::attribute_closer:        return "attribute_closer";
      case T::keyword:                 return "keyword";
      case T::identifier:              return "identifier";
      case T::generic_opener:          return "generic_opener";
      case T::generic_closer:          return "generic_closer";
      case T::numeric_literal:         return "numeric_literal";
      case T::string_literal:          return "string_literal";
      case T::include_literal:         return "include_literal";
      case T::scope_opener:            return "scope_opener";
      case T::scope_closer:            return "scope_closer";
      case T::paren_opener:            return "paren_opener";
      case T::paren_closer:            return "paren_closer";
      case T::array_opener:            return "array_opener";
      case T::array_closer:            return "array_closer";
      case T::op:                      return "op";
      case T::terminator:              return "terminator";
      case T::invalid_character:       return "invalid_character";
      default:
         return "<unknown>";
   }
}

///////////////////////////////////////////////////////////////////////////////
const char* get_name(TokenSubtype subtype) {
   using T = TokenSubtype;
   switch (subtype) {
      case T::start_of_file:        return "start_of_file";
      case T::end_of_file:          return "end_of_file";
      case T::start_of_line:        return "start_of_line";
      case T::end_of_line:          return "end_of_line";
      case T::whitespace:           return "whitespace";
      case T::comment_single_line:  return "comment_single_line";
      case T::comment_multi_line:   return "comment_multi_line";
      case T::comment_unterminated: return "comment_unterminated";
      case T::pp_include:           return "pp_include";
      case T::pp_if:                return "pp_if";
      case T::pp_ifdef:             return "pp_ifdef";
      case T::pp_ifndef:            return "pp_ifndef";
      case T::pp_elif:              return "pp_elif";
      case T::pp_else:              return "pp_else";
      case T::pp_endif:             return "pp_endif";
      case T::pp_pragma:            return "pp_pragma";
      case T::pp_define:            return "pp_define";
      case T::pp_undef:             return "pp_undef";
      case T::pp_line:              return "pp_line";
      case T::pp_error:             return "pp_error";
      case T::pp_unknown:           return "pp_unknown";
      case T::attribute_opener:     return "attribute_opener";
      case T::attribute_closer:     return "attribute_closer";
      case T::kw_alignas:           return "kw_alignas";
      case T::kw_alignof:           return "kw_alignof";
      case T::kw_auto:              return "kw_auto";
      case T::kw_bool:              return "kw_bool";
      case T::kw_break:             return "kw_break";
      case T::kw_case:              return "kw_case";
      case T::kw_catch:             return "kw_catch";
      case T::kw_char:              return "kw_char";
      case T::kw_char16_t:          return "kw_char16_t";
      case T::kw_char32_t:          return "kw_char32_t";
      case T::kw_class:             return "kw_class";
      case T::kw_const:             return "kw_const";
      case T::kw_constexpr:         return "kw_constexpr";
      case T::kw_const_cast:        return "kw_const_cast";
      case T::kw_continue:          return "kw_continue";
      case T::kw_decltype:          return "kw_decltype";
      case T::kw_default:           return "kw_default";
      case T::kw_delete:            return "kw_delete";
      case T::kw_do:                return "kw_do";
      case T::kw_double:            return "kw_double";
      case T::kw_dynamic_cast:      return "kw_dynamic_cast";
      case T::kw_else:              return "kw_else";
      case T::kw_enum:              return "kw_enum";
      case T::kw_explicit:          return "kw_explicit";
      case T::kw_export:            return "kw_export";
      case T::kw_extern:            return "kw_extern";
      case T::kw_false:             return "kw_false";
      case T::kw_float:             return "kw_float";
      case T::kw_for:               return "kw_for";
      case T::kw_friend:            return "kw_friend";
      case T::kw_goto:              return "kw_goto";
      case T::kw_if:                return "kw_if";
      case T::kw_inline:            return "kw_inline";
      case T::kw_int:               return "kw_int";
      case T::kw_long:              return "kw_long";
      case T::kw_mutable:           return "kw_mutable";
      case T::kw_namespace:         return "kw_namespace";
      case T::kw_new:               return "kw_new";
      case T::kw_noexcept:          return "kw_noexcept";
      case T::kw_nullptr:           return "kw_nullptr";
      case T::kw_operator:          return "kw_operator";
      case T::kw_private:           return "kw_private";
      case T::kw_protected:         return "kw_protected";
      case T::kw_public:            return "kw_public";
      case T::kw_register:          return "kw_register";
      case T::kw_reinterpret_cast:  return "kw_reinterpret_cast";
      case T::kw_return:            return "kw_return";
      case T::kw_short:             return "kw_short";
      case T::kw_signed:            return "kw_signed";
      case T::kw_sizeof:            return "kw_sizeof";
      case T::kw_static:            return "kw_static";
      case T::kw_static_assert:     return "kw_static_assert";
      case T::kw_static_cast:       return "kw_static_cast";
      case T::kw_struct:            return "kw_struct";
      case T::kw_switch:            return "kw_switch";
      case T::kw_template:          return "kw_template";
      case T::kw_this:              return "kw_this";
      case T::kw_thread_local:      return "kw_thread_local";
      case T::kw_throw:             return "kw_throw";
      case T::kw_true:              return "kw_true";
      case T::kw_try:               return "kw_try";
      case T::kw_typedef:           return "kw_typedef";
      case T::kw_typeid:            return "kw_typeid";
      case T::kw_typename:          return "kw_typename";
      case T::kw_union:             return "kw_union";
      case T::kw_unsigned:          return "kw_unsigned";
      case T::kw_using:             return "kw_using";
      case T::kw_virtual:           return "kw_virtual";
      case T::kw_void:              return "kw_void";
      case T::kw_volatile:          return "kw_volatile";
      case T::kw_wchar_t:           return "kw_wchar_t";
      case T::kw_while:             return "kw_while";
      case T::identifier:           return "identifier";
      case T::generic_opener:       return "generic_opener";
      case T::generic_closer:       return "generic_closer";
      case T::numeric_literal_int:  return "numeric_literal_int";
      case T::numeric_literal_char: return "numeric_literal_char";
      case T::numeric_literal_fp:   return "numeric_literal_fp";
      case T::string_literal:       return "string_literal";
      case T::include_literal:      return "include_literal";
      case T::scope_opener:         return "scope_opener";
      case T::scope_closer:         return "scope_closer";
      case T::paren_opener:         return "paren_opener";
      case T::paren_closer:         return "paren_closer";
      case T::array_opener:         return "array_opener";
      case T::array_closer:         return "array_closer";
      case T::op_eq:                return "op_eq";
      case T::op_eq_eq:             return "op_eq_eq";
      case T::op_not:               return "op_not";
      case T::op_not_eq:            return "op_not_eq";
      case T::op_plus:              return "op_plus";
      case T::op_plus_plus:         return "op_plus_plus";
      case T::op_plus_eq:           return "op_plus_eq";
      case T::op_minus:             return "op_minus";
      case T::op_minus_minus:       return "op_minus_minus";
      case T::op_minus_eq:          return "op_minus_eq";
      case T::op_star:              return "op_star";
      case T::op_star_eq:           return "op_star_eq";
      case T::op_slash:             return "op_slash";
      case T::op_slash_eq:          return "op_slash_eq";
      case T::op_backslash:         return "op_backslash";
      case T::op_percent:           return "op_percent";
      case T::op_percent_eq:        return "op_percent_eq";
      case T::op_amp:               return "op_amp";
      case T::op_amp_amp:           return "op_amp_amp";
      case T::op_amp_eq:            return "op_amp_eq";
      case T::op_bar:               return "op_bar";
      case T::op_bar_bar:           return "op_bar_bar";
      case T::op_bar_eq:            return "op_bar_eq";
      case T::op_caret:             return "op_caret";
      case T::op_caret_eq:          return "op_caret_eq";
      case T::op_left:              return "op_left";
      case T::op_left_eq:           return "op_left_eq";
      case T::op_right:             return "op_right";
      case T::op_right_eq:          return "op_right_eq";
      case T::op_less:              return "op_less";
      case T::op_less_eq:           return "op_less_eq";
      case T::op_greater:           return "op_greater";
      case T::op_greater_eq:        return "op_greater_eq";
      case T::op_dot:               return "op_dot";
      case T::op_elipsis:           return "op_elipsis";
      case T::op_comma:             return "op_comma";
      case T::op_arrow:             return "op_arrow";
      case T::op_question:          return "op_question";
      case T::op_colon:             return "op_colon";
      case T::op_scope:             return "op_scope";
      case T::op_tilde:             return "op_tilde";
      case T::op_hash:              return "op_hash";
      case T::op_hash_hash:         return "op_hash_hash";
      case T::terminator:           return "terminator";
      case T::invalid_character:    return "invalid_character";
      default:
         return "<unknown>";
   }
}

///////////////////////////////////////////////////////////////////////////////
TokenType get_token_type(TokenSubtype subtype) {
   using T = TokenType;
   using ST = TokenSubtype;
   switch (subtype) {
      case ST::start_of_file:       return T::start_of_file;
      case ST::end_of_file:         return T::end_of_file;
      case ST::start_of_line:       return T::start_of_line;
      case ST::end_of_line:         return T::end_of_line;
      case ST::whitespace:          return T::whitespace;
      case ST::comment_single_line: return T::comment;
      case ST::comment_multi_line:  return T::comment;
      case ST::comment_unterminated:return T::comment;
      case ST::pp_include:          return T::preprocessor_directive;
      case ST::pp_if:               return T::preprocessor_directive;
      case ST::pp_ifdef:            return T::preprocessor_directive;
      case ST::pp_ifndef:           return T::preprocessor_directive;
      case ST::pp_elif:             return T::preprocessor_directive;
      case ST::pp_else:             return T::preprocessor_directive;
      case ST::pp_endif:            return T::preprocessor_directive;
      case ST::pp_pragma:           return T::preprocessor_directive;
      case ST::pp_define:           return T::preprocessor_directive;
      case ST::pp_undef:            return T::preprocessor_directive;
      case ST::pp_line:             return T::preprocessor_directive;
      case ST::pp_error:            return T::preprocessor_directive;
      case ST::pp_unknown:          return T::preprocessor_directive;
      case ST::attribute_opener:    return T::attribute_opener;
      case ST::attribute_closer:    return T::attribute_closer;
      case ST::kw_alignas:          return T::keyword;
      case ST::kw_alignof:          return T::keyword;
      case ST::kw_auto:             return T::keyword;
      case ST::kw_bool:             return T::keyword;
      case ST::kw_break:            return T::keyword;
      case ST::kw_case:             return T::keyword;
      case ST::kw_catch:            return T::keyword;
      case ST::kw_char:             return T::keyword;
      case ST::kw_char16_t:         return T::keyword;
      case ST::kw_char32_t:         return T::keyword;
      case ST::kw_class:            return T::keyword;
      case ST::kw_const:            return T::keyword;
      case ST::kw_constexpr:        return T::keyword;
      case ST::kw_const_cast:       return T::keyword;
      case ST::kw_continue:         return T::keyword;
      case ST::kw_decltype:         return T::keyword;
      case ST::kw_default:          return T::keyword;
      case ST::kw_delete:           return T::keyword;
      case ST::kw_do:               return T::keyword;
      case ST::kw_double:           return T::keyword;
      case ST::kw_dynamic_cast:     return T::keyword;
      case ST::kw_else:             return T::keyword;
      case ST::kw_enum:             return T::keyword;
      case ST::kw_explicit:         return T::keyword;
      case ST::kw_export:           return T::keyword;
      case ST::kw_extern:           return T::keyword;
      case ST::kw_false:            return T::keyword;
      case ST::kw_float:            return T::keyword;
      case ST::kw_for:              return T::keyword;
      case ST::kw_friend:           return T::keyword;
      case ST::kw_goto:             return T::keyword;
      case ST::kw_if:               return T::keyword;
      case ST::kw_inline:           return T::keyword;
      case ST::kw_int:              return T::keyword;
      case ST::kw_long:             return T::keyword;
      case ST::kw_mutable:          return T::keyword;
      case ST::kw_namespace:        return T::keyword;
      case ST::kw_new:              return T::keyword;
      case ST::kw_noexcept:         return T::keyword;
      case ST::kw_nullptr:          return T::keyword;
      case ST::kw_operator:         return T::keyword;
      case ST::kw_private:          return T::keyword;
      case ST::kw_protected:        return T::keyword;
      case ST::kw_public:           return T::keyword;
      case ST::kw_register:         return T::keyword;
      case ST::kw_reinterpret_cast: return T::keyword;
      case ST::kw_return:           return T::keyword;
      case ST::kw_short:            return T::keyword;
      case ST::kw_signed:           return T::keyword;
      case ST::kw_sizeof:           return T::keyword;
      case ST::kw_static:           return T::keyword;
      case ST::kw_static_assert:    return T::keyword;
      case ST::kw_static_cast:      return T::keyword;
      case ST::kw_struct:           return T::keyword;
      case ST::kw_switch:           return T::keyword;
      case ST::kw_template:         return T::keyword;
      case ST::kw_this:             return T::keyword;
      case ST::kw_thread_local:     return T::keyword;
      case ST::kw_throw:            return T::keyword;
      case ST::kw_true:             return T::keyword;
      case ST::kw_try:              return T::keyword;
      case ST::kw_typedef:          return T::keyword;
      case ST::kw_typeid:           return T::keyword;
      case ST::kw_typename:         return T::keyword;
      case ST::kw_union:            return T::keyword;
      case ST::kw_unsigned:         return T::keyword;
      case ST::kw_using:            return T::keyword;
      case ST::kw_virtual:          return T::keyword;
      case ST::kw_void:             return T::keyword;
      case ST::kw_volatile:         return T::keyword;
      case ST::kw_wchar_t:          return T::keyword;
      case ST::kw_while:            return T::keyword;
      case ST::identifier:          return T::identifier;
      case ST::generic_opener:      return T::generic_opener;
      case ST::generic_closer:      return T::generic_closer;
      case ST::numeric_literal_int: return T::numeric_literal;
      case ST::numeric_literal_char:return T::numeric_literal;
      case ST::numeric_literal_fp:  return T::numeric_literal;
      case ST::string_literal:      return T::string_literal;
      case ST::include_literal:     return T::include_literal;
      case ST::scope_opener:        return T::scope_opener;
      case ST::scope_closer:        return T::scope_closer;
      case ST::paren_opener:        return T::paren_opener;
      case ST::paren_closer:        return T::paren_closer;
      case ST::array_opener:        return T::array_opener;
      case ST::array_closer:        return T::array_closer;
      case ST::op_eq:               return T::op;
      case ST::op_plus_eq:          return T::op;
      case ST::op_minus_eq:         return T::op;
      case ST::op_star_eq:          return T::op;
      case ST::op_slash_eq:         return T::op;
      case ST::op_percent_eq:       return T::op;
      case ST::op_amp_eq:           return T::op;
      case ST::op_bar_eq:           return T::op;
      case ST::op_caret_eq:         return T::op;
      case ST::op_left_eq:          return T::op;
      case ST::op_right_eq:         return T::op;
      case ST::op_plus_plus:        return T::op;
      case ST::op_minus_minus:      return T::op;
      case ST::op_plus:             return T::op;
      case ST::op_minus:            return T::op;
      case ST::op_star:             return T::op;
      case ST::op_slash:            return T::op;
      case ST::op_backslash:        return T::op;
      case ST::op_percent:          return T::op;
      case ST::op_tilde:            return T::op;
      case ST::op_amp:              return T::op;
      case ST::op_bar:              return T::op;
      case ST::op_caret:            return T::op;
      case ST::op_left:             return T::op;
      case ST::op_right:            return T::op;
      case ST::op_not:              return T::op;
      case ST::op_amp_amp:          return T::op;
      case ST::op_bar_bar:          return T::op;
      case ST::op_eq_eq:            return T::op;
      case ST::op_not_eq:           return T::op;
      case ST::op_less:             return T::op;
      case ST::op_greater:          return T::op;
      case ST::op_less_eq:          return T::op;
      case ST::op_greater_eq:       return T::op;
      case ST::op_dot:              return T::op;
      case ST::op_arrow:            return T::op;
      case ST::op_question:         return T::op;
      case ST::op_colon:            return T::op;
      case ST::op_scope:            return T::op;
      case ST::op_comma:            return T::op;
      case ST::op_elipsis:          return T::op;
      case ST::op_hash:             return T::op;
      case ST::op_hash_hash:        return T::op;
      case ST::terminator:          return T::terminator;
      case ST::invalid_character:   return T::invalid_character;
      default: throw std::invalid_argument("Unknown token subtype!");
   }
}

} // be::bstyle
} // be
