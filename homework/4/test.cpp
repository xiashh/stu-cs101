#include <iostream>   // std::cout
#include <string>     // std::string, std::stoi


using namespace std;

int quick_mod (int, int, int);
bool is_number(const std::string& s);

int main ()
{
    string s = "12";
    int hash_code = 0;
    int str_len= s.size ();
    int n = 0;

    for (int i = 0; i < str_len; i++)
    {
        hash_code += (s[i] * quick_mod (2, 8*(str_len-i-1), 39)) % 39;
    }

    cout << stoi(s, nullptr, 10) + 1<< endl;

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