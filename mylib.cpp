#include "mylib.h"
#include "studentas.h"
#include <fstream>
#include <iostream>
#include <algorithm>
#include <chrono>
#include <iomanip>    
#include <sstream>     
#include <string>     
#include <limits>   
#include <fstream>
#include <cstdlib>
#include <ctime>
using namespace std;

vector<Studentas> NuskaitytiVector(const string& failas) {
    std::ifstream fin(failas);
    if (!fin) {
        std::cerr << "Nepavyko atidaryti failo: " << failas << std::endl;
        return {};
    }

    string eilute;
    getline(fin, eilute); // praleidžia antraštę

    vector<Studentas> studentai;
    studentai.reserve(100000);

    while (getline(fin, eilute)) {
        istringstream iss(eilute);
        Studentas s;
        iss >> s;           // naudoja perdengtą >> operatorių
        studentai.push_back(s);
    }

    return studentai;
}

void Paskirstymas_vector_1_strategija(const vector<Studentas> &Grupe, const int irasu_sk, const string& failo_vardas)
{
    Timer t;
    vector<Studentas> Vargsai, Kietiakai;
    for (auto &stud : Grupe)
    {
        if (stud.galVid() < 5)
            Vargsai.push_back(stud);
        else
            Kietiakai.push_back(stud);
    }
    cout << irasu_sk << " irasu vektoriaus padalijimo 1 strategijos laikas: "
         << t.elapsed() << " s\n";

    Spausdinimas(Kietiakai, 1, failo_vardas);
    Spausdinimas(Vargsai, 1, failo_vardas);
}

void Paskirstymas_vector_2_strategija(vector<Studentas> Grupe, const int irasu_sk, const string& failo_vardas)
{
    Timer t;
    vector<Studentas> Vargsai;
    size_t newSize = 0;
    for (size_t i = 0; i < Grupe.size(); i++)
    {
        if (Grupe[i].galVid() < 5)
            Vargsai.push_back(Grupe[i]);
        else
            Grupe[newSize++] = std::move(Grupe[i]);
    }
    Grupe.erase(Grupe.begin() + newSize, Grupe.end());
    cout << irasu_sk << " irasu vektoriaus padalijimo 2 strategijos laikas: "
         << t.elapsed() << " s\n";

    Spausdinimas(Grupe, 2, failo_vardas);
    Spausdinimas(Vargsai, 2, failo_vardas);
}

void Paskirstymas_vector_3_strategija(vector<Studentas>& Grupe, const int irasu_sk, const string& failo_vardas) {
    Timer t;
    vector<Studentas> Vargsai;
    Vargsai.reserve(Grupe.size());

    std::remove_copy_if(Grupe.begin(), Grupe.end(), std::back_inserter(Vargsai),
                        [](const Studentas& stud) {
                            return stud.galVid() >= 5;
                        });

    auto new_end = std::remove_if(Grupe.begin(), Grupe.end(),
                                  [](const Studentas& stud) {
                                      return stud.galVid() < 5;
                                  });
    Grupe.erase(new_end, Grupe.end());

    cout << irasu_sk << " irasu vektoriaus padalijimo 3 strategijos laikas: "
         << t.elapsed() << " s\n";

    Spausdinimas(Grupe, 3, failo_vardas);
    Spausdinimas(Vargsai, 3, failo_vardas);
}

void Paskirstymas_list_1_strategija(const list<Studentas> &Grupe, const int irasu_sk, const string& failo_vardas)
{
    Timer t;
    list<Studentas> Vargsai, Kietiakai;
    for (auto &stud : Grupe)
    {
        if (stud.galVid() < 5)
            Vargsai.push_back(stud);
        else
            Kietiakai.push_back(stud);
    }
    cout << irasu_sk << " irasu saraso padalijimo 1 strategijos laikas: "
         << t.elapsed() << " s\n";

    Spausdinimas(Kietiakai, 1, failo_vardas);
    Spausdinimas(Vargsai, 1, failo_vardas);
}

void Paskirstymas_list_2_strategija(list<Studentas> Grupe, const int irasu_sk, const string& failo_vardas)
{
    Timer t;
    list<Studentas> Vargsai;
    for (auto it = Grupe.begin(); it != Grupe.end();)
    {
        if (it->galVid() < 5)
        {
            Vargsai.push_back(*it);
            it = Grupe.erase(it);
        }
        else
        {
            ++it;
        }
    }
    cout << irasu_sk << " irasu saraso padalijimo 2 strategijos laikas: "
         << t.elapsed() << " s\n";

    Spausdinimas(Grupe, 2, failo_vardas);
    Spausdinimas(Vargsai, 2, failo_vardas);
}

