#ifndef LEARNING_C_2D_ARRAY_MIN_VALUE_H
#define LEARNING_C_2D_ARRAY_MIN_VALUE_H

#include <inttypes.h>

int64_t* int64_ptr_min(int64_t* x, int64_t* y);

int64_t** marray_read( size_t* rows, size_t** sizes );
void marray_print(int64_t** marray, size_t* sizes, size_t rows);
void marray_free( int64_t** marray, size_t rows );

void perform_2D();

#endif //LEARNING_C_2D_ARRAY_MIN_VALUE_H
