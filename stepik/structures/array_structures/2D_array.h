#ifndef LEARNING_C_2D_ARRAY_H
#define LEARNING_C_2D_ARRAY_H

#include <inttypes.h>

struct maybe_int64 {
    int64_t value;
    bool valid;
};

struct array_int {
    int64_t* data;
    size_t size;
};

void array_int_print( struct array_int array );
struct maybe_int64 array_int_min( struct array_int array );
struct array_int array_int_read();
void array_int_free( struct array_int a );
struct maybe_int64 array_int_get( struct array_int a, size_t i );
bool array_int_set( struct array_int a, size_t i, int64_t value );


#endif //LEARNING_C_2D_ARRAY_H
