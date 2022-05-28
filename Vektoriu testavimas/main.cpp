#include <iostream>
#include <fstream>
#include <string>
#include <iomanip>
#include <algorithm>
#include <chrono>
#include <vector>
#include <sstream>
#include <random>

using std::cout;
using std::cin;
using std::string;
using std::endl;
using std::setw;
using std::vector;

#include "head.h"

int main()
{
    using hrClock = std::chrono::high_resolution_clock;
    hrClock::time_point start, end;
    std::chrono::duration<double> time;

    Vector<data> list, Nlist;
    bool PrintType = false;
    int sorting;
    bool vm = false;
    bool CreateFiles = false;

    CreateFiles = InputBool("Ar norite sukurti tekstinius failus? 1 - taip; 0 - ne: ");
    if (CreateFiles) {
        int dydis = 1;
        int ND = InputNumber("Kiek yra pazymiu (neskaitant egzamino pazymio): ");
        cout << "Duomenu failu generavimo trukme:" << endl;
        for (int i = 0; i < 5; i++) {
            start = hrClock::now();
            CreateFile(1000 * dydis, ND);
            cout << "kursiokai" << 1000 * dydis << ".txt - ";
            dydis *= 10;
            end = hrClock::now();
            time = end - start;
            cout << time.count() << " sekundziu" << endl;
            ;
        }
    }
    PrintType = InputBool("Ar norite, kad duomenys butu nuskaityti is failo? 1 - taip, 0 - ne: ");
    string fileName;
    if (PrintType) {
        bool badFile;
        cout << "Iveskite failo varda (pvz.: failas.txt): ";
        cin >> fileName;
        do {
            try {
                std::ifstream in(fileName);
                if (!in.good())
                    throw 404;
                else {
                    in.close();
                    badFile = false;
                }
            }
            catch (int exception) {
                badFile = true;
                cout << "Duomenu failas " << fileName << " neegzistuoja. Iveskite esamo failo varda: " << endl;
                cin >> fileName;
            }
        } while (badFile);
    }
    sorting = InputNumber("Jeigu norite, kad galutinis rezultatas butu surusiuotas pagal varda spauskite - 1, pagal pavarde - 0, pagal galutini bala(skaitant is failo) - 2: ");
    vm = InputBool("Jeigu norite kad galutiniai balai butu isvesti vidurkio forma spauskite - 1, medianos forma - 0: ");

    if (PrintType) {
        start = hrClock::now();
        ReadFromFile(list, fileName);
        end = hrClock::now();
        time = end - start;
        cout << "Failo nuskaitymas uztruko: " << time.count() << endl;

        if (sorting == 1) {
            start = hrClock::now();
            std::sort(list.begin(), list.end(), SortByName);
            end = hrClock::now();
            time = end - start;
            cout << "Suskirstymas/surusiavimas uztruko: " << time.count() << endl;
        }
        else if (sorting == 0) {
            start = hrClock::now();
            std::sort(list.begin(), list.end(), SortBySurname);
            end = hrClock::now();
            time = end - start;
            cout << "Suskirstymas/surusiavimas uztruko: " << time.count() << endl;
        }
        else {
            int b = 0;
            FinalResult(list, vm);
            
            start = hrClock::now();
            Groups(list, Nlist);
            end = hrClock::now();
            time = end - start;
            cout << "Suskirstymas uztruko: " << time.count() << endl;
            start = hrClock::now();
            Output(Nlist, "saunuoliai.txt", vm);
            end = hrClock::now();
            time = end - start;
            cout << "Saunuoliu surasymas i faila uztruko: " << time.count() << endl;

            start = hrClock::now();
            Output(list, "vargsai.txt", vm);
            end = hrClock::now();
            time = end - start;
            cout << "Vargsu surasymas i faila uztruko: " << time.count() << endl;
        }
    }
    if (sorting == 0 || sorting == 1 && PrintType == 1) {
        FinalResult(list, vm);
        std::ofstream fr("rezultatai.txt");
        fr << setw(20) << std::left << "Vardas" << setw(20) << "Pavarde" << setw(20);
        if (vm == 1) {
            fr << "Galutinis (Vid.)" << endl;
        }
        else {
            fr << "Galutinis (Med.)" << endl;
        }
        fr << endl;
        
        for (auto& a : list) {
            double number = a.GetGalutinis() * 0.4 + 0.6 * a.GetEgz();
            fr << std::setw(20) << std::left << a.GetVardas() << std::setw(20) << a.GetPavarde() << std::setw(20) << std::fixed << std::setprecision(3) << number << endl;
        }
    }

    if (!PrintType) {
        int stud = InputNumber("Iveskite kiek yra studentu: ");
        data K;
        list.reserve(stud);

        bool more = false;
        int alrd = 0;
        for (int i = 0; i < stud; i++) {
            if (alrd != stud) {
                Input(K);
                list.push_back(K);
                alrd++;
            }
            if (alrd == stud) {
                more = InputBool("Jeigu norite ivesti dar viena studenta spauskite 1, jeigu ne - 0: ");
                if (more) {
                    list.reserve(stud + 1);
                    Input(K);
                    list.push_back(K);
                    stud++;
                    alrd++;
                }
            }
        }
        if (sorting == 1)
            std::sort(list.begin(), list.end(), SortByName);
        else
            std::sort(list.begin(), list.end(), SortBySurname);

        FinalResult(list, vm);

        cout << setw(20) << std::left << "Vardas" << setw(20) << "Pavarde" << setw(20);
        if (vm == 1)
            cout << "Galutinis (Vid.)" << endl;
        else
            cout << "Galutinis (Med.)" << endl;

        for (auto& a : list) {
            double number = a.GetGalutinis() * 0.4 + 0.6 * a.GetEgz();
            cout << std::setw(20) << std::left << a.GetVardas() << std::setw(20) << a.GetPavarde() << std::setw(20) << std::setprecision(3) << number << endl;
        }

        system("pause");
    }
}