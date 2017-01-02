#pragma once
#ifndef BE_BSTYLE_TOKEN_TYPE_HPP_
#define BE_BSTYLE_TOKEN_TYPE_HPP_

namespace be {
namespace bstyle {

///////////////////////////////////////////////////////////////////////////////
enum class TokenType {
   start_of_file,
   end_of_file,

   start_of_line,
   end_of_line,

   whitespace,
   comment,
   preprocessor_directive,
   attribute_opener,
   attribute_closer,

   keyword,
   identifier,

   generic_opener,
   generic_closer,

   numeric_literal,
   string_literal,
   include_literal,

   scope_opener,
   scope_closer,

   paren_opener,
   paren_closer,

   array_opener,
   array_closer,

   op,
   terminator,

   invalid_character,

   count_
};

///////////////////////////////////////////////////////////////////////////////
const char* get_name(TokenType type);

///////////////////////////////////////////////////////////////////////////////
enum class TokenSubtype {
   start_of_file,

   end_of_file,

   start_of_line,

   end_of_line,

   whitespace,

   comment_single_line,
   comment_multi_line,
   comment_unterminated,

   pp_include,
   pp_if,
   pp_ifdef,
   pp_ifndef,
   pp_elif,
   pp_else,
   pp_endif,
   pp_pragma,
   pp_define,
   pp_undef,
   pp_line,
   pp_error,
   pp_unknown,

   attribute_opener,

   attribute_closer,

   kw_alignas,
   kw_alignof,
   kw_auto,
   kw_bool,
   kw_break,
   kw_case,
   kw_catch,
   kw_char,
   kw_char16_t,
   kw_char32_t,
   kw_class,
   kw_const,
   kw_constexpr,
   kw_const_cast,
   kw_continue,
   kw_decltype,
   kw_default,
   kw_delete,
   kw_do,
   kw_double,
   kw_dynamic_cast,
   kw_else,
   kw_enum,
   kw_explicit,
   kw_export,
   kw_extern,
   kw_false,
   kw_float,
   kw_for,
   kw_friend,
   kw_goto,
   kw_if,
   kw_inline,
   kw_int,
   kw_long,
   kw_mutable,
   kw_namespace,
   kw_new,
   kw_noexcept,
   kw_nullptr,
   kw_operator,
   kw_private,
   kw_protected,
   kw_public,
   kw_register,
   kw_reinterpret_cast,
   kw_return,
   kw_short,
   kw_signed,
   kw_sizeof,
   kw_static,
   kw_static_assert,
   kw_static_cast,
   kw_struct,
   kw_switch,
   kw_template,
   kw_this,
   kw_thread_local,
   kw_throw,
   kw_true,
   kw_try,
   kw_typedef,
   kw_typeid,
   kw_typename,
   kw_union,
   kw_unsigned,
   kw_using,
   kw_virtual,
   kw_void,
   kw_volatile,
   kw_wchar_t,
   kw_while,

   identifier,

   generic_opener,

   generic_closer,

   numeric_literal_int,
   numeric_literal_char,
   numeric_literal_fp,

   string_literal,

   include_literal,

   scope_opener,

   scope_closer,

   paren_opener,

   paren_closer,

   array_opener,

   array_closer,

   op_eq,            // =
   op_eq_eq,         // ==
   op_not,           // !
   op_not_eq,        // !=
   op_plus,          // +
   op_plus_plus,     // ++
   op_plus_eq,       // +=
   op_minus,         // -
   op_minus_minus,   // --
   op_minus_eq,      // -=
   op_star,          // *
   op_star_eq,       // *=
   op_slash,         // /
   op_slash_eq,      // /=
   op_backslash,     // \ 
   op_percent,       // %
   op_percent_eq,    // %=
   op_amp,           // &
   op_amp_amp,       // &&
   op_amp_eq,        // &=
   op_bar,           // |
   op_bar_bar,       // ||
   op_bar_eq,        // |=
   op_caret,         // ^
   op_caret_eq,      // ^=
   op_left,          // <<
   op_left_eq,       // <<=
   op_right,         // >>
   op_right_eq,      // >>=
   op_less,          // <
   op_less_eq,       // <=
   op_greater,       // >
   op_greater_eq,    // >=
   op_dot,           // .
   op_elipsis,       // ...
   op_comma,         // ,
   op_arrow,         // ->
   op_question,      // ?
   op_colon,         // :
   op_scope,         // ::
   op_tilde,         // ~
   op_hash,          // #
   op_hash_hash,     // ##
   
   terminator,

   invalid_character,

   count_
};

///////////////////////////////////////////////////////////////////////////////
const char* get_name(TokenSubtype subtype);

///////////////////////////////////////////////////////////////////////////////
TokenType get_token_type(TokenSubtype subtype);

} // be::bstyle
} // be

#endif
