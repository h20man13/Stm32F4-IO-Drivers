#include "linkedList.h"

template <class L> struct linkedList<L>::Node{
    L* data;
    Node* next;
};

template <class L> void linkedList<L>::add(L Data){
    Node* temp = root;
    while(temp -> next != (Node*)0){
        temp = temp -> next;
    }
    temp -> next = new Node;
    (temp -> next) -> data = Data;
    (temp -> next).next = (Node*)0;
}

template <class L> void linkedList<L>::remove(L data){
    Node* temp = root;
    if(root != (Node*)0)
    {
        while(temp -> next != (Node*)0){
            if((temp -> next).data == data)
            {
                Node* save = temp -> next;
                temp -> next = save -> next;
                delete save;
                break;
            }
            temp = temp -> next;
        }
    }
}

template <class L> void linkedList<L>::list_func(void (*func)(L)){
    Node* temp = root;
    while(temp -> next != (Node*)0){
        (*func)(temp -> data);
    }
}

