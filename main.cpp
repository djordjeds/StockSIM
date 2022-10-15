#define _CRT_SECURE_NO_WARNINGS
#include <fstream>
#include <string>
#include <algorithm>
#include "TrieStablo.h"
#include <filesystem>

using namespace std;
namespace fs = filesystem;



bool ispravna_rec(string& rec){
    return rec.find_first_not_of("ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz") == string::npos;
}

void trazi_kljuc(TrieStablo* stablo, string& kljuc){
    if (stablo->pronadjiCvor(kljuc.data()) && stablo->pronadjiCvor(kljuc.data())->frekvencija) {
        cout << kljuc << " (" << stablo->pronadjiCvor(kljuc.data())->frekvencija <<")" <<endl;
        stablo->top_tri(stablo, kljuc);
    }
    //else cout << "Rec " << kljuc << " ne postoji"<< endl;
}


string mala_slova(string rijec) {
    int i;
    for (int i = 0; i < rijec.length(); i++)rijec[i] = tolower(rijec[i]);
    //cout << rijec << endl;
    return rijec;
}

int pozicija(const char* niz, size_t velicina, char c){
    const char* end = niz + velicina;
    const char* mes = find(niz, end, c);
    if (end == mes) {
        return -1;
    }
    else return (mes - niz);
}

void indeks(string rec, int* pos, int* flag, int ind) {
    int i, j, k;
    char qw0[10] = { 'q', 'w', 'e', 'r', 't', 'y', 'u', 'i', 'o', 'p' };
    char qw1[9] = { 'a', 's', 'd', 'f', 'g', 'h', 'j', 'k', 'l' };
    char qw2[7] = { 'z', 'x', 'c', 'v', 'b', 'n', 'm' };

    if (ispravna_rec(rec)) {
        rec = mala_slova(rec);
    }
    else {
        cout << endl << "Rec koju ste uneli nije ispravna." << endl;
        return;
    }
    for (i = 0; i < strlen(rec.data()); i++) {
        *flag = 0;
        *pos = -1;
        *pos = pozicija(qw0, 10, rec[i]);
        if (*pos == -1) {
            *pos = pozicija(qw1, 9, rec[i]);
            (*flag)++;
        }
        if (*pos == -1) {
            *pos = pozicija(qw2, 7, rec[i]);
            (*flag)++;
        }
        if (i == ind) return;
        //cout << "Pozicija " << rec[i] << " je " << *pos << " u qw" << *flag << endl;
    }

    return;

}

