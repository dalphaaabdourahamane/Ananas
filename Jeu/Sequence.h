//
// Created by DIALLO on 27/12/2016.
//

#ifndef KAKURO_SEQUENCE_H
#define KAKURO_SEQUENCE_H


#include "Variable.h"

class Sequence {
protected:
    Variable *v ;
    vector<Variable*> setOfVariable;

public:
    Sequence(Variable *v);

    Sequence(Variable *v, const vector<Variable *> &setOfVariable);

    Variable *getV() const;

    void setV(Variable *v);

    const vector<Variable *> &getSetOfVariable() const;

    void setSetOfVariable(const vector<Variable *> &setOfVariable);

    bool updateDomaine(int i, int j, int val);

};


#endif //KAKURO_SEQUENCE_H
