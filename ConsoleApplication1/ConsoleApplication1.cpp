#include <iostream>
#include <unordered_map>

using namespace std;



class plata {
protected:
    int currentId;
    float suma;
    string data;
    bool Pvalid = false;
public:
    plata(float s = 0, string d = "01.01.1970")
    {
        try
        {
            if (s <= 0)
                throw s;
            else
            {
                suma = s;
                Pvalid = true;
            }
        }
        catch (float s)
        {
            Pvalid = false;
        }
        catch (...)
        {
            cout << "plata nu a fost inregistrata";
            Pvalid = false;
        }
        try
        {
            if (!dataValida(d))
                throw d;
            else
            {
                data = d;
                Pvalid = true;

            }
        }
        catch (string d)
        {
            Pvalid = false;
        }
    }
    plata(const plata& ob)
    {
        data = ob.data;
        suma = ob.suma;
        currentId = ob.currentId;
    }
    virtual ~plata()
    {
        data = "";
        suma = 0;
        currentId = 0;
    }
    void setId(int x)
    {
        currentId = x;
    }
    const int getId()
    {
        return currentId;
    }
    float getSuma()
    {
        return suma;
    }
    void setSuma(float s)
    {
        suma = s;
    }
    virtual void afis(ostream& os)
    {
        os << currentId << " " << suma << "RON " << data << '\n';
    }

    bool valid()
    {
        return Pvalid;
    }
    friend istream& operator>>(istream& in, plata& p)
    {
        p.citeste(in);
        return in;
    }

    friend ostream& operator<<(ostream& in, plata& p)
    {
        p.afis(in);
        return in;
    }
    bool dataValida(string d)
    {
        if (d[2] != '.' || d[5] != '.' || d[0] > '3' || d[3] > '1')
            return false;
        if (d.length() != 10)
            return false;
        for (int i = 0; i < d.length(); i++)
            if (i != 2 && i != 5)
                if (d[i] < '0' || d[i]>'9')
                    return false;
        return true;
    }
    virtual void citeste(istream& in)
    {
        cout << "Suma platita:\n";
        try
        {
            float s;
            in >> s;
            if (s > 0)
            {
                setSuma(s);
                Pvalid = true;
            }
            else
                throw s;
        }
        catch (float s)
        {
            cout << "suma invalida";
            Pvalid = false;
        }
        try
        {
            string d;
            cout << "Introduceti data:\n";
            in >> d;
            if (!dataValida(d))
                throw d;
            else
                data = d;
        }
        catch (string d)
        {
            cout << "data invalida";
            Pvalid = false;
        }

    }
};

class cec :public plata {
private:
    string nume;
public:
    cec(string a = "", float s = 0, string d = "01.01.1970") :plata(s, d)
    {
        nume = a;
    }
    cec(const cec& ob)
    {
        data = ob.data;
        suma = ob.suma;
        currentId = ob.currentId;
        nume = ob.nume;
    }
    ~cec()
    {
        data = "";
        suma = 0;
        currentId = 0;
        nume = "";
    }

    void afis(ostream& os)
    {
        if (Pvalid)
            os << currentId << " " << suma << "RON " << data << " " << nume << '\n';
    }

    void citeste(istream& in)
    {
        cout << "Suma platita:\n";
        try
        {
            float s;
            in >> s;
            if (s > 0)
            {
                setSuma(s);
                Pvalid = true;
            }
            else
                throw s;
        }
        catch (float s)
        {
            cout << "suma invalida";
            Pvalid = false;
        }
        try
        {
            string d;
            cout << "Introduceti data:\n";
            in >> d;
            if (!dataValida(d))
                throw d;
            else
                data = d;
        }
        catch (string d)
        {
            cout << "data invalida";
            Pvalid = false;
        }
        cout << "Nume:\n";
        string a;
        in >> nume;

    }


};

