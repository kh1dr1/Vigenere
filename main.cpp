#include <iostream>
#include <string>

using namespace std;

const char abecele[] = {
    'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i', 'j', 'k', 'l', 'm',
    'n', 'o', 'p', 'q', 'r', 's', 't', 'u', 'v', 'w', 'x', 'y', 'z'
};

int rask_raides_numeri(char raide)
{
    for (int i = 0; i < size(abecele); i++)
    {
        if (abecele[i] == raide)
        {
            return i;
        }   
    }
    return -1;
}

string sugeneruok_rakta(string tekstas, string vart_raktas)
{
    int x = tekstas.size();
    int r = vart_raktas.size();

    string naujas_raktas;

    if (vart_raktas.size() < x)
    {
        for (int i = 0; i < x; ++i)
        {
            int n = i % r; // Raides indeksas
            char raide = vart_raktas[n];
            naujas_raktas.push_back(raide);
        }
    }
    else
    {
        return vart_raktas;
    }
    
    return naujas_raktas;
}

string sifravimas(string tekstas, string raktas)
{
    string sifras;

    for (int i = 0; i < tekstas.size(); i++)
    {
        int p = rask_raides_numeri(tekstas[i]);
        int k = rask_raides_numeri(raktas[i]);

        if (p == -1)
        {
            sifras.push_back(' ');
            continue;
        }

        int r = (p + k) % 26;
        sifras.push_back(abecele[r]);
    }
    
    return sifras;
}

int main()
{
    string tekstas;
    string raktas;
    string atsakimas;
    
    cout << "Tekstas:";
    getline(cin, tekstas);
    cout << "Raktas:";
    getline(cin, raktas);

    if (raktas.size() == 0 || tekstas.size() == 0)
    {
        cout << "Klaida: Nebuvo įvestas tekstas arba raktas!\n";
        exit(1);
    }

    raktas = sugeneruok_rakta(tekstas, raktas);
    atsakimas = sifravimas(tekstas, raktas);

    cout << endl;
    
    cout << "Tekstas:" << tekstas << endl;
    cout << "Raktas:" << raktas << endl;
    cout << "Atsakimas:" << atsakimas << endl;

    return 0;
}
