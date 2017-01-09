#include <iostream>
#include <stack>
#include <algorithm>
#include <conio.h>
#include "Jeu/Grille.h"
#include "Jeu/Sequence.h"
#include <time.h>



bool forwardChecking (Grille &p,int predictionValue=0,int predictionI =0,int predictionJ =0);

int sample (Grille &p);

bool generateGrille (Grille &p );

void SommeGrille(Grille &p);

void deleteGrilleValue(Grille &p,int min=1,int max=10);

using namespace std;
int main() {
    srand (time(NULL));

    Grille *p = new Grille(3,3,1);


    int menu;
    do
    {
        cout<<endl<<" _____________ MENU ____________"<<endl;
            cout<<"|         1. Creation           |"<<endl;
            cout<<"|         2. Generation         |"<<endl;
            cout<<"|         0. Quitter            |"<<endl;
            cout<<"|_______________________________|"<<endl;
        cout<<"Choix : ";
        cin>>menu;
        cout<<endl;

        switch(menu)
        {
            case 1 :{
                system("cls");
                int rep;
                cout<<"Remplir avec UN SEUL CHIFFRE (0 = OK )? : ";cin>>rep;
                switch(rep){
                    case 0: {
                        int val =10;
                        int taille =5,min=1,max=5;

                        system("cls");
                        cout<<"Donner la TAILLE de la grille : ";cin>>taille;
                        cout<<"Donner le min du domaine : ";cin>>min;
                        cout<<"Donner le max du domaine: ";cin>>max;
                        cout<<"Donner le chiffre : ";cin>>val;

                        *p = *new Grille(taille,max,min);
                         p->insertLigneColonne(val);

                        p->printGrille();

                        cout<<endl<<" Taper une touche pour le resoudre "<<endl;
                        getch();

                        system("cls");
                        forwardChecking(*p);
                        p->printGrille();
                        getch();
                        system("cls");

                    }
                        break;
                    default:{
                        int taille =5,min=1,max=5;

                        system("cls");
                        cout<<"Donner la TAILLE de la grille : ";cin>>taille;
                        cout<<"Donner le min du domaine : ";cin>>min;
                        cout<<"Donner le max du domaine: ";cin>>max;

                        *p = *new Grille(taille,max,min);
                            int *ligne = new int[taille];
                            int *colonne = new int[taille];

                        cout<<"Saisir la Ligne "<<endl;
                        for(int i = 0; i<taille; i++){
                            cout<<i<<" : ";cin>>ligne[i];
                        }

                        cout<<"Saisir la Colonne "<<endl;
                        for(int i = 0; i<taille; i++){
                            cout<<i<<" : ";cin>>colonne[i];
                        }
                        p->insertLigne(ligne);
                        p->insertColonne(colonne);

                        system("cls");
                        p->printGrille();

                        cout<<endl<<" Taper une touche pour le resoudre "<<endl;
                        getch();

                        system("cls");
                        forwardChecking(*p);
                        p->printGrille();
                        getch();
                        system("cls");
                    }
                        break;
                }
            } break;

            case 2 :{
                int taille =5,min=1,max=5;

                system("cls");
                cout<<"Donner la TAILLE de la grille : ";cin>>taille;
                cout<<"Donner le min du domaine : ";cin>>min;
                cout<<"Donner le max du domaine: ";cin>>max;

                system("cls");
                cout<<"GENERATE GRILLE ....";
                *p = *new Grille(taille,max,min);

                generateGrille(*p);
                SommeGrille(*p);
                deleteGrilleValue(*p,min,max);

                p->printGrille();

                cout<<endl<<" Taper une touche pour le resoudre "<<endl;
                getch();

                system("cls");
                forwardChecking(*p);
                p->printGrille();
                getch();
                system("cls");

            }
                break;

            default:break;
        }

    }while (menu!=0);
    system("cls");



//    int *colonne = new int[5];
//    colonne[0] = 0;
//    colonne[1] = 14;
//    colonne[2] = 10;
//    colonne[3] = 12;
//    colonne[4] = 14;
//
//    int *ligne = new int[5];
//    ligne[0] = 0;
//    ligne[1] = 10;
//    ligne[2] = 14;
//    ligne[3] = 12;
//    ligne[4] = 14;
//
//    p->insertColonne(colonne);
//    p->insertLigne(ligne);
//    p->insertLigneColonne(16);
//    for (int i = 0; i < 5 ; ++i) {
//        cout<<sample(p->clone())<<endl;
//    }
//    p->printGrille();
//    cout<<endl;
//
//    generateGrille(*p);
//    SommeGrille(*p);
//    p->printGrille();
//    deleteGrilleValue(*p,1,8);
//    forwardChecking(*p);
//    p->printGrille();
//    getch();
    return 0;
}

