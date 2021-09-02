#include <iostream>
#include <string>
#include <chrono>
#include <cstdlib>
#include <time.h>
#include <vector>

int main()
{
    //putte randomme tall fra -10 til 10 i en array, skulle jobbet med vector, men akk ble array nå..

    //random seed om vi vil teste tilfeldige seeds. Vanskelig å sjekke resultater med random
    /* srand(time(NULL));
    
    signed char kursforandring[1000000];
    int arrSize = sizeof(kursforandring) / sizeof(kursforandring[0]);
    for (size_t i = 0; i < arrSize; i++)
    {
        kursforandring[i] = (rand() % 21) - 10;
    }
    double kurs[1000000]; */

    //Om du vil bruke den oppgitte tabellen

    signed char kursforandring[] = {-1,3,-9,2,2,-1,2,-1,-5};
    double kurs[9];
    int arrSize = sizeof(kursforandring)/sizeof(kursforandring[0]);

    //Printer kjøp på dagene 1,3,6 og salg på 2,5,7

    //Ta tid herifra
    std::chrono::steady_clock::time_point begin = std::chrono::steady_clock::now();
    double tmpBottom = 100;
    double bottom = -1;
    double tmpTop = 0;
    double top = 1;
    int kjop, salg;
    /**
     * Ble ikke super pent siden alt ble bassert på forrige innlevering.
     * Synest oppgaven var altfor dårlig forklart og åpen til tolkning,
     * det er litt ukult etter at vi har så lite tid på å fikse den etter misstolkning.
     * MEN, dette skal fungere og skal gjøre
     * */


    //Bruker denne for å oversikt på kursen, ble lettere å tenke da.
    for (size_t i = 0; i < arrSize; i++)
    {
        if (i == 0)
        {
            kurs[0] = 100;
        }
        else if (i != 0)
        {
            kurs[i] = kurs[i - 1] + (kurs[i - 1] * kursforandring[i] / 100);
        }
    }


    //Sammenligner lave punkter mot høye punkter, setter Top og Bottom til den største forsjellen vi finner.
    //Kunne blitt gjort mer optimalt med å bare sjekke punktene hvor det snur. kanskje noe lagring av verdier som er værdt å sjekke.
    for (int i = 0; i < arrSize; i++)
    {
        if (kurs[i] < tmpBottom && !(i > arrSize - 1))
        {
            tmpBottom = kurs[i];
            tmpTop = 0;
            //sjekk mot de høyere kursene etter denne dagen
            for (int j = i + 1; j < arrSize; j++)
            {
                if (kurs[j]> kurs[i])
                {
                    tmpTop = kurs[j];
                    //sjekk nye top/bunn med beste top/bunn
                    if(top/bottom < tmpTop/tmpBottom){
                            top=tmpTop;
                            bottom=tmpBottom;
                            kjop = i;
                            salg = j;
                    }

                }
            }
        }
    }
    std::chrono::steady_clock::time_point end = std::chrono::steady_clock::now();
    std::cout << "Tid brukt: " << std::chrono::duration_cast<std::chrono::nanoseconds>(end - begin).count() << "[ns]" << std::endl;
    std::cout << "Kjøps dag: " << kjop + 1 << std::endl;
    std::cout << "Salgs dag: " << salg + 1 << std::endl;
    //sjekke kurs på kjøp og salgsdagene
    std::cout << "Kurs Kjøps dag: " << kurs[kjop] << std::endl;
    std::cout << "Kurs Salgs dag: " << kurs[salg] << std::endl;

    return 0;
}