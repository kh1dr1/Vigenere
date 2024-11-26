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

int alphaCharCode(char ch)
{
    if (isalpha(ch)) // Abeceles raide
    {
        // Konvertuojame i didziasias raides
        ch = toupper(ch);

        // Randame simbolio (raides) indeksa abeceles masyve
        for (int i = 0; i < N_ABC; i++)
        {
            if (ABC[i] == ch) return i;
        }
    }
    else
    {
        return -1; // Nezinomas simbolis
    }

    return -1;
}

string vigenere_alpha(const string& text, const string& key, bool encrypt = true)
{
    string result;

    int keyLength = key.length();

    for (size_t i = 0; i < text.length(); i++)
    {
        int t = alphaCharCode(text[i]); // text
        int k = alphaCharCode(key[i % keyLength]); // key

        if (t == -1 || k == -1)
        {
            // Ignoruojame nezinomus simbolius
            result.push_back(text[i]);
            continue;
        }

        int index;

        if (encrypt)
        {
            index = (t + k) % N_ABC;
        }
        else
        {
            index = (t - k + N_ABC) % N_ABC;
        }

        result.push_back(ABC[index]);
    }

    return result;
}

string vigenere_ascii(const string &text, const string &key, bool encrypt = true)
{
    string result;

    int keyLength = key.length();
    int charRange = 126 - 32 + 1; // ASCII characters from 32 to 126

    for (size_t i = 0; i < text.length(); ++i)
    {
        char currentChar = text[i];
        char keyChar = key[i % keyLength];

        if (currentChar < 32 || currentChar > 126)
        {
            // Ignore characters outside the range
            result += currentChar;
            continue;
        }

        int offset = keyChar - 32;

        if (encrypt)
        {
            currentChar = 32 + (currentChar - 32 + offset) % charRange;
        }
        else
        {
            currentChar = 32 + (currentChar - 32 - offset + charRange) % charRange;
        }

        result += currentChar;
    }

    return result;
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
        cout << "\nPasirinkite pageidaujamą funkciją:\n";
        cout << "[1] Šifravimas su abėcėle\n";
        cout << "[2] Šifravimas per ASCII kodus\n";
        cout << "[0] Išeiti iš programos\n";

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
                atsakimas = vigenere_alpha(tekstas, raktas);
                cout << "\nAtsakimas: " << atsakimas << '\n';
            }

            // Desifravimas
            cout << '\n';

            read(tekstas, "Šifras");
            read(raktas, "Raktas");

            if (!strEmpty(tekstas, raktas))
            {
                atsakimas = vigenere_alpha(tekstas, raktas, false);
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
                atsakimas = vigenere_ascii(tekstas, raktas);
                cout << "\nAtsakimas: " << atsakimas << '\n';
            }

            // Desifravimas ASCII
            cout << '\n';

            read(tekstas, "Šifras");
            read(raktas, "Raktas");

            if (!strEmpty(tekstas, raktas))
            {
                atsakimas = vigenere_ascii(tekstas, raktas, false);
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
