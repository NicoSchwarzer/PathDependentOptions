#ifndef BinModel_h
#define BinModel_h

class BinModel
{
private:
    double S0;
    double U;
    double D;
    double R;
public:
//computing risk neutral probability
    double RiskNeutProb();
//inputting, displaying and checking binomial model data
    int GetInputData();
    double GetR();
    double GetS0(); // new getter function for S0
    double GetU(); // new getter function for u
    double GetD(); // new getter function for d


};
#endif
