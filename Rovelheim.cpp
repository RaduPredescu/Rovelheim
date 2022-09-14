#include <bits/stdc++.h>

#include <utility>

using namespace std;

class Atelier {
private:
    string nume;
    int baniAtelier;
    int prag;
    int pret;
    map<string, int> coeficienti;
    map<string, int> bonus;
    int puncte;
    int nrObiecte;
public:
    Atelier() = default;

    Atelier(string nume, int baniAtelier, int prag, int pret, const map<string, int>& coeficienti,
        const map<string, int>& bonus, int puncte, int nrObiecte) : nume(std::move(nume)), baniAtelier(baniAtelier),
        prag(prag), pret(pret),
        coeficienti(coeficienti), bonus(bonus),
        puncte(0), nrObiecte(0) {};


    int oferta(const map<string, int>& atribute) {
        int oferta = 0;
        for (auto [numeAtribut, valoare] : atribute) {
            oferta += coeficienti[numeAtribut] * valoare;
        }
        return oferta;
    }


    bool verificaoferta(int _oferta) const {
        if (baniAtelier >= _oferta)
            return true;
        else return false;
    }

    bool verificaplata(int _bani) const {
        if (_bani >= pret)
            return true;
        return false;
    }

    bool verificastoc() const {
        if (nrObiecte > 0)
            return true;
        return false;
    }


    void platesteangajat(int& bani, int salariu) {
        bani += salariu;
        baniAtelier -= salariu;
        puncte += salariu;
        nrObiecte += puncte / prag;
        puncte = puncte % prag;
    }

    void vindeObiect(int& bani, map<string, int>& atribute) {

        bani -= pret;
        baniAtelier += pret;
        for (auto& [numeAtribut, valoareAtribut] : atribute) {
            valoareAtribut += bonus[numeAtribut];
        }
        nrObiecte--;

    };

    const string& getNume() const {
        return nume;
    }

    int getBonus(const string& numePref) {
        return bonus[numePref];
    };

    ~Atelier() = default;
};

class Persoana {
private:
    string nume;
    map<string, int> atribute;
    int bani{};
    vector<string> preferinte;
public:
    Persoana() = default;;

    Persoana(string nume, const vector<string>& preferinte) : nume(std::move(nume)), preferinte(preferinte) {
        bani = 0;
        atribute["STR"] = 1;
        atribute["DEX"] = 1;
        atribute["INT"] = 1;
        atribute["CHR"] = 1;
    }


    void munceste(vector<Atelier>& ateliere) {
        Atelier* ateliergasit = nullptr;
        int salariuMax = -1;
        for (auto& atelier : ateliere) {
            if (atelier.verificaoferta(atelier.oferta(atribute))) {
                if (ateliergasit == nullptr || atelier.oferta(atribute) > ateliergasit->oferta(atribute) ||
                    atelier.oferta(atribute) == ateliergasit->oferta(atribute) &&
                    atelier.getNume() < ateliergasit->getNume()) {
                    ateliergasit = &atelier;
                    salariuMax = atelier.oferta(atribute);
                }
            }
        }
        if (ateliergasit != nullptr) {
            ateliergasit->platesteangajat(bani, salariuMax);
        }
    }

    void cumpara(vector<Atelier>& ateliere) {
        Atelier* ateliergasit = nullptr;
        for (auto& atelier : ateliere) {
            if (atelier.verificastoc() && atelier.verificaplata(bani)) {
                if (ateliergasit == nullptr) {
                    ateliergasit = &atelier;
                }
                else if (
                    atelier.getBonus(preferinte[0]) == ateliergasit->getBonus(preferinte[0]) ?
                    atelier.getBonus(preferinte[1]) == ateliergasit->getBonus(preferinte[1]) ?
                    atelier.getBonus(preferinte[2]) == ateliergasit->getBonus(preferinte[2]) ?
                    atelier.getBonus(preferinte[3]) > ateliergasit->getBonus(preferinte[3]) :
                    atelier.getBonus(preferinte[2]) > ateliergasit->getBonus(preferinte[2]) :
                    atelier.getBonus(preferinte[1]) > ateliergasit->getBonus(preferinte[1]) : atelier.getBonus(preferinte[0]) > ateliergasit->getBonus(preferinte[0])) {
                    ateliergasit = &atelier;
                }
            }
        }
        if (ateliergasit != nullptr) {
            ateliergasit->vindeObiect(bani, atribute);
        }
    }

