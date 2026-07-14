#include "BinModel.h"
#include "PathDependentOption.h"
#include <iostream>
#include <cmath>
using namespace std;

int main()
{

    BinModel MyModel;
    if (MyModel.GetInputData()==1) return 1;

    // Code for 2.1

    string printEx21;
    cout << "If you want to have the output for Ex 2.1, say 'yes' \n";
    cin >> printEx21;

    if (printEx21 == "yes") {

    cout << " --- Output for Ex 2.1 --- \n";

    ArithmeticAsianCall MyArithmeticAsianCall;
    LookbackOption MyLookbackOption;


    // first set of input data

    int N_1 = 1;
    MyArithmeticAsianCall.SetN(N_1);
    MyLookbackOption.SetN(N_1);
    MyArithmeticAsianCall.SetK(100);

    cout << "Based on the input data for the Stock, the Price for an Arithmetic Asian Call with N = " << N_1 <<", K = 100 is: " << MyArithmeticAsianCall.PriceByPathEvaluation(MyModel, false) << ".\n";
    cout << "Correspondingly, the Price for a Lookback Option with N = " << N_1 <<" is: " << MyLookbackOption.PriceByPathEvaluation(MyModel, false) << ".\n";


    // second set of input data

    int N_2 = 5;
    MyArithmeticAsianCall.SetN(N_2);
    MyLookbackOption.SetN(N_2);
    MyArithmeticAsianCall.SetK(100);

    cout << "Based on the input data for the Stock, the Price for an Arithmetic Asian Call with N = " << N_2 <<", K = 100 is: " << MyArithmeticAsianCall.PriceByPathEvaluation(MyModel, false) << ".\n";
    cout << "Correspondingly, the Price for a Lookback Option with N = " << N_2 <<" is: " << MyLookbackOption.PriceByPathEvaluation(MyModel, false) << ".\n";


    // third set of input data

    int N_3 = 10;
    MyArithmeticAsianCall.SetN(N_3);
    MyLookbackOption.SetN(N_3);
    MyArithmeticAsianCall.SetK(90);

    cout << "Based on the input data for the Stock, the Price for an Arithmetic Asian Call with N = " << N_3 <<", K = 90 is: " << MyArithmeticAsianCall.PriceByPathEvaluation(MyModel, false) << ".\n";
    cout << "Correspondingly, the Price for a Lookback Option with N = " << N_3 <<" is: " << MyLookbackOption.PriceByPathEvaluation(MyModel, false) << ".\n";


    // fourth set of input data


    int N_4 = 15;
    MyArithmeticAsianCall.SetN(N_4);
    MyLookbackOption.SetN(N_4);
    MyArithmeticAsianCall.SetK(110);


    cout << "Based on the input data for the Stock, the Price for an Arithmetic Asian Call with N = " << N_4 <<", K = 110 is: " << MyArithmeticAsianCall.PriceByPathEvaluation(MyModel, false) << ".\n";
    cout << "Correspondingly, the Price for a Lookback Option with N = " << N_4 <<" is: " << MyLookbackOption.PriceByPathEvaluation(MyModel, false) << ".\n";


    } else {
        cout << "Ok, continuing with 2.2 \n";

    }


    // Code for 2.2

    string printEx22;
    cout << "If you want to have the output for Ex 2.2, say 'yes' \n";
    cin >> printEx22;

    if (printEx22 == "yes") {

    cout << " --- Output for Ex 2.2 --- \n";

    // retrieving computational speed for ArithmeticAsianCall
    ArithmeticAsianCall MyArithmeticAsianCall;
    MyArithmeticAsianCall.SetK(100);


    for (int i=1; i<=25; i++){

        cout << "For N= " << i << ", the speed of the Computation for the Arithmetic Asian Call is:\n";

        MyArithmeticAsianCall.SetN(i);
        MyArithmeticAsianCall.PriceByPathEvaluation(MyModel, true);


    }

    // retrieving computational speed for LookbackOption
    LookbackOption MyLookbackOption;


    for (int i=1; i<=25; i++){

        cout << "For N= " << i << ", the speed of the Computation for the Lookback Option is:\n";

        MyLookbackOption.SetN(i);
        MyLookbackOption.PriceByPathEvaluation(MyModel, true);

    }

    } else {
        cout << "Ok, continuing with 2.3 \n";

    }

    // Code for 2.3

    string printEx23;
    cout << "If you want to have the output for Ex 2.3, say 'yes' \n";
    cin >> printEx23;

    if (printEx23 == "yes") {

    cout << " --- Output for Ex 2. --- \n";

    ArithmeticAsianCall MyArithmeticAsianCall;
    LookbackOption MyLookbackOption;

    int M = 5000;
    // first set of input data

    int N_1 = 1;
    MyArithmeticAsianCall.SetN(N_1);
    MyLookbackOption.SetN(N_1);
    MyArithmeticAsianCall.SetK(100);

    cout << "Based on the input data for the Stock, the Price by Monte Carlo Simulation for an Arithmetic Asian Call with N = " << N_1 <<", K = 100 is: " << MyArithmeticAsianCall.PriceByMonteCarlo(MyModel, M, false).first << ".\n";
    cout << "Correspondingly, the Price by Monte Carlo Simulation for a Lookback Option with N = " << N_1 <<" is: " << MyLookbackOption.PriceByMonteCarlo(MyModel, M, false).first << ".\n";



    // second set of input data

    int N_2 = 5;
    MyArithmeticAsianCall.SetN(N_2);
    MyLookbackOption.SetN(N_2);
    MyArithmeticAsianCall.SetK(100);

    cout << "Based on the input data for the Stock, the Price by Monte Carlo Simulation for an Arithmetic Asian Call with N = " << N_2 <<", K = 100 is: " << MyArithmeticAsianCall.PriceByMonteCarlo(MyModel, M, false).first << ".\n";
    cout << "Correspondingly, the Price by Monte Carlo Simulation for a Lookback Option with N = " << N_2 <<" is: " << MyLookbackOption.PriceByMonteCarlo(MyModel, M, false).first << ".\n";


    // third set of input data

    int N_3 = 10;
    MyArithmeticAsianCall.SetN(N_3);
    MyLookbackOption.SetN(N_3);
    MyArithmeticAsianCall.SetK(90);

    cout << "Based on the input data for the Stock, the Price by Monte Carlo Simulation for an Arithmetic Asian Call with N = " << N_3 <<", K = 90 is: " << MyArithmeticAsianCall.PriceByMonteCarlo(MyModel, M, false).first << ".\n";
    cout << "Correspondingly, the Price by Monte Carlo Simulation for a Lookback Option with N = " << N_3 <<" is: " << MyLookbackOption.PriceByMonteCarlo(MyModel, M, false).first << ".\n";


    // fourth set of input data


    int N_4 = 15;
    MyArithmeticAsianCall.SetN(N_4);
    MyLookbackOption.SetN(N_4);
    MyArithmeticAsianCall.SetK(110);


    cout << "Based on the input data for the Stock, the Price by Monte Carlo Simulation for an Arithmetic Asian Call with N = " << N_4 <<", K = 110 is: " << MyArithmeticAsianCall.PriceByMonteCarlo(MyModel, M, false).first << ".\n";
    cout << "Correspondingly, the Price by Monte Carlo Simulation for a Lookback Option with N = " << N_4 <<" is: " << MyLookbackOption.PriceByMonteCarlo(MyModel, M, false).first << ".\n";


    } else {
        cout << "Ok, continuing with 2.4 \n";

    }



    // Code for 2.4

    string printEx24;
    cout << "If you want to have the output for Ex 2.4, say 'yes' \n";
    cin >> printEx24;

    if (printEx24 == "yes") {

    cout << " --- Output for Ex 2.4 --- \n";


    ArithmeticAsianCall MyArithmeticAsianCall;
    MyArithmeticAsianCall.SetK(100);
    LookbackOption MyLookbackOption;

    // different values of M to try
    int MValues[] = {10000,50000};



    //results for MyArithmeticAsianCall
    for (int i=22; i<=25; i++){

        MyArithmeticAsianCall.SetN(i);

        for (int m = 0; m <2; m++) {

            cout << "For N= " << i << " and M= " << MValues[m] << ",  the speed of the Computation for the Arithmetic Asian Call is:";
            pair<double, double> result = MyArithmeticAsianCall.PriceByMonteCarlo(MyModel, MValues[m], true);
            cout << ". The price is " << result.first << " and the associated standard error of the MC approximation is " << result.second << ".\n\n";

        }
    }

    //results for MyArithmeticAsianCall
    for (int i=22; i<=25; i++){

        MyLookbackOption.SetN(i);

        for (int m = 0; m <2; m++) {

            cout << "For N= " << i << " and M= " << MValues[m] << ",  the speed of the Computation for the Lookback Option Call is:";
            pair<double, double> result = MyLookbackOption.PriceByMonteCarlo(MyModel, MValues[m], true);
            cout << ". The price is " << result.first << " and the associated standard error of the MC approximation is " << result.second << ".\n\n";

        }

    }

    } else {
        cout << "Ok, Ending Program\n";

    }





}
