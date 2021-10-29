#include <iostream>
#include <string>
#include <fstream>
#include <cctype>
#include <vector>
#include <algorithm>

typedef struct Node
{
    double freq;
    char data;
    struct Node *left, *right;
} Node;

Node *newNode(char data, double freq)
{
    Node *node = new Node;
    node->data = data;
    node->freq = freq;
    node->left = node->right = NULL;
    return node;
}
Node *newParent(Node *left, Node *right)
{
    Node *node = new Node;
    node->data = ' ';
    node->freq = left->freq + right->freq;
    node->left = left;
    node->right = right;

    return node;
}

void buildTree()
{
    
}
void printNode(Node *n)
{
    std::cout << "_________Node_________" << std::endl;
    std::cout << "Data: " << n->data << std::endl;
    std::cout << "Freq: " << n->freq << std::endl;
    std::cout << "Left: " << n->left << std::endl;
    std::cout << "Right: " << n->right << std::endl;
}
void printVector(std::vector<Node> nodes)
{
    for (auto &node : nodes)
    {
        printNode(&node);
    }    
}



//_______________________________________________________________________________________________________________________________________________________________________
int main()
{

    std::string text = "diverse.pdf";
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
            //c = tolower(c);
            alphabet[(int)c]++;
            totalInputs++;
            
        }
        f.close();
    }

    for (size_t i = 0; i < arrSize-1; i++)
    {
        freq[i] = alphabet[i] / totalInputs;
    }

    std::cout << totalInputs << " chars counted" << std::endl;

    std::vector<Node> nodes;
    Node *n;
    for (size_t i = 0; i < arrSize - 1; i++)
    {
        if(freq[i] != 0)
        {
            n = newNode((char)i, freq[i]);
            nodes.push_back(*n);
        }
        
    }
    sort(nodes.begin(), nodes.end(),[](Node a, Node b) {
        return a.freq < b.freq;
    });
    
    //printVector(nodes);


    //virker, henter de 2 minste
    Node *parent = newParent(&nodes.at(0), &nodes.at(1));
    std::cout<<std::endl;
    std::cout<<"Parent"<<std::endl;
    printNode(parent);
    return 0;
}
