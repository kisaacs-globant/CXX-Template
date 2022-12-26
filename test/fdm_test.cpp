#include <catch2/catch_test_macros.hpp>
#include <fdm.hpp>
#include <ringbuffer.hpp>

#define DATA_TEST 22
#define LEN_TEST 5
#define DT 2

TEST_CASE("diff method - 1st order", "[fdm]") {
  ringbuffer<int, LEN_TEST> rb{};

  for (auto i = 0; i < LEN_TEST; i++) {
    INFO("i: " << i);
    REQUIRE(rb.write(DATA_TEST + i) == 0);
  }

  auto drb = fdm::diff(rb, DT);

  for (auto drbi : *drb) REQUIRE(drbi == (1 / static_cast<float>(DT)));

  auto ddrb = fdm::diff(*drb, DT);

  for (auto ddrbi : *ddrb) REQUIRE(ddrbi == 0);
}

TEST_CASE("diff method - 2nd order", "[fdm]") {
  ringbuffer<int, LEN_TEST> rb{};

  for (auto i = 0; i < LEN_TEST; i++) {
    INFO("i: " << i);
    REQUIRE(rb.write(DATA_TEST + i * i) == 0);
  }

  auto drb = fdm::diff(rb, DT);

  auto ddrb = fdm::diff(*drb, DT);

  for (auto ddrbi : *ddrb) REQUIRE(ddrbi == (1 / static_cast<float>(DT)));
}
