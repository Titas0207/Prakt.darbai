#include <iostream>
#include <fstream>
#include <iomanip>
#include <string>

using namespace std;


string kategorijosPavadinimas(int nr) {
    if (nr == 1) return "Dviraciai";
    if (nr == 2) return "Dalys";
    return "Aksesuarai";
}

bool arTinkamaKategorija(string kat) {
    return kat == "Dviraciai" || kat == "Dalys" || kat == "Aksesuarai";
}

bool nuskaitytiDuomenis(string failas, string kategorijos[], string pavadinimai[],
                        double kainos[], int kiekiai[], int& n, int maxIrasu) {
    ifstream in(failas);
    if (!in) {
        cout << "Klaida: nepavyko atidaryti failo " << failas << endl;
        return false;
    }

    in >> n;
    if (!in || n < 1 || n > maxIrasu) {
        cout << "Klaida: neteisingas irasu skaicius (turi buti nuo 1 iki "
             << maxIrasu << ")." << endl;
        return false;
    }

    for (int i = 0; i < n; i++) {
        in >> ws;
        getline(in, kategorijos[i], ';');
        getline(in, pavadinimai[i], ';');
        in >> kainos[i];
        in.ignore();
        in >> kiekiai[i];

        if (!in) {
            cout << "Klaida: nepavyko nuskaityti " << i + 1 << " iraso (is "
                 << n << ")." << endl;
            return false;
        }
        if (!arTinkamaKategorija(kategorijos[i])) {
            cout << "Klaida: neteisinga kategorija " << i + 1 << " irase." << endl;
            return false;
        }
        if (kainos[i] <= 0) {
            cout << "Klaida: kaina turi buti teigiama (" << i + 1 << " irasas)." << endl;
            return false;
        }
        if (kiekiai[i] <= 0) {
            cout << "Klaida: kiekis turi buti teigiamas (" << i + 1 << " irasas)." << endl;
            return false;
        }
    }
    return true;
}


double eilutesSuma(double kaina, int kiekis) {
    return kaina * kiekis;
}

double nuolaida(double suma, int kiekis) {
    if (kiekis >= 10) {
        return suma * 0.10;
    }
    return 0;
}

double bendraSuma(double kainos[], int kiekiai[], int n) {
    double suma = 0;
    for (int i = 0; i < n; i++) {
        suma += eilutesSuma(kainos[i], kiekiai[i]);
    }
    return suma;
}

double bendraNuolaida(double kainos[], int kiekiai[], int n) {
    double suma = 0;
    for (int i = 0; i < n; i++) {
        double eilute = eilutesSuma(kainos[i], kiekiai[i]);
        suma += nuolaida(eilute, kiekiai[i]);
    }
    return suma;
}

double kategorijosSuma(string kategorijos[], double kainos[], int kiekiai[], int n,
                       string kategorija) {
    double suma = 0;
    for (int i = 0; i < n; i++) {
        if (kategorijos[i] == kategorija) {
            double eilute = eilutesSuma(kainos[i], kiekiai[i]);
            suma += eilute - nuolaida(eilute, kiekiai[i]);
        }
    }
    return suma;
}


int spausdintiLentele(ostream& out, string kategorijos[], string pavadinimai[],
                      double kainos[], int kiekiai[], int n, string kategorija) {
    out << fixed << setprecision(2);
    out << left << setw(12) << "Kategorija" << setw(48) << "Pavadinimas"
        << right << setw(10) << "Kaina" << setw(8) << "Kiekis"
        << setw(12) << "Suma" << setw(12) << "Nuolaida" << setw(12) << "Moketina" << endl;
    out << string(114, '-') << endl;

    int kiek = 0;
    for (int i = 0; i < n; i++) {
        if (kategorija == "" || kategorijos[i] == kategorija) {
            double suma = eilutesSuma(kainos[i], kiekiai[i]);
            double nuol = nuolaida(suma, kiekiai[i]);
            out << left << setw(12) << kategorijos[i] << setw(48) << pavadinimai[i]
                << right << setw(10) << kainos[i] << setw(8) << kiekiai[i]
                << setw(12) << suma << setw(12) << nuol
                << setw(12) << suma - nuol << endl;
            kiek++;
        }
    }
    return kiek;
}

void spausdintiSumas(ostream& out, double kainos[], int kiekiai[], int n) {
    double pries = bendraSuma(kainos, kiekiai, n);
    double nuol = bendraNuolaida(kainos, kiekiai, n);
    out << fixed << setprecision(2);
    out << "Suma pries nuolaidas:    " << pries << " EUR" << endl;
    out << "Bendra nuolaida:         " << nuol << " EUR" << endl;
    out << "Galutine moketina suma:  " << pries - nuol << " EUR" << endl;
}

void spausdintiKategorijuSumas(ostream& out, string kategorijos[], double kainos[],
                               int kiekiai[], int n) {
    out << fixed << setprecision(2);
    for (int nr = 1; nr <= 3; nr++) {
        string kat = kategorijosPavadinimas(nr);
        out << left << setw(12) << kat << right << setw(12)
            << kategorijosSuma(kategorijos, kainos, kiekiai, n, kat) << " EUR" << endl;
    }
}

