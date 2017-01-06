//
// Created by DIALLO on 26/12/2016.
//

#ifndef KAKURO_VARIABLE_H
#define KAKURO_VARIABLE_H


#include <iostream>
#include <set>
#include <vector>

using namespace std;

class Variable {
protected:
    int i=0,j=0;
    int valeur = 0;
    vector<int> setOfdomaine;
    bool border = false;
    bool isSeleted = false;

public:
    void updateDomain(int u);

    int selectionValue();

    bool isEmptyDomain();

    Variable(const vector<int> &setOfdomaine);

    Variable(int i, int j, int valeur);

    Variable(int i, int j);

    Variable(int i, int j, const vector<int> &setOfdomaine);

    Variable(int i, int j, int valeur, const vector<int> &setOfdomaine, bool border);

    Variable();

    void setSetOfdomaine(int i, int j);

    int getI() const;

    void setI(int i);

    int getJ() const;

    void setJ(int j);

    int getValeur() const;

    void setValeur(int valeur);

    bool isIsSeleted() const;

    void setIsSeleted(bool isSeleted);

    vector<int> &getSetOfdomaine();

    vector<int> &getRamdomSetOfdomaine();

    void setSetOfdomaine(const vector<int> &setOfdomaine);

    bool isBorder() const;

    void setBorder(bool border);

    friend ostream &operator<<(ostream &os, const Variable *variable1);

    friend ostream &operator<<(ostream &os, const Variable variable1);

//    Variable & operator=(Variable e);

//    Variable & operator=(Variable *e);

    Variable* clone();
};


#endif //KAKURO_VARIABLE_H
