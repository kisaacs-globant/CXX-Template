#include <catch2/catch_test_macros.hpp>
#include <ringcounter.hpp>

TEST_CASE("rc constructor", "[ring counter]") {
  ringcounter rc(5);

  REQUIRE(rc.len() == 5);

  rc = 3;
  REQUIRE(rc == 3);
  // testing the limits:
  REQUIRE((rc++) == 3);
  REQUIRE((rc++) == 4);
  REQUIRE((rc++) == 0);
  REQUIRE((rc--) == 1);
  REQUIRE((rc--) == 0);
  REQUIRE((rc++) == 4);
  REQUIRE((rc--) == 0);
  REQUIRE((rc + 1) == 0);
  REQUIRE((++rc) == 0);

  // testing comparator
  ringcounter rc2{5};
  rc = 2;
  rc2 = 2;
  REQUIRE(rc == rc2);
}
