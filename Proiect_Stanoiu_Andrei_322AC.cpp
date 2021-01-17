#include <bits/stdc++.h>
using namespace std;

int k = 0;

class scrisoare
{
    string nume;
    string prenume;
    int varsta;
    string culoare_plic;
    int id;
    int gen; //0 pt baiat, 1 pt fata

public:
    vector <string> wishlist;
    string oras;

    int Gen_get()
    {
        return gen;
    }

    string Nume_get()
    {
        return nume;
    }

    string Prenume_get()
    {
        return prenume;
    }

    scrisoare(string nm, string pn, int vr, string orr,
              vector <string> ws, string cul, int gn)
    {
        gen = gn;
        id = k++;
        nume = nm;
        pn = prenume;
        varsta = vr;
        oras = orr;
        for (int i = 0; i < ws.size(); ++i)
            wishlist.push_back(ws[i]);
        culoare_plic = cul;
    }

    ~scrisoare()
    {
        wishlist.clear();
    }
};

vector <scrisoare> scr; //ca sa am acces in clasa inventar

//------------------------------


class inventar
{
    map <string, int> depozit;
    map <string, int> pret_cadou;

public:
    vector <string> lista_troli[1000]; //presupunem ca avem maxim 1000 copii
    vector <int> lista_acadele;
    vector <string> lista_orase;
    map <int, int> lista_copii;

    invetar(map <string, int> dp, map <int, int> lc, map <string, int> pc)
    {
        map <string, int>::iterator it;
        map <int, int>::iterator it2;

        for (it2 = lc.begin(); it2 != lc.end(); ++it2)
            lista_copii[it2->first] = it2->second;

        for (it = dp.begin(); it != dp.end(); ++it)
            depozit[it->first] = it->second;

        for (it = pc.begin(); it != pc.end(); ++it)
            pret_cadou[it->first] = it->second;
    }
    ~inventar(){}

    void solve();
};

void inventar::solve()
{
    map <int, int>::iterator it;

    int id, buget;

    for (it = lista_copii.begin(); it != lista_copii.end(); ++it)
    {
        id = it->first;
        if (it->second == true)
            buget = 100;
        else buget = 10;

        bool am_dat = false;

        for (int i = 0; i < scr[id].wishlist.size(); ++i)
        {
            string elem = scr[id].wishlist[i];

            if (depozit[elem] == 0) continue;
            if (pret_cadou[elem] > buget) continue;

            lista_troli[id].push_back(elem);
            buget -= pret_cadou[elem];
            am_dat = true;
        }

        if (am_dat == false)
            lista_troli[id].push_back("cadou_default");

        lista_acadele.push_back(buget);
        lista_orase.push_back(scr[id].oras);

        //aici afisam pentru fiecare copil ce va primi

        cout << scr[id].Nume_get() << ' ' << scr[id].Prenume_get() << " va primi:\n";
        for (int i = 0; i < lista_troli[id].size(); ++i)
            cout << lista_troli[id][i] << ' ';
        cout << '\n' << '\n';

    }

}

inventar act;

class troli
{
    int amb_fete;
    int amb_baieti;
    int obraznic;
public:

    int fete_get()
    {
        return amb_fete;
    }

    int baieti_get()
    {
        return amb_baieti;
    }

    int obraznic_get()
    {
        return obraznic;
    }

    troli()
    {
        obraznic = 0;
        amb_fete = 0;
        amb_baieti = 0;
    }

    ~troli()
    {
        obraznic = 0;
        amb_fete = 0;
        amb_baieti = 0;
    }

    void ambalaje();
};

void troli::ambalaje()
{
    //k reprezinta cati copii avem, este tinut global
    //si incrementat cand intram in constructorul scrisoare

    for (int i = 0; i < k; ++i)
    {
        if (scr[i].Gen_get() == 0)
            ++amb_baieti;

        else ++amb_fete;

        if (act.lista_copii[i] == 0) //copil cuminte
            continue;

        else ++obraznic;
    }
}

troli trols;

class doamnaC
{
    double buget;

public:

    double buget_get()
    {
        return buget;
    }

    doamnaC()
    {
        buget = 0;
    }

    ~doamnaC()
    {
        buget = 0;
    }

