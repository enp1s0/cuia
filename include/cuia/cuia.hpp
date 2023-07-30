#pragma once
#include <string>
#include <sstream>
#include <iomanip>
#ifdef __CUDA_ARCH__
#define CUIA_DEVICE_HOST __device__ __host__
#else
#define CUIA_DEVICE_HOST
#endif

namespace mtk {
namespace cuia {
template <class T>
struct interval {
	T x, y;

	CUIA_DEVICE_HOST interval(const T t) : x(t), y(t) {}
	CUIA_DEVICE_HOST interval(const T x, const T y) : x(x), y(y) {}

	CUIA_DEVICE_HOST interval<T> operator+(const interval<T>& a) const {
		return interval<T>{x + a.x, y + a.y};
	}

	CUIA_DEVICE_HOST interval<T> operator-(const interval<T>& a) const {
		return interval<T>{x - a.x, y - a.y};
	}

	CUIA_DEVICE_HOST interval<T> operator*(const interval<T>& a) const {
		const auto c00 = x * y;
		const auto c01 = x * a.y;
		const auto c10 = a.x * y;
		const auto c11 = a.x * a.y;
		return interval<T>{min(c00, min(c01, min(c10, c11))), max(c00, max(c01, max(c10, c11)))};
	}

	CUIA_DEVICE_HOST interval<T> operator/(const interval<T>& a) const {
		const auto b = interval<T>{1 / a.x, 1 / a.y};
		return *this * b;
	}

	CUIA_DEVICE_HOST bool operator<(const interval<T>& a) const {
		return (x + y) < (a.x + a.y);
	}

	CUIA_DEVICE_HOST bool operator>(const interval<T>& a) const {
		return (x + y) > (a.x + a.y);
	}

	CUIA_DEVICE_HOST bool operator<<(const interval<T>& a) const {
		return y < a.x;
	}

	CUIA_DEVICE_HOST bool operator>>(const interval<T>& a) const {
		return x > a.y;
	}

	CUIA_DEVICE_HOST T mean() {
		return (x + y) / 2;
	}

	inline std::string to_string() const {
		std::stringstream ss;
		ss << "(" << std::scientific << static_cast<float>(x) << ", " << static_cast<float>(y) << ")";
		return ss.str();
	}
};
} // namespace cuia
} // namespace mtk
