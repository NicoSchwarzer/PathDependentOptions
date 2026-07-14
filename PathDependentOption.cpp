#include "PathDependentOption.h"
#include "BinModel.h"
#include <iostream>
#include <algorithm>
#include <cmath>
#include <ctime>
#include <cstdlib>
#include <utility>

using namespace std;


double PathDependentOption::PriceByPathEvaluation(BinModel Model, bool PrintOutTime)
{


    clock_t StartTimer;
    StartTimer = clock();   // start timer


    double p=Model.RiskNeutProb();
    double S0=Model.GetS0();
    double u=Model.GetU();
    double d=Model.GetD();



    double* path = new double[N + 1]; // array of Stock values for this path to be filled, using dynamic memory allocation

    int totalPaths = static_cast<int>(pow(2, N)); // 2^N, mapping from double to int using https://www.geeksforgeeks.org/cpp/static_cast-in-cpp/

    double resultSum = 0.0;



    for (int i = 0; i < totalPaths; ++i) {

        double S = S0;
        path[0] = S;


        // building the path
        int up_moves = 0;

        for (int step = 0; step < N; ++step) {

            if (i & (1 << step)) {  // check if bit corresponding to each step in the 'path' denoted by i is 1 (up) or 0 (down)
            // see https://www.geeksforgeeks.org/dsa/all-about-bit-manipulation/

                S *= u;   // up move
                up_moves += 1;
            } else {
                S *= d;   // down move
            }

            path[step + 1] = S;
        }

        // risk-neutral probability
        double PathProb = pow(p, up_moves) * pow(1.0 - p, (N-up_moves));

        // Calculate Payoff for path and multiply by P*

        resultSum += PathProb * Payoff(path, N+1);

    }

    delete[] path;


    clock_t EndTimer;
    EndTimer = clock();     //  end timer


    if (PrintOutTime == true) {

        cout << "CPU Time: " << double(EndTimer - StartTimer) << ".\n";
        cout << "Seconds: " << double(EndTimer - StartTimer) / CLOCKS_PER_SEC << ".\n";

    }


    return pow(Model.GetR(), -N) * resultSum;


    }





pair<double, double> PathDependentOption::PriceByMonteCarlo(BinModel Model, int M, bool PrintOutTime)
{


    clock_t StartTimer;
    StartTimer = clock();   // start timer


    double p=Model.RiskNeutProb();
    double S0=Model.GetS0();
    double u=Model.GetU();
    double d=Model.GetD();

    //double resultSum = 0;
    // double VarianceSum = 0;
    double PayoffSum = 0;

    srand(123); // random seed for reproducibility


    double* path = new double[N + 1]; // array of Stock values for this path to be filled, using dynamic memory allocation
    double* payoffs = new double[M]; // using array of payoffs since we need one for the calculation of the variance

    for (int i = 0; i < M; i++){

        double S = S0;
        path[0] = S;

            // simulate paths through sampling from Omega per step
            for (int step = 0; step < N; ++step) {

                double r = (double)rand() / RAND_MAX;  // random number in [0,1]

                if (r < p) {


                    S *= u;   // up move
                } else {
                    S *= d;   // down move
                }

            path[step + 1] = S;
        }


        // Increment the Price by Payoff
        payoffs[i] =  Payoff(path, N+1);
        PayoffSum += Payoff(path, N+1);
    }


    clock_t EndTimer;
    EndTimer = clock();     //  end timer


    if (PrintOutTime == true) {

        cout << "CPU Time: " << double(EndTimer - StartTimer) << ".\n";
        cout << "Seconds: " << double(EndTimer - StartTimer) / CLOCKS_PER_SEC << ".\n";

    }


    double OptionPrice = pow(Model.GetR(), -N) * (PayoffSum/M);

    double EstimatedVaraince = 0;

    double AvgPayoff = PayoffSum / M;

    for (int i = 0; i<M; i++){
        EstimatedVaraince +=  (pow(payoffs[i] - AvgPayoff, 2)/(M-1) );
    }

    // now mapping to standard error of MC approxaimation
    double SeMC = pow(Model.GetR(), -N) * (sqrt(EstimatedVaraince)/sqrt(M));

    delete[] path;
    delete[] payoffs;

    return make_pair(OptionPrice, SeMC);


    }



double  ArithmeticAsianCall::Payoff(const double* path, int size){

    double PriceSum = 0;
    for (int i = 0; i<size; i++) {
        PriceSum += path[i];
    }
    double MeanPrice = PriceSum / size;

    return max(MeanPrice - K, 0.0);


}


int ArithmeticAsianCall::GetInputData()
{
    cout << "ArithmeticAsianCall Asian Call data:" << endl;
    cout << "Enter steps to expiry N: ";
    int N;
    cin >> N;
    SetN(N);
    cout << "Enter strike price K: ";
    cin >> K;
    cout << endl;
    cout << "N = " << N << endl;
    cout << "K = " << K << endl;
    cout << endl;
    return 0;
}


double  LookbackOption::Payoff(const double* path, int size){

    double minPrice = path[0];

    for (int i = 1; i<size; i++) {
        if (path[i] < minPrice){
            minPrice = path[i];
        }
    }

    return path[size-1] - minPrice;


}


int LookbackOption::GetInputData()
{
    cout << "Lookback Option  data:" << endl;
    cout << "Enter steps to expiry N: ";
    int N;
    cin >> N;
    cout << "N = " << N << endl;
    return 0;
}
