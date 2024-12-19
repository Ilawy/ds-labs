#include <cstdint>
#include <cstdlib>
#include <cstdio>


extern "C" void* __cxa_allocate_exception(std::size_t thrown_size) {
    std::fprintf(stderr, "[Fake] __cxa_allocate_exception called. Size: %zu\n", thrown_size);
    return std::malloc(thrown_size); // Return a dummy memory allocation
}

extern "C" void __cxa_throw(void* thrown_object, void* tinfo, void (*dest)(void*)) {
    std::fprintf(stderr, "[Fake] __cxa_throw called. Aborting.\n");
    std::abort(); // Forcefully terminate since exceptions are not supported
}

extern "C" void __cxa_free_exception(void* thrown_object) {
    std::fprintf(stderr, "[Fake] __cxa_free_exception called.\n");
    std::free(thrown_object);
}
