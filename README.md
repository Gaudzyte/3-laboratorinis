# Objektinis programavimas 
## **v3.0**
Pridėtas programos diegimo failas setup.exe. Diegimo paketas įtraukia visus reikiamus programos failus ir automatiškai sukuria nuorodas.

**Įdiegimo instrukcija**
1. Atsisiųsti setup.exe (pagal nutylėjimą, programa bus įdiegta į „C:/Program files/VU/Urtė_Gaudzytė“);
2. Paspauskite ant atsisiųsto failo;
3. Pažymėkite, jog norite programos vykdymo nuorodos darbalaukyje;
4. Galiausiai spauskite "Install";
5. Programa paruošta.

## **v2.0**
- Sukurta dokumentacija panaudojant Doxygen.
- Realizuota Unit Test naudojant doctest. Tikrinta:
  - Galutinis balas pagal vidurkį;
  - Galutinis balas pagal medianą;
  - Kai nera pažymių, galutiniai balai yra 0.
 

<img width="915" height="857" alt="image" src="https://github.com/user-attachments/assets/f92ad0c8-ffd3-485e-acc8-5a6286a57d36" />

Matome, kad viskas "passed", vadinasi sėkminngai buvo įvykdyti testai.


**Naudojimosi ir įdiegimo instrukcija:**
1. Atsisiųskite failus, CMakeLists.txt ir **runme.bat**
2. Kompiuteryje sukurkite naują aplanką, kuriame vykdysite kodo paleidimą ir įkelkite CMakeLists.txt ir **runme.bat**
3. Šiame aplankale taip pat sukurkite aplanką "src" ir "include".
4. Į "src" aplankalą sukelkite atsisiųstus .cpp failus ir sugeneruotus studentų failus (studentai.1000.txt, studentai.10000.txt ir t.t.), o į "include" .h failus.
5. Paspauskite ant **runme.bat** ir programa pradės veikti.



## **v1.5**
Vietoje turimos vienos Studentas klasės buvo sukurta:
  - Bazinė abstrakti klasė Žmogus, kuri apibūdina bendrus žmogaus atributus (vardas, pavardė) ir elgseną.
  - Išvestinė Studento klasė iš Žmogaus palaikanti 1.2 versijoje realizuotą  „Rule of three“ taisyklę ir paveldinti vardą ir pavardę. 

Žmogus aprašyta kaip abstrakti bazinė klasė, tad ji negali būti naudojama tiesioginiam objekto kūrimui.  Tad yra išvedama klaida:
<img width="1132" height="480" alt="image" src="https://github.com/user-attachments/assets/cff72549-1abc-4599-96b0-4c1febb83265" />



## **v1.2**
Buvo realizuota **"Rule of three"**:
   - Kopijavimo konstruktorius
   ```
Studentas(const Studentas& other)
    : vardas_(other.vardas_),
      pavarde_(other.pavarde_),
      paz_(other.paz_),
      egz_(other.egz_),
      gal_vid_(other.gal_vid_),
      gal_med_(other.gal_med_) {}
   ```
   - Priskyrimo operatorius
   ```
Studentas& operator=(const Studentas& other){
    if (this != &other) {
        vardas_ = other.vardas_;
        pavarde_ = other.pavarde_;
        paz_     = other.paz_;
        egz_     = other.egz_;
        gal_vid_ = other.gal_vid_;
        gal_med_ = other.gal_med_;
    }
    return *this;
}
   ```
   - Destruktorius
   ```
~Studentas() {
    vardas_.clear();
    pavarde_.clear();
    paz_.clear();
    egz_ = 0;
    gal_vid_ = 0.0;
    gal_med_ = 0.0;
}

   ```

Taip pat realizuota **įvesties ir išvesties** operatoriai turimai Studentas klasei:
 1. **Įvesties operatorius (>>)**
   ```
friend std::istream& operator>>(std::istream& is, Studentas& s);
   ```
   ```
std::istream& operator>>(std::istream& in, Studentas& s)
{
    return s.readStudent(in);
}
   ```
