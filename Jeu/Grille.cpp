//
// Created by DIALLO on 26/12/2016.
//

#include <iostream>
#include <algorithm>
#include <iomanip>
#include "Grille.h"
using namespace std;

Grille::Grille(int size) : size(size) {
    this->grille = new Variable * [size];
    for (int i = 0; i < this->size; ++i) {
        this->grille[i] =  new Variable[size];
    }
    for (int i = 0; i < size; ++i) {
        for (int j = 0; j < size; ++j) {
            this->grille[i][j].setValeur(0);
            this->grille[i][j].setI(i);
            this->grille[i][j].setJ(j);
            this->grille[i][j].setSetOfdomaine(1,size);
        }
    }
    for (int i = 1; i < size ; ++i) {
        for (int j = 1; j < size; ++j) {
            this->setOfVariable.push_back(&this->grille[i][j]);
        }
    }
}

Grille::Grille(int size, int max, int min): size(size) {
    this->grille = new Variable * [size];
    for (int i = 0; i < this->size; ++i) {
        this->grille[i] =  new Variable [size];
    }
    for (int i = 0; i < size; ++i){
        for (int j = 0; j < size; ++j) {
            this->grille[i][j].setValeur(0);
            this->grille[i][j].setI(i);
            this->grille[i][j].setJ(j);
            this->grille[i][j].setSetOfdomaine(min,max);
        }
    }
    for (int i = 1; i < size ; ++i) {
        for (int j = 1; j < size; ++j) {
            this->setOfVariable.push_back(&this->grille[i][j]);
        }
    }
}


int Grille::getSize() const {
    return size;
}

void Grille::setSize(int size) {
    Grille::size = size;
}

Variable **Grille::getGrille() const {
    return grille;
}

void Grille::setGrille(Variable **grille) {
    Grille::grille = grille;
}

bool Grille::operator<(const Grille &rhs) const {
    if (size < rhs.size)
        return true;
    if (rhs.size < size)
        return false;
    return grille < rhs.grille;
}

bool Grille::operator>(const Grille &rhs) const {
    return rhs < *this;
}

bool Grille::operator<=(const Grille &rhs) const {
    return !(rhs < *this);
}

bool Grille::operator>=(const Grille &rhs) const {
    return !(*this < rhs);
}

void Grille::insertColonne(int *colonne) {
    for(int i = 0; i<this->size; i++){
        this->grille[i][0].setValeur(colonne[i]);
        this->grille[i][0].setBorder(true);
    }
}

void Grille::insertLigne(int *ligne) {
    for(int i = 0; i<this->size; i++){
        this->grille[0][i].setValeur(ligne[i]);
        this->grille[0][i].setBorder(true);
    }
}

void Grille::printGrille() {
    cout<<endl<< "size: " << this->size <<endl;
//    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 0);
    for (int i = 0; i < this->size; ++i) {
        for (int j = 0; j < this->size; ++j) {
            cout<<setw(4)<< this->grille[i][j].getValeur()<<" |";
        }
        cout<<endl;
    }

    for(Variable *& v : this->setOfVariable){
        cout<<*v<<"[ ";
        if(v->getSetOfdomaine().size() > 0){
            for (int i = 0; i < v->getSetOfdomaine().size()-1; ++i) {
                cout<<v->getSetOfdomaine().at(i)<<", ";
            }
            cout<<v->getSetOfdomaine().at(v->getSetOfdomaine().size()-1);
        }
        cout<<" ]"<<endl;
    }

}

Grille::Grille(int **grille) {

}

ostream &operator<<(ostream &os, const Grille &grille) {
    os << "size: " << grille.size << " grille: " << grille.grille;
    return os;
}

const vector<Variable*> & Grille::getSetOfVariable() const {
    return setOfVariable;
}

void Grille::setSetOfVariable(const vector<Variable*> &setOfVariable) {
    Grille::setOfVariable = setOfVariable;
}

void Grille::setSetOfVariable(int i, int j) {
    for(Variable *v :  this->setOfVariable){
        v->setSetOfdomaine(i,j);
    }
}

Variable * Grille::getFreeVariable() {
    if (this->setOfVariable.size() > 0) {
        Variable *res = nullptr ;
        int j = 0;
        for (; j < this->setOfVariable.size(); ++j) {
            if ( ! this->setOfVariable.at(j)->isIsSeleted()) {
                res = this->setOfVariable.at(j);
                break;
            }
        }
//        for (int i = j; i < this->setOfVariable.size(); ++i) {
//            Variable *& var = this->setOfVariable.at(i);
//            if(( ! var->isIsSeleted()) && (var->getSetOfdomaine().size() < res->getSetOfdomaine().size())){
//                res = var;
//            }
//        }
        if (res) {
//            res->setIsSeleted(true);
            return res ;
        }
    }
        return nullptr;

}

int Grille::differenceLigne(const int i) {
    //si res = 0
    int sommeLigne = 0;
    //j = 1 car 0 valeur bordure
    for (int j = 1; j < this->size; ++j) {
        sommeLigne += this->grille[i][j].getValeur();
    }

    return grille[i][0].getValeur() - sommeLigne;
}

