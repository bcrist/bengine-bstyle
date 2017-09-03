#include "all_rules.hpp"

namespace be {
namespace bstyle {
namespace {

std::vector<std::unique_ptr<Rule>>& mutable_all_rules() {
   static std::vector<std::unique_ptr<Rule>> rules;
   return rules;
}

} // be::bstyle::()
namespace detail {

Nil init_rule(std::unique_ptr<Rule> rule) {
   mutable_all_rules().push_back(std::move(rule));
   return Nil();
}

} // be::bstyle::detail

const std::vector<std::unique_ptr<Rule>>& all_rules() {
   return mutable_all_rules();
}

} // be::bstyle
} // be
