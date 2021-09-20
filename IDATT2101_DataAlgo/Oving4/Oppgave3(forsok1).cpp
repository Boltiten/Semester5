#include <iostream>
#include <stdlib.h>
#include <stack>

typedef struct TreeNode 
{
    char info;
    TreeNode *left, *right;
} TreeNode;

typedef struct TreeNode* ExpTree;

//tree
ExpTree newNode(int info)
{
    TreeNode* temp;
    temp = (TreeNode*)malloc(sizeof(TreeNode));
    if(temp==NULL){
        std::cout<<"no space! \n";
        return temp;
    }
    temp->left=NULL;
    temp->right=NULL;
    temp->info=info;
    return temp;
}
ExpTree buildTree(ExpTree tree, char postfix[])
{
    int i = 0;
    std::stack<TreeNode*> st;
    TreeNode* temp_tree1;
    TreeNode* temp_tree2;
    while (postfix[i] != '\0')
    {
        if(!isOperator(postfix[i]))
        {
            tree = newNode(postfix[i]);
            st.push(tree);
        }
        else
        {
            tree = newNode(postfix[i]);
            temp_tree1 = st.top();
            st.pop();
            temp_tree2 = st.top();
            st.pop();
            tree->right = temp_tree1;
            tree->left = temp_tree2;
            st.push(tree);
        }
        i++;
    }
    return tree;
}

int getPriority (char ch);
void ConvertInToPost(std::string infix, char postfix[]);

//extra
void resultExpression(char postfix[]);
int height(ExpTree T);
int size(ExpTree node);

//output
void showNode(ExpTree T);
void preorder(ExpTree T);
void postorder(ExpTree T);
void inorder(ExpTree T);
void printExtra(char postfix[], ExpTree T);
void display(ExpTree tree, char postfix[]);
void line();

//input validation
bool isExpCorrect(std::string infix)
{
    for (unsigned int i = 0; i < infix.length(); i++) {
		if (!isDigit(infix[i]) && !isOperator(infix[i]) && infix[i] != '(' && infix[i] != ')')
			return false;
	}
	return true;
}
bool isOperator(char ch)
{
    if (ch == '+' || ch == '-' || ch == '*' || ch == '/' || ch == '%' || ch == '^'){
        return true;
    }
    return false;
}
bool isDigit(char ch)
{
    if(ch>47 && ch <57)return true;
    return false;
}

int main()
{
    return 0;
}