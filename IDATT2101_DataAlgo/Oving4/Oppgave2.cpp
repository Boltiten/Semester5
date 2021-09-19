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

    //husk å lukke
    if(file.is_open())
    {
        //les chars fra programmet inn i en vector med char, kunne kanskje lest det rett inn i stacken? men har ikke blitt sånn nå. 
        //Måtte vite hvor stor stacken skulle være, så må finne alle tegna som skal inn først
        //Er heller ikke helt vant til c++, og void* var vanskelig å jobbe med, førte til mye strev.
        //Håper dette er en OK løsning, vet ikke om det var heeelt det som var planen eller ikke.7
        while (file.get(ch)){
            chars.push_back(ch);
        }
        //finner størrelse på stacken
        for (const auto &ch : chars)
        {
            if(starters(ch) || enders(ch))
            {
                stackSize++;
            }            
        }
        //oppretter stacken
        s = newStack(stackSize);
        std::cout<<"Stack Size: "<<s->max<<std::endl;

        //putter tegn i stacken
        for (const auto &ch : chars)
        {
            if(starters(ch)){
                push(s, (void*)&ch);
            } else if(enders(ch)){
                push(s, (void*)&ch);
                //sjekke om tegnet matcher starteren som ligger øverst i stacken
                //Bygg en error om det ikke er match.
            }
        }
        for (size_t i = 0; i < stackSize; i++)
        {
            //hvis error, print den før stacken
            //hvis ingen error, print det før stacken
            std::cout<<((char*)checkStack(s))[0];
            pop(s);
 
        }
        std::cout<<std::endl;
        std::cout<<"Stack Size: "<<s->antall<<std::endl;
        //lukk filen
        file.close();
    } else std::cout<<"Couldn't open file.";
    return 0;
}