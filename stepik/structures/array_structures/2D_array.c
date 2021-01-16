#include <stdio.h>
#include <inttypes.h>
#include <stdlib.h>
#include <stdbool.h>


#include "2D_array.h"
#include "../../2D_array_min_value/2D_array_min_value.h"
#include "../../array_min_value/array_min_value.h"
#include "../../helper_functions/helper_functions.h"


struct array_int array_int_read() {
    const size_t size = read_size();
    if (size > 0) {
        int64_t* array = malloc( sizeof(int64_t) * size);
        array_int_fill( array, size );
        return (struct array_int) { .data = array, .size = size };
    }
    else return (struct array_int) {0};
}

// возвращает ошибку если индекс за пределами массива
struct maybe_int64 array_int_get( struct array_int a, size_t i ) {
    if (i < a.size){
        return (struct maybe_int64){*(a.data + i), true};
    }
    return (struct maybe_int64){0};
}

// возвращает false если индекс за пределами массива
bool array_int_set( struct array_int a, size_t i, int64_t value ) {
    if (i < a.size){
        *(a.data + i) = value;
        return true;
    }
    return false;
}

void array_int_print( struct array_int array ) {
    for (size_t i = 0; i < array.size; i = i + 1) {
        printf("%" PRId64 " " , array_int_get( array, i).value);
    }
}

struct maybe_int64 array_int_min( struct array_int array ) {
    size_t size = array.size;
    if (size > 0){
        int64_t* ptr_min = array.data;
        for (size_t i = 0; i < size; i++){
            if (int64_ptr_min(ptr_min, array.data + i) != ptr_min){
                ptr_min = array.data + i;
            }
        }
        return (struct maybe_int64) {*ptr_min, true};
    } else {
        return (struct maybe_int64){0};
    }

}

void array_int_free( struct array_int a ) {
    if ( a.size > 0 ) {
        free(a.data);
        a.size = 0;
    }
}