bool forwardChecking (Grille &p,int predictionValue,int predictionI ,int predictionJ ){
    Variable *v = p.getFreeVariable();
    if(! v){
        return true;
    }
    if (! predictionValue) {
        v->setIsSeleted(true);
        //    for(int val :  v->getRamdomSetOfdomaine()){
        for(int val :  v->getSetOfdomaine()){
            if (val != 0) {
                v->setValeur(val);
                if( p.updateDomaine(v->getI(), v->getJ(), val)){
                    if(p.isInconsistantColonne(v->getJ()) >= 0 && p.isInconsistantLigne(v->getI()) >= 0 ){
                        if ( ! p.ecartLastCaseLigne(v->getI()) && ! p.ecartLastCaseColonne(v->getJ())) {
                            if(forwardChecking(p)) return true;
                        } else {
                            int ecartColonne = p.ecartLastCaseColonne(v->getJ());
                            int ecartLigne = p.ecartLastCaseLigne(v->getI());
                            Variable pre = p.getXYPredictiveVariable((!ecartLigne)?0:v->getI(),(!ecartColonne)?0:v->getJ());

                            if(ecartColonne) {
                                if (find(p.getGrille()[pre.getI()][pre.getJ()].getSetOfdomaine().begin(),
                                         p.getGrille()[pre.getI()][pre.getJ()].getSetOfdomaine().end(), ecartColonne)
                                    != p.getGrille()[pre.getI()][pre.getJ()].getSetOfdomaine().end()) {

                                    if (forwardChecking(p,ecartColonne,pre.getI(),pre.getJ())) {
                                        return true;
                                    }
                                }
                            }else{
                                if(find(p.getGrille()[pre.getI()][pre.getJ()].getSetOfdomaine().begin(),
                                        p.getGrille()[pre.getI()][pre.getJ()].getSetOfdomaine().end(), ecartLigne)
                                   != p.getGrille()[pre.getI()][pre.getJ()].getSetOfdomaine().end()){

                                    if(forwardChecking(p,ecartLigne,pre.getI(), pre.getJ())){
                                        return true;
                                    }

                                }
                            }
                        }
                    }
                }
                p.reverseUpdateDomaine(v->getI(), v->getJ(), val);
            }
        }
    } else {
        v = &p.getGrille()[predictionI][predictionJ];
        v->setIsSeleted(true);
        int val = predictionValue;
        v->setValeur(val);
        if( p.updateDomaine(v->getI(), v->getJ(), val)){
            if(p.isInconsistantColonne(v->getJ()) >= 0 && p.isInconsistantLigne(v->getI()) >= 0 ){
                if ( ! p.ecartLastCaseLigne(v->getI()) && ! p.ecartLastCaseColonne(v->getJ())) {
                    if(forwardChecking(p)) return true;
                } else {
                    int ecartColonne = p.ecartLastCaseColonne(v->getJ());
                    int ecartLigne = p.ecartLastCaseLigne(v->getI());
                    Variable pre = p.getXYPredictiveVariable((!ecartLigne)?0:v->getI(),(!ecartColonne)?0:v->getJ());

                    if(ecartColonne) {
                        if (find(p.getGrille()[pre.getI()][pre.getJ()].getSetOfdomaine().begin(),
                                 p.getGrille()[pre.getI()][pre.getJ()].getSetOfdomaine().end(), ecartColonne)
                            != p.getGrille()[pre.getI()][pre.getJ()].getSetOfdomaine().end()) {

                            if (forwardChecking(p,ecartColonne,pre.getI(), pre.getJ())) {
                                return true;
                            }
                        }
                    }else{
                        if(find(p.getGrille()[pre.getI()][pre.getJ()].getSetOfdomaine().begin(),
                                p.getGrille()[pre.getI()][pre.getJ()].getSetOfdomaine().end(), ecartLigne)
                           != p.getGrille()[pre.getI()][pre.getJ()].getSetOfdomaine().end()){

                            if(forwardChecking(p,ecartLigne,pre.getI(), pre.getJ())){
                                return true;
                            }

                        }
                    }
                }
            }
        }
        p.reverseUpdateDomaine(v->getI(), v->getJ(), val);
    }

    v->setIsSeleted(false);
    v->setValeur(0);
    return false;
}

