#include <iostream>

struct Node
{
    int data;
    struct Node *next;
};

//Linker til seg selv
Node *newNode(int data)
{
    Node *node = new Node;
    node->data = data;
    node->next = NULL;

    return node;
}
Node *createList(int size)
{
    Node *head = NULL;
    Node *node = NULL;
    Node *nextNode = NULL;

    for (size_t i = 0; i < size; i++)
    {
        if (i > 0)
        {
            node = newNode(size - i + 1);
            node->next = nextNode;
            nextNode = node;
        }
        else
        {
            head = newNode(1);
            head->next = head;
            nextNode = head;
        }
    }
    head->next = node;
    return head;
}

void deleteNode(Node *kill)
{
    Node *prev = NULL;
    Node *temp = kill;
    while (kill->next != temp)
    {
        kill = kill->next;
    }
    prev = kill;
    prev->next = temp->next;
    //delete(kill);
}

void printList(Node *head)
{
    Node *end = head;
    std::cout << "Print List:" << std::endl;
    do
    {
        std::cout << head->data << " ";
        head = head->next;
    } while (head != end);
    std::cout << std::endl;
}

int josephusCircle(Node *head, int skip)
{
    if (head == head->next)
    {
        std::cout << "Return: " << head->data << std::endl;
        return head->data;
    }
    else
    {
        for (size_t i = 1; i < skip; i++)
        {
            head = head->next;
        }
        Node *kill = head;
        head = kill->next;
        std::cout << "Kill: " << kill->data << "\n";
        deleteNode(kill);
        //printList(head);
        return josephusCircle(head, skip);
    }
}

int main()
{
    int num_soldiers = 10;
    int skip = 4;
    int killSoldier = skip;
    Node *list = createList(num_soldiers);

    printList(list);
    int survivor = josephusCircle(list, skip);
    std::cout << "Survivor: " << survivor << std::endl;

    return 0;
}