<img width="510" height="643" alt="image" src="https://github.com/user-attachments/assets/3a87a967-1a79-4ee4-8d09-fecbec1706ce" />

   - **Įvestis rankiniu būdu:**
Vykdoma funkcijoje VartotojoIvedimas().

Leidžia įvesti: vardą, pavardę, namų darbų pažymius, egzaminą.

   - **Automatinė įvestis iš failo:**
Atliekama funkcijoje NuskaitytiVector(const string& failas):
<img width="715" height="526" alt="image" src="https://github.com/user-attachments/assets/da10743a-54b4-479c-9483-f6e51614b358" />

 2. **Išvesties operatorius (<<)**: Leidžia tvarkingai spausdinti studento duomenis į ekraną ar failą.
   ```
friend std::ostream& operator<<(std::ostream& os, const Studentas& s);
   ```
   ```
std::ostream& operator<<(std::ostream& os, const Studentas& s) {
    os << std::setw(15) << std::left << s.vardas()
       << std::setw(20) << std::left << s.pavarde()
       << std::setw(17) << std::left << std::fixed << std::setprecision(2) << s.galVid()
       << std::setw(17) << std::left << std::fixed << std::setprecision(2) << s.galMed();
    return os;
}
   ```


   - Yra atliekama **išvestis į ekraną** po rankinio įvedimo VartotojoIvedimas():
<img width="557" height="236" alt="image" src="https://github.com/user-attachments/assets/457266f8-bec5-4414-a172-1cbe3ae068db" />

   - Yra atliekama **išvestis į failą**. Funkcija Spausdinimas sukuria rezultato failus (pvz: studentai.1000_kietiakai1.txt):
   ```
for (const auto& s : grupe) {
    ss << s << std::endl;
}
   ```



## **v1.1**
Ankstesnės atliktos užduoties pagrindu sukurta nauja repozitorija 2-labaratorinis, kurioje išliko commit'ų istorija.

Iš ankščiau naudotos struktūros kodas buvo modifikuotas į klasę.

   - Palyginau v1.0 ir v1.1 spartą naudojant vektoriaus 3 strategiją su 100000 ir 1000000 dydžio failais.
<img width="948" height="272" alt="image" src="https://github.com/user-attachments/assets/6f6fe4c7-5b50-40d7-8ff1-d3b82abc03d6" />

   - exe failo dydžiai pagal kompiliatoriaus optimizavimo lygį naudojant vektorių 3 strategiją.
<img width="759" height="223" alt="image" src="https://github.com/user-attachments/assets/e42b2cc6-370f-4340-9e04-6a3f7850745d" />

**Išvados:**  
   - Struct ir Class versijos spartumo skirtumai yra labai maži. Tačiau abejais atvejais Class realizacija dažniau buvo spartesnė: mažesnio duomenų kiekio atveju - 100'000 studentų, O1 ir O3 buvo net šiek tiek spartesnė, o su didesniu duomenų kiekiu-1'000'000 ties O1 ir O2 realizacijomis.
   - Lyginant optimizacijas greičiausiai atliko O1.
   - Lyginant .exe failų dydžius, galima matyti, kad Struct programų vykdomieji failai yra vidutiniškai 7–9 KB mažesni už Class versijos failus.


## **v0.1**
Programa leidžia pasirinkti:
1. "Įvesti pažymius ranka"
   - Įvedamas studentų skaičius grupėje, jų vardai, pavardės ir pažymiai.
   
2. "Generuoti atsitiktinius pažymius ir egzaminą" 
   - Programa automatiškai sugeneruoja nurodytą kiekį studentų su pažymiais ir egzamino rezultatais.
  
3. "Nuskaityti studentus iš failo"
   - Programa nuskaito duomenis iš failų
     
Programa studentų vardus ir pavardes bei jų galutinį vidurkį/medianą atspausdina ekrane.

