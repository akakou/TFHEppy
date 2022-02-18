#include <stdio.h>

#include <cstdio>
#include <fstream>
#include <iostream>
#include <sstream>
#include <tfhe++.hpp>
#include <vector>

using namespace TFHEpp;
using namespace std;

void mul_test()
{
    printf("hello, world\n");

    TFHEpp::Encoder encoder(0, 32, 31, 2);
    printf("encoder: %d\n", encoder.div);
    printf("unit: %d\n", encoder.unit);

    std::unique_ptr<TFHEpp::SecretKey> sk =
        std::make_unique<TFHEpp::SecretKey>();
    std::unique_ptr<TFHEpp::GateKey> gk = std::make_unique<TFHEpp::GateKey>();

    double x = 10.6;
    double x2 = 10.6;

    TLWE<TFHEpp::lvl0param> c1, c2, c3;

    c1 = TFHEpp::tlweSymEncodeEncrypt<TFHEpp::lvl0param>(
        x, TFHEpp::lvl0param::alpha, sk->key.lvl0, encoder);
    c2 = TFHEpp::tlweSymEncodeEncrypt<TFHEpp::lvl0param>(
        x2, TFHEpp::lvl0param::alpha, sk->key.lvl0, encoder);

    TFHEpp::HomADD(c3, c1, c2, encoder, encoder);

    double d = TFHEpp::tlweSymDecryptDecode<TFHEpp::lvl0param>(c3, sk->key.lvl0,
                                                               encoder);
    printf("result: %lf\n", d);
}

int main()
{
    printf("hello, world\n");
    mul_test();
}
