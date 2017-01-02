#pragma once
#ifndef BE_BSTYLE_RULE_HPP_
#define BE_BSTYLE_RULE_HPP_

#include "token.hpp"
#include "document.hpp"
#include <be/core/filesystem.hpp>
#include <boost/type_erasure/any.hpp>
#include <boost/type_erasure/operators.hpp>
#include <boost/type_erasure/member.hpp>
#include <boost/type_erasure/callable.hpp>
#include <boost/mpl/vector.hpp>

BOOST_TYPE_ERASURE_MEMBER((be)(bstyle)(has_id), id)
BOOST_TYPE_ERASURE_MEMBER((be)(bstyle)(has_size), size)
BOOST_TYPE_ERASURE_MEMBER((be)(bstyle)(has_applies_to), applies_to)
BOOST_TYPE_ERASURE_MEMBER((be)(bstyle)(has_strictness), strictness)
BOOST_TYPE_ERASURE_MEMBER((be)(bstyle)(has_priority), priority)

namespace be {
namespace bstyle {

///////////////////////////////////////////////////////////////////////////////
/// \brief  A type-erasure container for linter rules.
///
/// \details See RuleBase for a more readable definition of the Rule interface.
using Rule = boost::type_erasure::any<boost::mpl::vector<
   boost::type_erasure::copy_constructible<>,
   has_id<const S&(), const boost::type_erasure::_self>,
   has_size<std::size_t(), const boost::type_erasure::_self>,
   boost::type_erasure::subscriptable<const S&, const boost::type_erasure::_self, std::size_t>,
   has_applies_to<bool(const Path&), const boost::type_erasure::_self>,
   has_applies_to<bool(TokenSubtype), const boost::type_erasure::_self>,
   has_strictness<U8(), const boost::type_erasure::_self>,
   has_priority<I32(), const boost::type_erasure::_self>,
   boost::type_erasure::callable<void(Document&, Token), const boost::type_erasure::_self>,
   boost::type_erasure::relaxed>>;

} // be::bstyle
} // be

#endif
