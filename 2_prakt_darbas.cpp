#include <iostream>
#include <iomanip>
#include <string>

using namespace std;

int main()
{
    const int MAX_MOK = 100;
    const int MAX_PAZ = 10;

    string vardai[MAX_MOK];
    int pazymiai[MAX_MOK][MAX_PAZ];
    int pazSk[MAX_MOK];

    int sk = 0;
    int meniu = 0;

    do
    {
        cout << "\n===== MOKINIU PAZYMIU SISTEMA =====\n";
        cout << "1. Ivesti mokini ir jo pazymius\n";
        cout << "2. Perziureti visu mokiniu pazymius\n";
        cout << "3. Perziureti konkretaus mokinio pazymius\n";
        cout << "4. Atnaujinti pazymi\n";
        cout << "5. Apskaiciuoti mokinio vidurki\n";
        cout << "6. Pasalinti mokini\n";
        cout << "7. Iseiti\n";
        cout << "Jusu pasirinkimas: ";
        cin >> meniu;

        if (meniu == 1)
        {
            if (sk >= MAX_MOK)
            {
                cout << "Pasiektas mokiniu limitas (" << MAX_MOK << ").\n";
            }
            else
            {
                cout << "Iveskite mokinio varda: ";
                cin >> ws;
                getline(cin, vardai[sk]);

                int kiek;
                do
                {
                    cout << "Kiek pazymiu turi mokinys (0-" << MAX_PAZ << "): ";
                    cin >> kiek;
                    if (kiek < 0 || kiek > MAX_PAZ)
                        cout << "Neteisingas kiekis. Leidziama nuo 0 iki " << MAX_PAZ << ".\n";
                } while (kiek < 0 || kiek > MAX_PAZ);

                pazSk[sk] = kiek;

                for (int j = 0; j < kiek; j++)
                {
                    int p;
                    do
                    {
                        cout << j + 1 << "-asis pazymys (1-10): ";
                        cin >> p;
                        if (p < 1 || p > 10)
                            cout << "Neteisingas pazymys. Iveskite skaiciu nuo 1 iki 10.\n";
                    } while (p < 1 || p > 10);

                    pazymiai[sk][j] = p;
                }

                sk++;
                cout << "Mokinys pridetas.\n";
            }
        }
        else if (meniu == 2)
        {
            if (sk == 0)
            {
                cout << "Sarasas tuscias.\n";
            }
            else
            {
                for (int i = 0; i < sk; i++)
                {
                    cout << i + 1 << ". " << vardai[i] << ": ";
                    if (pazSk[i] == 0)
                        cout << "pazymiu nera";
                    for (int j = 0; j < pazSk[i]; j++)
                        cout << pazymiai[i][j] << " ";
                    cout << "\n";
                }
            }
        }
        else if (meniu == 3)
        {
            if (sk == 0)
            {
                cout << "Sarasas tuscias.\n";
            }
            else
            {
                int nr;
                do
                {
                    cout << "Iveskite mokinio numeri (1-" << sk << ", 0 - atgal i meniu): ";
                    cin >> nr;
                    if (nr < 0 || nr > sk)
                        cout << "Neteisingas mokinio numeris. Iveskite skaiciu nuo 1 iki " << sk << ".\n";
                } while (nr < 0 || nr > sk);

                if (nr != 0)
                {
                    int i = nr - 1;
                    cout << "Mokinys: " << vardai[i] << "\n";
                    if (pazSk[i] == 0)
                    {
                        cout << "Pazymiu nera.\n";
                    }
                    else
                    {
                        cout << "Pazymiai: ";
                        for (int j = 0; j < pazSk[i]; j++)
                            cout << pazymiai[i][j] << " ";
                        cout << "\n";
                    }
                }
            }
        }
        else if (meniu == 4)
        {
            if (sk == 0)
            {
                cout << "Sarasas tuscias.\n";
            }
            else
            {
                int nr;
                do
                {
                    cout << "Iveskite mokinio numeri (1-" << sk << ", 0 - atgal i meniu): ";
                    cin >> nr;
                    if (nr < 0 || nr > sk)
                        cout << "Neteisingas mokinio numeris. Iveskite skaiciu nuo 1 iki " << sk << ".\n";
                } while (nr < 0 || nr > sk);

                if (nr != 0)
                {
                    int i = nr - 1;

                    if (pazSk[i] == 0)
                    {
                        cout << "Mokinys pazymiu neturi.\n";
                    }
                    else
                    {
                        cout << "Mokinio " << vardai[i] << " pazymiai: ";
                        for (int j = 0; j < pazSk[i]; j++)
                            cout << j + 1 << ") " << pazymiai[i][j] << "  ";
                        cout << "\n";

                        int pn;
                        do
                        {
                            cout << "Iveskite pazymio numeri (1-" << pazSk[i] << ", 0 - atgal i meniu): ";
                            cin >> pn;
                            if (pn < 0 || pn > pazSk[i])
                                cout << "Neteisingas pazymio numeris. Iveskite skaiciu nuo 1 iki " << pazSk[i] << ".\n";
                        } while (pn < 0 || pn > pazSk[i]);

                        if (pn != 0)
                        {
                            int naujas;
                            do
                            {
                                cout << "Iveskite nauja pazymi (1-10): ";
                                cin >> naujas;
                                if (naujas < 1 || naujas > 10)
                                    cout << "Neteisingas pazymys. Iveskite skaiciu nuo 1 iki 10.\n";
                            } while (naujas < 1 || naujas > 10);

                            pazymiai[i][pn - 1] = naujas;
                            cout << "Pazymys atnaujintas.\n";
                        }
                    }
                }
            }
        }
        else if (meniu == 5)
        {
            if (sk == 0)
            {
                cout << "Sarasas tuscias.\n";
            }
            else
            {
                int nr;
                do
                {
                    cout << "Iveskite mokinio numeri (1-" << sk << ", 0 - atgal i meniu): ";
                    cin >> nr;
                    if (nr < 0 || nr > sk)
                        cout << "Neteisingas mokinio numeris. Iveskite skaiciu nuo 1 iki " << sk << ".\n";
                } while (nr < 0 || nr > sk);

                if (nr != 0)
                {
                    int i = nr - 1;

                    if (pazSk[i] == 0)
                    {
                        cout << "Mokinys pazymiu neturi.\n";
                    }
                    else
                    {
                        int suma = 0;
                        for (int j = 0; j < pazSk[i]; j++)
                            suma += pazymiai[i][j];

                        double vid = (double)suma / pazSk[i];
                        cout << "Mokinio " << vardai[i] << " vidurkis: "
                             << fixed << setprecision(2) << vid << "\n";
                    }
                }
            }
        }
        else if (meniu == 6)
        {
            if (sk == 0)
            {
                cout << "Sarasas tuscias.\n";
            }
            else
            {
                int nr;
                do
                {
                    cout << "Iveskite mokinio numeri (1-" << sk << ", 0 - atgal i meniu): ";
                    cin >> nr;
                    if (nr < 0 || nr > sk)
                        cout << "Neteisingas mokinio numeris. Iveskite skaiciu nuo 1 iki " << sk << ".\n";
                } while (nr < 0 || nr > sk);

                if (nr != 0)
                {
                    int i = nr - 1;

                    for (int k = i; k < sk - 1; k++)
                    {
                        vardai[k] = vardai[k + 1];
                        pazSk[k] = pazSk[k + 1];
                        for (int j = 0; j < MAX_PAZ; j++)
                            pazymiai[k][j] = pazymiai[k + 1][j];
                    }

                    vardai[sk - 1] = "";
                    pazSk[sk - 1] = 0;
                    for (int j = 0; j < MAX_PAZ; j++)
                        pazymiai[sk - 1][j] = 0;

                    sk--;
                    cout << "Mokinys pasalintas.\n";
                }
            }
        }
        else if (meniu == 7)
        {
            cout << "Programa baigta.\n";
        }
        else
        {
            cout << "Neteisingas pasirinkimas. Iveskite skaiciu nuo 1 iki 7.\n";
        }

    } while (meniu != 7);

    return 0;
}