void yeahright3(TrieStablo* stablo, string rec, int NO, int NOPE) {
    int i, j, k, pos, flag;
    char qw0[10] = { 'q', 'w', 'e', 'r', 't', 'y', 'u', 'i', 'o', 'p' };
    char qw1[9] = { 'a', 's', 'd', 'f', 'g', 'h', 'j', 'k', 'l' };
    char qw2[7] = { 'z', 'x', 'c', 'v', 'b', 'n', 'm' };
    string tekost;

    for (i = 0; i < strlen(rec.data()); i++) {
        if (i == NO || i==NOPE) continue;
        indeks(rec, &pos, &flag, i);
        //cout << "Pozicija " << rec[i] << " je " << pos << " u qw" << flag << endl;
        tekost = rec;
        trazi_kljuc(stablo, tekost);
        stablo->pronadji_sve_ispod(stablo, tekost);
        if (flag == 0) {
            if (pos == 0) {
                tekost[i] = qw0[pos + 1];
                trazi_kljuc(stablo, tekost);
                stablo->pronadji_sve_ispod(stablo, tekost);
                tekost[i] = qw1[pos];
                trazi_kljuc(stablo, tekost);
                stablo->pronadji_sve_ispod(stablo, tekost);
            }
            else if (pos == 9) {
                tekost[i] = qw0[8];
                trazi_kljuc(stablo, tekost);
                stablo->pronadji_sve_ispod(stablo, tekost);
                tekost[i] = qw1[8];
                trazi_kljuc(stablo, tekost);
                stablo->pronadji_sve_ispod(stablo, tekost);

            }
            else {
                tekost[i] = qw0[pos - 1];
                trazi_kljuc(stablo, tekost);
                stablo->pronadji_sve_ispod(stablo, tekost);
                tekost[i] = qw0[pos + 1];
                trazi_kljuc(stablo, tekost);
                stablo->pronadji_sve_ispod(stablo, tekost);
                tekost[i] = qw1[pos];
                trazi_kljuc(stablo, tekost);
                stablo->pronadji_sve_ispod(stablo, tekost);
                tekost[i] = qw1[pos - 1];
                trazi_kljuc(stablo, tekost);
                stablo->pronadji_sve_ispod(stablo, tekost);
            }



        }

        else if (flag == 1) {
            if (pos == 0) {
                tekost[i] = qw0[pos + 1];
                trazi_kljuc(stablo, tekost);
                stablo->pronadji_sve_ispod(stablo, tekost);
                tekost[i] = qw0[pos];
                trazi_kljuc(stablo, tekost);
                stablo->pronadji_sve_ispod(stablo, tekost);
                tekost[i] = qw1[pos + 1];
                trazi_kljuc(stablo, tekost);
                stablo->pronadji_sve_ispod(stablo, tekost);
            }
            else if (pos == 8) {
                tekost[i] = qw0[pos + 1];
                trazi_kljuc(stablo, tekost);
                stablo->pronadji_sve_ispod(stablo, tekost);
                tekost[i] = qw0[pos];
                trazi_kljuc(stablo, tekost);
                stablo->pronadji_sve_ispod(stablo, tekost);
                tekost[i] = qw1[pos - 1];
                trazi_kljuc(stablo, tekost);
                stablo->pronadji_sve_ispod(stablo, tekost);
            }
            else {
                tekost[i] = qw0[pos];
                trazi_kljuc(stablo, tekost);
                stablo->pronadji_sve_ispod(stablo, tekost);
                tekost[i] = qw0[pos + 1];
                trazi_kljuc(stablo, tekost);
                stablo->pronadji_sve_ispod(stablo, tekost);
                tekost[i] = qw2[pos - 1];
                trazi_kljuc(stablo, tekost);
                stablo->pronadji_sve_ispod(stablo, tekost);
                tekost[i] = qw1[pos - 1];
                trazi_kljuc(stablo, tekost);
                stablo->pronadji_sve_ispod(stablo, tekost);
                tekost[i] = qw1[pos + 1];
                trazi_kljuc(stablo, tekost);
                stablo->pronadji_sve_ispod(stablo, tekost);
            }


        }
        else if (flag == 2) {
            if (pos == 0) {
                tekost[i] = qw1[pos + 1];
                trazi_kljuc(stablo, tekost);
                stablo->pronadji_sve_ispod(stablo, tekost);
                tekost[i] = qw1[pos];
                trazi_kljuc(stablo, tekost);
                stablo->pronadji_sve_ispod(stablo, tekost);
                tekost[i] = qw2[pos + 1];
                trazi_kljuc(stablo, tekost);
                stablo->pronadji_sve_ispod(stablo, tekost);
            }
            else if (pos == 6) {
                tekost[i] = qw2[pos - 1];
                trazi_kljuc(stablo, tekost);
                stablo->pronadji_sve_ispod(stablo, tekost);
                tekost[i] = qw1[pos];
                trazi_kljuc(stablo, tekost);
                stablo->pronadji_sve_ispod(stablo, tekost);
                tekost[i] = qw1[pos + 1];
                trazi_kljuc(stablo, tekost);
                stablo->pronadji_sve_ispod(stablo, tekost);

            }
            else {
                tekost[i] = qw2[pos - 1];
                trazi_kljuc(stablo, tekost);
                stablo->pronadji_sve_ispod(stablo, tekost);
                tekost[i] = qw2[pos + 1];
                trazi_kljuc(stablo, tekost);
                stablo->pronadji_sve_ispod(stablo, tekost);
                tekost[i] = qw1[pos + 1];
                trazi_kljuc(stablo, tekost);
                stablo->pronadji_sve_ispod(stablo, tekost);
            }


        }

        /*
        for (j = 0; strlen(rec.data()); j++) {
            for (k = 0; strlen(rec.data()); k++) {

            }
        }*/
    }
    return;

}