void Paskirstymas_list_3_strategija(list<Studentas>& Grupe, const int irasu_sk, const string& failo_vardas) {
    Timer t;
    list<Studentas> Vargsai;

    std::remove_copy_if(Grupe.begin(), Grupe.end(), std::back_inserter(Vargsai),
                        [](const Studentas& stud) {
                            return stud.galVid() >= 5;
                        });

    Grupe.remove_if([](const Studentas& stud) {
        return stud.galVid() < 5;
    });

    cout << irasu_sk << " irasu saraso padalijimo 3 strategijos laikas: "
         << t.elapsed() << " s\n";

    Spausdinimas(Grupe, 3, failo_vardas);
    Spausdinimas(Vargsai, 3, failo_vardas);
}

void TestavimasIsFailo(const string &failas, int irasu_sk)
{
    cout << "\n"
         << failas << "\n";

    Timer t;
    auto Grupe_vector = NuskaitytiVector(failas);
    double readTime = t.elapsed();
    list<Studentas> Grupe_list(Grupe_vector.begin(), Grupe_vector.end());

    cout << "Failo nuskaitymas uztruko: " << readTime << " s\n";

    Paskirstymas_vector_1_strategija(Grupe_vector, irasu_sk, failas);
    Paskirstymas_vector_2_strategija(Grupe_vector, irasu_sk, failas);
    Paskirstymas_vector_3_strategija(Grupe_vector, irasu_sk, failas);
    Paskirstymas_list_1_strategija(Grupe_list, irasu_sk, failas);
    Paskirstymas_list_2_strategija(Grupe_list, irasu_sk, failas);
    Paskirstymas_list_3_strategija(Grupe_list, irasu_sk, failas);
}

template <typename T>
void Spausdinimas(const T& grupe, const int& strat, const std::string& failo_vardas) {
    if (grupe.empty()) return;

    std::stringstream ss;
    ss << std::setw(15) << std::left << "Vardas"
       << std::setw(20) << std::left << "Pavarde"
       << std::setw(17) << std::left << "Galutinis (Vid.)"
       << std::setw(17) << std::left << "Galutinis (Med.)" << std::endl;
    ss << std::string(70, '-') << std::endl;

    for (const auto& s : grupe) {
        ss << s << std::endl;   // naudoja perdengtą << operatorių
    }

    std::string tipas = (grupe.begin()->galVid() >= 5) ? "_kietiakai" : "_vargsiukai";
    std::string failoPav = failo_vardas.substr(0, failo_vardas.find_last_of('.')) +
                           tipas + std::to_string(strat) + ".txt";

    std::ofstream out(failoPav);
    out << ss.str();
    out.close();
}

void VartotojoIvedimas() {
    int n;

    cout << "Kiek studentu grupeje? ";
    while (!(cin >> n) || n <= 0) {
        cout << "Iveskite teigiama sveika skaiciu: ";
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
    }

    vector<Studentas> grupe;
    grupe.reserve(n);

    for (int i = 0; i < n; ++i) {
        string vardas, pavarde;
        cout << "\nStudentas " << i + 1 << endl;

        cout << "Vardas: ";
        cin >> vardas;
        cout << "Pavarde: ";
        cin >> pavarde;

        // isvalom buferi pries getline
        cin.ignore(numeric_limits<streamsize>::max(), '\n');

        vector<int> paz;
        cout << "Iveskite namu darbu pazymius (0-10).\n";
        cout << "Baigti ivedima: 2 kartus is eiles ENTER\n";

        int tusciuEiluciuIsEiles = 0;
        while (true) {
            cout << "Pazymys " << paz.size() + 1 << ": ";
            string line;
            if (!std::getline(cin, line)) {
                break;
            }

            if (line.empty()) {
                tusciuEiluciuIsEiles++;
                if (tusciuEiluciuIsEiles >= 2) {
                    break; 
                }
                continue;
            } else {
                tusciuEiluciuIsEiles = 0;
            }

            std::istringstream iss(line);
            int pazymys;
            if (!(iss >> pazymys) || !(iss.eof())) {
                cout << "Netinkama ivestis. Iveskite sveika skaiciu 0-10, arba tuscia eilute baigimui.\n";
                continue;
            }

            if (pazymys < 0 || pazymys > 10) {
                cout << "Pazymys turi buti tarp 0 ir 10.\n";
                continue;
            }

            paz.push_back(pazymys);
        }

        int egz;
        cout << "Egzamino pazymys: ";
        while (true) {
            if (!(cin >> egz)) {
                cout << "Netinkama ivestis. Bandykite dar karta.\n";
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                continue;
            }
            if (egz < 0 || egz > 10) {
                cout << "Pazymys turi buti tarp 0 ir 10.\n";
                continue;
            }
            break;
        }

        grupe.emplace_back(vardas, pavarde, paz, egz);
    }

    int rusiavimas;
    cout << "\nPagal ka norite rusiuoti?" << endl;
    cout << "1 - Pagal varda" << endl;
    cout << "2 - Pagal pavarde" << endl;
    cout << "3 - Pagal galutini pazymi (vid.)" << endl;
    cout << "Jusu pasirinkimas: ";

    while (true) {
        if (!(cin >> rusiavimas)) {
            cout << "Netinkama ivestis. Iveskite 1, 2 arba 3: ";
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            continue;
        }
        if (rusiavimas < 1 || rusiavimas > 3) {
            cout << "Pasirinkite 1, 2 arba 3: ";
            continue;
        }
        break;
    }

    switch (rusiavimas) {
        case 1:
            sort(grupe.begin(), grupe.end(),
                 [](const Studentas& a, const Studentas& b) {
                     return a.vardas() < b.vardas();
                 });
            break;
        case 2:
            sort(grupe.begin(), grupe.end(),
                 [](const Studentas& a, const Studentas& b) {
                     return a.pavarde() < b.pavarde();
                 });
            break;
        case 3:
            sort(grupe.begin(), grupe.end(),
                 [](const Studentas& a, const Studentas& b) {
                     return a.galVid() > b.galVid();
                 });
            break;
    }

    cout << "\nRezultatai:\n";
    cout << setw(15) << left << "Vardas"
         << setw(20) << left << "Pavarde"
         << setw(17) << left << "Galutinis (Vid.)"
         << setw(17) << left << "Galutinis (Med.)" << endl;
    cout << string(70, '-') << endl;

    for (const auto& s : grupe) {
        cout << s << '\n';   
    }
}


