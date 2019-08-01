#ifndef CPP_MT_SRC_UTILS_H_
#define CPP_MT_SRC_UTILS_H_
#include <iterator>
#include <random>
namespace randpicker {
template <typename I>
I random_element(I begin, I end)
{
    const unsigned long n = std::distance(begin, end);
    const unsigned long divisor = (RAND_MAX + 1) / n;

    unsigned long k;
    do { k = std::rand() / divisor; } while (k >= n);

    std::advance(begin, k);
    return begin;
}
}  // namespace randpicker
#endif  // CPP_MT_SRC_UTILS_H_