    int sumaAtribute() {
        int suma = 0;
        for (auto [_nume, _atribute] : atribute)
            suma += _atribute;
        return suma;
    }


    string& getNume() {
        return nume;
    }

    int getBani() const {
        return bani;
    }

    map<string, int> getAtribute() {
        return atribute;
    }

    int getCHR() {
        return atribute["CHR"];
    }

    int getSTR() {
        return atribute["STR"];
    }

    int getINT() {
        return atribute["INT"];
    }

    int getDEX() {
        return atribute["DEX"];
    }

};


int main() {

    int N;
    cin >> N;
    vector<Persoana> persoane;
    for (int i = 0; i < N; i++) {
        string _nume;
        cin >> _nume;
        vector<string> _preferinte;
        for (int j = 0; j < 4; j++) {
            string pref;
            cin >> pref;
            _preferinte.push_back(pref);
        }
        Persoana persoana(_nume, _preferinte);
        persoane.push_back(persoana);

    }

    int M;
    cin >> M;
    vector<Atelier> ateliere;
    for (int j = 0; j < M; j++) {
        string numeAtelier;
        int _bani, _pret, _prag;
        cin >> numeAtelier >> _bani >> _prag >> _pret;
        map<string, int> _coeficienti;
        int coef_str, coef_dex, coef_int, coef_chr;
        cin >> coef_str >> coef_dex >> coef_int >> coef_chr;
        _coeficienti.insert(make_pair("STR", coef_str));
        _coeficienti.insert(make_pair("DEX", coef_dex));
        _coeficienti.insert(make_pair("INT", coef_int));
        _coeficienti.insert(make_pair("CHR", coef_chr));

        map<string, int> _bonus;
        int bonus_str, bonus_dex, bonus_int, bonus_chr;
        cin >> bonus_str >> bonus_dex >> bonus_int >> bonus_chr;
        _bonus.insert(make_pair("STR", bonus_str));
        _bonus.insert(make_pair("DEX", bonus_dex));
        _bonus.insert(make_pair("INT", bonus_int));
        _bonus.insert(make_pair("CHR", bonus_chr));
        Atelier atelier(numeAtelier, _bani, _prag, _pret, _coeficienti, _bonus, 0, 0);
        ateliere.push_back(atelier);
    }


    int D;
    cin >> D;

    for (int i = 0; i < D; i++) {

        sort(persoane.begin(), persoane.end(),
            [](auto& left, auto& right) {
                if (left.getCHR() == right.getCHR()) {
                    return left.sumaAtribute() == right.sumaAtribute() ?
                        left.getNume() < right.getNume() : left.sumaAtribute() > right.sumaAtribute();
                }
                else {
                    return left.getCHR() > right.getCHR();
                }
            });
        for (auto& pers : persoane) {
            pers.cumpara(ateliere);
        }
        sort(persoane.begin(), persoane.end(),
            [](auto& left, auto& right) {
                if (left.getCHR() == right.getCHR()) {
                    return left.sumaAtribute() == right.sumaAtribute() ?
                        left.getNume() < right.getNume() : left.sumaAtribute() > right.sumaAtribute();
                }
                else {
                    return left.getCHR() > right.getCHR();
                }
            });
        for (auto& pers : persoane) {
            pers.munceste(ateliere);
        }
    }
    sort(persoane.begin(), persoane.end(),
        [](auto& left, auto& right) {
            return left.getBani() == right.getBani() ? left.sumaAtribute() == right.sumaAtribute() ?
                left.getNume() < right.getNume() : left.sumaAtribute() >
                right.sumaAtribute()
                : left.getBani() > right.getBani();

        });

    for (auto& persoana : persoane) {
        map<string, int> atribute = persoana.getAtribute();
        cout << persoana.getNume() << " ";
        cout << persoana.getSTR() << " " << persoana.getDEX() << " " << persoana.getINT() << " " << persoana.getCHR() << " ";
        cout << persoana.getBani() << endl;
    }
    return 0;
}