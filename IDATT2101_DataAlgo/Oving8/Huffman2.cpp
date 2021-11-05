#include <iostream>
#include <string>
#include <fstream>
#include <cctype>
#include <vector>
#include <algorithm>

void debug(std::string tag)
{
    std::cout << "Debug: " << tag << std::endl;
}


typedef struct Node
{
    double freq;
    char data;
    struct Node *left, *right;
} Node;
void printNode(Node *n)
{
    std::cout << "_________Node_________" << std::endl;
    std::cout << "Data: " << n->data << std::endl;
    std::cout << "Freq: " << n->freq << std::endl;
    std::cout << "Left: " << n->left << std::endl;
    std::cout << "Right: " << n->right << std::endl;
    std::cout << "Address: " <<std::addressof(n)<<std::endl;
}
void printVector(std::vector<Node>* nodes)
{
    for (auto &node : *nodes)
    {
        printNode(&node);
    }
}
void printArr(int arr[], int n)
{
    int i;
    for (i = 0; i < n; ++i)
    {
        std::cout<< arr[i];
    }
 
    std::cout<<"\n";
}

void printTree(Node* root, int arr[], int top)
{
    //printNode(root);
    if(root->left)
    {
        arr[top] = 0;
        printTree(root->left,arr,top+1);
    }
    if(root->right)
    {
        arr[top] = 1;
        printTree(root->right,arr,top+1);    
    }
    if(!root->left && !root->right)
    {
        std::cout<<root->data<<": ";
        printArr(arr,top);
    }

}
Node *newNode(char data, double freq)
{
    Node *node = (Node *)malloc(sizeof(Node));
    node->data = data;
    node->freq = freq;
    node->left = node->right = NULL;
    return node;
}


Node *newParent(Node *left, Node *right)
{
    Node *node = (Node*)malloc(sizeof(Node));
    node->data = '$';
    node->freq = left->freq + right->freq;
    node->left = left;
    node->right = right;

    return node;
}

Node *getMinNode(std::vector<Node> *nodes)
{
    Node *node = &nodes->back();
    return node;
}

std::vector<Node>* sortVector(std::vector<Node> *nodes)
{
    sort(nodes->begin(), nodes->end(), [](Node a, Node b)
              { return a.freq > b.freq; });
    return nodes;
}

std::vector<Node> buildTree(std::vector<Node> *nodes)
{
    if (nodes->size()>1) 
    {
        Node *right = &nodes->back();   
        nodes->pop_back();
        Node *left = &nodes->back();
        nodes->pop_back();
        Node *parent = newParent(left, right);
        nodes->push_back(*parent);        
        sortVector(nodes);
        return buildTree(nodes);
    } else {
        //printVector(*nodes);
        return *nodes;
    }
    
}



//_______________________________________________________________________________________________________________________________________________________________________
int main()
{
    std::string text = "Test.txt";
    std::fstream f(text, std::ios::in);
    char c;
    int alphabet[256];
    double freq[256];
    size_t arrSize = sizeof(alphabet) / sizeof(alphabet[0]) + 1;
    double totalInputs = 0.0;
    for (size_t i = 0; i < arrSize; i++)
    {
        alphabet[i] = 0;
        freq[i] = 0.0;
    }

    if (f.is_open())
    {

        while (f.get(c))
        {
            // c = tolower(c);
            alphabet[(int)c]++;
            totalInputs++;
        }
        f.close();
    }

    for (size_t i = 0; i < arrSize - 1; i++)
    {
        freq[i] = alphabet[i] / totalInputs;
    }

    std::cout << totalInputs << " chars counted" << std::endl;

    std::vector<Node> nodes;
    Node *n[255];

    for (size_t i = 0; i < arrSize - 1; i++)
    {
        if (freq[i] != 0)
        {           
            n[i] = newNode((char)i, freq[i]);
            //printNode(n);
            nodes.push_back(*n[i]);
        }
    }
    printVector(&nodes);
    sort(nodes.begin(), nodes.end(), [](Node a, Node b)
         { return a.freq > b.freq; });
    // virker, henter de 2 minste
    nodes = buildTree(&nodes);
    int arr[100];
    int top = 0;
    
    std::cout<<"Vector address: "<<std::addressof(nodes)<<std::endl;
    //printNode(nodes.front().right);

    return 0;
}
