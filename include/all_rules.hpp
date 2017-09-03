#pragma once
#ifndef BE_BSTYLE_ALL_RULES_HPP_
#define BE_BSTYLE_ALL_RULES_HPP_

#include "rule.hpp"

namespace be {
namespace bstyle {
namespace detail {

Nil init_rule(std::unique_ptr<Rule> rule);

} // be::bstyle::detail

const std::vector<std::unique_ptr<Rule>>& all_rules();

} // be::bstyle
} // be

#endif
