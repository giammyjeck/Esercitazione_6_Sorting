#include<chrono>
#include<iostream>
#include<unistd.h>
#include<vector>
#include<numeric>
#include<sstream>
#include"SortingAlgorithm.hpp"
#include<algorithm> //generate (lambdafunction)

using namespace std;


/// Il programma prende la dimensione in input da command line, setta una variabile di perturbazione,
/// il numero di componenti perturbate cresce nel tempo, si parte da vettori con nessuna componente perturbata (vettore completamente ordinato)
/// e si arriva ad un vettore completamente perturbato (le comp. pert. sono tutte vicine)
/// esegue un "TEST": costruisce 1000 vettori ordinati con la corrispondente percentuale di componenti perturbate
/// e applica per ognuno dei 1000 vettori sia MergeSort che BubbleSort (per ognuno dei 1000 vettori entrambi gli algoritmi vengono applicati 100 volte)
/// memorizzo i tempi in due variabili
/// calcola poi i tempi medi.

/// configurazione 1
/// media singolo vettore m = 100
/// media vettori stessa perturbazione p = 100


/// configurazione 2
/// media singolo vettore m = 10
/// media vettori stessa perturbazione p = 100



int main(int argc, char ** argv)
{

    //variabili di configurazione
    unsigned int m = 10;
    unsigned int p = 1000 ;



    // elaboro la dimensione scelta dall'utente
    stringstream converter;
    size_t dimv;
    converter << argv[1];
    converter >> dimv;
    cout << "dimv: " << dimv << endl;
    //  a questo punto dimv contiene la dimensione dei vettori su cui testo gli algoritmi


    // "perturbazione" indica di volta in volta il numero di componenti del vettore da perturbare
    for (unsigned int perturbazione = 0; perturbazione <= dimv; perturbazione = perturbazione + dimv*(0.1))
    {


        double sommaBubble = 0;
        double sommaMerge = 0;

        for (unsigned int ciclo = 0; ciclo < p; ciclo++) // m è il numero di test che faccio per tipo di vettore
        {
            vector<int> vOrigin(dimv);
            unsigned int n = rand() % 100;
            iota(vOrigin.begin(),vOrigin.end(),n); // genero un vettore ordinato partendo da un numero intero casuale

            // perturbo eventualmente un numero '#perturbazione' di componenti
            for (unsigned int i = 0; i < perturbazione; i++)
            {
                vOrigin[i] = rand() % 100;
            }


            vector<int> vBubble(dimv);
            vBubble = vOrigin;

            vector<int> vMerge(dimv);
            vMerge = vOrigin;

            double sommaMerge100 = 0;
            for (unsigned t = 0; t<m; t++)
            {
            // tempi mergeSort
                chrono::steady_clock::time_point t_begin2 =  chrono::steady_clock::now();
                SortLibrary::MergeSort(vMerge);
                chrono::steady_clock::time_point t_end2 = chrono::steady_clock::now();
                vMerge= vOrigin;
                double timeElapsed2 = chrono::duration_cast<chrono::nanoseconds> (t_end2 - t_begin2).count();
                sommaMerge100 = sommaMerge100 + timeElapsed2;
            }
            double MergeT = sommaMerge100/m;


            double sommaBubble100 = 0;
            for (unsigned t = 0; t<m; t++)
            {
            // tempi bubbleSort
                chrono::steady_clock::time_point t_begin =  chrono::steady_clock::now();
                SortLibrary::BubbleSort(vBubble);
                chrono::steady_clock::time_point t_end = chrono::steady_clock::now();
                vBubble = vOrigin;
                double timeElapsed = chrono::duration_cast<chrono::nanoseconds> (t_end - t_begin).count();
                sommaBubble100 = sommaBubble100 + timeElapsed;
            }
            double BubbleT = sommaBubble100/m;

            sommaMerge = sommaMerge + MergeT;
            sommaBubble = sommaBubble + BubbleT;
        }

        double mediaMerge = sommaMerge/p;
        double mediaBubble = sommaBubble/p;

        if (mediaMerge < mediaBubble)
        {
            cout <<"comp perturbate: "<< perturbazione<<"\t" <<"MediaBubble: " << mediaBubble <<"\t" << "MediaMerge: " << mediaMerge << "\t" <<"[Merge]"<<endl;
        }
        else
        {
            cout <<"comp perturbate: "<< perturbazione<<"\t" <<"MediaBubble: " << mediaBubble << "\t" << "MediaMerge: " << mediaMerge << "\t" <<"[Bubble]"<<endl;
        }


    } //for esterno sulla perturbazione
   return 0;
}


