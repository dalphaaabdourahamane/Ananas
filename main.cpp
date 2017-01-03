#include <iostream>
#include <stack>
#include <algorithm>
#include <conio.h>
#include "Jeu/Grille.h"
#include "Jeu/Sequence.h"


bool forwardChecking (Grille &p);

int sample (Grille &p);

using namespace std;
int main() {
    Grille *p = new Grille(5,8,1);
    int *colonne = new int[5];
    colonne[0] = 0;
    colonne[1] = 14;
    colonne[2] = 10;
    colonne[3] = 12;
    colonne[4] = 14;

    int *ligne = new int[5];
    ligne[0] = 0;
    ligne[1] = 10;
    ligne[2] = 14;
    ligne[3] = 12;
    ligne[4] = 14;

    p->insertColonne(colonne);
    p->insertLigne(ligne);
//    p->insertLigneColonne(16);
    cout<<sample(*p)<<endl;
    p->printGrille();
    cout<<endl;

//    forwardChecking(*p);
//    p->printGrille();
    getch();
    return 0;
}

bool forwardChecking (Grille &p){
    Variable *v = p.getFreeVariable();
    if(! v){
        return true;
    }
    for(int val :  v->getSetOfdomaine()){
        if (val != 0) {
            v->setValeur(val);
            p.printGrille();
            if( p.updateDomaine(v->getI(), v->getJ(), val)){
                if(p.isInconsistantColonne(v->getJ()) >= 0 && p.isInconsistantLigne(v->getI()) >= 0 ){
                    if(forwardChecking(p)) return true;
                }
            }
            p.reverseUpdateDomaine(v->getI(), v->getJ(), val);
        }
    }
    v->setIsSeleted(false);
    v->setValeur(0); ///!!!!!!!!!!!!!!!!!
    return false;
}

int sample (Grille &p){
    while (true){
        Variable *v = p.getFreeVariable();
        if(! v){
            return 0;
        }
        int val = v->selectionValue();
        if (val != 0) {
            v->setValeur(val);
            if(! p.updateDomaine(v->getI(), v->getJ(), val) ||
                    p.isInconsistantColonne(v->getJ()) < 0 || p.isInconsistantLigne(v->getI()) < 0 ){
                return 1 + p.getNomberFreeVariable();
            }
        }
    }
}

