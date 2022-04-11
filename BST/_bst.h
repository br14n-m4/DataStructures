//
// Created by br14n on 8/1/22.
//

#ifndef BST__BST_H
#define BST__BST_H
#include <stack>
template <class T>
class node{
public:
    T info{};
    node<T>* llink = nullptr;
    node<T>* rlink = nullptr;

    node() = default;
    explicit node(const T & _info, node<T>* _llink = nullptr, node<T>* _rlink = nullptr):
            info(_info), llink(_llink), rlink(_rlink){}
};

template <class T>
class bstree{
public:
    using t_node = node<T>*;
    t_node root = nullptr;

    bstree() = default;
    bool empty() const { return root == nullptr;}
    bool insert(const T& value);
    void print_inorder() { secondary_inorder(root);}
    node<T>* leftchild(const T& value)  { return ptr_element(value)->llink;}
    node<T>* rightchild(const T& value) { return ptr_element(value)->rlink;}
    std::pair<node<T>* , bool> parent(const T& value);
    int height(const t_node& n) const;
    int leaftcount() const;
    int singleparentcount() const;
    bool __NULL(const T& value){ return ptr_element(value) == nullptr;}
    bool _delete(const T& value);


private:
    node<T>* ptr_element(const T &value);
    node<T>* parent_simulate(const T& value);
    void secondary_inorder(t_node __Node);
    bool secondary_delete(t_node &__Node);
};

template<class T>
node<T> *bstree<T>::parent_simulate(const T &value) {
    auto current_node = root;
    auto trail_node = current_node;

    if(!empty()){
        while(current_node != nullptr){
            trail_node = current_node;
            if (current_node->info == value)
                break;
            else if (current_node->info > value)
                current_node = current_node->llink;
            else
                current_node = current_node->rlink;
        }
    }
    return  trail_node;
}

template<class T>
bool bstree<T>::insert(const T &value) {
    auto new_node = new node<T>(value);
    auto current_node = parent_simulate(value);
    if(empty())
        root = new_node;
    else{
        if (current_node->info != value){
            (current_node->info > value) ?
                    current_node->llink = new_node :
                    current_node->rlink = new_node;
        }
        else return false;
    }
    return true;
}

template<class T>
void bstree<T>::secondary_inorder(t_node __Node) {
    if(__Node != nullptr){
        secondary_inorder(__Node->llink);
        std::cout<< __Node->info <<" ";
        secondary_inorder(__Node->rlink);
    }
}

template<class T>
node<T> *bstree<T>::ptr_element(const T &value) {
    auto current = root;
    if (!empty()){
        while(current != nullptr){
            if (current->info == value)
                return current;
            else if (current->info > value)
                current = current->llink;
            else
                current = current->rlink;
        }
    }
    return nullptr;
}

template<class T>
std::pair<node<T>*, bool> bstree<T>::parent(const T &value) {
    std::pair<t_node, bool> p;
    auto current = root;
    p.first = current ;

    if(!empty()){
        while( current != nullptr){
            if (current ->info == value)
                break;

            p.first = current;

            (current->info > value)?
                    current  = current ->llink:
                    current  = current ->rlink;
        }
    }

    auto lchild = p.first->llink,
            rchild  = p.first->rlink;

    p.second = !((lchild == nullptr) and (rchild == nullptr));
    return p;
}

template<class T>
int bstree<T>::height(bstree::t_node const &n) const {
    return (n == nullptr)? 0:
           1 + max(height(n->llink), height(n->rlink));
}


template<class T>
int bstree<T>::leaftcount() const {
    std::stack<t_node> s;
    int sum = 0;

    for(auto i = root; i != nullptr or !s.empty();){
        if (i != nullptr){
            s.push(i);
            i = i->llink;
        }
        else{
            i = s.top();
            s.pop();

            if (i->rlink == nullptr and i->llink == nullptr)
                ++sum;
            i = i->rlink;
        }
    }
    return sum;
}

template<class T>
int bstree<T>::singleparentcount() const {
    std::stack<t_node> s;
    int sum = 0;

    for(auto i = root; i != nullptr or !s.empty();){
        if (i != nullptr){
            s.push(i);
            i = i->llink;
        }
        else{
            i = s.top();
            s.pop();

            if ((i ->rlink == nullptr) + (i->llink == nullptr) == 1)
                ++sum;
            i = i->rlink;
        }
    }
    return sum;
}

template<class T>
bool bstree<T>::secondary_delete(bstree::t_node &__Node) {
    t_node temp;
    if (__Node == nullptr)
        return false;
    else if (__Node->rlink == nullptr and __Node->llink == nullptr){
        temp = __Node;
        __Node = nullptr;
        delete temp;
    }
    else if (__Node->llink == nullptr) {
        temp = __Node;
        __Node = temp->rlink;
        delete  temp;
    }
    else if (__Node->rlink == nullptr){
        temp = __Node;
        __Node = temp->llink;
        delete temp;
    }
    else{
        t_node trail_current = nullptr;

        auto i = __Node->llink;
        for (;i->rlink != nullptr; i = i->rlink)
            trail_current = i;
        __Node->info = i->info;

        (trail_current == nullptr)?
                __Node->llink = i->llink:
                trail_current->rlink = i->llink;
    }

    return true;
}

template<class T>
bool bstree<T>::_delete(const T &value) {
    if (this->empty())
        return false;
    else{
        auto trail = parent(value);

        if (!trail.second) //Not found
            return false;

        if (trail.first == root)
            secondary_delete(this->root);
        else if (trail.first->info > value)
            secondary_delete(trail.first->llink);
        else
            secondary_delete(trail.first->rlink);
    }
    return true;
}


#endif //BST__BST_H
