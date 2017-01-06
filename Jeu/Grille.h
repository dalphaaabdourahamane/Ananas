//
// Created by DIALLO on 26/12/2016.
//

#ifndef KAKURO_GRILLE_H
#define KAKURO_GRILLE_H


#include <ostream>
#include "Variable.h"
#include <set>
#include <vector>

class Grille {
private:
    int size = 5;
    Variable **grille;
    vector<Variable *> setOfVariable;

public:
    Grille(int size);

    Grille(int size,int max,int min =1);

    Grille(int size, Variable **grille, const vector<Variable *> &setOfVariable);

    Grille(int **grille);

    int getSize() const;

    void setSize(int size);

    Variable **getGrille() const;

    void setGrille(Variable **grille);

    friend std::ostream &operator<<(std::ostream &os, const Grille &grille);

    bool operator<(const Grille &rhs) const;

    bool operator>(const Grille &rhs) const;

    bool operator<=(const Grille &rhs) const;

    bool operator>=(const Grille &rhs) const;

    void insertColonne(int *colonne);

    void insertLigne(int *ligne);

    void insertLigneColonne(int val);

    void printGrille();

    void insert(int i, int j, int val);

    const vector<Variable *> &getSetOfVariable() const;

    void setSetOfVariable(int i, int j);

    void setSetOfVariable(const vector<Variable *> &setOfVariable);

    Variable *getFreeVariable();

    int differenceLigne(int const i);

    int differenceColonne(int const j);

    int isInconsistantLigne(int const l);

    int isInconsistantColonne(int const c);

    int allDifferentLigne(int const l);

    int allDifferentColonne(int const c);

    bool updateDomaine(int i, int j, int val);

    void reverseUpdateDomaine(int i, int j, int val);

    Grille &clone();

    int getNomberFreeVariable();

    Variable getXYPredictiveVariable(int x,int y);

    int ecartLastCaseLigne(int l);

    int ecartLastCaseColonne(int j);
};

#endif //KAKURO_GRILLE_H