## **v0.2**
Sukurta programa kur yra generuojami studentų duomenys.
#### Studentai automatiškai suskirstomi į dvi grupes: ####
- **vargšiukai** – galutinis pažymys < 5.0;
- **kietiakai** – galutinis pažymys ≥ 5.0.

#### Galima pasirinkti rūšiavimo kriterijų: ####
- pagal vardą;
- pagal pavardę;
- pagal galutinį pažymį (vidurkį).

#### Galiausiai programa matuoja ir išveda šių etapų vykdymo trukmę: ####
- įrašų nuskaitymo laiką,
- rūšiavimo laiką,
- dalijimo į dvi grupes laiką,
- rezultatų įrašymo laiką,
- bendrą viso testo laiką.

## **v0.3**

#### Paleidus kodą leidžiama pasirinkti konteinerį: ####
- **std::vector**
-  **std::list** 

Pridėta galimybė matyti vector ir list adresą kompiuterio atmintyje, kai duomenys apie studentus yra įrašomi ranka.

Atlikta programos spartos analizė

<img width="1066" height="622" alt="image" src="https://github.com/user-attachments/assets/8ccfbfa4-bffc-4d70-8765-031e53283a63" />

Galime matyti jog duomenų nuskaitymo laikas yra labai panašus tarp vector ir list. Duomenų rūšiavimą list atlieka žymiai greičiau negu vector. Duomenų dalijimą į dvi grupes šįkart vector atlieka sparčiau. Nors paprastai duomenų įrašymą greičiau atlieka vector, šiuo atveju, esant 10 milijonų duomenų, list veikė greičiau – net 19 sekundžių skirtumu.

#### Testavimo sistemos parametrai: ####
  - CPU - **AMD Ryzen 5 7520U with Radeon Graphics**
  - 2.80GHz
  - RAM - **16GB**
  - SSD - **477GB**

    ## **v1.0**
Atliktos trys strategijos optimizuojant studentų rūšiavimą į dvi kategorijas:
- 1 strategija: yra identiška, kaip veikdavo anksčiau.
- 2 strategija: yra sukuriamas tik vienas papildomas konteineris - "Vargšiukai". Tie studentai, kurie neatitinka kriterijaus (vidurkis mažesnis už 5) yra ištrinami iš pagrindinio konteinerio.
- 3 strategija: pritaikyti algoritmai (std::remove_if, std::remove_copy_if, std::stable_partition), jog būtų paspartintas skaidymas.

Rezultatai sekundėmis:

<img width="821" height="252" alt="image" src="https://github.com/user-attachments/assets/5f94ef9e-b3fe-417f-b720-fe56bafbd4bd" />

**Išvados:**

3 strategija vector konteineryeje greičiausiai atliko spartos analizę. Tačiau ir 1000 įrašų turinčio failo duomenys buvo greitai apdoroti, naudojant antrąją strategiją tiek su vector, tiek su list konteineriais.


**Naudojimosi ir įdiegimo instrukcija:**

1. Atsisiųskite failus main.cpp, mylib.cpp, laikas.h, mylib.h, studentas.h, Generuojami file, CMakeLists.txt ir **runme.bat**
2. Patikrinkite ar kompiuteryje turite įdiegtus C++ kompiliatorių ir projekto generavimo įrankius cmake. Jei jų neturite - įdiekite.
3. Kompiuteryje sukurkite naują aplanką, kuriame vykdysite kodo paleidimą ir įkelkite CMakeLists.txt ir **runme.bat**
4. Šiame aplankale taip pat sukurkite aplanką "src" ir "include".
5. Į "src" aplankalą sukelkite atsisiųstus .cpp failus ir sugeneruotus studentų failus (studentai.1000.txt, studentai.10000.txt ir t.t.), o į "include" .h failus.
6. Paspauskite ant **runme.bat** ir programa pradės veikti.
7. Galiausiai matysite programos veikimo spartą skirtingoms strategijoms.
