#include <iostream>
using namespace std;

int split(string input, char delim, string tokens[], const int ARR_SIZE)
{
    string token = "";
    int count = 0;
    int length = input.length();
    if (input.length() == 0)
    {
        return 0;
    }

    for (int i = 0; i < length; i++)
    {
        if (input.at(i) == delim)
        {
            if (count == ARR_SIZE)
            {
                return -1;
            }
            tokens[count] = token;
            token = "";
            count++;
        }
        else
        {
            token += input.at(i);
        }
    }

    if (count == ARR_SIZE)
    {
        return -1;
    }
    tokens[count] = token;
    token = "";
    count++;

    return count;
}
