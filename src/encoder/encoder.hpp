/**
 * @file encoder.hpp
 *
 * @brief encoder abstaction class
 *
 * @author rouxfederico@gmail.com
 */

#ifndef __ENCODER_HPP
#define __ENCODER_HPP

#include <fdm.hpp>
#include <iostream>
#include <linear_cal.hpp>
#include <memory>
#include <ringbuffer.hpp>

using namespace std;

class encoder {
 public:
  encoder() : adc2deg(0, 0, adc_max, pos_max) {}
  ~encoder() {}

  /**
   * @fn log_position
   * @brief log position from adc value(0-4095) in degree values inside the
   * ringbuffer
   *
   */
  int log(uint16_t adc_val) {
    if (adc_val >= adc_max) return 1;

    return (pos.write(adc2deg.cal(adc_val)));
  }

  void show_positions(void) {
    for (auto pos_i : pos) cout << "pos: " << pos_i << "º" << endl;
  }

  void show_velocity(void) {
    for (auto vel_i : *velocity) cout << "vel: " << vel_i << "º/ms" << endl;
  }

  void show_acceleration(void) {
    for (auto acc_i : *acceleration)
      cout << "acc: " << acc_i << "º/ms2" << endl;
  }

  int calc_velocity(void) {
    try {
      velocity = move(fdm::diff(pos, _dt));
    } catch (const std::exception& e) {
      cout << "Error: " << e.what() << endl;
    }
    return 0;
  }

  int calc_acceleration(void) {
    try {
      acceleration = move(fdm::diff(*velocity, _dt));
    } catch (const std::exception& e) {
      cout << "Error: " << e.what() << endl;
    }
    return 0;
  }

 private:
  static constexpr uint16_t adc_max = 4096;
  static constexpr uint16_t pos_max = 360;

  /** @brief sampling period */
  static constexpr uint16_t _dt = 1;
  /** @brief buffer size */
  static constexpr uint16_t _n_samples = 8;

  ringbuffer<uint16_t, _n_samples> pos{};
  linear_cal<uint16_t, uint16_t> adc2deg;

  unique_ptr<vector<float>> velocity;
  unique_ptr<vector<float>> acceleration;
};

#endif  // __ENCODER_HPP
