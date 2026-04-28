#define SCU_SHORT_ALIASES

#include <stdlib.h>
#include "scu/array.h"
#include "scu/assert.h"

void scu_array_sort(
    void* array,
    isize count,
    isize elemSize,
    ScuCompareFunc* cmpFunc
) {
    SCU_ASSERT(count >= 0);
    SCU_ASSERT(elemSize > 0);
    SCU_ASSERT(cmpFunc != nullptr);
    if (count == 0) {
        return;
    }
    SCU_ASSERT(array != nullptr);
    qsort(array, (usize) count, (usize) elemSize, cmpFunc);
}