/*
4_1. Жадина.
Вовочка ест фрукты из бабушкиной корзины. В корзине лежат фрукты разной массы. Вовочка может поднять не более K грамм. Каждый фрукт весит не более K грамм. За раз он выбирает несколько самых тяжелых фруктов, которые может поднять одновременно, откусывает от каждого половину и кладет огрызки обратно в корзину. Если фрукт весит нечетное число грамм, он откусывает большую половину. Фрукт массы 1гр он съедает полностью.
Определить за сколько подходов Вовочка съест все фрукты в корзине.
Формат входных данных. Вначале вводится n - количество фруктов и n строк с массами фруктов. Затем K - "грузоподъемность".
Формат выходных данных. Неотрицательное число - количество подходов к корзине.
*/

#include <cstddef>
#include <iostream>

//Comparators. Способ решения с семинара не получился. Чтобы функция сравнения передавалась снаружи, сделала поле класса-кучи - указатель на базовый класс Comparator, в конструкторе в него можно поместить объект дочернего класса

template<class T>
struct Comparator {
    virtual bool operator()(const T& l, const T& r) const {
        return r < l;
    }
};

template<class T>
struct MyComparator: Comparator<T> {
    bool operator()(const T& l, const T& r) const {
        return l < r;
    }
};

// просто функция, вместо std

template <typename T>
void swap(T& l, T& r){
    T temp = l;
    l = r;
    r = temp;
};

template <class T>
class MyVec { //объявление класса
public:
    size_t size;
    bool push_back(T&);
    T& operator[](int);
    T pop_back();
    bool is_not_empty();
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

//MyHeap

template <class T>
class MyHeap {
public:
    void insert(T&);
    T pop();
    bool is_not_empty();
    MyHeap(Comparator<T>* corp_in){
        size = 0;
        capacity = 10;
        buf = new T[capacity];
        comp = corp_in;
    };
    ~MyHeap(){
        delete[] buf;
    };
private:
    T* buf;
    size_t size;
    size_t capacity;
    Comparator<T>* comp;
    void siff_up(size_t);
    void siff_down(size_t);
    void increase_buf();
};

template<class T>
void MyHeap<T>::insert(T& t){
    if (size+1 == capacity){
        increase_buf();
    }
    buf[size] = t;
    siff_up(size++);
};

template<class T>
T MyHeap<T>::pop(){
    T temp = buf[0];
    buf[0] = buf[size-1];
    size--;
    siff_down(0);
    return temp;
};

template<class T>
bool MyHeap<T>::is_not_empty(){
    return size;
}

template<class T>
void MyHeap<T>::siff_up(size_t pos){
    while((*comp)(buf[pos/2], buf[pos])){
        swap(buf[pos/2], buf[pos]);
        pos = pos/2;
    }
};

template<class T>
void MyHeap<T>::siff_down(size_t pos){
    bool l_comp, r_comp;
    while(2*pos < size){

        if(2*pos+1 > size){
            if((*comp)(buf[pos], buf[2*pos])){
                swap(buf[2*pos], buf[pos]);
            }
            return;
        }

        l_comp = (*comp)(buf[pos], buf[2*pos]);
        r_comp = (*comp)(buf[pos], buf[2*pos+1]);
        if (!l_comp && !r_comp){
            return;
        }
        if(l_comp && !r_comp){
            swap(buf[pos], buf[2*pos]);
            pos = 2*pos;
        } else if (!l_comp && r_comp) {
            swap(buf[pos], buf[2*pos+1]);
            pos = 2*pos+1;
        } else {
            if ((*comp)(buf[2*pos], buf[2*pos+1])){
                swap(buf[2*pos+1], buf[pos]);
                pos = 2*pos+1;
            } else {
                swap(buf[2*pos], buf[pos]);
                pos = 2*pos;
            }
        }
    };
};

template<class T>
void MyHeap<T>::increase_buf(){
    T* new_buf;
    size_t new_capacity = capacity*2;
    new_buf = new T[new_capacity];
    for (int i = 0; i < capacity; i++){
        new_buf[i] = buf[i];
    }
    delete[] buf;
    buf = new_buf;
    capacity = new_capacity;
};

//MyVector (реализация, только то, что нужно)

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
T MyVec<T>::pop_back(){
    return buf[--size];
}

template<class T>
bool MyVec<T>::is_not_empty(){
    return size;
}

template<class T>
bool MyVec<T>::increase_buf() {
    T* vec = new T[capacity*2];
    for (int i = 0; i < size; i++){
        vec[i] = buf[i];
    }
    delete[] buf;
    buf = vec;
    capacity *= 2;
    return true;
}

template<class T>
T& MyVec<T>::operator[](int index){
    return buf[index];
}

// функции для решения задачи

void input(MyHeap<short>&basket, int &n, short &K){
    std::cin >> n;
    short fruit;
    for(int i = 0; i < n; i++){
        std::cin >> fruit;
        basket.insert(fruit);
    }
    std::cin >> K;
};

int logics(MyHeap<short>&basket, int n, short K){
    short fruit;
    int count = 0;
    int cur_K;
    MyVec<short> cur_fruits;
    while(basket.is_not_empty()){
        cur_K = 0;
        do{
            fruit = basket.pop();
            if(cur_K+fruit <= K){
                cur_K += fruit;
                cur_fruits.push_back(fruit);
            } else {
                basket.insert(fruit);
                break;
            }
        }while (basket.is_not_empty());

        for(int i = 0; i < cur_fruits.size; i++){
            fruit = cur_fruits[i];
            if(fruit == 1){
                cur_fruits[i] = 0; //!
                continue;
            }
            cur_fruits[i] = fruit/2;
        }

        while(cur_fruits.is_not_empty()){
            fruit = cur_fruits.pop_back();
            if (fruit != 0){
                basket.insert(fruit);
            }
        }

        count++;
    }
    return count;
}


int main(){
    MyComparator<short> corp;
    MyHeap<short> basket = MyHeap<short>(&corp);
    int n;
    short K;
    input(basket, n, K);
    std::cout << logics(basket, n, K);
    return 0;
};
