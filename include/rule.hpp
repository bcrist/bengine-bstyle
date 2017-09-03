#pragma once
#ifndef BE_BSTYLE_RULE_HPP_
#define BE_BSTYLE_RULE_HPP_

#include "token.hpp"
#include "document.hpp"
#include <be/core/filesystem.hpp>

namespace be::bstyle {

///////////////////////////////////////////////////////////////////////////////

class Rule {
public:
   virtual ~Rule() = default;

   virtual const S& id() const = 0;
   virtual std::size_t size() const = 0;
   virtual const S& operator[](std::size_t index) const = 0;
   virtual bool applies_to(const Path& path) const = 0;
   virtual bool applies_to(TokenSubtype type) const = 0;
   virtual U8 strictness() const = 0;
   virtual I32 priority() const = 0;
   virtual void operator()(Document&, Token) const = 0;
};

} // be::bstyle

#endif
