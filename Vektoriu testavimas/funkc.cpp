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
using std::to_string;
using std::vector;

#include "head.h"

bool isNumber(string s)
{
    for (int i = 0; i < s.length(); i++)
        if (!isdigit(s[i]))
            return false;
    return true;
}
int InputNumber(string text)
{
    string temp;
    cout << text;
    cin >> temp;
    while (!isNumber(temp)) {
        cout << "Bloga ivestis. Bandykite dar karta: ";
        cin >> temp;
    }
    return atoi(temp.c_str());
}
void ReadFromFile(Vector<data>& list, string filename)
{
    std::ifstream fd(filename);
    string TempVardas, TempPavarde;
    int TempEgz;
    int TempPaz;
    int count = 0;

    if (fd.good()) {
        string first;
        getline(fd, first);
        std::stringstream s(first);
        string word;
        while (s >> word)
            count++;
        count -= 3;
    }
    do {
        data temp;
        fd >> TempVardas >> TempPavarde;
        temp.SetVardas(TempVardas);
        temp.SetPavarde(TempPavarde);
        for (int i = 0; i < count; i++) {
            fd >> TempPaz;
            temp.SetPaz(TempPaz);
        }
        fd >> TempEgz;
        temp.SetEgz(TempEgz);
        list.push_back(temp);
    } while (!fd.eof());

    fd.close();
}
void CreateFile(int lines, int ND)
{
    using hrClock = std::chrono::high_resolution_clock;
    std::mt19937 mt(static_cast<long unsigned int>(hrClock::now().time_since_epoch().count()));
    std::uniform_int_distribution<int> random10(0, 10);
    std::ostringstream fileName;
    fileName << "kursiokai" << lines << ".txt";
    std::ofstream fr(fileName.str());

    fr << setw(20) << std::left << "Vardas" << setw(20) << "Pavarde";
    for (int i = 1; i <= ND; i++)
        fr << "ND" << std::setw(8) << std::left << i;
    fr << "Egz." << endl;
    fr <<endl;

    int last = 0, mark;
    for (int i = 1; i <= lines; i++) {
        fr << "Vardas" << setw(14) << std::left << i << "Pavarde" << setw(14) << std::left << i;
        for (int j = 0; j <= ND; j++) {
            mark = random10(mt);
            fr << setw(10) << std::left << mark;
            last = mark;
        }
        if(lines != i)
        fr <<endl;
    }
}
bool InputBool(string text)
{
    string temp;
    cout << text;
    cin >> temp;
    while (temp != "0" && temp != "1") {
        cout << "Bloga ivestis. Bandykite dar karta: ";
        cin >> temp;
    }
    return temp == "1";
}
double AverageGrade(Vector<int> paz)
{
    double sum = 0;
    for (int i = 0; i < paz.size(); i++)
        sum += paz[i];

    return sum /= paz.size();
}
double MedianGrade(Vector<int> paz)
{
    double vidurkis;
    std::sort(paz.begin(), paz.end());
    if (paz.size() % 2 != 0)
        return paz[paz.size() / 2];
    else
        return vidurkis = (paz[paz.size() / 2] + paz[paz.size() / 2 - 1]) / 2;
}
void Input(data& temp)
{
    string TempVardas, TempPavarde;
    int TempEgz;
    cout << "Iveskite studento varda: ";
    cin >> TempVardas;
    temp.SetVardas(TempVardas);
    if (isNumber(temp.GetVardas())) {
        cout << "Bloga ivestis. Bandykite dar karta: ";
        cin >> TempVardas;
        temp.SetVardas(TempVardas);
    }
    cout << "Iveskite studento pavarde: ";
    cin >> TempPavarde;
    temp.SetPavarde(TempPavarde);
    if (isNumber(temp.GetPavarde())) {
        cout << "Bloga ivestis. Bandykite dar karta: ";
        cin >> TempPavarde;
        temp.SetPavarde(TempPavarde);
    }
    bool gen = false;
    gen = InputBool("Iveskite 1 jeigu norite, kad pazymiai ir egzamino rezultatas butu sugeneruoti automatiskai, 0 - jeigu nenorite: ");

    int pazymiuSkaicius = InputNumber("Ivesite pazymiu skaiciu: ");
    int TempPaz;
    if (gen == 0) {
        for (int i = 0; i < pazymiuSkaicius; i++) {
            TempPaz = InputNumber("Ivesite " + to_string(i + 1) + " pazymi: ");
            temp.SetPaz(TempPaz);
        }
        TempEgz = InputNumber("Iveskite egzamino rezultata: ");
        temp.SetEgz(TempEgz);
    }
    else {
        using hrClock = std::chrono::high_resolution_clock;
        std::mt19937 mt(static_cast<long unsigned int>(hrClock::now().time_since_epoch().count()));
        std::uniform_int_distribution<int> dist(0, 10);
        int random;
        for (int i = 0; i < pazymiuSkaicius; i++) {
            random = dist(mt);
            temp.SetPaz(random);
            cout << i + 1 << " pazymys yra: " << random << endl;
        }
        random = dist(mt);
        cout << "Egzamino rezultatas: " << random << endl;
        temp.SetEgz(random);
    }
}
void FinalResult(Vector<data>& list, bool AvgMed)
{
    double TempGalutinis;
    for (auto& a : list)
        if (AvgMed == 1){
            TempGalutinis = AverageGrade(a.GetPaz()) * 0.4 + a.GetEgz() * 0.6;
            a.SetGalutinis(TempGalutinis);
        }
        else{
            TempGalutinis = MedianGrade(a.GetPaz()) * 0.4 + a.GetEgz() * 0.6;
            a.SetGalutinis(TempGalutinis);
        }
}
void Output(Vector<data>& list, string filename, int vm)
{
    std::ofstream fr(filename);
    fr << setw(20) << std::left << "Vardas" << setw(20) << "Pavarde" << setw(20);
    if (vm == 1)
        fr << "Galutinis (Vid.)" << endl;
    else
        fr << "Galutinis (Med.)" << endl;

    for (int i = 0; i < list.size(); i++) {
        fr << setw(20) << std::left << list[i].GetVardas() << setw(20) << list[i].GetPavarde() << setw(20) << std::setprecision(3) << list[i].GetGalutinis() << endl;
    }
    fr.close();
}
void Groups(Vector<data>& list, Vector<data>& Nlist)
{
    int lessthan5 = 0;

    std::sort(list.begin(), list.end(), [](data& f, data& s) { return f.GetGalutinis() < s.GetGalutinis(); });

    auto index = std::find_if(list.begin(), list.end(), []( data& temp){
    return temp.GetGalutinis() >= 5;
    });

    Vector<data> temp(index, list.end());
    Nlist = temp;
    temp.clear();

    list.resize(list.size() - Nlist.size());
}
bool SortByName(data x, data y)
{
    return x.GetVardas() < y.GetVardas();
}
bool SortBySurname(data x, data y)
{
    return x.GetPavarde() < y.GetPavarde();
}