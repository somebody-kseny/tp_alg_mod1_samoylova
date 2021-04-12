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
#include <fstream>
#include <string.h>


template <class T> //так как методы класса иногда возращают -1, у него очень ограниченный круг допустимых T
class Dek {
public:
    void push_front(T&);
    T pop_front();
    void push_back(T&);
    T pop_back();
    bool is_not_empty();
    Dek(){
        size = 0;
        capacity = 10;
        buf = new T[capacity];
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
    if(size == 0){
        buf[0] = new_item;
        ++size;
        return;
    }
    if (size == capacity){
        increase_buf();
    }
    if( --begin < 0 ){
        begin += capacity;
    }
    buf[begin] = new_item;
    ++size;
}

template<class T>
T Dek<T>::pop_front(){
    if(size == 0){
        return -1;
    }
    T return_val = buf[begin];
    if (++begin >= capacity){
        begin -= capacity;
    }
    --size;
    return return_val;
}

template<class T>
void Dek<T>::push_back(T &new_item) {
    if(size == 0){
        buf[0] = new_item;
        ++size;
        return;
    }
    if (size == capacity){
        increase_buf();
    }
    if( ++end >= capacity ){
        end -= capacity;
    }
    buf[end] = new_item;
    ++size;
}

template<class T>
T Dek<T>::pop_back(){
    if(size == 0){
        return -1;
    }
    T return_val = buf[end];
    if (--end < 0){
        end += capacity;
    }
    --size;
    return return_val;
}

template<class T>
bool Dek<T>::increase_buf() {
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

    for (int i = 1; i <= 12; i++){ 
        std::string s = "./tests3_2/input" + std::to_string(i);
        std::ifstream fin;
        fin.open(s);
        int n;
        fin >> n;
        short a;
        int b; 
        Dek<int> dek = Dek<int>();
        bool flag = true;
        for(int i = 0; i < n; i++){
            fin >> a >> b;
            //std::cout << a << b;
            switch (a)
            {
            case 1:
                dek.push_front(b);
                break;
            case 2:
                if (dek.pop_front() != b){
                    flag = false;
                }
                break;
            case 3:
                dek.push_back(b);
                break;
            case 4:
                if (dek.pop_back() != b){
                    flag = false;
                }
                break;   
            }
        }

        std::cout << i << "\t: ";
        if (flag){
            
            //std::cout << "YES" << std::endl;
            std::string req;
            fin >> req;
            if (req == "YES"){
                std::cout << "ok" << std::endl;
            } else {
                std::cout << "err" << std::endl;
            }
        } else {
            //std::cout << "NO" << std::endl;
            std::string req;
            fin >> req;
            if (req == "NO"){
                std::cout << "ok" << std::endl;
            } else {
                std::cout << "err" << std::endl;
            }
        }
        fin.close();
    }
    return 0;
};
