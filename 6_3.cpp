/*
6_3. Реализуйте стратегию выбора опорного элемента “случайный элемент”. Функцию Partition реализуйте методом прохода двумя итераторами от начала массива к концу.

Даны неотрицательные целые числа n,k и массив целых чисел из [0..10^9] размера n. Требуется найти k-ю порядковую статистику. т.е. напечатать число, 
которое бы стояло на позиции с индексом k (0..n-1) в отсортированном массиве. 

Требования: к дополнительной памяти: O(n). Среднее время работы: O(n). Должна быть отдельно выделенная функция partition. Рекурсия запрещена. 
Решение должно поддерживать передачу функции сравнения снаружи.
*/

#include <iostream>

template<typename T>
void swap(T& a, T& b){
    T temp = a;
    a = b;
    b = temp;
};

template<typename T>
bool first_is_greater(const T& a, const T& b){
    if (a > b) {
        return true;
    } else {
        return false;
    }
}

template<typename T>
void print_arr(T* arr, int start, int end){
    std::cout << "print: ";
    for(int i = start; i < end; i++){
        std::cout << arr[i] << " ";
    }
    std::cout << std::endl;
};

template<typename T>
int partition(T* arr, int start, int end, bool (*compare)(const T&, const T&)){
    // выбор опорного элемента
    int pivot_pos = start + rand() % (end - start);
    swap(arr[pivot_pos], arr[end-1]);
    T pivot = arr[end-1];
    // разделение массива на две части
    int i = start;
    int j = start;
    while (j != end-1){
        if(compare(arr[j], pivot)){
            ++j;
        } else {
            swap(arr[i], arr[j]);
            ++i;
            ++j;
        }
    }
    swap(arr[end-1], arr[i]);

    return i;
};

void search_of_k_statistic(long*array, const int k, const long n){
    bool (*compare)(const long&, const long&) = first_is_greater;
    int pos_start = 0;
    int pos_end = n;
    int pos_of_part;
    do {
        pos_of_part = partition(array, pos_start, pos_end, compare);
        if ( compare(pos_of_part , k) ){
            pos_end = pos_of_part;
        } else {
            pos_start = pos_of_part;
        }
    } while((pos_of_part != k)&&((pos_end - pos_start) > 2));
};

int main(){
    // ввод
    long n;
    int k;
    std::cin >> n >> k;
    long * array = new long[n];
    for(long i = 0; i < n; i++){
        std::cin >> array[i];
    }

    search_of_k_statistic(array, k, n);
    
    std::cout << array[k] << std::endl;
    delete[] array;
    return 0;
}