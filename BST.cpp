#include <iostream>
using namespace std;

template <typename KeyType, typename DataType> class BST {

protected:

    class Node {

    public:

        KeyType key;
        DataType data;
        Node* left;
        Node* right;
        int weight; // сколько в поддереве элементов (включая корень)

        Node(KeyType key, DataType data) {
            this->key = key;
            this->data = data;
            this->left = nullptr;
            this->right = nullptr;
            this->weight = 1;
        }

    };

    Node* root;
    int size;

    int stepCount; // число шагов предыдущей операции

public:

    BST(); // конструктор
    BST(const BST<KeyType, DataType>& tree); // конструктор копирования
    ~BST(); // деструктор
    void clear(); // очистка дерева
    void show_keys(); // структура дерева
    void show_data();
    void show_weight();
    void show_numbers();
    void show_keyweight();
    int getStepCount();
    void show_keylist();
    int getSerialNumber(KeyType key);
    bool insert(typename KeyType key, typename DataType data); // включение данных по ключу
    bool remove(typename KeyType key);
    int getSize();
    bool isEmpty();
    typename DataType* readwrite(KeyType key); // возвращает адресную ссылку на данные
    DataType read(KeyType key); // устарела
    bool write(KeyType key, DataType data); // устарела

protected:

    typename Node* copy_recursively(typename Node* node); // рекурсивное копирование дерева (для конструктора копирования)

    void clear_recursively(Node* node); 

    void show_recursively(typename BST<KeyType, DataType>::Node* r, int level, int mode);

    void show_keylist_recursively(Node* node);

    int getSerialNumber_recursively(KeyType key, Node* node, int number, bool left);

    virtual typename Node* insert_recursively(typename KeyType key, typename DataType data, typename Node* node, bool& is_ok); // рекурсивное включение данных по ключу

    virtual typename Node* remove_recursively(typename KeyType key, typename Node* node, bool& is_ok); // рекурсивное удаление данных по ключу
    
    typename Node* rem(typename Node* node, typename Node* node0); // рекурсивное удаление, когда у удаляемой ноды два потомка

    typename DataType read_recursively(KeyType key, typename Node* node); // возвращает данные или кидает эксепшн - устарела
    bool write_recursively(KeyType key, DataType data, typename Node* node); // записывает данные - устарела
    typename Node* search_recursively(KeyType key, typename Node* node); // возвращает ноду c нужным ключем
    typename Node* getNext(typename Node* x); // следующий элемент при симметричном обходе (l-t-r)
    typename Node* getPrev(typename Node* node);
    typename Node* getLParent(typename Node* t, typename Node* x);
    typename Node* getRParent(typename Node* t, typename Node* x);

public:
    class Iterator {

    private:

        BST* tree;
        Node* node;

    public:

        Iterator(BST* tree = nullptr, Node* node = nullptr) {
            this->tree = tree;
            this->node = node;
        }
        Iterator(const Iterator& iterator) {
            tree = iterator.tree;
            node = iterator.node;
        }

        Iterator* operator++()
        {
            this->node = tree->getNext(node);
            return this;
        }

        Iterator* operator--()
        {
            this->node = tree->getPrev(node);
            return this;
        }

        DataType& operator*() const {
            if (node != nullptr) return node->data;
            else throw exception("Exception: pointer == nullptr");
        }

        bool operator==(const Iterator& lhs) const
        {
            return (node == lhs.node);
        }

        bool operator!=(const Iterator& lhs) const
        {
            return (node != lhs.node);
        }

    };

    class ReverseIterator {

    private:

        BST* tree;
        Node* node;

    public:

        ReverseIterator(BST* tree = nullptr, Node* node = nullptr) {
            this->tree = tree;
            this->node = node;
        }
        ReverseIterator(const ReverseIterator& iterator) {
            tree = iterator.tree;
            node = iterator.node;
        }

        ReverseIterator* operator++()
        {
            this->node = tree->getPrev(node);
            return this;
        }

        ReverseIterator* operator--()
        {
            this->node = tree->getNext(node);
            return this;
        }

        DataType& operator*() const {
            if (node != nullptr) return node->data;
            else throw exception("Exception: pointer == nullptr");
        }

        bool operator==(const ReverseIterator& lhs) const
        {
            return (node == lhs.node);
        }

        bool operator!=(const ReverseIterator& lhs) const
        {
            return (node != lhs.node);
        }

    };

    friend class Iterator;
    friend class ReverseIterator;

    using iterator = Iterator;
    using reverse_iterator = ReverseIterator;

    iterator begin() { // возвращает самый левый узел
        Node* p = root;
        if (p != nullptr)
            while (p->left != nullptr)
                p = p->left;
        return iterator(this, p);
    }
    iterator end() { // node = nullptr
        return iterator(this);
    }

    reverse_iterator rbegin() { // возвращает самый правый узел
        Node* p = root;
        if (p != nullptr)
            while (p->right != nullptr)
                p = p->right;
        return reverse_iterator(this, p);
    }
    reverse_iterator rend() { // node = nullptr
        return reverse_iterator(this);
    }

    

};