void yeahright2(TrieStablo* stablo, string rec, int NO) {
    int i, j, k, pos, flag;
    char qw0[10] = { 'q', 'w', 'e', 'r', 't', 'y', 'u', 'i', 'o', 'p' };
    char qw1[9] = { 'a', 's', 'd', 'f', 'g', 'h', 'j', 'k', 'l' };
    char qw2[7] = { 'z', 'x', 'c', 'v', 'b', 'n', 'm' };
    string tekost;

    for (i = 0; i < strlen(rec.data()); i++) {
        if (i == NO) continue;
        indeks(rec, &pos, &flag, i);
        //cout << "Pozicija " << rec[i] << " je " << pos << " u qw" << flag << endl;
        tekost = rec;
        trazi_kljuc(stablo, tekost);
        stablo->pronadji_sve_ispod(stablo, tekost);
        if (flag == 0) {
            if (pos == 0) {
                tekost[i] = qw0[pos + 1];
                yeahright3(stablo, tekost, NO,i);
                trazi_kljuc(stablo, tekost);
                stablo->pronadji_sve_ispod(stablo, tekost);
                tekost[i] = qw1[pos];
                yeahright3(stablo, tekost, NO, i);
                trazi_kljuc(stablo, tekost);
                stablo->pronadji_sve_ispod(stablo, tekost);
            }
            else if (pos == 9) {
                tekost[i] = qw0[8];
                yeahright3(stablo, tekost, NO, i);
                trazi_kljuc(stablo, tekost);
                stablo->pronadji_sve_ispod(stablo, tekost);
                tekost[i] = qw1[8];
                yeahright3(stablo, tekost, NO, i);
                trazi_kljuc(stablo, tekost);
                stablo->pronadji_sve_ispod(stablo, tekost);

            }
            else {
                tekost[i] = qw0[pos - 1];
                yeahright3(stablo, tekost, NO, i);
                trazi_kljuc(stablo, tekost);
                stablo->pronadji_sve_ispod(stablo, tekost);
                tekost[i] = qw0[pos + 1];
                yeahright3(stablo, tekost, NO, i);
                trazi_kljuc(stablo, tekost);
                stablo->pronadji_sve_ispod(stablo, tekost);
                tekost[i] = qw1[pos];
                yeahright3(stablo, tekost, NO, i);
                trazi_kljuc(stablo, tekost);
                stablo->pronadji_sve_ispod(stablo, tekost);
                tekost[i] = qw1[pos - 1];
                yeahright3(stablo, tekost, NO, i);
                trazi_kljuc(stablo, tekost);
                stablo->pronadji_sve_ispod(stablo, tekost);
            }



        }

        else if (flag == 1) {
            if (pos == 0) {
                tekost[i] = qw0[pos + 1];
                yeahright3(stablo, tekost, NO, i);
                trazi_kljuc(stablo, tekost);
                stablo->pronadji_sve_ispod(stablo, tekost);
                tekost[i] = qw0[pos];
                yeahright3(stablo, tekost, NO, i);
                trazi_kljuc(stablo, tekost);
                stablo->pronadji_sve_ispod(stablo, tekost);
                tekost[i] = qw1[pos + 1];
                yeahright3(stablo, tekost, NO, i);
                trazi_kljuc(stablo, tekost);
                stablo->pronadji_sve_ispod(stablo, tekost);
            }
            else if (pos == 8) {
                tekost[i] = qw0[pos + 1];
                yeahright3(stablo, tekost, NO, i);
                trazi_kljuc(stablo, tekost);
                stablo->pronadji_sve_ispod(stablo, tekost);
                tekost[i] = qw0[pos];
                yeahright3(stablo, tekost, NO, i);
                trazi_kljuc(stablo, tekost);
                stablo->pronadji_sve_ispod(stablo, tekost);
                tekost[i] = qw1[pos - 1];
                yeahright3(stablo, tekost, NO, i);
                trazi_kljuc(stablo, tekost);
                stablo->pronadji_sve_ispod(stablo, tekost);
            }
            else {
                tekost[i] = qw0[pos];
                yeahright3(stablo, tekost, NO, i);
                trazi_kljuc(stablo, tekost);
                stablo->pronadji_sve_ispod(stablo, tekost);
                tekost[i] = qw0[pos + 1];
                yeahright3(stablo, tekost, NO, i);
                trazi_kljuc(stablo, tekost);
                stablo->pronadji_sve_ispod(stablo, tekost);
                tekost[i] = qw2[pos - 1];
                yeahright3(stablo, tekost, NO, i);
                trazi_kljuc(stablo, tekost);
                stablo->pronadji_sve_ispod(stablo, tekost);
                tekost[i] = qw1[pos - 1];
                yeahright3(stablo, tekost, NO, i);
                trazi_kljuc(stablo, tekost);
                stablo->pronadji_sve_ispod(stablo, tekost);
                tekost[i] = qw1[pos + 1];
                yeahright3(stablo, tekost, NO, i);
                trazi_kljuc(stablo, tekost);
                stablo->pronadji_sve_ispod(stablo, tekost);
            }


        }
        else if (flag == 2) {
            if (pos == 0) {
                tekost[i] = qw1[pos + 1];
                yeahright3(stablo, tekost, NO, i);
                trazi_kljuc(stablo, tekost);
                stablo->pronadji_sve_ispod(stablo, tekost);
                tekost[i] = qw1[pos];
                yeahright3(stablo, tekost, NO, i);
                trazi_kljuc(stablo, tekost);
                stablo->pronadji_sve_ispod(stablo, tekost);
                tekost[i] = qw2[pos + 1];
                yeahright3(stablo, tekost, NO, i);
                trazi_kljuc(stablo, tekost);
                stablo->pronadji_sve_ispod(stablo, tekost);
            }
            else if (pos == 6) {
                tekost[i] = qw2[pos - 1];
                yeahright3(stablo, tekost, NO, i);
                trazi_kljuc(stablo, tekost);
                stablo->pronadji_sve_ispod(stablo, tekost);
                tekost[i] = qw1[pos];
                yeahright3(stablo, tekost, NO, i);
                trazi_kljuc(stablo, tekost);
                stablo->pronadji_sve_ispod(stablo, tekost);
                tekost[i] = qw1[pos + 1];
                yeahright3(stablo, tekost, NO, i);
                trazi_kljuc(stablo, tekost);
                stablo->pronadji_sve_ispod(stablo, tekost);

            }
            else {
                tekost[i] = qw2[pos - 1];
                yeahright3(stablo, tekost, NO, i);
                trazi_kljuc(stablo, tekost);
                stablo->pronadji_sve_ispod(stablo, tekost);
                tekost[i] = qw2[pos + 1];
                yeahright3(stablo, tekost, NO, i);
                trazi_kljuc(stablo, tekost);
                stablo->pronadji_sve_ispod(stablo, tekost);
                tekost[i] = qw1[pos + 1];
                yeahright3(stablo, tekost, NO, i);
                trazi_kljuc(stablo, tekost);
                stablo->pronadji_sve_ispod(stablo, tekost);
            }


        }

        /*
        for (j = 0; strlen(rec.data()); j++) {
            for (k = 0; strlen(rec.data()); k++) {

            }
        }*/
    }
    return;

}

