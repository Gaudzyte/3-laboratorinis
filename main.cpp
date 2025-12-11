#include <iostream>
#include <vector>
#include <list>
#include <string>
#include <chrono>
#include <ctime>    
#include <cstdlib> 
#include "studentas.h"
#include "mylib.h"
#include "timer.h"
#include "zmogus.h" 

using namespace std;

int main() {
    ios::sync_with_stdio(false);
    
    //cin.tie(nullptr);
    //Zmogus zmog;  //sukeltų klaidą: error: cannot declare variable 'zmog' to be of abstract type 'Zmogus'

    int pasirinkimas;
    cout << "Pasirinkite veiksma:\n";
    cout << "1 - Ivesti studentus ranka\n";
    cout << "2 - Nuskaityti pasirinkta faila \n";
    cout << "3 - Spartos testavimas failams\n";
    cout << "Jusu pasirinkimas: ";

    if (!(cin >> pasirinkimas)) return 0;

    if (pasirinkimas == 1) {
        VartotojoIvedimas();
    }
    else if (pasirinkimas == 2) {

        int sub;
        cout << "\nPasirinkite:\n";
        cout << "1 - Sugeneruoti testinius failus\n";
        cout << "2 - Naudoti jau sugeneruotus failus\n";
        cout << "Jusu pasirinkimas: ";

        if (!(cin >> sub)) return 0;

        if (sub == 1) {
            GeneruotiTestiniusFailus();
            cout << "\n Pasirinkite, koki faila noresite apdoroti.\n";
        }

        PaprastasFailoApdorojimas();
    }
    else if (pasirinkimas == 3) {

        int sub;
        cout << "\nPasirinkite:\n";
        cout << "1 - Sugeneruoti testinius failus\n";
        cout << "2 - Naudoti jau sugeneruotus failus\n";
        cout << "Jusu pasirinkimas: ";

        if (!(cin >> sub)) return 0;

        if (sub == 1) {
            GeneruotiTestiniusFailus();
            cout << "\nBus atliktas spartos testavimas sugeneruotiems failams.\n";
        }

        cout << "Nuskaitomi failai\n" << flush;

        vector<pair<string, int>> failai = {
            {"studentai.1000.txt", 1000},
            {"studentai.10000.txt", 10000},
            {"studentai.100000.txt", 100000},
            {"studentai.1000000.txt", 1000000}
            //{"studentai.10000000.txt", 10000000}
        };

        for (auto& f : failai)
            TestavimasIsFailo(f.first, f.second);
    }
    else {
        cout << "Neteisingas pasirinkimas.\n";
    }

    return 0;
}
