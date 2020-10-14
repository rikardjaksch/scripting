#pragma once

#include <stdint.h>
#include <malloc.h>
#include <assert.h>

typedef struct array_header_t {
    uint32_t size;
    uint32_t capacity;
} array_header_t;

#define array_header(a) ((array_header_t *)((uint8_t *)(a) - sizeof(array_header_t)))
#define array_size(a) ((a) ? array_header(a)->size : 0)
#define array_capacity(a) ((a) ? array_header(a)->capacity : 0)

#define array_needs_to_grow(a, n) ((n) > array_capacity(a))
#define array_grow(a, n) ((a) = array_grow_internal(a, n, sizeof(*(a))))
#define array_ensure(a, n) (array_needs_to_grow(a, n) ? array_grow(a, n) : 0)

#define array_push(a, item) (array_ensure(a, array_size(a) + 1), (a)[array_header(a)->size++] = (item), (a) + array_header(a)->size - 1)
#define array_pop(a) ((a)[--array_header(a)->size])

#define array_free(a) (free(a))

static inline void* array_set_capacity_internal(void* arr, uint32_t new_capacity, uint32_t item_size) {
    uint8_t* p = arr ? (uint8_t*)array_header(arr) : 0;
    uint32_t extra = sizeof(array_header_t);
    uint32_t size = array_size(arr);
    const size_t num_bytes = new_capacity ? (size_t)item_size * new_capacity + extra : 0;
    p = (uint8_t*)realloc(p, num_bytes);
    
    void* new_a = p ? p + extra : p;
    if (new_a) {
        array_header(new_a)->size = size;
        array_header(new_a)->capacity = new_capacity;
    }
    else {
        free(arr);
    }
    return new_a;
}

static inline void* array_grow_internal(void* arr, uint32_t to_at_least, uint32_t item_size) {
    const uint32_t capacity = arr ? array_capacity(arr) : 0;
    uint32_t new_capacity = capacity ? capacity * 2 : 2;
    while (new_capacity < to_at_least)
        new_capacity *= 2;
    return array_set_capacity_internal(arr, new_capacity, item_size);
}