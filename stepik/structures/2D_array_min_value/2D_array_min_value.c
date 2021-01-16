#include "2D_array_min_value.h"
#include "../array_structures/2D_array.h"
#include "../../helper_functions/helper_functions.h"

#include <stdlib.h>

//was predefined
void array_int_normalize( struct array_int array, int64_t m ) {
    for (size_t i = 0; i < array.size; i = i + 1) {
        array.data[i] = array.data[i] - m;
    }
}

/*  ---- maybe int[] ---- */

struct maybe_array_int {
    struct array_int value;
    bool valid;
};

//was predefined
struct maybe_array_int some_array_int(struct array_int array) {
    return (struct maybe_array_int) { array, true };
}
const struct maybe_array_int none_array_int = { {NULL, 0}, false };


/*  ---- int[][] ---- */

struct array_array_int {
    struct array_int* data;
    size_t size;
};

/*  --- строки ---  */
//was predefined
struct maybe_array_int array_array_int_get_row( struct array_array_int a, size_t i ) {
    if ( 0 <= i && i < a.size ) { return some_array_int( a.data[i] ); }
    else { return none_array_int; }
}

//was predefined
bool array_array_int_set_row( struct array_array_int a, size_t i, struct array_int value ) {
    if (0 <= i && i < a.size) {
        a.data[i] = value;
        return true;
    }
    else { return false; }
}

/*  --- get/set ---  */

//never used, needed for complete the task
struct maybe_int64 array_array_int_get( struct array_array_int a, size_t i, size_t j ) {
    struct maybe_array_int array = array_array_int_get_row(a, i);
    if (array.valid){
        if (0 <= j && j < array.value.size){
            return array_int_get(array.value, j);
        }
    }
    return (struct maybe_int64){0};
}

//never used, needed for complete the task
bool array_array_int_set( struct array_array_int a, size_t i, size_t j, int64_t value ) {
    if (0 <= i && i < a.size){
        return array_int_set(a.data[i], j, value);
    }
    return false;
}

/*  --- read/print ---  */

struct array_array_int array_array_int_read() {
    size_t size = read_size();
    struct array_int* data = malloc(sizeof(struct array_int) * size);
    struct array_array_int array_array = {.data = data, .size = size};
    for (size_t i = 0; i < size; i++) {
            struct array_int array = array_int_read();
            if(!array_array_int_set_row(array_array, i, array)){
                //what if inserting the row would be unsuccessful?
            }
    }
    return array_array;
}


void array_array_int_print( struct array_array_int array) {
    for (size_t i = 0; i < array.size; i++){
        struct maybe_array_int array_row = array_array_int_get_row(array,i);
        if (array_row.valid){
            array_int_print(array_row.value);
        }
        printf("\n");
    }
}


/*  --- min/normalize ---  */

struct maybe_int64 maybe_int64_min(struct maybe_int64 a, struct maybe_int64 b) {
    if (!a.valid){
        if (!b.valid){
            return (struct maybe_int64) {0};
        } else {
            return b;
        }
    } {
        if (!b.valid){
            return a;
        } else {
            return a.value < b.value ? a : b;
        }
    }
}

// найти минимальный элемент в массиве массивов
struct maybe_int64 array_array_int_min( struct array_array_int array ) {
    struct maybe_int64 min = {0};
    for (size_t i = 0; i < array.size; i++){
        struct maybe_int64 local_min = array_int_min(*(array.data + i));
        min = maybe_int64_min(local_min, min);
    }
    return min;
}

// вычесть из всех элементов массива массивов число m
//was predefined
void array_array_int_normalize( struct array_array_int array, int64_t m) {
    for (size_t i = 0; i < array.size; i = i + 1) {
        const struct maybe_array_int cur_row = array_array_int_get_row( array, i );
        if (cur_row.valid) {
            array_int_normalize( cur_row.value, m );
        }
    }
}

void array_array_int_free( struct array_array_int array ) {
    for (size_t i = 0; i < array.size; i++){
        array_int_free(*(array.data + i));
    }
    free(array.data);
}

void perform() {
    struct array_array_int array = array_array_int_read();
    struct maybe_int64 m = array_array_int_min( array );
    if (m.valid) {
        array_array_int_normalize( array, m.value );
        array_array_int_print( array );
    }
    array_array_int_free( array );
}