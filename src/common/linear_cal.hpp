/**
 * @file linear_cal.hpp
 *
 * @brief calibration abstaction class
 *
 * @author rouxfederico@gmail.com
 */

#ifndef __LINEAR_CAL_HPP
#define __LINEAR_CAL_HPP

template <class T1, class T2>
class linear_cal {
 public:
  linear_cal(T1 x0, T2 y0, T1 x1, T2 y1) : _x0(x0), _x1(x1), _y0(y0), _y1(y1) {
    if (_y1 == _y0) throw std::invalid_argument("y1 must be != y0");
    if (_y1 == _y0) throw std::invalid_argument("x1 must be != x0");

    _m = static_cast<float>(_y1 - _y0) / static_cast<float>(_x1 - _x0);
    _b = _y0 - (_m * static_cast<float>(_x0));
  }
  ~linear_cal() {}

  float cal(T1 x) { return (_m * x + _b); }

  //   float cal(float x) { return (_m * x + _b); }

 private:
  /** @brief calibration values */
  T1 _x0, _x1;
  T2 _y0, _y1;
  /** @brief slope and offset */
  float _m, _b;
};

#endif  //__LINEAR_CAL_HPP