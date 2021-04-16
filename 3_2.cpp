/*
3_2. Реализовать дек с динамическим зацикленным буфером.
Требования: Дек должен быть реализован в виде класса.

a = 1 - push front
a = 2 - pop front
a = 3 - push back
a = 4 - pop back
Команды добавления элемента 1 и 3 заданы с неотрицательным параметром b.
Если дана команда pop*, то число b - ожидаемое значение. Если команда pop вызвана для пустой структуры данных, то ожидается “-1”. 
*/

#include <cstddef>
#include <iostream>

template <class T> //так как методы класса иногда возращают -1, у него очень ограниченный круг допустимых T
class Dek {
public:
    void push_front(T&);
    const T* pop_front();
    void push_back(T&);
    const T* pop_back();
    bool is_not_empty();
    Dek(){
        size = 0;
        capacity = 0;
        begin = 0;
        end = 0;
    };
    void print();
private:
    T begin;
    T end;
    size_t size;
    size_t capacity;
    T* buf;
    bool increase_buf();
};

template<class T>
void Dek<T>::push_front(T &new_item) {
    if (size == capacity){
        increase_buf();
    }
    if(size == 0){
        buf[begin] = new_item;
        ++size;
        return;
    }
    if( --begin < 0 ){
        begin += capacity;
    }
    buf[begin] = new_item;
    ++size;
}

template<class T>
const T* Dek<T>::pop_front(){
    if(size == 0){
        return nullptr;
    }
    T* return_val = &buf[begin];
    if(--size == 0){
        return return_val;
    }
    if (++begin >= capacity){
        begin -= capacity;
    }
    return return_val;
}

template<class T>
void Dek<T>::push_back(T &new_item) {
    if (size == capacity){
        increase_buf();
    }
    if(size == 0){
        buf[end] = new_item;
        ++size;
        return;
    }
    if( ++end >= capacity ){
        end -= capacity;
    }
    buf[end] = new_item;
    ++size;
}

template<class T>
const T* Dek<T>::pop_back(){
    if(size == 0){
        return nullptr;
    }
    T* return_val = &buf[end];
    if (--size == 0){
        return return_val;
    }
    if (--end < 0){
        end += capacity;
    }
    return return_val;
}

template<class T>
bool Dek<T>::increase_buf() {
    if (capacity == 0){
        capacity = 10;
        buf = new T[capacity];
        return true;
    }
    T* vec = new T[capacity*2];
    if(begin < end){
    	for(int i = begin; i <= end; i++){
        	vec[i] = buf[i];
        }
    } else {
    	for(int i = 0; i <= end; i++){
        	vec[i] = buf[i];
        }
        for(int i = capacity-1; i >= begin; i--){
        	vec[capacity+i] = buf[i];
        }
        begin += capacity;
    }
    buf = vec;
    capacity *= 2;
    return true;
}

int main(){ // отделять ввод от решения, кажется, не стоит
        int n;
        std::cin >> n;
        short a;
        int b; 
        Dek<int> dek = Dek<int>();
        bool flag = true;
        const int* tmp;
        int returned_b;
        for(int i = 0; i < n; i++){
            std::cin >> a >> b;

            switch (a)
            {
            case 1:
                dek.push_front(b);
                break;
            case 2:
                tmp = dek.pop_front();
                if(tmp){
                    returned_b = *tmp;
                }else{
                    returned_b = -1;
                }
                if (returned_b != b){
                    flag = false;
                }
                break;
            case 3:
                dek.push_back(b);
                break;
            case 4:
                tmp = dek.pop_back();
                if(tmp){
                    returned_b = *tmp;
                }else{
                    returned_b = -1;
                }
                if (returned_b != b){
                    flag = false;
                }
                break;
            default:
                break;
            }
        }

        if (flag){
            std::cout << "YES" << std::endl;
        } else {
            std::cout << "NO" << std::endl;
        }
    return 0;
};
