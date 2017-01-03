//
// Created by DIALLO on 26/12/2016.
//

#include "Variable.h"
#include <algorithm>
#include <time.h>

int Variable::getI() const {
    return i;
}

void Variable::setI(int i) {
    Variable::i = i;
}

int Variable::getJ() const {
    return j;
}

void Variable::setJ(int j) {
    Variable::j = j;
}

int Variable::getValeur() const {
    return valeur;
}

void Variable::setValeur(int valeur) {
    Variable::valeur = valeur;
}

vector<int> &Variable::getSetOfdomaine() {
    return setOfdomaine;
}

void Variable::setSetOfdomaine(const vector<int> &setOfdomaine) {
    Variable::setOfdomaine = setOfdomaine;
}

bool Variable::isBorder() const {
    return border;
}

void Variable::setBorder(bool border) {
    Variable::border = border;
}

Variable::Variable(const vector<int> &setOfdomaine) : setOfdomaine(setOfdomaine) {}

void Variable::setSetOfdomaine(int debut, int fin) {
    for (int i = debut; i <=fin ; ++i) {
        this->setOfdomaine.push_back(i);
    }
}

ostream &operator<<(ostream &os, const Variable *variable1) {
    os << "i: " << variable1->getI() << " j: " << variable1->getJ() << " valeur: " << variable1->getValeur()<< " select: " << variable1->isIsSeleted()<<endl;
//    << " setOfdomaine: "<< variable1.setOfdomaine;
//    << " border: " << variable1.border;
    return os;
}

Variable::Variable() {}

Variable::Variable(int i, int j, int valeur, const vector<int> &setOfdomaine, bool border)
        : i(i), j(j), valeur(valeur), setOfdomaine(setOfdomaine), border(border) {}

Variable::Variable(int i, int j, const vector<int> &setOfdomaine)
        : i(i), j(j), setOfdomaine(setOfdomaine) {}

Variable::Variable(int i, int j, int valeur) : i(i), j(j), valeur(valeur) {}

Variable::Variable(int i, int j) : i(i), j(j) {}

void Variable::updateDomain(int u) {
    this->setOfdomaine.erase(remove(this->setOfdomaine.begin(), this->setOfdomaine.end(), u), this->setOfdomaine.end());
}

int Variable::selectionValue() {
    int res=0;
    if (setOfdomaine.size() > 1 ) {
        srand (time(NULL));
        unsigned int r  = (rand() % (setOfdomaine.size()));
        res = this->setOfdomaine.at(r);
        this->setOfdomaine.erase(this->setOfdomaine.begin() + r);
    }
    return res;
}

bool Variable::isEmptyDomain() {
    return this->setOfdomaine.size() == 0;
}

ostream &operator<<(ostream &os, const Variable variable1) {
    os << "i: " << variable1.getI() << " j: " << variable1.getJ() << " valeur: " << variable1.getValeur()<< " isSelected: " << variable1.isIsSeleted();
//    << " setOfdomaine: "<< variable1.setOfdomaine;
//    << " border: " << variable1.border;
    return os;
}

bool Variable::isIsSeleted() const {
    return isSeleted;
}

void Variable::setIsSeleted(bool isSeleted) {
    Variable::isSeleted = isSeleted;
}

Variable *Variable::clone() {
    Variable * v = new Variable();
    v->setValeur(this->getValeur());
    v->setI(this->getI());
    v->setJ(this->getJ());
    v->setSetOfdomaine(this->getSetOfdomaine());
    v->setIsSeleted(this->isIsSeleted());
    v->setBorder(this->isBorder());
    return v;
}

//Variable &Variable::operator=(Variable e) {
//    this->setValeur(e.getValeur());
//    this->setI(e.getI());
//    this->setJ(e.getJ());
//    this->setSetOfdomaine(e.getSetOfdomaine());
//    this->setIsSeleted(e.isIsSeleted());
//    this->setBorder(e.isBorder());
//    return *this;
//}

//Variable &Variable::operator=(Variable *e) {
//    this->setValeur(e->getValeur());
//    this->setI(e->getI());
//    this->setJ(e->getJ());
//    this->setSetOfdomaine(e->getSetOfdomaine());
//    this->setIsSeleted(e->isIsSeleted());
//    this->setBorder(e->isBorder());
//    return *this;
//}


