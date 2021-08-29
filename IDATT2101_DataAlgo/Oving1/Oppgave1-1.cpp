#include <iostream>
#include <string>
#include <chrono>
#include <cstdlib>
#include <time.h>

enum Handling {
    INGEN,
    KJOP,
    SALG
};

Handling SISTHANDLING = Handling::INGEN;

int main(){
    //putte randomme tall fra -10 til 10 i en array, skulle jobbet med vector, men akk ble array nå..
    srand(time(NULL));
    signed char kursforandring[10000]; 
    int arrSize = sizeof(kursforandring)/sizeof(kursforandring[0]);
    for (size_t i = 0; i < arrSize; i++)
    {
        kursforandring[i] = (rand()%21) -10;
    }

    //Om du vil bruke den oppgitte tabellen
    //signed char kursforandring[] = {-1,3,-9,2,2,-1,2,-1,-5};
    //int arrSize = sizeof(kursforandring)/sizeof(kursforandring[0]);
    //Printer kjøp på dagene 1,3,6 og salg på 2,5,7


    //Ta tid herifra
    std::chrono::steady_clock::time_point begin = std::chrono::steady_clock::now();

    //initialiserer kjøp og salgdag
    int kjopDag = -1;
    int selgDag = -1;
    int tmp = 0;
    std::string handlinger;

    /**
     * Så denne koden funker slik:
     * Hvis kursforandringen er noe annet enn 0, så setter vi den til tmp.
     * Der etter har vi en sjekk hva siste handlingen er
     * Hvis det ikke er et kjøp så kan vi kjøpe. Altså etter salg eller før vi har gjort noen handling.
     * Hvis vi har kjøpt, så kan vi selge.
     * Inne i disse sjekkene så ser vi om tmp er positiv eller negativ.
     * Hvis vi har solgt så kjører kjøp sjekken. Den ser etter neste positive forandring, for da er aksjen på bunn.
     * Motsatt når vi selger, den sjekker etter når aksjen vil gå negativ, da vil den selge, og den vil alltid ha kjøpt for å nå hit.
     * (Unntak om første forandring er positiv eller 0)
     * */
    for (size_t i = 0; i < arrSize; i++)
    {
        if(kursforandring[i] != 0){
            tmp = kursforandring[i];
        }

        //kan kjøpe enten når ingen handling er gjort eller når man har solgt.
        if(SISTHANDLING != Handling::KJOP){
            if(i+1<arrSize
            && tmp<0 
            && kursforandring[i+1]>0){
                handlinger += "Kjøp dag: " + std::to_string(i+1) + ".\n";
                SISTHANDLING = Handling::KJOP;
            }
        }
        //kan selge når sist handling er et kjøp
        if(SISTHANDLING == Handling::KJOP){
            if(i+1<arrSize
            && tmp>0 
            && kursforandring[i+1]<0){
                handlinger += "Salg dag: " + std::to_string(i+1) + ".\n";
                SISTHANDLING = Handling::SALG;
            } else if (i+1 == arrSize 
            && tmp>0) {
                handlinger += "Salg dag: " + std::to_string(i+1) + ".\n";
                SISTHANDLING = Handling::SALG;
            }
        }
    }

    //Ta tid til hit
    std::chrono::steady_clock::time_point end = std::chrono::steady_clock::now();
    //Skriver ut kjøps og salg dager
    std::cout<<handlinger<<std::endl;

    //farten på denne burde være O(n), siden vi bare kjører 1 forloop. 
    //Omega(n) blir også laveste mulige fordi vi kjører igjennom hele arrayet en gang uansett om vi utfører noe logikk.
    //Skriv ut tid
    std::cout << "Time difference = " << std::chrono::duration_cast<std::chrono::nanoseconds> (end - begin).count() << "[ns]" << std::endl;
    return 0;
}