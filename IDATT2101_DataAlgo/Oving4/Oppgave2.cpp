#include <iostream>
#include <fstream>
#include <string>
#include <cstring>
#include <vector>



typedef struct {
    void** tab;
    int antall, max;
} Stack;
Stack *newStack(int str){
    Stack* s = (Stack*)(malloc(sizeof(Stack)));
    s->tab = (void**)(malloc(str* sizeof(void*)));
    s->antall = 0;
    s->max = str;
    return s;
}

bool emptyStack(Stack* s){
    return !s->antall;
}
bool fullStack(Stack* s){
    return s->antall == s->max;
}
void push(Stack* s, void* e){
    if(!fullStack(s)){
        s->tab[s->antall++] = e;
    }
}
void* pop(Stack* s){
    if(emptyStack(s)) return NULL;
    return s->tab[--s->antall];
}
void* checkStack(Stack* s){
    if(emptyStack(s)) return NULL;
    return s->tab[s->antall-1];
}

bool starters(char ch){
    if(ch == '(' ||
    ch == '{' ||
    ch == '['
    ) return true;   
    return false;
}
bool enders(char ch){
    if(ch == ')' ||
    ch == '}' ||
    ch == ']'
    ) return true;
    
    return false;
}
bool match(char starter, char ender){
    if(starter == '(' && ender == ')'){
        return true;
    } else if(starter=='[' && ender ==']'){
        return true;
    } else if(starter=='{' && ender =='}'){
        return true;
    }
    return false;
}

int main(){
    //File
    std::ifstream file;
    std::string filename = "Oppgave2TestProgram.cpp";
    file.open(filename);

    //file vars
    std::vector<char> chars;
    char ch;


    //stack
    int stackSize = 0;
    Stack* s;
    if(file.is_open())
    {
        while (file.get(ch)){
            chars.push_back(ch);
        }
        for (const auto &ch : chars)
        {
            if(starters(ch) || enders(ch))
            {
                stackSize++;
            }
            
        }
        s = newStack(stackSize);
        std::cout<<"Stack Size: "<<stackSize<<std::endl;
        for (const auto ch : chars)
        {
            if(starters(ch)){
                push(s, (void*)&ch);
            } else if(enders(ch)){                
                push(s, (void*)&ch);
            }

        }
        for (size_t i = 0; i < stackSize; i++)
        {
            std::cout<<checkStack(s)<<std::endl;
            pop(s);
        }
        
        file.close();
    } else std::cout<<"Couldn't open file.";
    return 0;
}