#include "bstyle_app.hpp"
#include <be/cli/cli.hpp>
#include <be/core/logging.hpp>
#include <be/core/io_service_thread_pool.hpp>
#include <iostream>
#include <thread>

namespace be {
namespace bstyle {

BstyleApp::BstyleApp(int argc, char** argv)
   : interactive_(false),
     strictness_(1),
     n_threads_(std::max(1u, std::thread::hardware_concurrency()))
{
   U16 verbosity = v::info_or_worse;

   try {
      using namespace cli;
      using namespace color;
      using namespace ct;
      Processor proc;

      bool show_help = false;
      S help_query;

      
      proc
         (flag  ({ "i" },{ "interactive" }, "Use interactive resolution.", interactive_))
         
         (param({ "s" },{ "strictness" }, "N", "Set max rule strictness.",
            [](const S& value) {
               BE_IGNORE(value);
               // TODO
            }).extra(Cell() << nl
               << "Valid values are " << fg_cyan << '0' << reset
               << " - " << fg_cyan << '9' << reset << nl
               << "Rules with a higher strictness level than specified will be skipped." << nl))

         (param({ "T" },{ "threads" }, "N", "Set number of worker threads to use.",
            [](const S& value) {
               BE_IGNORE(value);
               // TODO
            }).extra(Cell() << nl
               << "If not provided or set to " << fg_cyan << '0' << reset
               << " or " << fg_cyan << "auto" << reset
               << " one thread per processor will be used. (" << n_threads_ << ")" << nl))
          
         (verbosity_param({ "v" },{ "verbosity" }, "LEVEL", default_log().verbosity_mask()))

         (param({ "?" },{ "help" }, "OPTION",
            [&](const S& value) {
               show_help = true;
               help_query = value;
            }).default_value(S())
              .allow_options_as_values(true)
              .desc(Cell() << "Output this help message.  For more verbose help, use " << fg_yellow << "--help")
              .extra(Cell() << nl << "If " << fg_cyan << "OPTION" << reset
                            << " is provided, the options list will be filtered to show only options that contain that string." << nl))

         (flag({ },{ "help" },
            [&]() {
               proc.verbose(true);
            }).ignore_values(true));

      proc(argc, argv);

      

         /*
      po::options_description hidden;
      hidden.add_options()
         ("input", po::value<std::vector<S>>(), "Specifies a glob-expression identifying files to process.")
         ;

      po::positional_options_description positional;
      positional.add("input", -1);
      */

      if (show_help) {
         proc.describe(std::cout, help_query);
         inputs_.clear();
         return;
      }
      
      n_threads_ = std::max(1ull, n_threads_);

      default_log().verbosity_mask(verbosity);

   } catch (const std::exception& e) {
      inputs_.clear();
      be_error() << "Exception parsing command line!"
         & attr("Message") << S(e.what())
         | default_log();
   }
}

int BstyleApp::operator()() {
   if (inputs_.empty()) {
      return 1;
   }

   IoServiceThreadPool exec;
   exec.threads(n_threads_);

   return 0;
}

} // be::bstyle
} // be
