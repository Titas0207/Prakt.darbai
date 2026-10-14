#include <iostream>
#include <iomanip>
#include <string>
using namespace std;


const double GBP_Bendras  = 0.8729;
const double GBP_Pirkti   = 0.8600;
const double GBP_Parduoti = 0.9220;

const double USD_Bendras  = 1.1793;
const double USD_Pirkti   = 1.1460;
const double USD_Parduoti = 1.2340;

const double INR_Bendras  = 104.6918;
const double INR_Pirkti   = 101.3862;
const double INR_Parduoti = 107.8546;

int main() {
    int veiksmas, valiuta;
    double suma;

    cout << fixed << setprecision(2);

    while (true) {
        cout << "\n===== VALIUTOS KEITYKLA =====" << endl;
        cout << "1. Valiutos kurso palyginimas su euru" << endl;
        cout << "2. Valiutos pirkimas (EUR -> pasirinkta valiuta)" << endl;
        cout << "3. Valiutos pardavimas (pasirinkta valiuta -> EUR)" << endl;
        cout << "4. Iseiti" << endl;
        cin >> veiksmas;

        if (cin.fail()) {
            cin.clear();
            cin.ignore(10000, '\n');
            cout << "Klaida: neteisingas meniu pasirinkimas!" << endl;
            continue;
        }

        if (veiksmas == 4) {
            cout << "Viso gero!" << endl;
            break;
        }

        if (veiksmas < 1 || veiksmas > 4) {
            cout << "Klaida: neteisingas meniu pasirinkimas!" << endl;
            continue;
        }

        cout << "--- Pasirinkite valiuta ---" << endl;
        cout << "1 - GBP (Didziosios Britanijos svaras)" << endl;
        cout << "2 - USD (JAV doleris)" << endl;
        cout << "3 - INR (Indijos rupija)" << endl;
        cin >> valiuta;

        if (cin.fail()) {
            cin.clear();
            cin.ignore(10000, '\n');
            cout << "Klaida: neteisingas valiutos pasirinkimas!" << endl;
            continue;
        }

        if (valiuta < 1 || valiuta > 3) {
            cout << "Klaida: neteisingas valiutos pasirinkimas!" << endl;
            continue;
        }


        if (veiksmas == 1) {
            cout << "--- Kursu palyginimas su EUR ---" << endl;
            cout << "1 EUR = ";
            if (valiuta == 1) {
                cout << GBP_Bendras << " GBP (bendras)" << endl;
                cout << "Pirkimo kursas:   " << GBP_Pirkti << endl;
                cout << "Pardavimo kursas: " << GBP_Parduoti << endl;
            } else if (valiuta == 2) {
                cout << USD_Bendras << " USD (bendras)" << endl;
                cout << "Pirkimo kursas:   " << USD_Pirkti << endl;
                cout << "Pardavimo kursas: " << USD_Parduoti << endl;
            } else {
                cout << INR_Bendras << " INR (bendras)" << endl;
                cout << "Pirkimo kursas:   " << INR_Pirkti << endl;
                cout << "Pardavimo kursas: " << INR_Parduoti << endl;
            }
            continue;
        }


        cout << "Iveskite suma: ";
        cin >> suma;

        if (cin.fail()) {
            cin.clear();
            cin.ignore(10000, '\n');
            cout << "Klaida: suma turi buti skaicius!" << endl;
            continue;
        }

        if (suma <= 0) {
            cout << "Klaida: suma turi buti teigiama!" << endl;
            continue;
        }

        string pavadinimas;
        double kursas;


        if (veiksmas == 2) {
            if (valiuta == 1) {
                pavadinimas = "GBP";
                kursas = GBP_Pirkti;
            } else if (valiuta == 2) {
                pavadinimas = "USD";
                kursas = USD_Pirkti;
            } else {
                pavadinimas = "INR";
                kursas = INR_Pirkti;
            }
            double gauta = suma * kursas;
            cout << "\n--- Pirkimo rezultatas ---" << endl;
            cout << "Pradine suma: " << suma << " EUR" << endl;
            cout << "Pasirinkta valiuta: " << pavadinimas << endl;
            cout << "Gaunama suma: " << gauta << " " << pavadinimas << endl;
        }

        else {
            if (valiuta == 1) {
                pavadinimas = "GBP";
                kursas = GBP_Parduoti;
            } else if (valiuta == 2) {
                pavadinimas = "USD";
                kursas = USD_Parduoti;
            } else {
                pavadinimas = "INR";
                kursas = INR_Parduoti;
            }
            double gauta = suma / kursas;
            cout << "--- Pardavimo rezultatas ---" << endl;
            cout << "Pradine suma: " << suma << " " << pavadinimas << endl;
            cout << "Pasirinkta valiuta: " << pavadinimas << endl;
            cout << "Gaunama suma: " << gauta << " EUR" << endl;
        }
    }

    return 0;
}