void yeahright(TrieStablo* stablo, string rec) {
    int i, j, k, pos, flag;
    char qw0[10] = { 'q', 'w', 'e', 'r', 't', 'y', 'u', 'i', 'o', 'p' };
    char qw1[9] = { 'a', 's', 'd', 'f', 'g', 'h', 'j', 'k', 'l' };
    char qw2[7] = { 'z', 'x', 'c', 'v', 'b', 'n', 'm' };
    string tekost;
  
    for (i = 0; i < strlen(rec.data()) ; i++) {
        indeks(rec, &pos, &flag, i);
        //cout << "Pozicija " << rec[i] << " je " << pos << " u qw" << flag << endl;
        tekost = rec;
        trazi_kljuc(stablo, tekost);
        stablo->pronadji_sve_ispod(stablo, tekost);
        if (flag == 0) {
            if (pos == 0) {
                tekost[i] = qw0[pos+1];
                yeahright2(stablo, tekost, i);
                trazi_kljuc(stablo, tekost);
                stablo->pronadji_sve_ispod(stablo, tekost);
                tekost[i] = qw1[pos];
                yeahright2(stablo, tekost, i);
                trazi_kljuc(stablo, tekost);
                stablo->pronadji_sve_ispod(stablo, tekost);
            }
            else if (pos == 9) {
                tekost[i] = qw0[8];
                yeahright2(stablo, tekost, i);
                trazi_kljuc(stablo, tekost);
                stablo->pronadji_sve_ispod(stablo, tekost);
                tekost[i] = qw1[8];
                yeahright2(stablo, tekost, i);
                trazi_kljuc(stablo, tekost);
                stablo->pronadji_sve_ispod(stablo, tekost);

            }
            else {
                tekost[i] = qw0[pos -1];
                yeahright2(stablo, tekost, i);
                trazi_kljuc(stablo, tekost);
                stablo->pronadji_sve_ispod(stablo, tekost);
                tekost[i] = qw0[pos +1];
                yeahright2(stablo, tekost, i);
                trazi_kljuc(stablo, tekost);
                stablo->pronadji_sve_ispod(stablo, tekost);
                tekost[i] = qw1[pos];
                yeahright2(stablo, tekost, i);
                trazi_kljuc(stablo, tekost);
                stablo->pronadji_sve_ispod(stablo, tekost);
                tekost[i] = qw1[pos -1];
                yeahright2(stablo, tekost, i);
                trazi_kljuc(stablo, tekost);
                stablo->pronadji_sve_ispod(stablo, tekost);
            }



        }
        
        else if (flag == 1) {
            if (pos == 0) {
                tekost[i] = qw0[pos + 1];
                yeahright2(stablo, tekost, i);
                trazi_kljuc(stablo, tekost);
                stablo->pronadji_sve_ispod(stablo, tekost);
                tekost[i] = qw0[pos];
                yeahright2(stablo, tekost, i);
                trazi_kljuc(stablo, tekost);
                stablo->pronadji_sve_ispod(stablo, tekost);
                tekost[i] = qw1[pos+1];
                yeahright2(stablo, tekost, i);
                trazi_kljuc(stablo, tekost);
                stablo->pronadji_sve_ispod(stablo, tekost);
            }
            else if (pos == 8) {
                tekost[i] = qw0[pos + 1];
                yeahright2(stablo, tekost, i);
                trazi_kljuc(stablo, tekost);
                stablo->pronadji_sve_ispod(stablo, tekost);
                tekost[i] = qw0[pos];
                yeahright2(stablo, tekost, i);
                trazi_kljuc(stablo, tekost);
                stablo->pronadji_sve_ispod(stablo, tekost);
                tekost[i] = qw1[pos - 1];
                yeahright2(stablo, tekost, i);
                trazi_kljuc(stablo, tekost);
                stablo->pronadji_sve_ispod(stablo, tekost);
            }
            else {
                tekost[i] = qw0[pos];
                yeahright2(stablo, tekost, i);
                trazi_kljuc(stablo, tekost);
                stablo->pronadji_sve_ispod(stablo, tekost);
                tekost[i] = qw0[pos + 1];
                yeahright2(stablo, tekost, i);
                trazi_kljuc(stablo, tekost);
                stablo->pronadji_sve_ispod(stablo, tekost);
                tekost[i] = qw2[pos-1];
                yeahright2(stablo, tekost, i);
                trazi_kljuc(stablo, tekost);
                stablo->pronadji_sve_ispod(stablo, tekost);
                tekost[i] = qw1[pos - 1];
                yeahright2(stablo, tekost, i);
                trazi_kljuc(stablo, tekost);
                stablo->pronadji_sve_ispod(stablo, tekost);
                tekost[i] = qw1[pos + 1];
                yeahright2(stablo, tekost, i);
                trazi_kljuc(stablo, tekost);
                stablo->pronadji_sve_ispod(stablo, tekost);
            }


        }
        else if(flag==2){
            if (pos == 0) {
                tekost[i] = qw1[pos + 1];
                yeahright2(stablo, tekost, i);
                trazi_kljuc(stablo, tekost);
                stablo->pronadji_sve_ispod(stablo, tekost);
                tekost[i] = qw1[pos];
                yeahright2(stablo, tekost, i);
                trazi_kljuc(stablo, tekost);
                stablo->pronadji_sve_ispod(stablo, tekost);
                tekost[i] = qw2[pos+1];
                yeahright2(stablo, tekost, i);
                trazi_kljuc(stablo, tekost);
                stablo->pronadji_sve_ispod(stablo, tekost);
            }
            else if (pos == 6) {
                tekost[i] = qw2[pos-1];
                yeahright2(stablo, tekost, i);
                trazi_kljuc(stablo, tekost);
                stablo->pronadji_sve_ispod(stablo, tekost);
                tekost[i] = qw1[pos];
                yeahright2(stablo, tekost, i);
                trazi_kljuc(stablo, tekost);
                stablo->pronadji_sve_ispod(stablo, tekost);
                tekost[i] = qw1[pos+1];
                yeahright2(stablo, tekost, i);
                trazi_kljuc(stablo, tekost);
                stablo->pronadji_sve_ispod(stablo, tekost);

            }
            else {
                tekost[i] = qw2[pos - 1];
                yeahright2(stablo, tekost, i);
                trazi_kljuc(stablo, tekost);
                stablo->pronadji_sve_ispod(stablo, tekost);
                tekost[i] = qw2[pos + 1];
                yeahright2(stablo, tekost, i);
                trazi_kljuc(stablo, tekost);
                stablo->pronadji_sve_ispod(stablo, tekost);
                tekost[i] = qw1[pos+1];
                yeahright2(stablo, tekost, i);
                trazi_kljuc(stablo, tekost);
                stablo->pronadji_sve_ispod(stablo, tekost);
            }


        }
 
        /*
        for (j = 0; strlen(rec.data()); j++) {
            for (k = 0; strlen(rec.data()); k++) {

            }
        }*/
    }
    return;

}

