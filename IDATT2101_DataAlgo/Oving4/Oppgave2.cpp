#include <iostream>
#include <fstream>
#include <string>
#include <cstring>
#include <vector>

typedef struct
{
    void **tab;
    int antall, max;
} Stack;
Stack *newStack(int str)
{
    Stack *s = (Stack *)(malloc(sizeof(Stack)));
    s->tab = (void **)(malloc(str * sizeof(void *)));
    s->antall = 0;
    s->max = str;
    return s;
}

bool emptyStack(Stack *s)
{
    return !s->antall;
}
bool fullStack(Stack *s)
{
    return s->antall == s->max;
}
void push(Stack *s, void *e)
{
    if (!fullStack(s))
    {
        s->tab[s->antall++] = e;
    }
}
void *pop(Stack *s)
{
    if (emptyStack(s))
        return NULL;
    return s->tab[--s->antall];
}
void *checkStack(Stack *s)
{
    if (emptyStack(s))
        return NULL;
    return s->tab[s->antall - 1];
}

bool starters(char ch)
{
    if (ch == '(' ||
        ch == '{' ||
        ch == '[')
        return true;
    return false;
}
bool enders(char ch)
{
    if (ch == ')' ||
        ch == '}' ||
        ch == ']')
        return true;

    return false;
}
bool match(char starter, char ender)
{
    if (starter == '(' && ender == ')')
    {
        return true;
    }
    else if (starter == '[' && ender == ']')
    {
        return true;
    }
    else if (starter == '{' && ender == '}')
    {
        return true;
    }
    return false;
}

int main()
{
    //File
    std::ifstream file;
    std::string filename = "Oppgave1.cpp";
    file.open(filename);

    //file vars
    std::vector<char> chars;
    char ch;

    //stack
    int stackSize = 0;
    Stack *s;

    //husk å lukke
    if (file.is_open())
    {
        //les chars fra programmet inn i en vector med char, kunne kanskje lest det rett inn i stacken? men har ikke blitt sånn nå.
        //Måtte vite hvor stor stacken skulle være, så må finne alle tegna som skal inn først
        //Er heller ikke helt vant til c++, og void* var vanskelig å jobbe med, førte til mye strev.
        //Håper dette er en OK løsning, vet ikke om det var heeelt det som var planen eller ikke.
        //Var spesielt å hente ting fra stacken som var et slit å finne ut av, men har noe mer forståelse nå da.
        //Den bruker ihvertfall stacken på en nyttig måte!
        //Såklart et par åpenbare errors er om du har strings eller kommentarer med tegnene i, det vil ikke fungere.
        while (file.get(ch))
        {
            chars.push_back(ch);
        }
        //finner størrelse på stacken
        for (const auto &ch : chars)
        {
            if (starters(ch) || enders(ch))
            {
                stackSize++;
            }
        }
        //oppretter stacken
        s = newStack(stackSize);
        std::cout << "Stack Size: " << s->max << std::endl;

        //putter tegn i stacken
        std::string stackString;
        for (const auto &ch : chars)
        {
            if (starters(ch))
            {
                push(s, (void *)&ch);
                stackString += ((char *)checkStack(s))[0];
                
            }
            else if (enders(ch))
            {
                //sjekker match
                if (match(((char *)checkStack(s))[0], ch))
                {
                    push(s, (void *)&ch);
                    stackString += ((char *)checkStack(s))[0];

                    //fjerner matcher fra stacken
                    pop(s);
                    pop(s);
                    stackSize -= 2;
                }
                else
                {
                    push(s, (void *)&ch);
                    stackString += ((char *)checkStack(s))[0];
                };
            }
        }
        std::cout<<stackString<<std::endl;
        std::cout << "Stack Size: " << s->antall << std::endl;
        std::string er;
        //Hvis det fortsatt er noe igjen i stacken, så ble ikke tegnene oppløst, da er det nøsting feil.
        if (stackSize != 0)
        {
            for (size_t i = 0; i < stackSize; i++)
            {
                er = ((char *)checkStack(s))[0] + er;
                pop(s);
            }
            //print tegnene som er igjen
            std::cout<<er<<std::endl;
            std::cout << "Det ble ikke fullstendig match, det er en error her" << std::endl;
        } else std::cout << "Alle tegnene løste seg";            

        //lukk filen
        file.close();
    }
    else
        std::cout << "Couldn't open file.";
    return 0;
}