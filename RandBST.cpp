#include "BST.cpp"

template <typename KeyType, typename DataType> 
class RandBST : public BST<KeyType, DataType>
{
    using BST<KeyType, DataType>::Node;

public:

    RandBST() {};
    RandBST(const RandBST<KeyType, DataType>& tree) {};
    ~RandBST() {};

protected:

    typename BST<KeyType, DataType>::Node* insert_recursively(typename KeyType key, 
        typename DataType data, typename BST<KeyType, DataType>::Node* node, bool& is_ok) override; // оверрайдим рекурсивную вставку, чтобы получить ранд дерево

    typename BST<KeyType, DataType>::Node* remove_recursively(typename KeyType key, 
        typename BST<KeyType, DataType>::Node* node, bool& is_ok) override; // оверрайдим рекурсивное удаление

    typename BST<KeyType, DataType>::Node* insertRoot(KeyType key, 
        DataType data, typename BST<KeyType, DataType>::Node* node, bool& is_ok); // вставка в корень поддерева

    typename BST<KeyType, DataType>::Node* rotateLeft(typename BST<KeyType, DataType>::Node* q); // левый поворот вокруг q
    typename BST<KeyType, DataType>::Node* rotateRight(typename BST<KeyType, DataType>::Node* p); // правый поворот вокруг p

    void fixWeight(typename RandBST<KeyType, DataType>::Node* node); // вес ноды = вес правого и левого поддерева + 1 

    typename BST<KeyType, DataType>::Node* join(typename RandBST<KeyType, DataType>::Node* a, typename RandBST<KeyType, DataType>::Node* b);

};



template<typename KeyType, typename DataType>
typename BST<KeyType, DataType>::Node* RandBST<KeyType, DataType>::insert_recursively
    (typename KeyType key, typename DataType data, typename BST<KeyType, DataType>::Node* node, bool& is_ok)
{
    if (node==nullptr) {
        is_ok = true;
        this->size++;
        return new Node(key, data);
    }

    
    if (rand() % (node->weight + 1) == 0) {
        return insertRoot(key, data, node, is_ok); // с некоторой вероятностью вставка в корень поддерева
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

    this->stepCount++;
    if (is_ok) node->weight++;
    return node;
}

template<typename KeyType, typename DataType>
typename BST<KeyType, DataType>::Node* RandBST<KeyType, DataType>::remove_recursively(typename KeyType key, typename BST<KeyType, DataType>::Node* node, bool& is_ok)
{
    if (node == nullptr) { // ноды с таким ключем не существует, отказ
        is_ok = false;
        return node;
    }

    this->stepCount++;

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

    // нужная нода достигнута

    Node* x = join(node->left, node->right);
    delete node;
    this->size--;
    is_ok = true;
    return x;
    
}



template<typename KeyType, typename DataType>
typename BST<KeyType, DataType>::Node* RandBST<KeyType, DataType>::insertRoot(KeyType key, DataType data, typename BST<KeyType, DataType>::Node* node, bool& is_ok) // вставка в корень
{
    if (node == nullptr) {
        is_ok = true;
        this->size++;
        return new Node(key, data);
    }

    this->stepCount++;

    if (key == node->key) {
        is_ok = false;
        return node;
    }

    if (key < node->key)
    {
        node->left = insertRoot(key, data, node->left, is_ok);
        if (is_ok) {
            node->weight++;
            node = rotateRight(node);
        }
    }
    else
    {
        node->right = insertRoot(key, data, node->right, is_ok);
        if (is_ok) {
            node->weight++;
            node = rotateLeft(node);
        }
    }
    return node;

}

template<typename KeyType, typename DataType>
void RandBST<KeyType, DataType>::fixWeight(typename RandBST<KeyType, DataType>::Node* node) // установление корректного размера дерева
{
    if (node == nullptr) return;
    int w1 = 0, w2 = 0;
    if (node->right != nullptr) w1 = node->right->weight;
    if (node->left != nullptr) w2 = node->left->weight;
    node->weight = w1 + w2 + 1;
}

template<typename KeyType, typename DataType>
typename BST<KeyType, DataType>::Node* RandBST<KeyType, DataType>::join(typename RandBST<KeyType, DataType>::Node* a, typename RandBST<KeyType, DataType>::Node* b)
{

    if (a == nullptr) return b;
    if (b == nullptr) return a;

    if (rand() % (a->weight + b->weight + 1) == 0) {
        a->right = join(a->right, b);
        fixWeight(a);
        return a;
    }

    else {
        b->left = join(a, b->left);
        fixWeight(b);
        return b;
    }

}

template<typename KeyType, typename DataType>
typename BST<KeyType, DataType>::Node* RandBST<KeyType, DataType>::rotateLeft(typename BST<KeyType, DataType>::Node* q)
{
    Node* p = q->right;
    if (p==nullptr) return q;
    q->right = p->left;
    p->left = q;
    p->weight = q->weight;
    fixWeight(q); // вес q = вес q->left + вес q->right + 1
    return p;
}

template<typename KeyType, typename DataType>
typename BST<KeyType, DataType>::Node* RandBST<KeyType, DataType>::rotateRight(typename BST<KeyType, DataType>::Node* p)
{
    Node* q = p->left;
    if (q==nullptr) return p;
    p->left = q->right;
    q->right = p;
    q->weight = p->weight;
    fixWeight(p); // вес p = вес p->left + вес p->right + 1
    return q;
}
