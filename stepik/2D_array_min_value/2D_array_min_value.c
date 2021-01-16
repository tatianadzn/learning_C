#include <inttypes.h>
#include <stdio.h>
#include <stdlib.h>
#include "../array_min_value/array_min_value.h"
#include "../helper_functions/helper_functions.h"



// Считывает массив массивов со входа и возвращает его
// sizes аллоцируется и заполняется длинами строк
// в rows записывается количество строк
int64_t** marray_read( size_t* rows, size_t** sizes ) {
    size_t size = read_size();
    size_t* sizes_arr = malloc(size * sizeof(size_t));
    *sizes = sizes_arr;
    *rows = size;


    int64_t** marray = malloc(size * sizeof(int64_t));
    for (size_t i = 0; i < size; i++){
        *(marray + i) = array_int64_read(sizes_arr + i);
    }
    return marray;
}

// освобождает память, аллоцированную под массив массивов
void marray_free( int64_t** marray, size_t rows ) {
    for (size_t i = 0; i < rows; i++){
        free(*(marray+i));
    }
    free(marray);
}

// выводит массив массивов на экран
void marray_print(int64_t** marray, size_t const* sizes, size_t rows) {
    for (size_t i = 0; i < rows; i++){
        for (size_t j = 0; j < *(sizes + i); j++){
            printf("%" PRId64 " ", *(*(marray + i) + j));
        }
        printf("\n");
    }
}

// вспомогательная функция для нахождения минимума двух чисел
// принимает указатели на два числа (возможно, NULL)
// возвращает указатель на меньшее из них или NULL если оба NULL
int64_t* int64_ptr_min(int64_t* x, int64_t* y) {
    if (x == NULL) return y;
    if (y == NULL) return x;

    if (*x < *y) return x;
    return y;
}

// возвращает указатель на минимальное число в массиве массивов
int64_t* marray_int_min( int64_t** marray, size_t const* sizes, size_t rows ) {
    int64_t* min = &marray[0][0];
    for (size_t i = 0; i < rows; i++){
        int64_t* local_min = array_int64_min(*(marray + i), *(sizes + i));

        if (int64_ptr_min(local_min, min) == local_min){
            min = local_min;
        }
    }

    return min;
}

// вычитает m изо всех чисел в массиве массивов.
// реализация функции дана платформой
void marray_normalize( int64_t** marray, size_t sizes[], size_t rows, int64_t m ) {
    for( size_t i = 0; i < rows; i = i + 1) {
        for( size_t j = 0; j < sizes[i]; j = j + 1) {
            marray[i][j] = marray[i][j] - m;
        }
    }
}

// считывает массив массивов, вычитает изо всех элементов минимальный.
// выводит результат и освобождает память
// реализация функцияи дана платформой
void perform_2D() {
    size_t rows;
    size_t* sizes;
    int64_t** marray = marray_read(&rows, &sizes);
    int64_t* min = marray_int_min(marray, sizes, rows);
    if (min) {

        marray_normalize( marray, sizes, rows, *min );
        marray_print( marray, sizes, rows );
    }
    marray_free( marray, rows );
    free( sizes );
}