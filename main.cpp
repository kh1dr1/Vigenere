#include <iostream>
#include <string>
#include <cctype>
#include <limits>

using namespace std;

const char ABC[] = {
    'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J', 'K', 'L', 'M',
    'N', 'O', 'P', 'Q', 'R', 'S', 'T', 'U', 'V', 'W', 'X', 'Y', 'Z'
};
const int N_ABC = size(ABC);

void eilutesFiltravimas(string& str)
{
    for (int i = 0; i < str.length(); i++)
    {
        char simbolis = str[i];
        if (simbolis == ' ') continue;

        if (isalpha(simbolis))
            str[i] = toupper(simbolis);
        else
            str[i] = '_';
    }
}

int simbolioKodas_ABC(char simbolis)
{
    if (simbolis == ' ') return -1; // Tarpas

    if (!isalpha(simbolis)) return -2; // Nezinomas simbolis
    simbolis = toupper(simbolis);

    for (int i = 0; i < N_ABC; i++)
    {
        if (ABC[i] == simbolis)
            return i;
    }

    return -2;
}

int simbolioKodas_ASCII(char simbolis)
{
    if (simbolis == ' ') return -1; // Tarpas
    if (!isalpha(simbolis)) return -2; // Nezinomas simbolis
    return static_cast<int>(toupper(simbolis));
}

string raktoGeneravimas(const string& tekstas, string& pradinisRaktas)
{
    int tekstoIlgis = tekstas.length();
    int raktoIlgis = pradinisRaktas.length();

    eilutesFiltravimas(pradinisRaktas);
    cout << "Pradinis raktas: " << pradinisRaktas << '\n';
    
    string sugeneruotasRaktas;

    if (pradinisRaktas.length() < tekstoIlgis)
    {
        for (int i = 0; i < tekstoIlgis; ++i)
        {
            int n = i % raktoIlgis; // Raides indeksas
            char raide = pradinisRaktas[n];
            sugeneruotasRaktas.push_back(raide);
        }
    }
    else
        return pradinisRaktas;

    return sugeneruotasRaktas;
}

string sifravimas_ABC(const string& tekstas, const string& raktas)
{
    string sifras;

    for (int i = 0; i < tekstas.length(); i++)
    {
        int p = simbolioKodas_ABC(tekstas[i]);
        int k = simbolioKodas_ABC(raktas[i]);

        if (p == -1)
        {
            sifras.push_back(' ');
            continue;
        }
        else if (p == -2)
        {
            sifras.push_back('_');
            continue;
        }
        
        int e = (p + k) % N_ABC;
        sifras.push_back(ABC[e]);
    }
    return sifras;
}

string desifravimas_ABC(const string& sifras, const string& raktas)
{
    string pradinisTekstas;

    for (int i = 0; i < sifras.length(); i++)
    {
        int e = simbolioKodas_ABC(sifras[i]);
        int k = simbolioKodas_ABC(raktas[i]);

        if (e == -1)
        {
            pradinisTekstas.push_back(' ');
            continue;
        }
        else if (e == -2)
        {
            pradinisTekstas.push_back('_');
            continue;
        }

        int d = (e - k + N_ABC) % N_ABC;
        pradinisTekstas.push_back(ABC[d]);
    }

    return pradinisTekstas;
}

string sifravimas_ASCII(const string &tekstas, const string &raktas)
{
    string sifras;

    for (int i = 0, j = 0; i < tekstas.length(); ++i)
    {
        char c = tekstas[i];
        if (c >= 'a' && c <= 'z')
            c += 'A' - 'a';
        else if (c < 'A' || c > 'Z')
            continue;
        sifras += (c + raktas[j] - 2 * 'A') % 26 + 'A'; // added 'A' to bring it in range of ASCII alphabet [ 65-90 | A-Z ]
        j = (j + 1) % raktas.length();
    }

    return sifras;
}

string desifravimas_ASCII(const string& sifras, const string& raktas)
{
    string pradinisTekstas;

    for (int i = 0, j = 0; i < sifras.length(); ++i)
    {
        char c = sifras[i];
        if (c >= 'a' && c <= 'z')
            c += 'A' - 'a';
        else if (c < 'A' || c > 'Z')
            continue;
        pradinisTekstas += (c - raktas[j] + 26) % 26 + 'A'; // added 'A' to bring it in range of ASCII alphabet [ 65-90 | A-Z ]
        j = (j + 1) % raktas.length();
    }

    return pradinisTekstas;
}

void read(string& str, const string& msg)
{
    cout << msg << ": ";
    getline(cin, str);
}

bool strEmpty(const string& str1, const string& str2)
{
    if (str1.empty() || str2.empty()) return true;
    return false;
}

int main()
{
    int mp = -1; // Meniu pasirinkimas

    string tekstas;
    string raktas;
    string atsakimas;

    while (mp != 0)
    {
        cout << "\nPasirinkite metodą, kaip šifruoti tekstą:\n";
        cout << "1. Abėcėlė\n";
        cout << "2. ASCII\n";

        cout << ">> ";
        cin >> mp;

        cin.ignore(numeric_limits<streamsize>::max(), '\n');

        switch (mp)
        {
        case 0:
            cout << "Išeinama...\n";
            break;
        case 1: 
            // Sifravimas su abecele
            cout << '\n';

            read(tekstas, "Pradinis tekstas");
            read(raktas, "Slaptas raktas");

            if (!strEmpty(tekstas, raktas))
            {
                raktas = raktoGeneravimas(tekstas, raktas);
                atsakimas = sifravimas_ABC(tekstas, raktas);

                cout << "\nSugeneruotas raktas: " << raktas << '\n';
                cout << "\nAtsakimas: " << atsakimas << '\n';
            }

            // Desifravimas
            cout << '\n';

            read(tekstas, "Šifras");
            read(raktas, "Raktas");

            if (!strEmpty(tekstas, raktas))
            {
                raktas = raktoGeneravimas(tekstas, raktas);
                atsakimas = desifravimas_ABC(tekstas, raktas);

                cout << "\nPanaudotas raktas: " << raktas << '\n';
                cout << "\nAtsakimas: " << atsakimas << '\n';
            }

            break;
        case 2:
            // ASCII sifravimas, desifravimas
            cout << '\n';

            read(tekstas, "Pradinis tekstas");
            read(raktas, "Slaptas raktas");

            if (!strEmpty(tekstas, raktas))
            {
                raktas = raktoGeneravimas(tekstas, raktas);
                atsakimas = sifravimas_ASCII(tekstas, raktas);

                cout << "\nSugeneruotas raktas: " << raktas << '\n';
                cout << "\nAtsakimas: " << atsakimas << '\n';
            }

            // Desifravimas ASCII
            cout << '\n';

            read(tekstas, "Šifras");
            read(raktas, "Raktas");

            if (!strEmpty(tekstas, raktas))
            {
                raktas = raktoGeneravimas(tekstas, raktas);
                atsakimas = desifravimas_ASCII(tekstas, raktas);

                cout << "\nPanaudotas raktas: " << raktas << '\n';
                cout << "\nAtsakimas: " << atsakimas << '\n';
            }

            break;
        default:
            cout << "Neteisingas pasirinkimas.\n";
            break;
        }
    }

    return 0;
}