void spausdintiAtaskaita(ostream& out, string kategorijos[], string pavadinimai[],
                         double kainos[], int kiekiai[], int n) {
    out << "=== DVIRACIU PARDUOTUVES UZSAKYMO ATASKAITA ===" << endl << endl;
    spausdintiLentele(out, kategorijos, pavadinimai, kainos, kiekiai, n, "");
    out << endl << "--- Viso uzsakymo sumos ---" << endl;
    spausdintiSumas(out, kainos, kiekiai, n);
    out << endl << "--- Kategoriju suvestine (po nuolaidu) ---" << endl;
    spausdintiKategorijuSumas(out, kategorijos, kainos, kiekiai, n);
}


bool issaugotiAtaskaita(string failas, string kategorijos[], string pavadinimai[],
                        double kainos[], int kiekiai[], int n) {
    ofstream out(failas);
    if (!out) {
        cout << "Klaida: nepavyko atidaryti failo " << failas << " rasymui." << endl;
        return false;
    }
    spausdintiAtaskaita(out, kategorijos, pavadinimai, kainos, kiekiai, n);
    out.close();
    if (out.fail()) {
        cout << "Klaida: nepavyko irasyti ataskaitos." << endl;
        return false;
    }
    return true;
}


void rodytiMeniu() {
    cout << endl;
    cout << "===== MENIU =====" << endl;
    cout << "1. Perziureti visas uzsakymo prekes" << endl;
    cout << "2. Perziureti pasirinktos kategorijos prekes" << endl;
    cout << "3. Perziureti viso uzsakymo sumas" << endl;
    cout << "4. Perziureti sumas pagal kategorijas" << endl;
    cout << "5. Parodyti visa uzsakymo ataskaita" << endl;
    cout << "6. Issaugoti visa ataskaita i faila" << endl;
    cout << "7. Iseiti" << endl;
}


int skaitytiSkaiciu() {
    int x;
    if (!(cin >> x)) {
        cin.clear();
        x = -1;
    }
    cin.ignore(10000, '\n');
    return x;
}


string pasirinktiKategorija() {
    int nr = -1;
    while (nr < 1 || nr > 3) {
        cout << endl;
        cout << "1. Dviraciai" << endl;
        cout << "2. Dalys" << endl;
        cout << "3. Aksesuarai" << endl;
        cout << "Pasirinkite kategorija (1-3): ";
        nr = skaitytiSkaiciu();
        if (nr < 1 || nr > 3) {
            cout << "Netinkamas pasirinkimas, bandykite dar karta." << endl;
        }
    }
    return kategorijosPavadinimas(nr);
}



int main() {
    const int MAX_IRASU = 100;
    string kategorijos[MAX_IRASU];
    string pavadinimai[MAX_IRASU];
    double kainos[MAX_IRASU];
    int kiekiai[MAX_IRASU];
    int n = 0;

    if (!nuskaitytiDuomenis("uzsakymas.txt", kategorijos, pavadinimai, kainos,
                            kiekiai, n, MAX_IRASU)) {
        cout << "Programa baigia darba." << endl;
        return 1;
    }
    cout << "Sekmingai nuskaityta irasu: " << n << endl;

    int pasirinkimas = 0;
    while (pasirinkimas != 7) {
        rodytiMeniu();
        cout << "Jusu pasirinkimas: ";
        pasirinkimas = skaitytiSkaiciu();
        cout << endl;

        if (pasirinkimas == 1) {
            spausdintiLentele(cout, kategorijos, pavadinimai, kainos, kiekiai, n, "");
        } else if (pasirinkimas == 2) {
            string kat = pasirinktiKategorija();
            cout << endl;
            int kiek = spausdintiLentele(cout, kategorijos, pavadinimai, kainos,
                                         kiekiai, n, kat);
            if (kiek == 0) {
                cout << "Sioje kategorijoje (" << kat << ") prekiu nera." << endl;
            }
            cout << fixed << setprecision(2);
            cout << endl << "Kategorijos " << kat << " moketina suma: "
                 << kategorijosSuma(kategorijos, kainos, kiekiai, n, kat) << " EUR" << endl;
        } else if (pasirinkimas == 3) {
            spausdintiSumas(cout, kainos, kiekiai, n);
        } else if (pasirinkimas == 4) {
            spausdintiKategorijuSumas(cout, kategorijos, kainos, kiekiai, n);
        } else if (pasirinkimas == 5) {
            spausdintiAtaskaita(cout, kategorijos, pavadinimai, kainos, kiekiai, n);
        } else if (pasirinkimas == 6) {
            if (issaugotiAtaskaita("ataskaita.txt", kategorijos, pavadinimai,
                                   kainos, kiekiai, n)) {
                cout << "Ataskaita sekmingai issaugota faile ataskaita.txt" << endl;
            }
        } else if (pasirinkimas == 7) {
            cout << "Viso gero!" << endl;
        } else {
            cout << "Netinkamas pasirinkimas, bandykite dar karta (1-7)." << endl;
        }
    }
    return 0;
}