    void solve();

};

void doamnaC::solve()
{
    for (int i = 0; i < k; ++i)
    {
        buget += act.lista_acadele[i];
    }

    buget += trols.obraznic_get() * 0.5;

}

map <string, int> codificare;
map <int, string> decodificare;

int distante[5][5];

class mosul
{
    int km;
    vector <int> orase;
    map <string, int> orase_copii;
    vector <int> sol;
    vector <int> p;
    int viz[1000]; //maxim 1000 orase
public:
    mosul()
    {
        km = 9999999; // initializam cu ceva mare
        // am strans toate orasele in care trebuie sa mearga mosu
        for (int i = 0; i < k; ++i)
        {
            viz[i] = 0;
            orase_copii[scr[i].oras]++;

            if (orase_copii[scr[i].oras] == 1)
            {
                orase.push_back(codificare[scr[i].oras]);
                continue;
            }
        }
    }

    ~mosul()
    {
        km = 9999999;
    }

    void toate_drumurile(int act, int lvl, int ant);

    void afis_mos()
    {
        cout << "Parcurgem " << km << " km, orasele fiind:\n";
        for (int i = 0; i < sol.size(); ++i)
            cout << sol[i] << ' ';
        cout << '\n';
    }
};

void mosul::toate_drumurile(int act, int lvl, int ant)
{
    if (act > km)
        return;

    if (lvl == orase.size() + 1)
    {
        if (act < km)
        {
            km = act;
            sol.clear();
            for (int i = 0; i < orase.size(); ++i)
            {
                sol.push_back(p[i]);
            }
            return;
        }
    }

    for (int i = 0; i < orase.size(); ++i)
    {
        if (viz[i]) continue;

        viz[i] = 1;

        if (ant == -1)
        {
            p.push_back(i);
            toate_drumurile(act + distante[0][orase[i]], lvl + 1, orase[i]);
            p.pop_back();
        }

        else
        {
            p.push_back(i);
            toate_drumurile(act + distante[ant][orase[i]], lvl + 1, orase[i]);
            p.pop_back();
        }

        viz[i] = 0;
    }
}


int main()
{
    ifstream f ("file.in");

    int nr_copii;
    f >> nr_copii;

    while(nr_copii--)
    {
        string nm, pm, orr, cul, x;
        int vr, marime_ws, gn;
        vector <string> ws;
        f >> nm;
        f >> pm;
        f >> vr;
        f >> orr;
        f >> marime_ws;
        ws.clear();
        for (int i = 0; i < marime_ws; ++i)
        {
            f >> x;
            ws.push_back(x);
        }
        f >> cul;
        f >> gn;
        scrisoare copil(nm, pm, vr, orr, ws, cul, gn);
        scr.push_back(copil);
    }

    act.solve();

    cout << "Trolii au folosit " << trols.baieti_get()
         << " ambalaje pentru baieti si " << trols.fete_get()
         << " ambalaje pentru fete.\n\n";

    doamnaC elena;

    elena.solve();

    cout << "Doamna Craciun va investi: " << elena.buget_get()
         << " dolari.\n\n";

    //Codificam:
    //-Rovaniemi 0 (unde e mosul)
    //-Bratislava 1
    //-Bardejov 2
    //-Zilina 3
    //-Trencin 4

    decodificare[0] = "Rovaniemi";
    decodificare[1] = "Bratislava";
    decodificare[2] = "Bardejov";
    decodificare[3] = "Zilina";
    decodificare[4] = "Trencin";

    codificare["Rovaniemi"] = 0;
    codificare["Bratislava"] = 1;
    codificare["Bardejov"] = 2;
    codificare["Zilina"] = 3;
    codificare["Trencin"] = 4;

    distante[0][1] = 2100;
    distante[0][2] = 1929;
    distante[0][3] = 1962;
    distante[0][4] = 2006;
    distante[1][2] = 331;
    distante[1][3] = 169;
    distante[1][4] = 107;
    distante[2][3] = 184;
    distante[2][4] = 239;
    distante[3][4] = 62;

    mosul mos;

    mos.toate_drumurile(0, 0, -1);

    mos.afis_mos();

    return 0;
}
