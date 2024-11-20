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

int raidesKodas(char raide)
{
    if (raide == ' ') return -1; // Tarpas

    if (!isalpha(raide)) return -2; // Nezinomas simbolis
    raide = toupper(raide);

    for (int i = 0; i < N_ABC; i++)
    {
        if (ABC[i] == raide)
            return i;
    }

    return -2;
}

string raktoGeneravimas(const string& tekstas, string& pradinisRaktas)
{
    int tekstoIlgis = tekstas.size();
    int raktoIlgis = pradinisRaktas.size();

    eilutesFiltravimas(pradinisRaktas);
    cout << "Pradinis raktas: " << pradinisRaktas << '\n';
    
    string sugeneruotasRaktas;

    if (pradinisRaktas.size() < tekstoIlgis)
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

    for (int i = 0; i < tekstas.size(); i++)
    {
        int p = raidesKodas(tekstas[i]);
        int k = raidesKodas(raktas[i]);

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
    string tekstas;

    for (int i = 0; i < sifras.size(); i++)
    {
        int e = raidesKodas(sifras[i]);
        int k = raidesKodas(raktas[i]);

        if (e == -1)
        {
            tekstas.push_back(' ');
            continue;
        }
        else if (e == -2)
        {
            tekstas.push_back('_');
            continue;
        }

        int d = (e - k + N_ABC) % N_ABC;
        tekstas.push_back(ABC[d]);
    }

    return tekstas;
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

            if (strEmpty(tekstas, raktas))
            {
                cout << "Nebuvo įvestas tekstas arba raktas.\n";
                break;
            }

            raktas = raktoGeneravimas(tekstas, raktas);
            atsakimas = sifravimas_ABC(tekstas, raktas);

            cout << "\nSugeneruotas raktas: " << raktas << '\n';
            cout << "\nAtsakimas: " << atsakimas << '\n';

            // Desifravimas
            cout << '\n';

            read(tekstas, "Šifras");
            read(raktas, "Raktas");

            if (strEmpty(tekstas, raktas))
            {
                cout << "Nebuvo įvestas tekstas arba raktas.\n";
                break;
            }

            raktas = raktoGeneravimas(tekstas, raktas);
            atsakimas = desifravimas_ABC(tekstas, raktas);

            cout << "\nPanaudotas raktas: " << raktas << '\n';
            cout << "\nAtsakimas: " << atsakimas << '\n';

            break;
        case 2:

            break;
        default:
            cout << "Neteisingas pasirinkimas.\n";
            break;
        }
    }

    return 0;
}