void PaprastasFailoApdorojimas() {
    string failo_vardas;
    cout << "Iveskite failo pavadinima (pvz. studentai.1000.txt): ";
    cin >> failo_vardas;

    {
        std::ifstream test(failo_vardas);
        if (!test) {
            cout <<  failo_vardas << " nepavyko atidaryti.\n";
            return;
        }
    }

    vector<Studentas> Grupe = NuskaitytiVector(failo_vardas);
    if (Grupe.empty()) {
        cout << "Nepavyko nuskaityti duomenu is failo.\n";
        return;
    }

    vector<Studentas> Vargsai;
    vector<Studentas> Kietiakai;

    for (const auto& s : Grupe) {
        if (s.galVid() < 5.0)
            Vargsai.push_back(s);
        else
            Kietiakai.push_back(s);
    }

    int rusiavimas;
    cout << "\nPagal ka norite rusiuoti?\n";
    cout << "1 - Pagal varda\n";
    cout << "2 - Pagal pavarde\n";
    cout << "3 - Pagal galutini pazymi (vid.)\n";
    cout << "Jusu pasirinkimas: ";

    while (true) {
        if (!(cin >> rusiavimas)) {
            cout << "Netinkama ivestis. Iveskite 1, 2 arba 3: ";
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            continue;
        }
        if (rusiavimas < 1 || rusiavimas > 3) {
            cout << "Pasirinkite 1, 2 arba 3: ";
            continue;
        }
        break;
    }

    auto rikiuok = [rusiavimas](vector<Studentas>& gr) {
        switch (rusiavimas) {
        case 1:
            sort(gr.begin(), gr.end(),
                 [](const Studentas& a, const Studentas& b) {
                     return a.vardas() < b.vardas();
                 });
            break;
        case 2:
            sort(gr.begin(), gr.end(),
                 [](const Studentas& a, const Studentas& b) {
                     return a.pavarde() < b.pavarde();
                 });
            break;
        case 3:
            sort(gr.begin(), gr.end(),
                 [](const Studentas& a, const Studentas& b) {
                     return a.galVid() > b.galVid();
                 });
            break;
        }
    };

    rikiuok(Kietiakai);
    rikiuok(Vargsai);

    Spausdinimas(Kietiakai, 0, failo_vardas);
    Spausdinimas(Vargsai, 0, failo_vardas);

    cout << "Rezultatu failai sukurti.\n";
}

// FAILŲ GENERAVIMAS
// ============================================

static void generuotiFaila(const std::string& pavadinimas, int kiek) {
    std::ofstream fr(pavadinimas);
    if (!fr) {
        std::cout << "Nepavyko sukurti failo: " << pavadinimas << std::endl;
        return;
    }

    fr << "Vardas Pavarde ND1 ND2 ND3 ND4 Egz" << std::endl;

    for (int i = 1; i <= kiek; i++) {
        fr << "Vardas" << i << " "
           << "Pavarde" << i << " "
           << (rand() % 10 + 1) << " "
           << (rand() % 10 + 1) << " "
           << (rand() % 10 + 1) << " "
           << (rand() % 10 + 1) << " "
           << (rand() % 10 + 1) << std::endl;
    }

    fr.close();
    std::cout << "Failas " << pavadinimas << " sukurtas (" << kiek << " irasu)." << std::endl;
}

void GeneruotiTestiniusFailus() {
    std::cout << "Generuojami testiniai failai..." << std::endl;

    generuotiFaila("studentai.1000.txt",    1000);
    generuotiFaila("studentai.10000.txt",   10000);
    generuotiFaila("studentai.100000.txt",  100000);
    generuotiFaila("studentai.1000000.txt", 1000000);
    //generuotiFaila("studentai.10000000.txt", 10000000);

    std::cout << "Failu generavimas baigtas." << std::endl;
}
