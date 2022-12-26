/**
 * @file ringbuffer.hpp
 * @brief class defined to control circular buffers and its operators
 * @author Federico Roux (rouxfederico@gmail.com)
 */

#ifndef __RINGBUFFER_HPP
#define __RINGBUFFER_HPP

#include <memory>
#include <mutex>
#include <ringcounter.hpp>

using namespace std;

template <typename T, int L>
class ringbuffer {
 public:
  explicit ringbuffer()
      : _rb(unique_ptr<T[]>(new T[L + 1])), _head(L + 1, L), _tail(L + 1, 0) {}
  ~ringbuffer() {}

  bool is_full(void) const { return (_tail == _head + 2); }

  bool is_empty(void) const { return (_tail == _head + 1); }

  T* begin() const { return &_rb[_tail + 0]; }

  T* end() const { return &_rb[_head + 1]; }

  T* operator++() { return &_rb[++_tail]; }

  int write(T data) {
    lock_guard<mutex> lock(_m);

    if (is_full()) return 1;

    _rb[++_head] = data;
    return 0;
  }

  int read(T& data) {
    lock_guard<mutex> lock(_m);

    if (is_empty()) return 1;

    data = _rb[_tail++];
    return 0;
  }

  uint16_t size(void) const { return L; }

 private:
  unique_ptr<T[]> _rb;
  mutex _m;

  ringcounter _head;
  ringcounter _tail;

  uint16_t _q;

  const uint16_t _len = L + 1;
};

#endif  // __RINGBUFFER_HPP