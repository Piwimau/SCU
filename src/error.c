#include <inttypes.h>
#include <stdarg.h>
#include <stdlib.h>
#include "scu/assert.h"
#include "scu/error.h"
#include "scu/io.h"

[[noreturn]]
void scu_fatal(
    const char* restrict file,
    int64_t line,
    const char* restrict func,
    const char* restrict fmt,
    ...
) {
    SCU_ASSERT(file != nullptr);
    SCU_ASSERT(line >= 0);
    SCU_ASSERT(func != nullptr);
    SCU_ASSERT(fmt != nullptr);
    scu_fprintf(
        SCU_STDERR,
        nullptr,
        "SCU: Fatal error occurred at %s:%" PRIi64 " in %s().\n",
        file,
        line,
        func
    );
    scu_fprintf(SCU_STDERR, nullptr, "Message: ");
    va_list args;
    va_start(args, fmt);
    scu_vfprintf(SCU_STDERR, nullptr, fmt, args);
    va_end(args);
    scu_fflush(SCU_STDERR);
    abort();
}