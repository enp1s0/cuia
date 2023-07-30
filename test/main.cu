#include <iostream>
#include <cuia/cuia.hpp>

int main() {
	mtk::cuia::interval<float> a(1, 2);
	mtk::cuia::interval<float> b(2, 3);
	mtk::cuia::interval<float> c(6, 7);
	const auto d = a * b + c;

	std::printf(
			"%s * %s + %s -> %s\n",
			a.to_string().c_str(),
			b.to_string().c_str(),
			c.to_string().c_str(),
			d.to_string().c_str()
			);
}