template<typename KeyType, typename DataType>
inline BST<KeyType, DataType>::BST()
{
    root = nullptr;
    size = 0;
    stepCount = 0;
}

template<typename KeyType, typename DataType>
inline BST<KeyType, DataType>::BST(const BST<KeyType, DataType>& tree)
{
    root = tree.root;
    size = tree.size;
    stepCount = 0;

    root = copy_recursively(tree.root);
}

template<typename KeyType, typename DataType>
inline typename BST<KeyType, DataType>::Node* BST<KeyType, DataType>::copy_recursively(typename Node* node)
{
    if (node==nullptr) return nullptr;

    Node* newNode = new Node(node->key, node->data);
    newNode->weight = node->weight;

    newNode->left = copy_recursively(node->left);
    newNode->right = copy_recursively(node->right);

    return newNode;
}

template<typename KeyType, typename DataType>
BST<KeyType, DataType>::~BST()
{
    clear();
}


template<typename KeyType, typename DataType>
inline void BST<KeyType, DataType>::clear()
{
    clear_recursively(root);
    root = nullptr;
}

template<typename KeyType, typename DataType>
inline void BST<KeyType, DataType>::clear_recursively(Node* node)
{
    if (node==nullptr) return;

    if (node->left) clear_recursively(node->left);
    if (node->right) clear_recursively(node->right);

    delete node;
    size--;
}


template<typename KeyType, typename DataType>
int BST<KeyType, DataType>::getStepCount()
{
    return stepCount;
}

template<typename KeyType, typename DataType>
inline void BST<KeyType, DataType>::show_keys()
{
    show_recursively(root, 0, 0);
}

template<typename KeyType, typename DataType>
inline void BST<KeyType, DataType>::show_data()
{
    show_recursively(root, 0, 1);
}

template<typename KeyType, typename DataType>
inline void BST<KeyType, DataType>::show_weight()
{
    show_recursively(root, 0, 2);
}


template<typename KeyType, typename DataType>
inline void BST<KeyType, DataType>::show_numbers()
{
    show_recursively(root, 0, 3);
}

template<typename KeyType, typename DataType>
inline void BST<KeyType, DataType>::show_keyweight()
{
    show_recursively(root, 0, 4);
}

template<typename KeyType, typename DataType>
inline void BST<KeyType, DataType>::show_recursively(typename BST<KeyType, DataType>::Node* r, int level, int mode)
{
    if (r==nullptr) return;

    show_recursively(r->right, level + 1, mode);
    for (int i = 0; i <= 2 * level; i++)
        cout << "  ";


    switch (mode) {
    case 0: // ключи
        cout << r->key << endl;
        break;
    case 1: // данные
        cout << r->data << endl;
        break;
    case 2: // веса
        cout << r->weight << endl;
        break;
    case 3: // порядковые номера
        cout << getSerialNumber(r->key) << endl;
        break;
    case 4:
        cout << r->key << "(" << r->weight << ")" << endl;
        break;
    }


    show_recursively(r->left, level + 1, mode);
}

template<typename KeyType, typename DataType>
void BST<KeyType, DataType>::show_keylist()
{
    show_keylist_recursively(root);
}

template<typename KeyType, typename DataType>
void BST<KeyType, DataType>::show_keylist_recursively(Node* node)
{
    if (node == nullptr) return;

    cout << node->key << " ";

    show_keylist_recursively(node->left);
    show_keylist_recursively(node->right);
}


