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
typedef struct MinHeap
{
    int size;
    int capacity;
    struct Node** array;
} MinHeap;

Node *newNode(char data, double freq)
{
    Node *node = (Node*)malloc(sizeof(Node));
    node->data = data;
    node->freq = freq;
    node->left = node->right = NULL;
    return node;
}

MinHeap* newMinHeap(int capacity)
{
    MinHeap* minHeap = (MinHeap*)malloc(sizeof(MinHeap));

    minHeap->size = 0;
    minHeap->capacity = capacity;
    minHeap->array = (Node**)malloc(minHeap->capacity*sizeof(Node*));

    return minHeap;
}

void swapMinHeapNode(Node** a, Node** b)
{
    Node* tmp = *a;
    *a = *b;
    *b = tmp;
}

void minHeapify(MinHeap* minHeap, int index)
{
    int smallest = index;
    int left = 2*index+1;
    int right = 2*index+2;

    if (left < minHeap->size && minHeap->array[left]->freq < minHeap->array[smallest]->freq)
        smallest = left;
 
    if (right < minHeap->size && minHeap->array[right]->freq < minHeap->array[smallest]->freq)
        smallest = right;
 
    if (smallest != index) {
        swapMinHeapNode(&minHeap->array[smallest], &minHeap->array[index]);
        minHeapify(minHeap, smallest);
    }
}

bool isSizeOne(MinHeap* minHeap)
{
    return (minHeap->size == 1);
}

Node* extractMin( MinHeap* minHeap) 
{
 
    Node* temp = minHeap->array[0];
    minHeap->array[0] = minHeap->array[minHeap->size - 1];
 
    --minHeap->size;
    minHeapify(minHeap, 0);
 
    return temp;
}
void insertMinHeap( MinHeap* minHeap, Node* minHeapNode)
{
 
    ++minHeap->size;
    int i = minHeap->size - 1;
 
    while (i && minHeapNode->freq < minHeap->array[(i - 1) / 2]->freq) {
 
        minHeap->array[i] = minHeap->array[(i - 1) / 2];
        i = (i - 1) / 2;
    }
 
    minHeap->array[i] = minHeapNode;
}

void buildMinHeap(MinHeap* minHeap)
{
 
    int n = minHeap->size - 1;
    int i;
 
    for (i = (n - 1) / 2; i >= 0; --i)
        minHeapify(minHeap, i);
}

bool isEndNode(Node* node)
{
    return !(node->left) && !(node->right);
}

MinHeap* createMinHeap(int data[], double freq[], int size)
{
    MinHeap* minHeap = newMinHeap(size);
    for (size_t i = 0; i < size; ++i)
    {
        minHeap->array[i] = newNode((char)data[i], freq[i]);
    }
    minHeap->size = size;
    buildMinHeap(minHeap);

    return minHeap;
}

Node* buildHuffmanTree(int data[], double freq[], int size)
{
    Node *left, *right, *top;
    MinHeap* minHeap = createMinHeap(data, freq, size);

    while(!isSizeOne(minHeap))
    {
        left = extractMin(minHeap);
        right = extractMin(minHeap);

        top = newNode('$', left->freq + right->freq);
        top->left = left;
        top->right = right;

        insertMinHeap(minHeap,top);
    }
    return extractMin(minHeap);
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

void printCodes(Node* root, int arr[], int top)
{
    if(root->left)
    {
        arr[top] = 0;
        printCodes(root->left, arr, top+1);
    }
    if(root->right)
    {
        arr[top] = 1;
        printCodes(root->right, arr, top+1);
    }
    if(isEndNode(root))
    {
        std::cout<<root->data<<": ";
        printArr(arr, top);
    }
}
void HuffmanCodes(int data[], double freq[], int size)
{
    Node* root = buildHuffmanTree(data, freq, size);

    int arr[100], top = 0;
    printCodes(root,arr,top);
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

    HuffmanCodes(alphabet, freq, arrSize-1);

    
    return 0;
}
