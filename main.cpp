#include <iostream>
#include <string>

using namespace std;

const char ABC[] = {
    'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i', 'j', 'k', 'l', 'm',
    'n', 'o', 'p', 'q', 'r', 's', 't', 'u', 'v', 'w', 'x', 'y', 'z'
};
const int N = size(ABC);

int raidesNumeris(char raide)
{
    for (int i = 0; i < N; i++)
    {
        if (ABC[i] == raide)
        {
            return i;
        }
    }
    return -1;
}

string raktoApdorojimas(const string& tekstas, const string& pradinisRaktas)
{
    int x = tekstas.size();
    int r = pradinisRaktas.size();

    string naujas_raktas;

    if (pradinisRaktas.size() < x)
    {
        for (int i = 0; i < x; ++i)
        {
            int n = i % r; // Raides indeksas
            char raide = pradinisRaktas[n];
            naujas_raktas.push_back(raide);
        }
    }
    else
    {
        return pradinisRaktas;
    }

    return naujas_raktas;
}

string sifravimas(const string& tekstas, const string& raktas)
{
    string sifruotasTekstas;

    for (int i = 0; i < tekstas.size(); i++)
    {
        int p = raidesNumeris(tekstas[i]);
        int k = raidesNumeris(raktas[i]);

        if (p == -1)
        {
            sifruotasTekstas.push_back(' ');
            continue;
        }

        int e = (p + k) % N;
        sifruotasTekstas.push_back(ABC[e]);
    }

    return sifruotasTekstas;
}

string desifravimas(string uzsifruotasTekstas, string raktas)
{
    string desifruotasTekstas;

    for (int i = 0; i < uzsifruotasTekstas.size(); i++)
    {
        int e = raidesNumeris(uzsifruotasTekstas[i]);
        int k = raidesNumeris(raktas[i]);

        if (e == -1)
        {
            desifruotasTekstas.push_back(' ');
            continue;
        }

        int d = (e - k + N) % N;
        desifruotasTekstas.push_back(ABC[d]);
    }

    return desifruotasTekstas;
}

int main()
{
    string tekstas;
    string raktas;

    // Sifravimas

    cout << "Tekstas:";
    getline(cin, tekstas);
    cout << "Raktas:";
    getline(cin, raktas);

    if (raktas.size() == 0 || tekstas.size() == 0)
    {
        cout << "Klaida: Nebuvo įvestas tekstas arba raktas!\n";
        exit(1);
    }

    raktas = raktoApdorojimas(tekstas, raktas);
    string atsakimas = sifravimas(tekstas, raktas);

    cout << '\n';
    cout << "Tekstas:" << tekstas << '\n';
    cout << "Raktas:" << raktas << '\n';
    cout << "Atsakimas:" << atsakimas << '\n';

    // Desifravimas

    cout << "Užšifruotas tekstas:";
    getline(cin, tekstas);
    cout << "Raktas:";
    getline(cin, raktas);

    if (raktas.size() == 0 || tekstas.size() == 0)
    {
        cout << "Klaida: Nebuvo įvestas tekstas arba raktas!\n";
        exit(1);
    }

    raktas = raktoApdorojimas(tekstas, raktas);
    atsakimas = desifravimas(tekstas, raktas);

    cout << '\n';
    cout << "Tekstas:" << tekstas << '\n';
    cout << "Raktas:" << raktas << '\n';
    cout << "Atsakimas:" << atsakimas << '\n';

    return 0;
}
