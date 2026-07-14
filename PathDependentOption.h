#ifndef PathDependentOption_h
#define PathDependentOption_h
#include "BinModel.h"
#include <utility>

using namespace std;

class PathDependentOption
{
private:
    int N; //steps to expiry
public:
    void SetN(int N_)
    {
        N=N_;
    }

    virtual double Payoff(const double* path, int N)
    {
        return 0;
    }
    /*
    Payoff defined to return 0 for pedagogical purposes.
    To to use a pure virtual function replace by
    virtual double Payoff(double S)=0;
    */


    //pricing by path evaluation, 2.1
    double PriceByPathEvaluation(BinModel Model, bool PrintOutTime);

    //pricing by Monte Carlo, 2.3
    pair<double, double> PriceByMonteCarlo(BinModel Model, int M, bool PrintOutTime);



};


class ArithmeticAsianCall: public PathDependentOption
{
private:
    double K; //strike price
public:
    void SetK(int K_)
    {
        K=K_;
    }
    int GetInputData();

    double Payoff(const double* path, int N);

};


class LookbackOption: public PathDependentOption
{

public:
    int GetInputData();

    double Payoff(const double* path, int N);

};


#endif
