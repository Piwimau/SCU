#include <stdlib.h>
#include "scu/array.h"
#include "scu/assert.h"

void scu_array_sort(
    void* array,
    int64_t count,
    int64_t elemSize,
    SCUCompareFunc* cmpFunc
) {
    SCU_ASSERT(count >= 0);
    SCU_ASSERT(elemSize > 0);
    SCU_ASSERT(cmpFunc != nullptr);
    if (count == 0) {
        return;
    }
    SCU_ASSERT(array != nullptr);
    qsort(array, (size_t) count, (size_t) elemSize, cmpFunc);
}