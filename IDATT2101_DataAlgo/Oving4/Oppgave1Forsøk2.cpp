#include <iostream>

struct Node{
    int data;
    struct Node* next;
};

//Linker til seg selv
Node *newNode(int data)
{
    Node* node = new Node;
    node->data = data;
    node->next = NULL;

    return node;
}

int aliveSoldier(int Num){
    if (Num == 1) return 1;
    Node* last = newNode(1);
    last->next = last;

    for (size_t i = 2; i < Num; i++)
    {
        Node* temp = newNode(i);
        temp->next = last->next;
        last->next = temp;
        last = temp;
    }
    Node *curr= last->next;
    Node *temp;
    while(curr->next != curr){
        temp = curr;
        curr = curr->next;
        temp->next = curr->next;

        delete curr;
        temp = temp->next;
        curr = temp;
    }
    int res = temp->data;
    delete temp;

    return res;
    
}




int main(){
    int num_soldiers = 10;
    int skip = 4;
    int killSoldier = skip;

    std::cout<<aliveSoldier(num_soldiers)<<std::endl;

    
    
    return 0;
}