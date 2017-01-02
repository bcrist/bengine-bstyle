#pragma once
#ifndef BE_BSTYLE_APP_HPP_
#define BE_BSTYLE_APP_HPP_

#include "ruleset.hpp"
#include <be/core/lifecycle.hpp>
#include <be/core/filesystem.hpp>
#include <be/core/service_mutex.hpp>

namespace be {
namespace bstyle {

class BstyleApp final {
public:
   BstyleApp(int argc, char** argv);

   int operator()();

private:
   CoreInitLifecycle init_;
   CoreLifecycle core_;

   std::vector<Path> inputs_;
   bool interactive_;
   U8 strictness_;
   std::size_t n_threads_;

};

} // be::bstyle
} // be

#endif
