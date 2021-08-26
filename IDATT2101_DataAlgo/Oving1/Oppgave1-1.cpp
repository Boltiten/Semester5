#include <iostream>
#include <vector>

int main(){
    /* int kursforandring[] = {-1, 3,-9,2,2,-1,2,-1,-2,-1, -5, 6};
    int arrSize = sizeof(kursforandring)/sizeof(kursforandring[0]);
    std::cout<<"ArrSize: "<< arrSize << std::endl;

    //initialiserer kjøp og salgdag
    int kjopDag = -1;
    int selgDag = -1;

    for (size_t i = 0; i < arrSize; i++)
    {
        //Setter en kjøp dag
        if(i<arrSize //ikke siste dag
        && kursforandring[i]<0 //kursforandringen må være negativ
        && kursforandring[i+1]>0) //kursen må stige dagen etter
        {
            kjopDag = i;
            std::cout<<"kjøp dag: "<< kjopDag << std::endl;
        }

        //Setter en salg dag
        if(kjopDag != -1 //Sjekker at man har kjøpt
        && kjopDag < i //Sjekker at dagen man kjøpte på er en tidligere dag
        && kursforandring[i]>0 //Sjekker at kursen er postitiv i dag
        && kursforandring[i+1]<0) //Sjekker at kursen går ned i morgen
        {
            selgDag = i;
            std::cout<<"selg dag: "<< selgDag << std::endl;
        }

        //stygg bug fix for om siste dagen er positiv, så den selger da, siden i+1 er aldri over 0 om i+1 ikke finnes
        if(i+1 == arrSize 
        && kursforandring[i]>0){
            selgDag = i;
            std::cout<<"selg dag: "<< selgDag << std::endl;
        }
    } */

    std::vector<int> kursforandringVector;
    for (size_t i = 0; i < 10; i++)
    {
        int add = (rand()%21) -10;
            std::cout<<add << std::endl;

    }
    

    

    return 0;
}