//fic_1868_9550.txt
int main(){
    int izbor;
    string f_ime, tekost;
    TrieStablo* stablo = nullptr;
  
    string path = "C:\\Users\\stano\\Documents\\Fakultet\\ASP2\\dz3\\text";
    
    while (true){
        cout << "========================================================\n";
        cout << "\t\tIzaberite komandu: " << endl;
        cout << "--------------------------------------------------------\n";
        cout << "(1) Stvaranje praznog recnika" << endl;
        cout << "(2) Unistavanje recnika" << endl;
        cout << "(3) Stvaranje recnika na osnovu zadate datoteke" << endl;
        cout << "(4) Trazenje reci u recniku i prikaz njene frekvencije" << endl;
        cout << "(5) Umetanje reci u recnik" << endl;
        cout << "(6) Promena frekvencije reci" << endl;
        cout << "(7) Sve reci ispod" << endl;
        cout << "(8) Predlozi za rec" << endl;
        cout << "(0) Gasenje programa" << endl;
        cout << "========================================================\n";
        cout << endl << "Izbor: ";
        cin >> izbor;
        switch (izbor) {
        case 1:
            stablo = new TrieStablo;
            cout << endl << "Prazan recnik uspesno stvoren!" << endl;
            break;
        case 2:
            if(stablo==nullptr) cout << endl << "Recnik nije ni formiran!" << endl;
            else {
                delete stablo;
                cout << endl << "Recnik nije ni formiran!" << endl;
            }
            break;
        case 3:
            if(stablo==nullptr) stablo = new TrieStablo;
            /*
            cout << endl << "Unesite ime datoteke: ";
            cin >> f_ime;
            //f_ime = "fic_1868_9550.txt";
            //f_ime = "bible.txt";
            fajl.open(f_ime);
            */
            for (const auto& entry : fs::directory_iterator(path)) {
                ifstream fajl(entry.path());
                while (fajl >> tekost) {
                    if (ispravna_rec(tekost)) {
                        stablo->umetni(mala_slova(tekost).data());
                    }
                }
                fajl.close();
            }
            cout << "Uspesno! "<<endl;
            break;
        case 4:
            if(stablo==nullptr) cout << endl << "Recnik nije ni formiran!" << endl;
            else {
                cout << endl << "Unesite rec koju trazite: ";
                cin >> tekost;
                tekost = mala_slova(tekost);
                trazi_kljuc(stablo, tekost);
            }
            break;
        case 5:
            if (stablo == nullptr) cout << endl << "Recnik nije ni formiran!" << endl;
            else {
                cout << endl << "Unesite rec koju unosite: ";
                cin >> tekost;
                if (ispravna_rec(tekost)) {
                    stablo->umetni(mala_slova(tekost).data());
                    cout << endl << "Rec je uspesno unesena je u recnik." << endl;
                }
                else {
                    cout << endl << "Rec koju ste uneli nije ispravna." << endl;
                }
            }
            break;
        case 6:
            if (stablo == nullptr) cout << endl << "Recnik nije ni formiran!" << endl;
            else {
                cout << endl << "Unesite kljuc ciju frekvenciju menjate: ";
                cin >> tekost;
                if (ispravna_rec(tekost)) {
                    stablo->promeni_f(stablo, tekost);
                }
                else {
                    cout << endl << "Rec koju ste uneli nije ispravna."<<endl;
                }
            }
            break;
        case 7:
            if (stablo == nullptr) cout << endl << "Recnik nije ni formiran!" << endl;
            else {
                cout << endl << "Unesite rec koju trazite: ";
                cin >> tekost;
                if (ispravna_rec(tekost)) {
                    tekost = mala_slova(tekost);
                    trazi_kljuc(stablo, tekost);
                    stablo->pronadji_sve_ispod(stablo, tekost);
                }
                else {
                    cout << endl << "Rec koju ste uneli nije ispravna." << endl;
                }
            }
            break;
        case 8:
            if (stablo == nullptr) cout << endl << "Recnik nije ni formiran!" << endl;
            else {
                cout << endl << "Unesite rec koju trazite: ";
                cin >> tekost;
                if (ispravna_rec(tekost)) {
                    yeahright(stablo,  mala_slova(tekost)); 
                    cout << "Predlozi: ";
                    if (stablo->frek1 != -1)cout << stablo->top1 << "(" << stablo->frek1 << ") ";
                    if (stablo->frek2 != -1)cout << stablo->top2 << "(" << stablo->frek2 << ") ";
                    if (stablo->frek3 != -1)cout << stablo->top3 << "(" << stablo->frek3 << ") ";
                    cout << endl;
                    stablo->top1.clear(), stablo->top2.clear(), stablo->top3.clear();
                    stablo->frek1 = -1, stablo->frek2 = -1, stablo->frek3 = -1;
                }
                else {
                    cout << endl << "Rec koju ste uneli nije ispravna." << endl;
                }
            }
            break;
        case 0:
            delete stablo;
            stablo = nullptr;
            return 0;
        default: cout << "*******************************\n" << "Izaberite validnu opciju\n" << "*******************************\n" << endl;
        }
    }
    
}
