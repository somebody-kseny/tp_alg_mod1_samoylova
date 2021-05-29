/*
Задача 4. Использование АВЛ-дерева
4_2. Порядковые статистики.
Дано число N и N строк. Каждая строка содержит команду добавления или удаления натуральных чисел,
а также запрос на получение k-ой порядковой статистики.
Команда добавления числа A задается положительным числом A,
команда удаления числа A задается отрицательным числом “-A”.
Запрос на получение k-ой порядковой статистики задается числом k.
Требования: скорость выполнения запроса - O(log n).
*/

#include <iostream>
#include <fstream>
#include <memory>
#include <vector>

template<class T>
struct Node {
    explicit Node(T& _data): key(_data), left(nullptr), right(nullptr) { height = 1;};
    unsigned char height;
    T key;
    std::shared_ptr<Node> left;
    std::shared_ptr<Node> right;
};

template<class T>
class BinTree{
public:
    BinTree() = delete;
    explicit BinTree<T>(bool(*_compare)(T&,T&)): compare(_compare) {};
    bool add(T& added);
    bool remove(T k);
    T getStatistic(int k);
    ~BinTree() = default;
private:
    std::shared_ptr<Node<T>> root = nullptr;
    bool(*compare)(T&,T&);

    unsigned char height(std::shared_ptr<Node<T>> node);
    int balanceFactor(std::shared_ptr<Node<T>> node);
    void fixHeight(std::shared_ptr<Node<T>> node);

    std::shared_ptr<Node<T>> smallRight(std::shared_ptr<Node<T>> p);
    std::shared_ptr<Node<T>> smallLeft(std::shared_ptr<Node<T>> q);
    std::shared_ptr<Node<T>> balance(std::shared_ptr<Node<T>> p);

    std::shared_ptr<Node<T>> insert(std::shared_ptr<Node<T>> node, T& key);
    std::shared_ptr<Node<T>> find(std::shared_ptr<Node<T>>& node, T key);

    std::shared_ptr<Node<T>> findMin(std::shared_ptr<Node<T>> node);

    std::shared_ptr<Node<T>> removeMin(std::shared_ptr<Node<T>> node);

    std::shared_ptr<Node<T>> remove(std::shared_ptr<Node<T>> p, int k);
};


template<class T>
unsigned char BinTree<T>::height(std::shared_ptr<Node<T>> node) {
    if(node){
        return node->height;
    } else {
        return 0;
    }
}

template<class T>
int BinTree<T>::balanceFactor(std::shared_ptr<Node<T>> node) {
    return height(node->right)-height(node->left);
}

template<class T>
void BinTree<T>::fixHeight(std::shared_ptr<Node<T>> node) {
    unsigned char hl = height(node->left);
    unsigned char hr = height(node->right);
    node->height = ( (hl>hr) ? hl : hr)+1;
}


template<class T>
std::shared_ptr<Node<T>> BinTree<T>::smallRight(std::shared_ptr<Node<T>> p) {
    std::shared_ptr<Node<T>> temp = p->left;
    p->left = temp->right;
    temp->right = p;
    fixHeight(p);
    fixHeight(temp);
    return temp;
}

template<class T>
std::shared_ptr<Node<T>> BinTree<T>::smallLeft(std::shared_ptr<Node<T>> q) {
    std::shared_ptr<Node<T>> temp = q->right;
    q->right = temp->left;
    temp->left = q;
    fixHeight(q);
    fixHeight(temp);
    return temp;
}

template<class T>
std::shared_ptr<Node<T>> BinTree<T>::balance(std::shared_ptr<Node<T>> p) // балансировка узла p
{
    fixHeight(p);
    if( balanceFactor(p)==2 )
    {
        if(balanceFactor(p->right) < 0 ){
            p->right = smallRight(p->right);
        }
        return smallLeft(p);
    }
    if( balanceFactor(p)==-2 )
    {
        if( balanceFactor(p->left) > 0  )
            p->left = smallLeft(p->left);
        return smallRight(p);
    }
    return p; // балансировка не нужна
}

template<class T>
std::shared_ptr<Node<T>> BinTree<T>::insert(std::shared_ptr<Node<T>> node, T& key) {
    if( !node ) return std::make_shared<Node<T>>(key);
    if( compare(node->key, key)){
        node->right = insert(node->right, key);
    } else {
        node->left = insert(node->left, key);
    }
    return balance(node);
}

template<class T>
bool BinTree<T>::add (T& added) {
    root = insert(root, added);
    return true;
}

template<class T>
bool BinTree<T>::remove(T k){
    if(find(root, k) == nullptr){
        return false;
    }
    root = remove(root , k);
    return true;
}

template<class T>
std::shared_ptr<Node<T>> BinTree<T>::find(std::shared_ptr<Node<T>>& node, T key) {
    if( !node ) return nullptr;
    if(node->key == key){
        return node;
    } else if( compare(key, node->key) ) {
        return node->left = find(node->left, key);
    } else {
        return node->right = find(node->right, key);
    }
}

template<class T>
std::shared_ptr<Node<T>> BinTree<T>::findMin(std::shared_ptr<Node<T>> node) // поиск узла с минимальным ключом в дереве p
{
    return node->left ? findMin(node->left) : node;
}

template<class T>
std::shared_ptr<Node<T>> BinTree<T>::removeMin(std::shared_ptr<Node<T>> node) // удаление узла с минимальным ключом из дерева p
{
    if( node->left == nullptr ){
        return node->right;
    }
    node->left = removeMin(node->left);
    return balance(node);
}

template<class T>
std::shared_ptr<Node<T>> BinTree<T>::remove(std::shared_ptr<Node<T>> p, int k) // удаление ключа k из дерева p
{
    if( !p ) return nullptr;
    if( compare(k, p->key) ){
        p->left = remove(p->left,k);
    } else if (k == p->key) {
        std::shared_ptr<Node<T>> q = p->left;
        std::shared_ptr<Node<T>> r = p->right;
        p = nullptr;
        if( !r ) return q;
        std::shared_ptr<Node<T>> min = findMin(r);
        min->right = removeMin(r);
        min->left = q;
        return balance(min);
    } else {
        p->right = remove(p->right,k);
    }
    return balance(p);

}

template<class T>
T BinTree<T>::getStatistic(int k) {
    std::weak_ptr<Node<T>> current = root;
    std::vector<std::weak_ptr<Node<T>>> passed;
    bool goRight = false;
    int i = 0;
    do{
        if(!goRight) {
            while (current.lock()->left != nullptr){
                passed.push_back(current);
                current = current.lock()->left;
            }
            passed.push_back(current);
            goRight = true;
        } else {
            if(!passed.empty()){
                current = passed.at(passed.size() - 1);
                passed.pop_back();
            }
            if(i == k){
                return current.lock()->key;
            }
            i++;
            if(current.lock()->right != nullptr){
                current = current.lock()->right;
                goRight = false;
            }
        }
    } while (i < 8); // используем гарантию что порядковая статистика существует
    return 42;
}

bool ifRightBigger(int &a, int &b){
    if(a<b){
        return true;
    } else {
        return false;
    }
}

int main(){
    BinTree<int> bt(ifRightBigger);
    int amount;
    std::ifstream input;
    input.open("../input.txt");
    std::ofstream output;
    output.open("../output.txt");
    input >> amount;
    int node, k;
    for(int i = 0; i < amount; i++){
        input >> node >> k;
        if(node < 0){
            bt.remove(-node);
        } else {
            bt.add(node);
        }
        output << bt.getStatistic(k) << std::endl;
    }
    return 0;
}
