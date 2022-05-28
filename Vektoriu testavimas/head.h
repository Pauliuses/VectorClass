#ifndef FUNKC_H
#define FUNKC_H

#include <string>

#include "vectest.h"

class Zmogus {
    protected:
        string vardas, pavarde;
    public:
        inline string GetVardas() const { return vardas; }
        inline string GetPavarde() const { return pavarde; }
        virtual void SetVardas(string v) = 0;
        virtual void SetPavarde(string p) = 0;
        Zmogus(string vard = " ", string pav = " ") : vardas{vard}, pavarde{pav}{}
};

class data: public Zmogus{
    private:
        double galutinis = 0;
        int egz = 0;
        Vector<int> paz;
    public:
        data(Vector<int> paz = { 0 }, int egz = 0, double galutinis = 0, string vard = " ", string pav = "") : Zmogus{vard, pav} {}


        data(const data& student) { // copy constructor
            vardas = student.vardas;
            pavarde = student.pavarde;
            galutinis = student.galutinis;
            egz = student.egz;
            paz = student.paz;
        }

        ~data() { paz.clear(); } // destructor

        data operator=(const data& student){ // assign operator
            if(this == &student)
                return *this;
            vardas = student.vardas;
            pavarde = student.pavarde;
            galutinis = student.galutinis;
            egz = student.egz;
            paz = student.paz;
            return *this;
        }

        // setters
        void SetVardas(std::string NaujasVardas) { vardas = NaujasVardas; }
        void SetPavarde(std::string NaujaPavarde) { pavarde = NaujaPavarde; }
        void SetGalutinis(double NaujasGalutinis) { galutinis = NaujasGalutinis; }
        void SetEgz(int NaujasEgz) { egz = NaujasEgz; }
        void SetPaz(int NaujasPaz) { paz.push_back(NaujasPaz);}

        // getters
        inline std::string GetVardas() const { return vardas; }
        inline std::string GetPavarde() const { return pavarde; }
        inline double GetGalutinis() const { return galutinis; }
        inline int GetEgz() const { return egz; }
        inline Vector<int> GetPaz() const { return paz; }

        void readData(vector<data> &list, string filename);
};

bool IsNumber(std::string);
bool isNumber(std::string);
int InputNumber(std::string);
void ReadFromFile(Vector<data>&, std::string);
void CreateFile(int, int);
bool InputBool(std::string);
double AverageGrade(Vector<int>);
double MedianGrade(Vector<int>);
void Input(data&);
void FinalResult(Vector<data>&, bool);
void Output(Vector<data>&, std::string, int);
void Groups(Vector<data>&, Vector<data>&);
void SortByResult(Vector<data>&, int);
bool SortByName(data, data);
bool SortBySurname(data, data);

#endif