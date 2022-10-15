#define _CRT_SECURE_NO_WARNINGS
#if !defined(AFX_TRIESTABLO_H__EA14736F_A30C_4DA9_A044_C865B9328099__INCLUDED_)
#define AFX_TRIESTABLO_H__EA14736F_A30C_4DA9_A044_C865B9328099__INCLUDED_
#include <iostream>
#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

using namespace std;
class TrieStablo{
public:
   class TrieCvor{
       public:
       TrieCvor *m_niz_pokazivaca[255];
       TrieCvor *m_roditelj;
       int frekvencija=0;
       TrieCvor(const TrieCvor &) { }
       TrieCvor &operator=(const TrieCvor &) { }
       TrieCvor(TrieCvor *roditelj);
       virtual ~TrieCvor();
       TrieCvor *roditelj() {return m_roditelj;}
       TrieCvor *pronadjiPodstablo(char deoKljuca);
       void dodajPodstablo(char deoKljuca, TrieCvor *cvor);
   };
    /*najbolji predlozi*/
    string top1, top2, top3;
    int frek1 = -1, frek2 = -1, frek3 = -1;
    TrieCvor *m_koren;
    TrieStablo(const TrieStablo &) { }
    TrieCvor *pronadjiCvor(const char *kljuc); // pronalazi cvor koji sadrzi dati kljuc
    TrieStablo();
    virtual ~TrieStablo();
    virtual void umetni(const char *kljuc);
    virtual void promeni_f(TrieStablo* stablo, string& kljuc);
    virtual void pronadji_sve_ispod(TrieStablo* stablo, string& kljuc);
    virtual void top_tri(TrieStablo* stablo, string kljuc);
};



#endif
