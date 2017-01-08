#include "bstyle_app.hpp"
#include <be/core/services.hpp>
#include <be/core/service_io_service_thread_pool.hpp>
#include <be/core/ids.hpp>

///////////////////////////////////////////////////////////////////////////////
int main(int argc, char** argv) {
   be::bstyle::BstyleApp app(argc, argv);
   auto result = app();
   return result;
}
