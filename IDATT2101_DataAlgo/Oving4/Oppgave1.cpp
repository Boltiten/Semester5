#include <iostream>
#include <stdio.h>
#include <stdlib.h>

typedef struct NodeStruct {
    double element;
    struct NodeStruct* neste;
} Node;

Node* nyNode(double e, Node* n){
    Node* res = (Node*)(malloc(sizeof(Node)));
    res->element = e;
    res->neste = n;
    return res;
}

typedef struct {
    Node* hode;
    int antElementer;
} EnkelLenke;

void settInnFremst(EnkelLenke* l, double verdi){
    Node* ny = nyNode(verdi,l->hode);
    l->hode = ny;
    l->antElementer++;
}

void settInnBakerst(EnkelLenke* l, double verdi){
    Node* ny = nyNode(verdi,NULL);
    if (l->hode){
        Node* denne = l->hode;
        while(denne->neste) denne = denne->neste;
    }else l->hode = ny;
    l->antElementer++;
}
Node* fjern(EnkelLenke* l, Node* n){
    Node* forrige = NULL;
    Node* denne = l->hode;
    while(denne&& denne != n){
        forrige = denne;
        denne = denne->neste;
    }
    if(denne){
        if(forrige) forrige->neste=denne->neste;
        else l->hode = denne->neste;
        l->antElementer--;
        return denne;
    }
    else return NULL;
}
Node* finnNr(EnkelLenke* l, int nr){
    if(nr<l->antElementer){
        Node*denne = l->hode;
        for(int i=0;i<nr;++i)denne=denne->neste;
        return denne;        
    }
    else return NULL;
}
void slettAlle(EnkelLenke* l){
    if(l->hode){
        Node* denne = l->hode;
        while (denne->neste){
            l->hode = denne->neste;
            free(denne);
            denne = l->hode;
        }
        free(denne);
        l->hode=NULL;
        l->antElementer=0;
    }
}

int main(){
    int num_soldiers = 10;
    int kill = 3;
    std::cout<<"Made variables"<<std::endl;
    EnkelLenke* soldiers;
    std::cout<<"Made list"<<std::endl;
    for (double i = 0; i < num_soldiers; i++)
    {
        settInnBakerst(soldiers,i);
        std::cout<<"Insert: " << i << std::endl;
    }    
    return 0;
}