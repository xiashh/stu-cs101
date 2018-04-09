#include <string>
#include <regex>
#include <iostream>
#include <istream>
#include <ostream>
#include <sstream>

using namespace std;

/* record frequencies of every char */
static unsigned int frequencies[256];

/* indicate to decoding or encoding */
static unsigned int decode_or_encode;

int decide_action ();
void cal_frequency ();
void print_frequency ();
void compress ();
void decompress ();

int main () {
    decide_action ();

    if (decode_or_encode == 1)
    {
        compress ();
    }
    else if (decode_or_encode == 0)
    {
        decompress ();
    }
    

}

/* decide whether decode(0) the data or encode(1) the data */
int decide_action ()
{   
    unsigned char c;
    string arg;
    cin >> noskipws;

    for (int i = 0; i < 6; i++)
    {
        cin >> c;
        arg.append(1, c);
    }
    
    if (arg == "DECODE") decode_or_encode = 0;
    else if (arg == "ENCODE") decode_or_encode = 1;
}

/* compress the data and print it */
void compress ()
{
    cal_frequency ();
    print_frequency ();
    printf("now we will compress the data.\n");
}

/* calculate the frequencies of data */
void cal_frequency ()
{
    unsigned char c;

    for (int i = 0; i < 256; i++)
    {
        frequencies[i] = 0;
    }

    while (cin >> c)
    {
        frequencies[c]++;
    }
}

/* print the frequency of every char */
void print_frequency ()
{
    for (int i = 0; i < 256; i++)
    {
        printf ("frequency of char %c = %d\n", i, frequencies[i]);
    }
}

/* decompress the data and print it */
void decompress ()
{
    printf("now we will decompress the data.\n");
}