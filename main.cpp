#include <iostream>
#include <string>

using namespace std;

const char abecele[] = {
    'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i', 'j', 'k', 'l', 'm',
    'n', 'o', 'p', 'q', 'r', 's', 't', 'u', 'v', 'w', 'x', 'y', 'z'
};

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

int main()
{
    string tekstas;
    string raktas;

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

    cout << endl;
    cout << "Tekstas:" << tekstas << endl;
    cout << "Raktas:" << raktas << endl;

    // string atsakimas = tekstas;
    // for (int i = 0; i < tekstas.size(); ++i)
    // {
    //
    // }

    return 0;
}