class card :public plata {
private:
    string nume;
    unsigned long long nr;
public:
    card(string a = "", unsigned long long l = 0, float s = 0, string d = "01.01.1970") :plata(s, d)
    {
        try
        {
            if (l < 1000000000000000 || l >= 10000000000000000)
                throw l;
            else
            {
                nr = l;
                nume = a;
                Pvalid = true;

            }
        }
        catch (unsigned long long l)
        {
            Pvalid = false;

        }
    }
    card(const card& ob)
    {
        data = ob.data;
        suma = ob.suma;
        currentId = ob.currentId;
        nume = ob.nume;
        nr = ob.nr;
    }
    ~card()
    {
        data = "";
        suma = 0;
        currentId = 0;
        nume = "";
        nr = 0;
    }
    void citeste(istream& in)
    {
        cout << "Suma platita:\n";
        try
        {
            float s;
            in >> s;
            if (s > 0)
            {
                setSuma(s);
                Pvalid = true;
            }
            else
                throw s;
        }
        catch (float s)
        {
            cout << "suma invalida";
            Pvalid = false;
        }
        try
        {
            string d;
            cout << "Introduceti data:\n";
            in >> d;
            if (!dataValida(d))
                throw d;
            else
                data = d;
        }
        catch (string d)
        {
            cout << "data invalida";
            Pvalid = false;
        }
        cout << "Nume:\n";
        string a;
        in >> nume;
        cout << "Numar de card:\n";
        try
        {

            unsigned long long l;
            in >> l;
            if (l < 1000000000000000 || l >= 10000000000000000)
                throw l;
            else
            {
                nr = l;
                Pvalid = true;

            }
        }
        catch (unsigned long long l)
        {
            cout << "numar de card invalid \n";
            Pvalid = false;
        }


    }
    void afis(ostream& os)
    {
        if (Pvalid)
            os << currentId << " " << suma << "RON " << data <<" "<< nume << " " << nr << '\n';
    }
    string getNume()
    {
        return nume;
    }
};

template <class t> class Gestiune {
private:
    static int id;
    unordered_map<int, t> umap;
public:
    void operator += (t& p)
    {

        if (p.valid())
        {
            incrementeaza();
            p.setId(id);
            umap.insert(make_pair(id, p));
            umap[id] = p;

        }
    }
    void afis()
    {
        for (auto x : umap)
            cout<<x.second<<'\n';
    }
    int nrClienti()
    {
        return id;
    }
    static void incrementeaza()
    {
        id++;
    }
    bool empty()
    {
        return umap.empty();
    }
};
template <class t>int Gestiune<t>::id = 0;

template <> class Gestiune<card> {
private:
    static int id;
    unordered_map<int, string> numele;
    unordered_map<int, card> umap;
public:
    void operator += (card& p)
    {
        if (p.valid())
        {
            incrementeaza();
            p.setId(id);
            numele.insert(make_pair(id, p.getNume()));
            umap.insert(make_pair(id, p));
        }
    }
    void afis()
    {
        for (auto x : umap)
            cout << x.second<<'\n';
    }
    void afisNume()
    {
        for (auto x : numele)
            cout << x.second << '\n';
    }
    int nrClienti()
    {
        return id;
    }
    static void incrementeaza()
    {
        id++;
    }

};

int Gestiune<card>::id = 0;

void menu_output()
{
    cout << "\n Bertalan Victor 141.1 - Tema 3: \n";
    cout << "\n\t MENIU:";
    cout << "\n===========================================\n";
    cout << "\n";
    cout << "1. Introduceti o noua plata\n";
    cout << "2. Afisare plati\n";
    cout << "3. Afiseaza numele celor ce au facut plati cu cardul\n";
    cout << "4. Afiseaza numarul de clienti\n";
    cout << "5. Introdu n plati:\n";
    cout << "6. Afisarea tuturor platilor:\n";
    cout << "0. Iesire.\n";
}

