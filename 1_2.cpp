/*
1_2. Вычислить площадь выпуклого n-угольника, заданного координатами своих вершин. Вначале вводится количество вершин, затем последовательно целочисленные координаты всех вершин в порядке обхода против часовой стрелки.
n < 1000, координаты < 10000.
Указание. Для вычисления площади n-угольника можно посчитать сумму ориентированных площадей трапеций под каждой стороной многоугольника. 
Требования: Координата должна быть реализована в виде структуры.
*/

#include <iostream>

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

typedef struct Point {
    int x;
    int y;
} Point;

MyVec<Point> input(int*);
double calc_area(MyVec<Point>, int);

int main(){
    int n = 0;
    MyVec<Point> vec = input(&n);
    std::cout  << calc_area(vec, n) << std::endl;
    return 0;
}

MyVec<Point> input(int* n){
    auto vs = new MyVec<Point>();
    int amount = 0;
    std::cin >> amount;
    Point to_add;
    for(int i = 0; i < amount; i++){
        std::cin >> to_add.x;
        std::cin >> to_add.y;
        bool res = vs->push_back(to_add);
    }
    *n = amount; // записываем в n количество элементов
    return *vs;
}

double calc_area(MyVec<Point> vec, int n){
    double area = 0;
    Point one, two;
    for (int i = 0; i+1 < n; i++){
        one = vec[i];
        two = vec[i+1];
        area+= ( (double)(one.y + two.y)/2 ) * (two.x - one.x);
    }
    one = vec[n-1];
    two = vec[0];
    area+= ( (double)(one.y + two.y)/2 ) * (two.x - one.x);
    return area;
}