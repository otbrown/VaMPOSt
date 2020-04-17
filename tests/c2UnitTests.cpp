#define CATCH_CONFIG_MAIN
#include <catch2/catch.hpp>
#include "datatypes.h"
#include "dmpo.h"

using namespace vampost;

TEST_CASE("DMPO", "[unit]")
{
  REQUIRE_NOTHROW(DMPO(3, 2, 10));
}