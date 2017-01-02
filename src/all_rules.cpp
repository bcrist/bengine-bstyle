#include "all_rules.hpp"

namespace be {
namespace bstyle {
namespace {

std::vector<Rule>& mutable_all_rules() {
   static std::vector<Rule> rules;
   return rules;
}

} // be::bstyle::()
namespace detail {

Nil init_rule(Rule rule) {
   mutable_all_rules().push_back(std::move(rule));
   return Nil();
}

} // be::bstyle::detail

const std::vector<Rule>& all_rules() {
   return mutable_all_rules();
}

} // be::bstyle
} // be
