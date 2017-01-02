#include "cxx_lexer.hpp"

#define BE_BSTYLE_TOKEN_ESTIMATE_RATIO 0.5

%%{
   machine test;
}%%

namespace be {
namespace bstyle {
namespace {
%%{
   machine cxx_lexer;
   variable p p_;
   variable pe pe_;
   variable ts ts_;
   variable te te_;
   write data;
#/*

   odigit =                   [0-7] ;
   bdigit =                   [0-1] ;
   digit_nz =                 [1-9] ;
   digit_sequence =           digit ( '\''? digit )* ;
   xdigit_sequence =          xdigit ( '\''? xdigit )* ;

   whitespace =               [\t\v\f ]+ ;
   newline =                  '\\'? ( '\r' '\n'? | '\n' ) ;

   single_line_comment =      '//' [^\r\n]* ;
   multi_line_comment =       '/*' ( ^'*' | '*'+ [^/*] )* '*'+ '/' ;
   unclosed_comment =         '/*' ( ^'*' | '*'+ [^/*] )* '*'*;

   initial_identifier_char =  alpha | '_' | ^ascii ;
   identifier_char =          initial_identifier_char | digit ;
   identifier =               initial_identifier_char identifier_char* ;

   decimal_literal =          digit_nz ( '\''? digit )* ;
   octal_literal =            '0' ( '\''? odigit )* ;
   hex_literal =              '0x'i ( '\''? xdigit )* ;
   binary_literal =           '0b'i ( '\''? bdigit )* ;
   integer_suffix =           'u'i ( 'l'i | 'll'i )? |
                                    ( 'l'i | 'll'i ) 'u'i? |
                                    '' ;
   integer_literal =          ( decimal_literal | octal_literal | hex_literal
                                    | binary_literal ) integer_suffix? ;

   fp_exponent =              'e'i ( '+' | '-' )? digit_sequence ;
   hex_fp_exponent =          'p'i ( '+' | '-' )? digit_sequence ;

   dec_fp_literal =           digit_sequence fp_exponent |
                                    digit_sequence '.' fp_exponent? |
                                    digit_sequence? '.' digit_sequence fp_exponent? ;

   hex_fp_significand =       xdigit_sequence '.'? | xdigit_sequence? '.' xdigit_sequence;
   hex_fp_literal =           '0x'i hex_fp_significand hex_fp_exponent ;

   fp_literal =               ( dec_fp_literal | hex_fp_literal ) [fl]? ;

   escape_seq =               '\\' ( [abfnrtv?\\'"] | odigit{1,3} | 'x' xdigit+ | 'u' xdigit{4} | 'U' xdigit{8} ) ;
   c_char =                   alnum | [ \t\v\f_{}\[\]#()<>%:;.?*+\-/^&|~!=,\"] | ^ascii | escape_seq ;
   s_char =                   alnum | [ \t\v\f_{}\[\]#()<>%:;.?*+\-/^&|~!=,\'] | ^ascii | escape_seq ;
   char_literal =             ( 'u8' | [uUL] )? '\'' c_char+ '\'' ;
   string_literal =           ( 'u8' | [uULR] )? '"' s_char* '"' ;

   main := |*

      whitespace => { t_(TokenSubtype::whitespace); };

      newline => {
         t_(TokenSubtype::end_of_line);
         ls_ = te_;
         ++line_;
         pp_include_ = false;
         t_(TokenSubtype::start_of_line, line_, 1, input_.subspan(te_ - ps_, 0));
      };

      integer_literal => { t_(TokenSubtype::numeric_literal_int); };
      char_literal => { t_(TokenSubtype::numeric_literal_char); };
      fp_literal => { t_(TokenSubtype::numeric_literal_fp); };
      string_literal => { t_(TokenSubtype::string_literal); };
      
      single_line_comment => { t_(TokenSubtype::comment_single_line); };
      multi_line_comment => { t_(TokenSubtype::comment_multi_line); check_comment_newlines_(); };
      unclosed_comment => { t_(TokenSubtype::comment_unterminated); check_comment_newlines_(); };

      'alignas'          => { t_(TokenSubtype::kw_alignas); };
      'alignof'          => { t_(TokenSubtype::kw_alignof); };
      'auto'             => { t_(TokenSubtype::kw_auto); };
      'bool'             => { t_(TokenSubtype::kw_bool); };
      'break'            => { t_(TokenSubtype::kw_break); };
      'case'             => { t_(TokenSubtype::kw_case); };
      'catch'            => { t_(TokenSubtype::kw_catch); };
      'char'             => { t_(TokenSubtype::kw_char); };
      'char16_t'         => { t_(TokenSubtype::kw_char16_t); };
      'char32_t'         => { t_(TokenSubtype::kw_char32_t); };
      'class'            => { t_(TokenSubtype::kw_class); };
      'const'            => { t_(TokenSubtype::kw_const); };
      'constexpr'        => { t_(TokenSubtype::kw_constexpr); };
      'const_cast'       => { t_(TokenSubtype::kw_const_cast); };
      'continue'         => { t_(TokenSubtype::kw_continue); };
      'decltype'         => { t_(TokenSubtype::kw_decltype); };
      'default'          => { t_(TokenSubtype::kw_default); };
      'delete'           => { t_(TokenSubtype::kw_delete); };
      'do'               => { t_(TokenSubtype::kw_do); };
      'double'           => { t_(TokenSubtype::kw_double); };
      'dynamic_cast'     => { t_(TokenSubtype::kw_dynamic_cast); };
      'else'             => { t_(TokenSubtype::kw_else); };
      'enum'             => { t_(TokenSubtype::kw_enum); };
      'explicit'         => { t_(TokenSubtype::kw_explicit); };
      'export'           => { t_(TokenSubtype::kw_export); };
      'extern'           => { t_(TokenSubtype::kw_extern); };
      'false'            => { t_(TokenSubtype::kw_false); };
      'float'            => { t_(TokenSubtype::kw_float); };
      'for'              => { t_(TokenSubtype::kw_for); };
      'friend'           => { t_(TokenSubtype::kw_friend); };
      'goto'             => { t_(TokenSubtype::kw_goto); };
      'if'               => { t_(TokenSubtype::kw_if); };
      'inline'           => { t_(TokenSubtype::kw_inline); };
      'int'              => { t_(TokenSubtype::kw_int); };
      'long'             => { t_(TokenSubtype::kw_long); };
      'mutable'          => { t_(TokenSubtype::kw_mutable); };
      'namespace'        => { t_(TokenSubtype::kw_namespace); };
      'new'              => { t_(TokenSubtype::kw_new); };
      'noexcept'         => { t_(TokenSubtype::kw_noexcept); };
      'nullptr'          => { t_(TokenSubtype::kw_nullptr); };
      'operator'         => { t_(TokenSubtype::kw_operator); };
      'private'          => { t_(TokenSubtype::kw_private); };
      'protected'        => { t_(TokenSubtype::kw_protected); };
      'public'           => { t_(TokenSubtype::kw_public); };
      'register'         => { t_(TokenSubtype::kw_register); };
      'reinterpret_cast' => { t_(TokenSubtype::kw_reinterpret_cast); };
      'return'           => { t_(TokenSubtype::kw_return); };
      'short'            => { t_(TokenSubtype::kw_short); };
      'signed'           => { t_(TokenSubtype::kw_signed); };
      'sizeof'           => { t_(TokenSubtype::kw_sizeof); };
      'static'           => { t_(TokenSubtype::kw_static); };
      'static_assert'    => { t_(TokenSubtype::kw_static_assert); };
      'static_cast'      => { t_(TokenSubtype::kw_static_cast); };
      'struct'           => { t_(TokenSubtype::kw_struct); };
      'switch'           => { t_(TokenSubtype::kw_switch); };
      'template'         => { t_(TokenSubtype::kw_template); };
      'this'             => { t_(TokenSubtype::kw_this); };
      'thread_local'     => { t_(TokenSubtype::kw_thread_local); };
      'throw'            => { t_(TokenSubtype::kw_throw); };
      'true'             => { t_(TokenSubtype::kw_true); };
      'try'              => { t_(TokenSubtype::kw_try); };
      'typedef'          => { t_(TokenSubtype::kw_typedef); };
      'typeid'           => { t_(TokenSubtype::kw_typeid); };
      'typename'         => { t_(TokenSubtype::kw_typename); };
      'union'            => { t_(TokenSubtype::kw_union); };
      'unsigned'         => { t_(TokenSubtype::kw_unsigned); };
      'using'            => { t_(TokenSubtype::kw_using); };
      'virtual'          => { t_(TokenSubtype::kw_virtual); };
      'void'             => { t_(TokenSubtype::kw_void); };
      'volatile'         => { t_(TokenSubtype::kw_volatile); };
      'wchar_t'          => { t_(TokenSubtype::kw_wchar_t); };
      'while'            => { t_(TokenSubtype::kw_while); };

      '{'   => { t_(TokenSubtype::scope_opener); };
      '}'   => { t_(TokenSubtype::scope_closer); };
      '('   => { t_(TokenSubtype::paren_opener); };
      ')'   => { t_(TokenSubtype::paren_closer); };
      '['   => { t_(TokenSubtype::array_opener); };
      ']'   => { t_(TokenSubtype::array_closer); };
      '='   => { t_(TokenSubtype::op_eq); };
      '=='  => { t_(TokenSubtype::op_eq_eq); };
      '!'   => { t_(TokenSubtype::op_not); };
      '!='  => { t_(TokenSubtype::op_not_eq); };
      '+'   => { t_(TokenSubtype::op_plus); };
      '++'  => { t_(TokenSubtype::op_plus_plus); };
      '+='  => { t_(TokenSubtype::op_plus_eq); };
      '-'   => { t_(TokenSubtype::op_minus); };
      '--'  => { t_(TokenSubtype::op_minus_minus); };
      '-='  => { t_(TokenSubtype::op_minus_eq); };
      '*'   => { t_(TokenSubtype::op_star); };
      '*='  => { t_(TokenSubtype::op_star_eq); };
      '/'   => { t_(TokenSubtype::op_slash); };
      '/='  => { t_(TokenSubtype::op_slash_eq); };
      '\\'  => { t_(TokenSubtype::op_backslash); };
      '%'   => { t_(TokenSubtype::op_percent); };
      '%='  => { t_(TokenSubtype::op_percent_eq); };
      '&'   => { t_(TokenSubtype::op_amp); };
      '&&'  => { t_(TokenSubtype::op_amp_amp); };
      '&='  => { t_(TokenSubtype::op_amp_eq); };
      '|'   => { t_(TokenSubtype::op_bar); };
      '||'  => { t_(TokenSubtype::op_bar_bar); };
      '|='  => { t_(TokenSubtype::op_bar_eq); };
      '^'   => { t_(TokenSubtype::op_caret); };
      '^='  => { t_(TokenSubtype::op_caret_eq); };
      '<<'  => { t_(TokenSubtype::op_left); };
      '<<=' => { t_(TokenSubtype::op_left_eq); };
      '>>'  => { t_(TokenSubtype::op_right); check_generic_closer_(); };
      '>>=' => { t_(TokenSubtype::op_right_eq); };
      '<'   => { t_(TokenSubtype::op_less); check_generic_opener_(); };
      '<='  => { t_(TokenSubtype::op_less_eq); };
      '>'   => { t_(TokenSubtype::op_greater); check_include_literal_(); check_generic_closer_(); };
      '>='  => { t_(TokenSubtype::op_greater_eq); };
      '.'   => { t_(TokenSubtype::op_dot); };
      '...' => { t_(TokenSubtype::op_elipsis); };
      ','   => { t_(TokenSubtype::op_comma); };
      '->'  => { t_(TokenSubtype::op_arrow); };
      '?'   => { t_(TokenSubtype::op_question); };
      ':'   => { t_(TokenSubtype::op_colon); };
      '::'  => { t_(TokenSubtype::op_scope); };
      '~'   => { t_(TokenSubtype::op_tilde); };
      '#'   => { t_(TokenSubtype::op_hash); };
      '##'  => { t_(TokenSubtype::op_hash_hash); };

      ';'   => {
         t_(TokenSubtype::terminator);
         in_attrib_ = false;
         unclosed_generics_ = 0;
      };

      '[[' => {
         t_(TokenSubtype::attribute_opener);
         in_attrib_ = true;
      };

      ']]' => {
         if (in_attrib_) {
            in_attrib_ = false;
            t_(TokenSubtype::attribute_closer);
         } else {
            std::ptrdiff_t offset = ts_ - ps_;
            t_(TokenSubtype::array_closer, line_, (U32)(ts_ - ls_ + 1), input_.subspan(offset, 1));
            t_(TokenSubtype::array_closer, line_, (U32)(ts_ - ls_ + 2), input_.subspan(offset + 1, 1));
         }
      };

      identifier => { t_(TokenSubtype::identifier); check_pp_identifier_(); };

      any => { t_(TokenSubtype::invalid_character); };
   *|;
#*/
}%%
} // be::bstyle::()

///////////////////////////////////////////////////////////////////////////////
CxxLexer::CxxLexer(gsl::string_span<> input)
   : input_(input)
{ }

///////////////////////////////////////////////////////////////////////////////
void CxxLexer::lex_all() {
   tokens_.clear();
   tokens_.reserve(std::max((std::size_t)32, std::min((std::size_t)input_.length(),
      (std::size_t)(input_.length() * BE_BSTYLE_TOKEN_ESTIMATE_RATIO))));

   t_(TokenSubtype::start_of_file, 1, 1, input_.subspan(0, 0));
   t_(TokenSubtype::start_of_line, 1, 1, input_.subspan(0, 0));

   ps_ = p_ = input_.data();
   pe_ = p_ + input_.length();
   char* eof = pe_;
   int cs;
   int act;
   ls_ = p_;
   line_ = 1;
   in_attrib_ = false;
   pp_include_ = false;
   unclosed_generics_ = 0;
   %% write init;
   %% write exec;

   if (cs == cxx_lexer_error) {
      throw std::runtime_error("Lexer error!");
   }

   t_(TokenSubtype::end_of_line, line_, (U32)(eof - ls_ + 1), input_.subspan(input_.length(), 0));
   t_(TokenSubtype::end_of_file, line_, (U32)(eof - ls_ + 1), input_.subspan(input_.length(), 0));
}

///////////////////////////////////////////////////////////////////////////////
const std::vector<TokenData>& CxxLexer::tokens() {
   return tokens_;
}

///////////////////////////////////////////////////////////////////////////////
void CxxLexer::t_(TokenSubtype type) {
   std::ptrdiff_t offset = ts_ - ps_;
   std::ptrdiff_t length = te_ - ts_;
   U32 line = line_;
   U32 column = (U32)(ts_ - ls_ + 1);
   tokens_.push_back({ input_.subspan(offset, length), type, { line, column } });
}

///////////////////////////////////////////////////////////////////////////////
void CxxLexer::t_(TokenSubtype type, U32 line, U32 column, gsl::string_span<> text) {
   tokens_.push_back({ text, type, { line, column } });
}

namespace {

///////////////////////////////////////////////////////////////////////////////
TokenSubtype pp_subtype(gsl::string_span<> id) {
   switch (id[0]) {
      case 'i': // if, ifdef, ifndef, include
         if (id == "include") {
            return TokenSubtype::pp_include;
         } else if (id == "if") {
            return TokenSubtype::pp_if;
         } else if (id == "ifdef") {
            return TokenSubtype::pp_ifdef;
         } else if (id == "ifndef") {
            return TokenSubtype::pp_ifndef;
         }
         break;
      case 'e': // elif, else, endif, error
         if (id == "endif") {
            return TokenSubtype::pp_endif;
         } else if (id == "else") {
            return TokenSubtype::pp_else;
         } else if (id == "elif") {
            return TokenSubtype::pp_elif;
         } else if (id == "error") {
            return TokenSubtype::pp_error;
         }
         break;
      case 'p': // pragma
         if (id == "pragma") {
            return TokenSubtype::pp_pragma;
         }
         break;
      case 'd': // define
         if (id == "define") {
            return TokenSubtype::pp_define;
         }
         break;
      case 'u': // undef
         if (id == "undef") {
            return TokenSubtype::pp_undef;
         }
         break;
      case 'l': // line
         if (id == "line") {
            return TokenSubtype::pp_line;
         }
         break;
      default:
         break;
   }
   return TokenSubtype::pp_unknown;
}

} // be::bstyle::()

  ///////////////////////////////////////////////////////////////////////////////
void CxxLexer::check_pp_identifier_() {
   // we don't check size of tokens_ anywhere here because we know there's
   // a sentinel start_of_file token (and start_of_line token) that we will
   // see before we underrun the vector.

   auto last = tokens_.end() - 1;
   if (last->type != TokenSubtype::identifier) {
      return;
   }

   auto first = last - 1;
   if (first->type == TokenSubtype::whitespace) {
      --first;
   }

   if (first->type != TokenSubtype::op_hash) {
      return;
   }

   if (first->location.column != 1) {
      --first;
      if (first->type != TokenSubtype::whitespace || first->location.column != 1) {
         return;
      }
   }

   char* ts = first->text.data();
   char* te = last->text.data() + last->text.length();
   TokenData new_token { input_.subspan(ts - ps_, te - ts), pp_subtype(last->text), first->location };

   tokens_.erase(first, tokens_.end());
   tokens_.push_back(new_token);
   if (new_token.type == TokenSubtype::pp_include) {
      pp_include_ = true;
   }
}

///////////////////////////////////////////////////////////////////////////////
void CxxLexer::check_comment_newlines_() {
   TokenData& comment = tokens_.back();

   bool prev_was_cr = false;
   int i = 0;
   int ls = -1;

   for (char c : comment.text) {
      ++i;

      if (c == '\n') {
         if (!prev_was_cr) {
            ++line_;
         }
         pp_include_ = false;
         ls = i;
      }

      if (c == '\r') {
         prev_was_cr = true;
         ++line_;
         pp_include_ = false;
         ls = i;
      } else {
         prev_was_cr = false;
      }
   }

   if (ls > 0) {
      ls_ = ts_ + ls;
   }
}

///////////////////////////////////////////////////////////////////////////////
void CxxLexer::check_include_literal_() {
   if (!pp_include_) {
      return;
   }
   pp_include_ = false;

   // we don't check size of tokens_ anywhere here because we know there's
   // a sentinel start_of_file token (and start_of_line token) that we will
   // see before we underrun the vector.

   auto last = tokens_.end() - 1;
   if (last->type != TokenSubtype::op_greater) {
      return;
   }

   auto first = last - 1;
   for (;; --first) {
      switch (first->type) {
         case TokenSubtype::identifier:
         case TokenSubtype::whitespace:
         case TokenSubtype::numeric_literal_fp:
         case TokenSubtype::numeric_literal_int:
         case TokenSubtype::op_backslash:
         case TokenSubtype::op_slash:
         case TokenSubtype::op_dot:
         case TokenSubtype::op_elipsis:
         case TokenSubtype::op_not:
         case TokenSubtype::op_plus:
         case TokenSubtype::op_plus_plus:
         case TokenSubtype::op_minus:
         case TokenSubtype::op_minus_minus:
         case TokenSubtype::op_comma:
         case TokenSubtype::op_tilde:
         case TokenSubtype::op_hash:
         case TokenSubtype::op_hash_hash:
         case TokenSubtype::terminator:
            continue;
         case TokenSubtype::op_less:
            break;
         default:
            if (get_token_type(first->type) == TokenType::keyword) {
               continue;
            } else {
               return;
            }
      }
      break;
   }

   auto before = first - 1;
   if (before->type == TokenSubtype::whitespace) {
      --before;
   }

   if (before->type != TokenSubtype::pp_include) {
      return;
   }

   char* ts = first->text.data();
   char* te = last->text.data() + last->text.length();
   TokenData new_token { input_.subspan(ts - ps_, te - ts), TokenSubtype::include_literal, first->location };

   tokens_.erase(first, tokens_.end());
   tokens_.push_back(new_token);
}

///////////////////////////////////////////////////////////////////////////////
void CxxLexer::check_generic_opener_() {
   // we don't check size of tokens_ anywhere here because we know there's
   // a sentinel start_of_file token (and start_of_line token) that we will
   // see before we underrun the vector.

   auto last = tokens_.end() - 1;
   if (last->type != TokenSubtype::op_less) {
      return;
   }

   auto first = last - 1;
   if (first->type == TokenSubtype::identifier) {
      last->type = TokenSubtype::generic_opener;
      ++unclosed_generics_;
      return;
   }

   if (first->type == TokenSubtype::whitespace) {
      --first;
   }

   if (first->type == TokenSubtype::kw_template) {
      last->type = TokenSubtype::generic_opener;
      ++unclosed_generics_;
   }
}

///////////////////////////////////////////////////////////////////////////////
void CxxLexer::check_generic_closer_() {
   // we don't check size of tokens_ anywhere here because we know there's
   // a sentinel start_of_file token (and start_of_line token) that we will
   // see before we underrun the vector.

   auto last = tokens_.end() - 1;
   if (last->type != TokenSubtype::op_greater && last->type != TokenSubtype::op_right) {
      return;
   }

   // Since (op_right) can get turned into (generic_closer op_greater) and
   // then another op_greater or op_right might get lexed, we should normalize
   // this situation to (op_right) or (op_right op_greater).
   if ((last - 1)->type == TokenSubtype::op_greater) {
      auto first = last - 1;
      char* ts = first->text.data();
      if (last->type == TokenSubtype::op_greater) {
         // combine into op_right.
         TokenData new_token { input_.subspan(ts - ps_, 2), TokenSubtype::op_right, first->location };
         tokens_.erase(first, tokens_.end());
         tokens_.push_back(new_token);
         last = tokens_.end() - 1;
      } else {
         // combine into op_right followed by op_greater
         TokenData new_right   { input_.subspan(ts - ps_, 2), TokenSubtype::op_right, first->location };
         TokenData new_greater { input_.subspan(ts - ps_ + 2, 1), TokenSubtype::op_greater, { last->location.line, last->location.column + 2 } };
         tokens_.erase(first, tokens_.end());
         tokens_.push_back(new_right);
         tokens_.push_back(new_greater);
         last = tokens_.end() - 2;
      }
   }

   if (unclosed_generics_ == 0) {
      return;
   }

   if (last->type == TokenSubtype::op_greater) {
      last->type = TokenSubtype::generic_closer;
      --unclosed_generics_;
   } else { // last->type == TokenSubtype::op_right
      char* ts = last->text.data();
      TokenData new_1 { input_.subspan(ts - ps_, 1), TokenSubtype::generic_closer, last->location };
      TokenData new_2 { input_.subspan(ts - ps_ + 1, 1), TokenSubtype::op_greater,
      { last->location.line, last->location.column + 1 } };

      --unclosed_generics_;
      if (unclosed_generics_ > 0) {
         new_2.type = TokenSubtype::generic_closer;
         --unclosed_generics_;
      }

      last = tokens_.erase(last);
      last = tokens_.insert(last, new_2);
      last = tokens_.insert(last, new_1);
   }

   // recurse; there could still be another op_greater lurking
   check_generic_closer_();
}

} // be::bstyle
} // be
