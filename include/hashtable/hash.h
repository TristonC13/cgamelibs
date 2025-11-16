#ifndef HASH_H
#define HASH_H

/**
 * @file hash.h
 * @brief Generic hash‑function generators.
 *
 * The macros below create hash functions for different key layouts.
 * The caller supplies the **return type** and the **function name** (and,
 * where needed, the key type).  All generated functions use a simple
 * “shift‑add” algorithm: `hash = (hash << 5) + byte`.
 */

/**
 * @def DEF_HASH_FN_SIZED(RET_TYPE, FN_NAME)
 * @brief Generate a hash function for a key of arbitrary size.
 *
 * @param RET_TYPE   Return type of the hash (e.g. `unsigned int`).
 * @param FN_NAME    Identifier that becomes the function name.
 *
 * The produced prototype is:
 * @code
 * RET_TYPE FN_NAME(void *p_key, size_t len);
 * @endcode
 *
 * @note The macro does **not** perform any alignment checks; the caller must
 * ensure that `p_key` points to at least `len` bytes.
 */
#define DEF_HASH_FN_SIZED(RET_TYPE, FN_NAME)                                                                           \
	RET_TYPE FN_NAME(void *p_key, size_t len) {                                                                        \
		RET_TYPE hash = 0;                                                                                             \
		for (unsigned i = 0; i < len; ++i) {                                                                           \
			unsigned char byte = ((unsigned char *) p_key)[i];                                                         \
			hash = (hash << 5) + byte;                                                                                 \
		}                                                                                                              \
		return hash;                                                                                                   \
	}

/**
 * @def DEF_HASH_FN_HEAP(RET_TYPE, KEY_TYPE, FN_NAME)
 * @brief Generate a hash function for a heap‑allocated key.
 *
 * @param RET_TYPE   Return type of the hash.
 * @param KEY_TYPE   Type of the key (used only for `sizeof`).
 * @param FN_NAME    Desired function name.
 *
 * Prototype:
 * @code
 * RET_TYPE FN_NAME(void *p_key);
 * @endcode
 *
 * The macro assumes the key occupies `sizeof(KEY_TYPE)` bytes.
 */
#define DEF_HASH_FN_HEAP(RET_TYPE, KEY_TYPE, FN_NAME)                                                                  \
	RET_TYPE FN_NAME(void *p_key) {                                                                                    \
		RET_TYPE hash = 0;                                                                                             \
		for (unsigned i = 0; i < sizeof(KEY_TYPE); ++i) {                                                              \
			unsigned char byte = ((unsigned char *) p_key)[i];                                                         \
			hash = (hash << 5) + byte;                                                                                 \
		}                                                                                                              \
		return hash;                                                                                                   \
	}

/**
 * @def DEF_HASH_FN_STACK(RET_TYPE, KEY_TYPE, FN_NAME)
 * @brief Generate a hash function for a stack‑allocated key passed by value.
 *
 * @param RET_TYPE   Return type of the hash.
 * @param KEY_TYPE   Type of the key.
 * @param FN_NAME    Desired function name.
 *
 * Prototype:
 * @code
 * RET_TYPE FN_NAME(KEY_TYPE key);
 * @endcode
 */
#define DEF_HASH_FN_STACK(RET_TYPE, KEY_TYPE, FN_NAME)                                                                 \
	RET_TYPE FN_NAME(KEY_TYPE key) {                                                                                   \
		KEY_TYPE *p_key = &key;                                                                                        \
		RET_TYPE  hash = 0;                                                                                            \
		for (unsigned i = 0; i < sizeof(KEY_TYPE); ++i) {                                                              \
			unsigned char byte = ((unsigned char *) p_key)[i];                                                         \
			hash = (hash << 5) + byte;                                                                                 \
		}                                                                                                              \
		return hash;                                                                                                   \
	}

/**
 * @def DEF_HASH_FN_NULLTERM(RET_TYPE, FN_NAME)
 * @brief Generate a hash function for a null‑terminated string.
 *
 * @param RET_TYPE   Return type of the hash.
 * @param FN_NAME    Desired function name.
 *
 * Prototype:
 * @code
 * RET_TYPE FN_NAME(const char *key);
 * @endcode
 */
#define DEF_HASH_FN_NULLTERM(RET_TYPE, FN_NAME)                                                                        \
	RET_TYPE FN_NAME(const char *key) {                                                                                \
		RET_TYPE hash = 0;                                                                                             \
		while (*key) {                                                                                                 \
			hash = (hash << 5) + *key++;                                                                               \
		}                                                                                                              \
		return hash;                                                                                                   \
	}

#endif /* HASH_H */
