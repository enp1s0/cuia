# CUDA Interval Arithmetic

## Example
```cpp
#include <cuia/cuia.hpp>

mtk::cuia::interval<float> a(1, 2);
mtk::cuia::interval<float> b(2, 3);
mtk::cuia::interval<float> c(6, 7);
const auto d = a * b + c;
```

## License
MIT
