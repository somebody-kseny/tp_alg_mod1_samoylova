/*
2_2. Дан массив целых чисел А[0..n-1]. Известно, что на интервале [0, m] значения массива строго возрастают, а на интервале [m, n-1] строго убывают. Найти m за O(log m). 
Требования:  Время работы O(log m). Внимание! В этой задаче сначала нужно определить диапазон для бинарного поиска размером порядка m с помощью экспоненциального поиска, а потом уже в нем делать бинарный поиск.
*/

#include <iostream>
#include <math.h>

template <class T>
class MyVec {
public:
    size_t size;
    bool push_back(T&);
    T& operator[](int);
    MyVec(){
        size = 0;
        capacity = 10;
        buf = new T[capacity];
    }
private:
    size_t capacity;
    T* buf;
    bool increase_buf();
};

template<class T>
bool MyVec<T>::push_back(T &new_item) {
    if (size == capacity){
        increase_buf();
    }
    buf[size] = new_item;
    ++size;
    return true;
}

template<class T>
bool MyVec<T>::increase_buf() {
    T* vec = new T[capacity*2];
    for (int i = 0; i < size; i++){
        vec[i] = buf[i];
    }
    buf = vec;
    capacity *= 2;
    return true;
}

template<class T>
T& MyVec<T>::operator[](int index){
    return buf[index];
}

MyVec<int> input(){
    MyVec<int> vs;
    int len;
    std::cin >> len;
    int num;
    for(int i = 0; i < len; i++){
        std::cin >> num;
        vs.push_back(num);
    }
    return vs;
}

int search(MyVec<int> vec){
    // экспоненциальный поиск
    int prev = 0;
    int current = 0;
    for (int i = 0; pow(2,i) < vec.size; i++){
        current = pow(2,i);
        if( vec[current-1] >= vec[current]){
            break;
        } else {
            prev = current;
            current = vec.size-1;
        }
    }
    
    // бинарный поиск
    while (prev < current){
        int new_it = (prev+current)/2 + 1;
        if (vec[ new_it - 1] < vec[ new_it ]){
            prev = new_it;
        } else {
            current = new_it - 1;
        }
    }
    return prev;
}

int main(){
    MyVec<int> vec = input();
    std::cout  <<  search(vec) << std::endl;
    return 0;
}