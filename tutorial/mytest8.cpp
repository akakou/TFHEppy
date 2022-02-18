#include <stdio.h>

#include <cstdio>
#include <fstream>
#include <iostream>
#include <sstream>
#include <tfhe++.hpp>
#include <vector>

using namespace TFHEpp;
using namespace std;

void add_test()
{
    printf("--- add test ---\n");

    TFHEpp::Encoder encoder(-32, 32, 32, 4);

    // generate a random key
    std::unique_ptr<TFHEpp::SecretKey> sk =
        std::make_unique<TFHEpp::SecretKey>();

    double x = 10.6;
    double x2 = 5.6;

    TLWE<TFHEpp::lvl0param> c1, c2, c3;

    c1 = TFHEpp::tlweSymEncodeEncrypt<TFHEpp::lvl0param>(
        x, TFHEpp::lvl0param::alpha, sk->key.lvl0, encoder);
    c2 = TFHEpp::tlweSymEncodeEncrypt<TFHEpp::lvl0param>(
        x2, TFHEpp::lvl0param::alpha, sk->key.lvl0, encoder);

    TFHEpp::HomADD(c3, c1, c2, encoder, encoder);

    double d = TFHEpp::tlweSymDecryptDecode<TFHEpp::lvl0param>(
        c3, sk->key.lvl0, encoder);

    printf("add result: %lf\n", d);
    printf("encoder unit: %lf\n", encoder.unit);
}

void mult_test()
{
    printf("--- mult test ---\n");

    TFHEpp::Encoder encoder(-20, 20, 32);
    TFHEpp::Encoder target_encoder(0, 400, 32, 4);

    // generate a random key
    std::unique_ptr<TFHEpp::SecretKey> sk =
        std::make_unique<TFHEpp::SecretKey>();

    std::unique_ptr<TFHEpp::GateKey> gk =
        std::make_unique<TFHEpp::GateKey>(*sk, encoder);

    double x = 10.6;
    double x2 = 5.6;

    TLWE<TFHEpp::lvl0param> c1, c2, c3;

    c1 = TFHEpp::tlweSymEncodeEncrypt<TFHEpp::lvl0param>(
        x, TFHEpp::lvl0param::alpha, sk->key.lvl0, encoder);
    c2 = TFHEpp::tlweSymEncodeEncrypt<TFHEpp::lvl0param>(
        x2, TFHEpp::lvl0param::alpha, sk->key.lvl0, encoder);

    TFHEpp::HomMULT(c3, c1, c2, *gk.get(), encoder, encoder, target_encoder);

    double d = TFHEpp::tlweSymDecryptDecode<TFHEpp::lvl0param>(c3, sk->key.lvl0,
                                                               target_encoder);

    printf("mult result: %lf\n", d);
    printf("encoder unit: %lf\n", target_encoder.unit);
}

int main()
{
    printf("hello, world\n");
    add_test();
    puts("");
    mult_test();
}
