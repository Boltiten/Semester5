#include <iostream>

struct Node{
    int data;
    struct Node *next;
};

//Linker til seg selv
struct Node *insertInEmpty(struct Node *last, int new_data)
{
    if(last != NULL)return last;
    struct Node *temp = new Node;

    temp->data = new_data;
    last = temp;
    last->next = last;

    return last;
}

Node *insertAtBegin(Node *last, int new_data){
    if(last==NULL)return insertInEmpty(last, new_data);
    struct Node *temp = new Node;
    temp->data = new_data;
    temp->next = last->next;
    last->next=temp;

    return last;
}

struct Node *insertAtEnd(struct Node *last, int new_data){
    if(last==NULL)return insertInEmpty(last, new_data);

    struct Node *temp = new Node;
    temp->data = new_data;
    temp->next = last->next;
    last->next = temp;
    last=temp;

    return last;
}

void traverseList(struct Node *last){
    struct Node *p;
    if(last == NULL){
        std::cout<<"List is empty"<<std::endl;
        return;
    }
    p = last->next;
    do {
        std::cout<<p->data<<"==>";
        p = p->next;
    } while (p!=last->next);
    std::cout<<p->data;
    std::cout<<"\n\n";
}

void deleteNode(Node**head, int key){
    if(*head == NULL)return;
    if((*head)->data==key && (*head)->next==*head){
        free(*head);
        *head=NULL;
    }
    Node *last=*head,*d;
    if((*head)->data==key){
        while(last->next !=*head)last=last->next;
        last->next=(*head)->next;
        free(*head);
        *head=last->next;
    }

    while(last->next !=*head && last->next->data != key){
        last=last->next;
    }
    if(last->next->data == key){
        d=last->next;
        last->next = d->next;
        std::cout<<"The Node with data " << key << " deleted from list" << std::endl;
        free(d);
        std::cout<<std::endl;
        std::cout<<"Circular linked list after deleting "<<key<<" is as follows:"<<std::endl;
        traverseList(last);
    } else std::cout<<"Couldnt find node with data "<< key << " in list"<<std::endl;
}

int main(){
    int num_soldiers = 10;
    int skip = 4;
    int killSoldier = skip;

    struct Node *soldiers = NULL;

    for (size_t i = 0; i < num_soldiers; i++)
    {
        soldiers = insertAtEnd(soldiers,i);
    }    
    traverseList(soldiers);
    for (size_t i = 0; i < num_soldiers-1; i++)
    {
        deleteNode(&soldiers, killSoldier);
        killSoldier = (killSoldier+skip)%num_soldiers;
    }
    
    
    return 0;
}