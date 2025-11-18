/* Define generator macro:
   NAME  - base name for generated functions (e.g., fnv1a)
   T     - integer return type (e.g., uint32_t, uint64_t)
   OFFSET - offset basis constant for type T
   PRIME  - prime constant for type T
*/
#define DEF_FNV1A(T, OFFSET, PRIME, NAME)                           \
static inline T NAME##_buf_##T(const void *data, size_t len) {      \
    const unsigned char *bytes = (const unsigned char *)data;      \
    T hash = (T)(OFFSET);                                           \
    const T prime = (T)(PRIME);                                     \
    for (size_t i = 0; i < len; ++i) {                              \
        hash ^= (T)bytes[i];                                        \
        hash *= prime;                                              \
    }                                                                \
    return hash;                                                     \
}                                                                    \
static inline T NAME##_str_##T(const char *s) {                     \
    const unsigned char *p = (const unsigned char *)s;              \
    T hash = (T)(OFFSET);                                           \
    const T prime = (T)(PRIME);                                     \
    while (*p) {                                                     \
        hash ^= (T)(*p++);                                          \
        hash *= prime;                                              \
    }                                                                \
    return hash;                                                     \
}