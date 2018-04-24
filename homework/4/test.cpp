#include <iostream>   // std::cout
#include <string>     // std::string, std::stoi
#include <cmath>


using namespace std;

int quick_mod (int, int, int);
bool is_number(const std::string& s);

int main ()
{
    string s = "rês";
    unsigned int a = (unsigned char) 'a';

    cout << a << endl;


    

}

int quick_mod (int n, int p, int mod)
{
    if (p == 0)
        return 1;
    
    if (p % 2 == 0)
        return (quick_mod (n, p/2, mod) * 
                quick_mod (n, p/2, mod)) % mod;
    else
        return (quick_mod(n, p-1, mod) * n) % mod;
}

bool is_number(const string & s)
{
    if (s.empty ()) return false;

    char c;
    for (int i = 0; i < s.size (); i++)
    {   
        c = s[i];
        if (isdigit(c))
            continue;
        else
            return false;
    }

    return true;
}