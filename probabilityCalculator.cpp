#include <iostream>
#include <string>
#include <math.h>
#include "BigInt.hpp"
using namespace std;

BigInt factorial(int a)
{
    BigInt sum = 1;
    if (a < 0)
    {
        return 0;
    }
    for(int i = 1; i < a+1; ++i)
    {
        sum = i * sum;
    }
    return sum;
}

__long_double_t binomialMass(double p, int k, int n)
{
    double q = 1 - p;
    BigInt binomialConstant = factorial(n)/(factorial(k)*factorial(n-k));
    int digits = binomialConstant.to_string().length();
    long long constantThing;
    __long_double_t otherThing = pow(p,k)*pow(q,n-k);
    if (digits < 19)
    {
        constantThing = binomialConstant.to_long_long();
    }
    else
    {
        BigInt divisionVar = 10;
        divisionVar = pow(divisionVar,digits-18);
        binomialConstant = binomialConstant / divisionVar;
        otherThing = otherThing * pow(10,digits-18);
        constantThing = binomialConstant.to_long_long();
    }
    
    __long_double_t answer = constantThing * otherThing;
    //cout << constantThing << ":" << otherThing << endl;
    return answer;
}

__long_double_t probAtleastOnce(double p ,int n)
{
    double q = 1 - p;
    return (1-pow(q,n));
}

int main(int argc, char** argv)
{
    if (argc != 4)
    {
        cout << "Requires 3 args (Format: p, k, n)" << endl;
        return 1;
    }
    double p = atof(argv[1]);
    if ((p < 0) || (p>1))
    {
        cout << "Arg p is required to be between 0 and 1" << endl;
        return 1;
    }
    double q = 1 - p;
    int k;
    int n = atoi(argv[3]);
    if (n < 0)
    {
        cout << "Cannot calculate negative n" << endl;
    }
    long long constantThing;
    __long_double_t otherThing;
    __long_double_t answer;
    if(argv[2][0] == '?')
    {
        for(int i = 0; i <= n; ++i)
        {
            k = i;
            answer = binomialMass(p,k,n);
            cout << "k = " << k << " Answer: " << answer << " / " << answer * 100 << "%" << endl;
        }
    }
    else if (argv[2][0] == '!')
    {
        answer = probAtleastOnce(p,n);
        cout << "Answer: " << answer << " / " << answer * 100 << "%" << endl;
    }
    else
    {
        k = atoi(argv[2]);
        if (k > n)
        {
            cout << "Cannot calculate k greater than n" << endl;
            return 1;
        }
        if (k < 0)
        {
            cout << "Cannot calculate negative k" << endl;
            return 1;
        }
        answer = binomialMass(p,k,n);
        cout << "Answer: " << answer << " / " << answer * 100 << "%" << endl;
    }

    
    return 0;
}