int main()
{
    int option;
    option = 0;
    int option2;
    Gestiune <plata> cash;
    Gestiune <cec> cecuri;
    Gestiune <card> carduri;
    do
    {
        menu_output();

        cout << "\nIntroduceti numarul actiunii: ";
        cin >> option;

        if (option == 1)
        {
            cout << "\nPentru o plata de tip cash apasati tasta 1\n";
            cout << "Pentru o plata de tip cec apasati tasta 2\n";
            cout << "Pentru o plata de tip card apasati tasta 3\n";
            cout << "Pentru a merge inapoi apasati tasta 0 \n";
            cout << "\nIntroduceti numarul actiunii: ";
            cin >> option2;
            cout << '\n';
            if (option2 == 1)
            {
                plata p;
                cin >> p;
                if (p.valid())
                    cout << "\nPlata a fost adaugata cu succes.\n";
                else
                    cout << "\nPlata nu a fost adaugata.\n";
                cash += p;
            }
            if (option2 == 2)
            {
                cec p;
                cin >> p;
                if (p.valid())
                    cout << "\nPlata a fost adaugata cu succes.\n";
                else
                    cout << "\nPlata nu a fost adaugata.\n";
                cecuri += p;
            }
            if (option2 == 3)
            {
                card p;
                cin >> p;
                if (p.valid())
                    cout << "\nPlata a fost adaugata cu succes.\n";
                else
                    cout << "\nPlata nu a fost adaugata.\n";
                carduri += p;
            }
            if (option2 == 0)
                continue;
            if (option < 0 || option>3)
            {
                cout << "\nSelectie invalida\n";
            }
        }
        if (option == 2)
        {
            cout << "\nPentru afisarea platilor de tip cash apasati tasta 1\n";
            cout << "Pentru afisarea platilor de tip cec apasati tasta 2\n";
            cout << "Pentru afisarea platilor de tip card apasati tasta 3\n";
            cout << "Pentru a merge inapoi apasati tasta 0 \n";
            cout << "\nIntroduceti numarul actiunii: ";
            cin >> option2;
            cout << '\n';
            if (option2 == 1)
            {
                cout << "Platile facute cash:\n Id.....Suma.....Data\n";
                cash.afis();
            }
            if (option2 == 2)
            {
                cout << "Platile facute prin cec:\n Id.....Suma.....Data.....Nume\n";
                cecuri.afis();
            }
            if (option2 == 3)
            {
                cout << "Platile facute cu cardul:\n Id.....Suma.....Data.....Nume.....Nr.Card\n";
                carduri.afis();
            }
            if (option2 == 0)
                continue;
            if (option2 < 0 || option2>3)
            {
                cout << "\nSelectie invalida\n";
            }
        }
        if (option == 3)
        {
            carduri.afisNume();
        }
        if (option == 4)
        {
            cout << "Cash:" << cash.nrClienti() << '\n';
            cout << "Cec:" << cecuri.nrClienti() << '\n';
            cout << "Card:" << carduri.nrClienti() << '\n';
        }
        if (option == 5)
        {
            cout << "Nr. de plati:";
            int n;
            cin >> n;
            for (int i = 0; i < n; i++)
            {
                cout << "\nPentru o plata de tip cash apasati tasta 1\n";
                cout << "Pentru o plata de tip cec apasati tasta 2\n";
                cout << "Pentru o plata de tip card apasati tasta 3\n";
                cout << "Pentru a merge inapoi apasati tasta 0 \n";
                cout << "\nIntroduceti numarul actiunii: ";
                cin >> option2;
                cout << '\n';
                if (option2 == 1)
                {
                    plata p;
                    cin >> p;
                    if (p.valid())
                        cout << "\nPlata a fost adaugata cu succes.\n";
                    else
                        cout << "\nPlata nu a fost adaugata.\n";
                    cash += p;
                }
                if (option2 == 2)
                {
                    cec p;
                    cin >> p;
                    if (p.valid())
                        cout << "\nPlata a fost adaugata cu succes.\n";
                    else
                        cout << "\nPlata nu a fost adaugata.\n";
                    cecuri += p;
                }
                if (option2 == 3)
                {
                    card p;
                    cin >> p;
                    if (p.valid())
                        cout << "\nPlata a fost adaugata cu succes.\n";
                    else
                        cout << "\nPlata nu a fost adaugata.\n";
                    carduri += p;
                }
                if (option2 == 0)
                    break;
                if (option2 < 0 || option2>3)
                {
                    cout << "\nSelectie invalida\n";
                }
            }
        }
        if (option == 6)
        {
            cout << '\n';
            cout << "Platile facute cash:\n Id.....Suma.....Data\n";
            cash.afis();
            cout << '\n';
            cout << "Platile facute prin cec:\n Id.....Suma.....Data.....Nume\n";
            cecuri.afis();
            cout << '\n';
            cout << "Platile facute cu cardul:\n Id.....Suma.....Data.....Nume.....Nr.Card\n";
            carduri.afis();
        }
        if (option == 0)
        {
            cout << "\nEXIT!\n";
        }
        if (option < 0 || option>7)
        {
            cout << "\nSelectie invalida\n";
        }
        printf("\n");
        if (option > 0 && option < 7)
            system("pause");
    } while (option != 0);
    

    return 0;
}
