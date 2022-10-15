#define _CRT_SECURE_NO_WARNINGS
#include "TrieStablo.h"
#include <stack>
using namespace std;

TrieStablo::TrieCvor::TrieCvor(TrieStablo::TrieCvor *roditelj): m_roditelj(roditelj){
      /*for(int i = 0; i < 255; i++) m_niz_pokazivaca[i] = 0;*/
}

TrieStablo::TrieCvor::~TrieCvor(){
      //if( m_info ) delete []m_info;

      for(int i = 0; i < 255; i++) if( m_niz_pokazivaca[i] ) delete m_niz_pokazivaca[i];
}


TrieStablo::TrieCvor* TrieStablo::TrieCvor::pronadjiPodstablo(char deoKljuca){
      return m_niz_pokazivaca[deoKljuca];
}

void TrieStablo::TrieCvor::dodajPodstablo(char deoKljuca, TrieStablo::TrieCvor *cvor){
      if( ! m_niz_pokazivaca[deoKljuca] ) m_niz_pokazivaca[deoKljuca] = cvor;
           
}

TrieStablo::TrieCvor *TrieStablo::pronadjiCvor(const char *kljuc){
      if( ! m_koren ) return nullptr;
      TrieCvor *tek = m_koren;
      for (int i = 0; i < strlen(kljuc) && tek; i++){
          tek = tek->pronadjiPodstablo(kljuc[i]);
      }
      return tek;
}

void TrieStablo::top_tri(TrieStablo* stablo, string kljuc) {
    int trenfrek, tempfrek, tempfrek2;
    string tempstr, tempstr2;
    if (stablo->pronadjiCvor(kljuc.data()) && stablo->pronadjiCvor(kljuc.data())->frekvencija) {
        trenfrek = stablo->pronadjiCvor(kljuc.data())->frekvencija;
        if (stablo->frek1 == -1) {
            stablo->frek1 = trenfrek;
            stablo->top1 = kljuc;
            return;
        }
        else if (stablo->frek2 == -1 && stablo->top1 != kljuc && stablo->top2 != kljuc && stablo->top3 != kljuc) {
            stablo->frek2 = trenfrek;
            stablo->top2 = kljuc;
            return;
        }
        else if (stablo->frek3 == -1 && stablo->top1 != kljuc && stablo->top2 != kljuc && stablo->top3!=kljuc) {
            stablo->frek3 = trenfrek;
            stablo->top3 = kljuc;
            return;
        }
        else if (trenfrek > stablo->frek1 && stablo->top1 != kljuc && stablo->top2 != kljuc && stablo->top3 != kljuc) {
            tempstr = stablo->top1;
            tempfrek = stablo->frek1;
            stablo->frek1 = trenfrek;
            stablo->top1 = kljuc;
            tempstr2 = stablo->top2;
            tempfrek2 = stablo->frek2;
            stablo->frek2 = tempfrek;
            stablo->top2 = tempstr;
            stablo->frek3 = tempfrek2;
            stablo->top3 = tempstr2;
            return;
        }
        else if (trenfrek < stablo->frek3) {
            return;
        }
        else if (trenfrek < stablo->frek2 && stablo->top1 != kljuc && stablo->top2 != kljuc && stablo->top3 != kljuc) {
            stablo->frek3 = trenfrek;
            stablo->top3 = kljuc;
            return;
        }
        else if (trenfrek < stablo->frek1 && stablo->top1 != kljuc && stablo->top2 != kljuc && stablo->top3 != kljuc) {
            tempstr = stablo->top2;
            tempfrek = stablo->frek2;
            stablo->frek2 = trenfrek;
            stablo->top2 = kljuc;
            stablo->frek3 = tempfrek;
            stablo->top3 = tempstr;
            return;
        }
    }
    return;
}

void TrieStablo::pronadji_sve_ispod(TrieStablo* stablo, string& kljuc) {
    int i;
    string holder, iter;
    if (!m_koren) return;
    TrieCvor* tek = m_koren;
    for (int i = 0; i < strlen(kljuc.data()) && tek; i++) {
        tek = tek->pronadjiPodstablo(kljuc[i]);
    }
    //tek pokazuje na mesto tog prefiksa

    stack<TrieCvor*> scvor;
    stack<string> srec;
    TrieCvor* curr = tek;
    scvor.push(curr);
    srec.push(kljuc);
    while (curr != NULL && scvor.empty() == false && curr != nullptr) {
        curr = scvor.top();
        scvor.pop();
        holder = srec.top();
        srec.pop();
        iter = holder;
        for (i = 96; i < 123; i++) {
            holder += i;
            if (curr->m_niz_pokazivaca[i] != nullptr) {
                scvor.push(stablo->pronadjiCvor(holder.data()));
                srec.push(holder);
                if (stablo->pronadjiCvor(holder.data()) && stablo->pronadjiCvor(holder.data())->frekvencija) {
                    cout << holder << " (" << stablo->pronadjiCvor(holder.data())->frekvencija <<")"<< endl;
                    stablo->top_tri(stablo, holder);
                }
            }
            holder = iter;
        }
    }
    return;
}


TrieStablo::TrieStablo(): m_koren(nullptr){
}
TrieStablo::~TrieStablo(){
      if( m_koren ) delete m_koren;
}

void TrieStablo::promeni_f(TrieStablo* stablo, string& kljuc) {
    int broj;
    if (stablo->pronadjiCvor(kljuc.data()) && stablo->pronadjiCvor(kljuc.data())->frekvencija) {
        cout << "Rec " << kljuc << " postoji i njena frekvencija je " << stablo->pronadjiCvor(kljuc.data())->frekvencija << endl;
        cout << "Unesite novu vrednost frekvencije: ";
        cin >> broj;
        stablo->pronadjiCvor(kljuc.data())->frekvencija = broj;
    }
    else {
        cout << "Rec ne" << kljuc << "postoji" << endl;
    }
}


void TrieStablo::umetni(const char *kljuc){
      if( ! m_koren ){
            m_koren = new TrieCvor(nullptr);
            
      }

      TrieCvor *tek = m_koren;
      TrieCvor *sledeci = nullptr;

      for( int i = 0; i < strlen(kljuc); i++ ){
      
            sledeci = tek->pronadjiPodstablo( kljuc[i] );

            if( ! sledeci )
            {
                  sledeci = new TrieCvor(tek);
                  tek->dodajPodstablo( kljuc[i], sledeci );
                  
            }

            tek = sledeci;
      }
      tek->frekvencija++;
}