bool generateGrille (Grille &p ){
    Variable *v = p.getFreeVariable();
    if(! v)return true;
    v->setIsSeleted(true);

    for(int val :  v->getRamdomSetOfdomaine()){
        v->setValeur(val);
        if( p.updateDomaine(v->getI(), v->getJ(), val)){
            if(generateGrille(p)) return true;
        } else p.reverseUpdateDomaine(v->getI(), v->getJ(), val);
    }
    v->setIsSeleted(false);
    v->setValeur(0);
    return false;
}

void SommeGrille(Grille &p){
    for (int i = 1; i < p.getSize(); ++i) {
        int som = 0;
        for (int j = 1; j < p.getSize(); ++j) {
            som+= p.getGrille()[i][j].getValeur();
        }
        p.getGrille()[i][0].setValeur(som);
        p.getGrille()[i][0].setBorder(true);
    }
    for (int i = 1; i < p.getSize(); ++i) {
        int som = 0;
        for (int j = 1; j < p.getSize(); ++j) {
            som+= p.getGrille()[j][i].getValeur();
        }
        p.getGrille()[0][i].setValeur(som);
        p.getGrille()[0][i].setBorder(true);
    }
}

void deleteGrilleValue(Grille &p,int min,int max){
    for (int i = 1; i < p.getSize(); ++i) {
        for (int j = 1; j < p.getSize(); ++j) {
            p.getGrille()[i][j].setValeur(0);
            p.getGrille()[i][j].setIsSeleted(false);
            p.getGrille()[i][j].setSetOfdomaine(min,max);
        }
    }

}
//************************************************
int sample (Grille &p){
    while (true){
        Variable *v = p.getFreeVariable();
        if(! v){
            p.printGrille();
            return 0;
        }
        int val = v->selectionValue();
        if (val != 0) {
            v->setValeur(val);
            if(! p.updateDomaine(v->getI(), v->getJ(), val) ||
               p.isInconsistantColonne(v->getJ()) < 0 ||
               p.isInconsistantLigne(v->getI()) < 0 ){
                p.printGrille();
                return 1 + p.getNomberFreeVariable();
            }
        }
    }

}

int metaMonteCarlo (Grille &p){
    int bestScore = p.getNomberFreeVariable(), score = 0;
    stack<Variable *> pileVariable;
    while (true){
        Variable *v = p.getFreeVariable();
        if(! v){
            return 0;
        }
        for(int val :  v->getSetOfdomaine()){
            if (val != 0) {
                v->setValeur(val);
                p.printGrille();
                if( ! p.updateDomaine(v->getI(), v->getJ(), val) ||
                    p.isInconsistantColonne(v->getJ()) < 0 ||
                    p.isInconsistantLigne(v->getI()) < 0){
                    score = 1 + p.getNomberFreeVariable();
                } else{
                    score = sample(p.clone());
                }
                if( score < bestScore){
                    bestScore = score ;
                    pileVariable.push(v);
                }
                p.reverseUpdateDomaine(v->getI(), v->getJ(), val);
            }
        }
//        v->setIsSeleted(false);
//        v->setValeur(0); ///!!!!!!!!!!!!!!!!!
//        return false;
        v = pileVariable.top();
        pileVariable.pop();
        if( ! p.updateDomaine(v->getI(), v->getJ(), v->getValeur()) ||
            p.isInconsistantColonne(v->getJ()) < 0 ||
            p.isInconsistantLigne(v->getI()) < 0){
            return  1 + p.getNomberFreeVariable();
        }
        if(bestScore == 0){
            return 0;
        }
    }


}



