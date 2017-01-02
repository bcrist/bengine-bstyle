#pragma once
#ifndef BE_BSTYLE_TOKEN_DATA_HPP_
#define BE_BSTYLE_TOKEN_DATA_HPP_

#include "token_type.hpp"
#include <be/core/be.hpp>
#include <gsl/string_span>

namespace be {
namespace bstyle {

///////////////////////////////////////////////////////////////////////////////
struct TokenLocation {
   U32 line;
   U32 column;
};

///////////////////////////////////////////////////////////////////////////////
struct TokenData {
   gsl::string_span<> text;
   TokenSubtype type;
   TokenLocation location;
};

} // be::bstyle
} // be

#endif