template<typename KeyType, typename DataType>
int BST<KeyType, DataType>::getSerialNumber_recursively(KeyType key, Node* node, int number, bool left)
{

    if (node == nullptr) { // не существует ноды с таким ключем
        return -1;
    }

    if (left) // текущая нода является левым потомком своего родителя (шаг влево)
    {
        // считаем порядковый номер текущей ноды
        if (node->left == nullptr) number -= (node->weight); // № = № родителя - (вес текущей ноды - 0)
        else number -= (node->weight - node->left->weight); // № = № родителя - (вес текущей ноды - вес левого потомка текущей ноды)
    }

    else // текущая нода является правым потомком своего родителя (шаг вправо)
    {
        // считаем порядковый номер текущей ноды
        if (node->right == nullptr) number += (node->weight); // № = № родителя + (вес текущей ноды - 0)
        else number += (node->weight - node->right->weight); // № = № родителя + (вес текущей ноды - вес правого потомка текущей ноды)
    }


    if (key < node->key) // нужная нода левее
    {
        number = getSerialNumber_recursively(key, node->left, number, true);
    }
    else if (key > node->key) // нужная нода правее
    {
        number = getSerialNumber_recursively(key, node->right, number, false);
    }

    else // до нужной ноды добрались и посчитали номер
        return number;

}

template<typename KeyType, typename DataType>
int BST<KeyType, DataType>::getSerialNumber(KeyType key)
{

    return getSerialNumber_recursively(key, root, 0, false); // false потому, что порядковый номер корня = вес корня - вес правого потомка
    
}





template<typename KeyType, typename DataType>
inline bool BST<KeyType, DataType>::insert(KeyType key, DataType data)
{
    stepCount = 0;
    bool is_ok = false;

    root = insert_recursively(key, data, root, is_ok);

    return is_ok;
}


template<class KeyType, class DataType>
inline typename BST<KeyType, DataType>::Node* BST<KeyType, DataType>::insert_recursively(KeyType key, DataType data, Node* node, bool& is_ok)
{

    if (!node) {
        is_ok = true;
        size++;
        return new Node(key, data);
    }

    if (key == node->key) {
        is_ok = false;
        return node;
    }

    if (key < node->key) {
        node->left = insert_recursively(key, data, node->left, is_ok);
    }

    else {
        node->right = insert_recursively(key, data, node->right, is_ok);
    }

    stepCount++;
    if (is_ok) node->weight++;
    return node;
}

template<typename KeyType, typename DataType>
int BST<KeyType, DataType>::getSize()
{
    return size;
}

template<typename KeyType, typename DataType>
bool BST<KeyType, DataType>::isEmpty()
{
    return (root == nullptr);
}

template<typename KeyType, typename DataType>
bool BST<KeyType, DataType>::remove(typename KeyType key)
{
    stepCount = 0;
    bool is_ok = false;

    root = remove_recursively(key, root, is_ok);  
    
    return is_ok;
}

template<typename KeyType, typename DataType>
typename BST<KeyType, DataType>::Node* BST<KeyType, DataType>::remove_recursively(typename KeyType key, typename Node* node, bool& is_ok)
{
    if (node == nullptr) { // ноды с таким ключем не существует, отказ
        is_ok = false;
        return node;
    }

    stepCount++;

    if (key < node->key) { // нода где-то слева
        node->left = remove_recursively(key, node->left, is_ok);
        if (is_ok) node->weight--;
        return node;
    }

    if (key > node->key) { // нода где-то справа
        node->right = remove_recursively(key, node->right, is_ok);
        if (is_ok) node->weight--;
        return node;
    }

    if (node->left == nullptr && node->right == nullptr) { // нужная нода достигнута, потомков нет
        delete node;
        size--;
        is_ok = true;
        return nullptr;
    }

    if (node->left == nullptr) { // нужная нода достигнута, есть только правый потомок
        Node* x = node->right;
        delete node;
        size--;
        is_ok = true;
        return x;
    }

    if (node->right == nullptr) { // нужная нода достигнула, есть только левый потомок
        Node* x = node->left;
        delete node;
        size--;
        is_ok = true;
        return x;
    }

    // нужная нода достигнута, есть оба потомка
    node->right = rem(node->right, node);
    node->weight--;
    is_ok = true;
    return node;
}

