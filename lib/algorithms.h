#pragma once

#include <cmath>
#include <functional>
#include <iterator>

namespace algos {
template<typename InputIterator, typename UnaryPredicate>
bool all_of(InputIterator first, InputIterator last, UnaryPredicate predicate) {
  while (first != last) {
    if (!predicate(*first)) return false;
    ++first;
  }
  return true;
}

template<typename InputIterator, typename UnaryPredicate>
bool any_of(InputIterator first, InputIterator last, UnaryPredicate predicate) {
  while (first != last) {
    if (predicate(*first)) return true;
    ++first;
  }
  return false;
}

template<typename InputIterator, typename UnaryPredicate>
bool none_of(InputIterator first, InputIterator last, UnaryPredicate predicate) {
  return !algos::all_of(first, last, predicate);
}

template<typename InputIterator, typename UnaryPredicate>
bool one_of(InputIterator first, InputIterator last, UnaryPredicate predicate) {
  bool f = false;
  while (first != last) {
    if (predicate(*first)) {
      if (f) return false;
      f = true;
    }
    ++first;
  }
  return f;
}

template<typename ForwardIterator>
bool is_sorted(ForwardIterator first, ForwardIterator last) {
  return is_sorted(first, last, std::less<>());
}

template<typename ForwardIterator, typename Compare>
bool is_sorted(ForwardIterator first, ForwardIterator last, Compare comp) {
  if (first == last) return true;
  ForwardIterator next = first;
  while (++next != last) {
    if (comp(*next, *first))
      return false;
    ++first;
  }
  return true;
}

template<typename InputIterator, typename UnaryPredicate>
bool is_partitioned(InputIterator first, InputIterator last, UnaryPredicate predicate) {
  while (first != last && predicate(*first)) {
    ++first;
  }
  while (first != last) {
    if (predicate(*first)) return false;
    ++first;
  }
  return true;
}

template<typename InputIterator, typename T>
InputIterator find_not(InputIterator first, InputIterator last, T el) {
  while (first != last) {
    if (*first != el) return first;
    ++first;
  }
  return last;
}

template<typename BidirectionalIterator, typename T>
BidirectionalIterator find_backward(BidirectionalIterator first, BidirectionalIterator last, T el) { // (first, last]
  while (last != first) {
    if (*last == el) return last;
    --last;
  }
  return first;
}

template<typename RandomAccessIterator, typename Compare>
bool is_palindrome(RandomAccessIterator first, RandomAccessIterator last, Compare comp) { // [first, last]
  while (last > first) {
    if (!comp(*first, *last)) return false;
    ++first;
    --last;
  }
  return true;
}

template<typename T>
class xrange {
 public:
  explicit xrange(T end) : start_(T()), end_(end), step_(1) {}
  xrange(T start, T end, T step = 1) : start_(start), end_(end), step_(step) {}

  class iterator : public std::iterator<std::input_iterator_tag, T> {
   public:
    iterator(T value, T step) : value_(value), step_(step) {}

    T operator*() const {
      return value_;
    }

    iterator& operator++() {
      value_ += step_;
      return *this;
    }

    iterator operator++(int) {
      iterator temp = *this;
      ++(*this);
      return temp;
    }

    bool operator==(const iterator& other) const {
      return std::fabs(value_ - other.value_) < 1e-9;
    }

    bool operator!=(const iterator& other) const {
      return !(*this == other);
    }

   private:
    double value_;
    double step_;
  };

  [[nodiscard]] iterator begin() const {
    return {start_, step_};
  }

  [[nodiscard]] iterator end() const {
    T remainder = std::remainder(end_ - start_, step_);
    if (remainder == 0)
      return {end_, step_};
    return {end_ - remainder + step_, step_};
  }

 private:
  T start_;
  T end_;
  T step_;
};

template <typename T1, typename T2>
class zip {
 public:
  zip(T1& range1, T2& range2)
      : range1(range1), range2(range2) {}

  class iterator {
   public:
    iterator(const typename T1::iterator& it1, const typename T2::iterator& it2)
        : it1_(it1), it2_(it2){}

    bool operator!=(const iterator& other) const {
      return it1_ != other.it1_ && it2_ != other.it2_;
    }

    bool operator==(const iterator& other) const {
      return !(*this != other);
    }

    iterator& operator++() {
      ++it1_;
      ++it2_;
      return *this;
    }

    std::pair<const typename T1::value_type&, const typename T2::value_type&> operator*() const {
      return {*it1_, *it2_};
    }

   private:
    typename T1::iterator it1_;
    typename T2::iterator it2_;
  };

  [[nodiscard]] iterator begin() const {
    return {range1.begin(), range2.begin()};
  }

  [[nodiscard]] iterator end() const {
    return {range1.end(), range2.end()};
  }

 private:
  T1& range1;
  T2& range2;
};

}
