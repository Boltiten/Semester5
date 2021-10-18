#include <iostream>
#include <string>
#include <fstream>
#include <cctype>
#include <vector>

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
void printNode(Node *n)
{
    std::cout << "_________Node_________"<< std::endl;
    std::cout << "Data: " << n->data << std::endl;
    std::cout << "Freq: " << n->freq << std::endl;
    std::cout << "Left: " << n->left << std::endl;
    std::cout << "Right: " << n->right << std::endl;
}




//_______________________________________________________________________________________________________________________________________________________________________
int main()
{

    std::string text = "text.txt";
    std::fstream f(text, std::ios::in);
    char c;
    int alphabet[28];
    double freq[28];
    size_t arrSize = sizeof(alphabet)/sizeof(alphabet[0]) +1;
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
            c = tolower(c);
            alphabet[(int)c - 'a']++;
            // space
            if ((int)c == 32)
                alphabet[26]++;
            // new line
            if ((int)c == 10)
                alphabet[27]++;
        }
        f.close();
    }
    for (size_t i = 0; i < arrSize; i++)
    {
        totalInputs += alphabet[i];
    }
    for (size_t i = 0; i < arrSize; i++)
    {
        freq[i] = alphabet[i] / totalInputs;
    }

    std::cout << totalInputs << " chars counted" << std::endl;

    std::vector<Node> nodes;
    Node *n;
    for (size_t i = 0; i < arrSize-1; i++)
    {
        if(i<26)n = newNode((char)(i + 'a'), freq[i]);
        else if(i==26)n = newNode((char)(32), freq[i]);
        else if(i==27)n = newNode((char)(10), freq[i]);
        nodes.push_back(*n);
        printNode(n);        
    }
    return 0;
}