template<typename KeyType, typename DataType>
typename BST<KeyType, DataType>::Node* BST<KeyType, DataType>::rem(typename Node* node, typename Node* node0)
{
    if (node->left != nullptr) {
        node->left = rem(node->left, node0);
        node->weight--;
        return node;
    }

    node0->key = node->key;
    node0->data = node->data;

    Node* x = node->right;
    delete node;
    size--;
    return x;
}

template<typename KeyType, typename DataType>
DataType BST<KeyType, DataType>::read(KeyType key)
{
    stepCount = 0;
    return read_recursively(key, root);
}

template<typename KeyType, typename DataType>
bool BST<KeyType, DataType>::write(KeyType key, DataType data)
{
    stepCount = 0;
    return write_recursively(key, data, root);
}

template<typename KeyType, typename DataType>
inline DataType BST<KeyType, DataType>::read_recursively(KeyType key, Node* node)
{

    if (node == nullptr) {
        throw exception("Exception: no such key");
    }

    if (key == node->key) {
        return node->data;
    }

    if (key < node->key) {
        return read_recursively(key, node->left);
    }

    else {
        return read_recursively(key, node->right);
    }
    stepCount++;

}

template<typename KeyType, typename DataType>
inline bool BST<KeyType, DataType>::write_recursively(KeyType key, DataType data, typename Node* node)
{
    if (node == nullptr) {
        return false;
    }

    if (key == node->key) {
        node->data = data;
        return true;
    }

    if (key < node->key) {
        return write_recursively(key, data, node->left);
    }

    else {
        return write_recursively(key, data, node->right);
    }
    stepCount++;
}

template<typename KeyType, typename DataType>
typename BST<KeyType, DataType>::Node* BST<KeyType, DataType>::search_recursively(KeyType key, typename Node* node)
{
    if (node == nullptr) {
        return nullptr;
    }

    if (key == node->key) {
        return node;
    }

    if (key < node->key) {
        return search_recursively(key, node->left);
    }

    else {
        return search_recursively(key, node->right);
    }
}

template<typename KeyType, typename DataType>
typename DataType* BST<KeyType, DataType>::readwrite(KeyType key)
{
    Node* node = search_recursively(key, root);
    if (node == nullptr) throw exception("Exception: ptr == nullptr");
    return &(node->data);
}

template<typename KeyType, typename DataType>
typename BST<KeyType, DataType>::Node* BST<KeyType, DataType>::getNext(typename Node* node)
{
    if (node == nullptr) return nullptr;

    if (node->right != nullptr)
    {
        Node* p = node->right;
        while (p->left != nullptr)
            p = p->left;
        return p;
    }
    else
        return getLParent(root, node);

}

template<typename KeyType, typename DataType>
typename BST<KeyType, DataType>::Node* BST<KeyType, DataType>::getPrev(typename Node* node)
{
    if (node == nullptr) return nullptr;

    if (node->left != nullptr) // если у текущей ноды есть левый потомок, то находим его самого правого потомка
    {
        Node* p = node->left;
        while (p->right != nullptr)
            p = p->right;
        return p;
    }
    else // иначе считаем от корня
        return getRParent(root, node);

}


template <class DataType, class KeyType>
typename BST<DataType, KeyType>::Node* BST<DataType, KeyType>::getLParent(typename BST<DataType, KeyType>::Node* tree, typename BST<DataType, KeyType>::Node* node) {
    if (tree == node) return nullptr;

    if (node->key < tree->key) // искать в левом поддереве
    {
        Node* rp = getLParent(tree->left, node); 
        if (rp != nullptr)
            return rp;
        else
            return tree;
    }
    else // искать в правом поддереве
        return getLParent(tree->right, node);
}

template <class DataType, class KeyType>
typename BST<DataType, KeyType>::Node* BST<DataType, KeyType>::getRParent(typename BST<DataType, KeyType>::Node* tree, typename BST<DataType, KeyType>::Node* node) {
    if (tree == node) return nullptr;

    if (node->key > tree->key) // искать в левом поддереве
    {
        Node* rp = getRParent(tree->right, node);
        if (rp != nullptr)
            return rp;
        else
            return tree;
    }
    else // искать в правом поддереве
        return getRParent(tree->left, node);
}

