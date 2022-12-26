/**
 * @file ringcounter.hpp
 * @brief class defined to control circular counter and its operators
 * @author Federico Roux (rouxfederico@gmail.com)
 */

#ifndef __RINGCOUNTER_HPP
#define __RINGCOUNTER_HPP

class ringcounter {
 public:
  explicit ringcounter(uint16_t l, uint16_t c = 0) : _c(c), _len(l) {}
  ~ringcounter() {}

  uint16_t len(void) const { return _len; }

  uint16_t operator++() {
    inc();
    return get();
  }

  uint16_t operator++(int) {
    auto tmp = get();
    inc();
    return tmp;
  }

  uint16_t operator--() {
    dec();
    return get();
  }

  uint16_t operator--(int) {
    auto tmp = get();
    dec();
    return tmp;
  }

  void operator=(int x) { set(x); }

  uint16_t get(void) const { return _c; }

  uint16_t operator+(const uint16_t x) const { return (get() + x) % _len; }

  bool operator==(const uint16_t& x) const { return is_equal(x); }
  bool operator==(const ringcounter& x) const {
    return (is_equal(x.get()) && (len() == x.len()));
  }

 private:
  void set(const uint16_t c) {
    if (_len == 0) return;
    _c = c % _len;
  }

  void inc(void) {
    if (_len == 0) return;
    _c = (_c + 1) % _len;
  }
  void dec(void) { (_c == 0) ? (_c = _len - 1) : _c--; }

  bool is_equal(const uint16_t& x) const { return (get() == x); }
  uint16_t _c;
  const uint16_t _len;
};

#endif  // __RINGCOUNTER_HPP