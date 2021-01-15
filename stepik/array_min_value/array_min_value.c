#include <stdio.h>
#include <inttypes.h>
#include <stdlib.h>

// Заполняет выделенный массив значениями, считанными со входа
void array_int_fill( int64_t* array, size_t size ) {
    for (size_t i = 0; i < size; i++){
        scanf("%" SCNd64, array + i);
    }
}

// Считывает размер и записывает в *size;
// Выделяет память под массив
// Заполняет массив значениями, считанными со входа
// возвращает его
int64_t* array_int_read( size_t* size ) {
    scanf("%zu", size);
    int64_t* array = malloc(sizeof(int64_t) * *size);
    array_int_fill(array, *size);
    return array;
}

// Печатает массив; пробел после каждого элемента
void array_int_print(int64_t const* array, size_t size) {
    for( size_t i = 0; i < size; i = i + 1) {
        printf( "%" PRId64 " ", array[i] );
    }
}

// Возвращает указатель на минимальный элемент; NULL если его нет
int64_t* array_int_min( int64_t* array, size_t size ) {
    if (size == 0){
        return NULL;
    }

    int64_t* min = array;
    for (size_t i = 1; i < size; i++){
        if (*(array + i) < *min){
            min = array + i;
        }
    }
    return min;
}

// Считывает массив, если минимальный элемент существует то печатает минимальный элемент
void perform() {
    size_t size;
    int64_t* array = array_int_read(&size);
    int64_t*  min = array_int_min(array, size);
    if (min != NULL){
        printf("%" PRId64, *min);
    }
    free(array);
}
