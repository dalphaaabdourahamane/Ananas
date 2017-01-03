//
// Created by DIALLO on 27/12/2016.
//

#include <algorithm>
#include "Sequence.h"

Sequence::Sequence(Variable *v, const vector<Variable *> &setOfVariable) :
        v(v), setOfVariable(setOfVariable) {}

Sequence::Sequence(Variable *v) : v(v) {}

Variable *Sequence::getV() const {
    return v;
}

void Sequence::setV(Variable *v) {
    Sequence::v = v;
}

const vector<Variable *> &Sequence::getSetOfVariable() const {
    return setOfVariable;
}

void Sequence::setSetOfVariable(const vector<Variable *> &setOfVariable) {
    Sequence::setOfVariable = setOfVariable;
}

bool Sequence::updateDomaine(int i, int j, int val) {
    bool  res = true;
    for(Variable *& v : this->setOfVariable){
        if(v->getI() == i || v->getJ() == j){
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
