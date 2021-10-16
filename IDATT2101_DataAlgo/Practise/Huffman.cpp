#include <iostream>
#include <string>
#include <queue>
#include <vector>

typedef struct HuffmanNode 
{
    char data;
    unsigned freq;
    Node *left, *right;

    Node(char data, unsigned freq)
    {
        left = right = NULL;
        this->data = data;
        this->freq = freq;
    }
}Node;
struct compare 
{
    bool operator()(Node* left, Node *right)
    {
        return(left->freq>right->freq);
    }
};
class Tree
{
public:
    
    void printID(Node* root, std::string str)
    {
        if(!root) return;
        if(root->data != '$') std::cout<<root->data<<": "<<str<<"\n";
        printID(root->left, str + "0");
        printID(root->right, str + "1");
    }
    Tree(char data[], int freq[], int size)
    {
        Node *left, *right, *top;
        std::priority_queue<Node*, std::vector<Node*>, compare> twig;

        for (int i = 0; i < size; ++i)
        {
            twig.push(new Node(data[i],freq[i]));
        }

        while(twig.size() != 1)
        {
            left = twig.top();
            twig.pop();
            right = twig.top();
            twig.pop();


            top = new Node('$', left->freq + right->freq);
            top->left = left;
            top->right = right;
            twig.push(top);
        }
        printID(twig.top(), "");
    }
};



int main(){
    char arr[] = { 'a', 'b', 'c', 'd', 'e', 'f' };
    int freq[] = { 5, 9, 12, 13, 16, 45 };
 
    int size = sizeof(arr) / sizeof(arr[0]);
 
    Tree t = Tree(arr, freq, size);
 
    return 0;
}