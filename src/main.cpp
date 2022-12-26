/**
 *    @file main.cpp
 *    @brief main file
 *    @author rouxfederico@gmail.com
 */

#include <cassert>
#include <encoder.hpp>
#include <iostream>

using namespace std;

/** @brief global instance of encoder */
encoder enc1{};

/**
 *   @fn adc_log
 *   @brief main program
 */

int adc_log(void) {
  enc1.log(3);
  enc1.log(122);
  enc1.log(493);
  enc1.log(1022);
  enc1.log(2033);
  enc1.log(3001);
  enc1.log(3900);
  enc1.log(4095);

  return 0;
}
/**
 *   @fn main
 *   @brief main program
 */

int main() {
  cout << "Hello Fluid-Dev!" << endl;

  adc_log();

  enc1.calc_velocity();
  enc1.calc_acceleration();

  enc1.show_positions();
  enc1.show_velocity();
  enc1.show_acceleration();
  return 0;
}