int Grille::differenceColonne(const int j) {
    //si res = 0
    int sommeColonne = 0;
    //j = 1 car 0 valeur bordure
    for (int i = 1; i < this->size; ++i) {
        sommeColonne += this->grille[i][j].getValeur();
    }

    return grille[0][j].getValeur() - sommeColonne;
}

int Grille::isInconsistantColonne(int const c) {
    int ad = allDifferentColonne(c);
    int dif = differenceColonne(c);
    if(ad == 1){
        if(dif == 0) return 1;
        else return -1;

    } else{
        if(ad == 0){
            if(dif <= 0) return -1;
            else return 0;
        }
        if(ad == -1){
            return -1;
        }
    }
    return 1;
}

//*verifier
int Grille::isInconsistantLigne(const int l) {
    int ad = allDifferentLigne(l);
    int dif = differenceLigne(l);
    if(ad == 1){
        if(dif == 0) return 1;
        else return -1;

    } else{
        if(ad == 0){
            if(dif <= 0) return -1;
            else return 0;
        }
        if(ad == -1){
            return -1;
        }
    }
    return 1;
}

int Grille::allDifferentLigne(int const l) {
    for (int i = 1; i < this->size; ++i) {
        for (int j = i+1; j < this->size; ++j) {
            if(this->grille[l][i].getValeur() == this->grille[l][j].getValeur())
                return -1; // pas ok
            if(this->grille[l][j].getValeur() == 0)
                return 0; // case vide
        }
    }
    return 1; //ok
}

int Grille::allDifferentColonne(int const c) {
    for (int i = 1; i < this->size; ++i) {
        for (int j = i+1; j < this->size; ++j) {
            if(this->grille[i][c].getValeur() == this->grille[j][c].getValeur())
                return -1; // pas ok
            if(this->grille[j][c].getValeur() == 0)
                return 0; // case vide
        }
    }
    return 1; //ok
}

bool Grille::updateDomaine(int i, int j, int val) {
    bool  res = true;
    for(Variable *& v : this->setOfVariable){
        if((! v->isIsSeleted()) &&(v->getI() == i || v->getJ() == j)){
            v->getSetOfdomaine().erase(remove(v->getSetOfdomaine().begin(),
                                              v->getSetOfdomaine().end(), val),
                                       v->getSetOfdomaine().end());
        }
        if(v->getSetOfdomaine().empty()){
            res = false;
        }
    }
    return res;
}

Grille& Grille::clone() {
    vector<Variable*> res;
    Variable **tab = new Variable * [this->size];

    for (int i = 0; i < this->size; ++i) {
        tab[i] =  new Variable[this->size];
    }
    for (int i = 0; i < this->size; ++i) {
        for (int j = 0; j < this->size; ++j) {
            tab[i][j].setValeur(this->grille[i][j].getValeur());
            tab[i][j].setI(this->grille[i][j].getI());
            tab[i][j].setJ(this->grille[i][j].getJ());
            tab[i][j].setSetOfdomaine(1,this->size); ///
        }
    }
    for (int i = 1; i < size ; ++i) {
        for (int j = 1; j < size; ++j) {
            res.push_back(&tab[i][j]);
        }
    }
    return *new Grille(this->size,tab,res);
}

Grille::Grille(int size, Variable **grille, const vector<Variable *> &setOfVariable) : size(size), grille(grille),
                                                                                       setOfVariable(setOfVariable) {}

void Grille::reverseUpdateDomaine(int i, int j, int val) {
    for(Variable *& v : this->setOfVariable){
        if((! v->isIsSeleted()) &&(v->getI() == i || v->getJ() == j)){
            v->getSetOfdomaine().push_back(val);
        }
    }
}

void Grille::insertLigneColonne(int val) {
    for(int i = 0; i<this->size; i++){
        this->grille[i][0].setValeur(val);
        this->grille[i][0].setBorder(true);
        this->grille[0][i].setValeur(val);
        this->grille[0][i].setBorder(true);
    }
}

int Grille::getNomberFreeVariable() {
    int res = 0;
    for(Variable *v : this->setOfVariable){
        if(! v->isIsSeleted()) res++;
    }
    return res;
}

int Grille::ecartLastCaseColonne(int c) {
    int cpt = 0,som = 0;
    for (int i = 1; i < this->size; ++i) {
        if(this->grille[i][c].isIsSeleted()){
            som+= this->grille[i][c].getValeur();
            cpt ++;
        }
    }
    return ((this->size - 1 - cpt) == 1)? this->grille[0][c].getValeur() -som : 0;
}

int Grille::ecartLastCaseLigne(int l) {
    int cpt = 0,som = 0;
    for (int i = 1; i < this->size; ++i) {
        if(this->grille[l][i].isIsSeleted()){
            som+= this->grille[l][i].getValeur();
            cpt ++;
        }
    }
    return ((this->size - 1 - cpt) == 1)? this->grille[l][0].getValeur() - som  : 0;
}

Variable Grille::getXYPredictiveVariable(int x, int y) {
    if (y != 0) {
        for (int i = 1; i < this->size; ++i) {
            if(! this->grille[i][y].isIsSeleted()){
                return this->grille[i][y];
            }
        }
    }
    if (x != 0) {
        for (int i = 1; i < this->size; ++i) {
            if(! this->grille[x][i].isIsSeleted()){
                return this->grille[x][i];
            }
        }
    }
//    return NULL;
}





