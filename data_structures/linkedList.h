#include <stdint.h>

template <typename L>
class linkedList{
    public:
    void add(L*);
    void remove(L*);
    void list_func(void(*)(L*));
    private:
    struct Node;
    Node* root = (Node*)0;
};