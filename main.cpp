#include <iostream>
#include <bits/stdc++.h>
#include <typeinfo>
using namespace std;

ifstream f("parole.in");
ofstream gparole("parole.in", std::ios::app);

typedef struct pass
{
    char tip[10];
    char user[50];
    char pp[50];
};

template < class T>
class loginSystem
{
    unordered_map<string, string> users;
    bool logged = false;
    T* meniuu;

public:

    void registerUser (const string username, const string password)
    {
        users[username] = password;
        cout<<"User registered successfully!\n";
    }
    void tryLogin(const string& username, const string& password)
    {
        if(users.find(username) != users.end() && users[username] == password)
        {
            cout<<"Login successful!" <<endl;
            this->logged = true;
            T *MainMenu = MainMenu->getInstance();
            MainMenu->meniuStart();
            return;
        }
        system("CLS");
        cout<<"Invalid username or password. Login failed!\n";
        cout<<"If you want to try again enter 1, else enter anything!\n";
        string c;
        cin>>c;
        if(c == "1")
            login();
        else
            return;

    }

    void login()
    {

        if(this->logged == true)
        {
            cout<<"You are already logged in!\nType anything to continue!\n";
            string x;
            cin>>x;
            T *MainMenu = MainMenu->getInstance();
            MainMenu->meniuStart();
            return;
        }
        system("CLS");
        string user, pass;
        cout<<"Username: ";
        cin>>user;
        cout<<"Password: ";
        cin>>pass;

        tryLogin(user, pass);
    }
    void logout()
    {
        try
        {
            if(this->logged == false) throw runtime_error("You are not logged in...");
            this->logged = false;
            cout<<"Logout succesfull!";
        }
        catch (runtime_error& e)
        {
            cout<<e.what();
        }
        cout<<"\nPress any key to go back.";
        string i;
        cin>>i;
    }
    ~loginSystem() {}
};

class IOinterface
{
public:
    virtual istream& read(istream& in) = 0;
    virtual ostream& write(ostream& out) const = 0;
};

class Ingredients
{
    string name;
    bool alergens;
    int grams;

public:
    Ingredients(string, bool, int);
    Ingredients(const Ingredients& aux);
    Ingredients& operator=(const Ingredients& aux);
    friend istream& operator>>(istream& in, Ingredients& aux);
    friend ostream& operator<<(ostream& out, const Ingredients& aux);

    string getName()
    {
        return this->name;
    }
    int getGrams()
    {
        return this->grams;
    }
    void setGrams(int g)
    {
        this->grams = this->grams + g;
    }
};

Ingredients::Ingredients(string name="anonim", bool alergens=false, int grams=0)
{

    this->name = name;
    this->alergens = alergens;
    this->grams = grams;
}

Ingredients::Ingredients(const Ingredients& aux)
{
    this->name = aux.name;
    this->alergens = aux.alergens;
    this->grams = aux.grams;
}

Ingredients& Ingredients::operator=(const Ingredients& aux)
{

    if(this != &aux)
    {
        this->name = aux.name;
        this->alergens = aux.alergens;
        this->grams = aux.grams;
    }

    return *this;
}

istream& operator>>(istream& in, Ingredients& aux)
{

    cout << "The name of the ingredient: ";
    in >> aux.name;
    cout << "\nDoes it contain alergens: ";
    in >> aux.alergens;
    cout << "\nQuantity: ";
    in >> aux.grams;

    return in;
}

ostream& operator<<(ostream& out, const Ingredients& aux)
{

    out << "Name: " << aux.name << endl;
    out << "Alergens: " << aux.alergens << endl;
    out << "Grams: " << aux.grams << endl;

    return out;
}

class Dish: public IOinterface
{
protected:
    string name;
    vector<Ingredients> ingredientsList;
/// int minutesPrep;
/// int kcal;

public:
    Dish();
    Dish(string, vector<Ingredients>);
    Dish(const Dish&);
    Dish& operator=(const Dish&);

    virtual string nume_fel() const
    {
        string a = typeid(this).name();
        return a;
    }
    virtual string getNume() const
    {
        return this->name;
    }
    virtual Ingredients& operator[](int i)
    {
        return ingredientsList[i];
    }
    virtual int getSize() const
    {
        return ingredientsList.size();
    }
    friend istream &operator >> (istream &in, Dish &d)
    {
        return d.read(in);
    }
    template <typename U>
    friend ostream& operator<<(ostream& out, const U& d)
    {
        return d.write(out);
    }

    istream& read(istream& in)
    {
        int k;
        system("CLS");
        cout << "Name: ";
        in >> this->name;

        if(!this->ingredientsList.empty())
        {
            this->ingredientsList.clear();
        }
        while(true)
        {
            system("CLS");
            cout<< "1 - New ingredient \n0 - Complete ";
            cin >> k;
            system("CLS");
            if(k == 0)
                break;
            else
            {
                this->ingredientsList.push_back(*(new Ingredients()));
                in >> this->ingredientsList.back();
            }
        }
        //cout << "How long does it take to make this dish: ";
        //in >> this->minutesPrep;

        return in;
    }

    ostream& write(ostream& out) const
    {
        out << "Name: " << this->name << endl;
        //out << "Preparation in minutes: " << this->minutesPrep << endl;
        out<<"Ingredients: \n";
        for(int i=0; i<this->ingredientsList.size(); i++)
            out << "\n * " << this->ingredientsList[i];

        return out;
    }
    virtual ~Dish() {}
};
Dish::Dish()
{

    this->name = "anonim";
    this->ingredientsList = {};
    //this->minutesPrep = minutesPrep;
}
Dish::Dish(string name="anonim", vector<Ingredients> ingredientsList = {})
{

    this->name = name;
    this->ingredientsList = ingredientsList;
    //this->minutesPrep = minutesPrep;
}

Dish::Dish(const Dish& aux)
{
    this->name = aux.name;
    this->ingredientsList = aux.ingredientsList;
    //this->minutesPrep = aux.minutesPrep;
}

Dish& Dish::operator=(const Dish& aux)
{

    if(this != &aux)
    {
        this->name = aux.name;
        this->ingredientsList = aux.ingredientsList;
        //this->minutesPrep = aux.minutesPrep;
    }

    return *this;
}

class Meal:virtual public Dish
{
protected:
    int protein_grams;

public:
    Meal(string name="anonim", vector<Ingredients> ingredientsList = {}, int protein_grams = 0)
        :Dish(name, ingredientsList)
    {
        this->protein_grams = protein_grams;
    }
    virtual string nume_fel()
    {
        string a = typeid(this).name();
        return a;
    }
    Meal(const Meal&);
    Meal& operator=(const Meal&);

    istream& read(istream& in)
    {
        this->Dish::read(in);
        cout << "Protein grams? ";
        in >> this->protein_grams;
        return in;
    }

    ostream& write(ostream& os) const
    {
        this->Dish::write(os);
        cout << "Protein grams: " << this->protein_grams << endl;
        return os;
    }
    friend istream &operator >> (istream &in, Meal &m)
    {
        return m.read(in);
    }

    friend ostream& operator<<(ostream& out, const Meal& m)
    {
        return m.write(out);
    }
    virtual ~Meal() {}
};

Meal::Meal(const Meal& obj): Dish(obj)
{
    this->protein_grams = protein_grams;
}
Meal& Meal::operator =(const Meal& obj)
{
    if(this != &obj)
    {
        Dish::operator=(obj);
        this->protein_grams = obj.protein_grams;
    }
    return *this;
}
class Desert:virtual public Dish
{
private:
    int sugar_grams;

public:
    Desert(string name="anonim", vector<Ingredients> ingredientsList = {}, int sugar_grams = 0)
        :Dish(name, ingredientsList)
    {
        this->sugar_grams = sugar_grams;
    }
    virtual string nume_fel()
    {
        string a = typeid(this).name();
        return a;
    }
    Desert(const Desert&);
    Desert& operator=(const Desert&);

    istream& read(istream& in)
    {
        this->Dish::read(in);
        cout << "Sugar grams? ";
        in >> this->sugar_grams;
        return in;
    }

    ostream& write(ostream& os) const
    {
        this->Dish::write(os);
        cout << "Sugar grams: " << this->sugar_grams << endl;
        return os;
    }
    friend istream &operator >> (istream &in, Desert &d)
    {
        return d.read(in);
    }

    friend ostream& operator<<(ostream& out, const Desert& d)
    {
        return d.write(out);
    }
    virtual ~Desert() {}
};

Desert::Desert(const Desert& obj): Dish(obj)
{
    this->sugar_grams = sugar_grams;
}
Desert& Desert::operator =(const Desert& obj)
{
    if(this != &obj)
    {
        Dish::operator=(obj);
        this->sugar_grams = obj.sugar_grams;
    }
    return *this;
}

class Combo: public Meal, public Desert
{
    bool WJET;
public:

    Combo(string name="anonim", vector<Ingredients> ingredientsList = {}, int protein_grams = 0, int surgar_grams = 0, bool WJET = 0): Dish(name, ingredientsList), Meal(name,
                ingredientsList, protein_grams)//, Desert(name, ingredientsList, sugar_grams)
    {
        this->WJET = WJET;///would Jamila eat this
    }

    Combo(const Combo& obj): Dish(obj), Meal(obj), Desert(obj)
    {
        this->WJET = obj.WJET;
    }
    virtual string nume_fel()
    {
        string a = typeid(this).name();
        return a;
    }
    bool wouldJET()
    {
        return this->WJET;
    }
    Combo& operator =(const Combo& obj)
    {
        if(this != &obj)
        {
            Meal::operator=(obj);
            Desert::operator=(obj);
            this->WJET = obj.WJET;
        }
        return *this;
    }

    istream& read(istream& in)
    {
        Dish::read(in);
        cout << "Protein grams: \n";
        in >> this->protein_grams;
        cout << "Sugar grams: \n";
        // in >> this->sugar_grams;
        cout << "Would Jamila eat this? ";
        in >> this->WJET;
        system("CLS");
        return in;
    }
    ostream& write(ostream& os) const
    {
        Dish::write(os);
        os << "\nProtein grams: " << this->protein_grams << endl;
        //os << "Sugar grams: " << this->sugar_grams << endl;
        os << "Would Jamila eat this?: " << this->WJET << endl;
        return os;
    }
    virtual ~Combo() {}
};

//class

class RecipeBookJamila
{
    Dish* dish;
public:

    Dish getDish()
    {
        return *this->dish;
    }
    Dish* getDish2()
    {
        return this->dish;
    }
    friend istream& operator >>(istream& in, RecipeBookJamila& obj)
    {
        cout << "1. Meal\n";
        cout << "2. Desert\n";
        cout << "3. Combo\n";
        int k;
        cin >> k;
        if(k == 1)
            obj.dish = new Meal();
        if(k == 2)
            obj.dish = new Desert();
        if(k == 3)
            obj.dish = new Combo();
        in >> *obj.dish;
        return in;
    }

    friend ostream& operator<<(ostream& os, const RecipeBookJamila& obj)
    {
        os << obj.dish->nume_fel() <<"\n" << *obj.dish << endl;
        return os;
    }


};

class Kitchen
{
    vector<RecipeBookJamila> recipes;
    vector<Ingredients> fridge;
    set<string> wishlist;
public:
    void addRecipe();
    void showRecipes();
    void whatIsInMyFridge();
    void newStuffInMyFridge();
    void jamilaHelp();
    void addOnWishlist();
    void seeWishlist();
    void whatOnPage();
    void hasMushroom();
    void showRecipesCombos();
};

void Kitchen::addOnWishlist()
{
    string element, comandaq;
    while(true)
    {
        system("CLS");
        cout<<"What do you want to add on the wishlist? ";
        cin>>element;
        try
        {
            for(int i = 0; i < fridge.size(); i++)
                if(fridge[i].getName() == element)
                    throw invalid_argument("You have that in your fridge!");
            wishlist.insert(element);
        }
        catch(invalid_argument& e)
        {
            cout<<e.what();
        }
        cout<<"\nDo you want to get something else? If yes press 1, else press any key! ";
        cin>>comandaq;
        if (comandaq != "1")
            break;
    }

}
Kitchen K;
void Kitchen::seeWishlist()
{
    for(set<string>::iterator iter = wishlist.begin(); iter != wishlist.end(); iter++)
        cout<<*iter<<endl;
    string i;
    cout<<"Press any key to go back! ";
    cin>>i;
}

void Kitchen::addRecipe()
{
    RecipeBookJamila R;
    cin>>R;
    recipes.push_back(R);
}
list<string> antiCiuperci;


bool contineCiuperci(Dish obj)
{
    for(int i = 0; i < obj.getSize(); i++)
    {
        string test= obj[i].getName();
        if(test == "Ciuperci")
            return 0;
    }

    return 1;

}

void Kitchen::hasMushroom()
{
    system("CLS");

    antiCiuperci.clear();
    for(int i = 0; i < K.recipes.size(); i++)
    {
        if(contineCiuperci(recipes[i].getDish()))
        {
            antiCiuperci.push_back(recipes[i].getDish().getNume());
        }
    }

    if(antiCiuperci.size() == 0)
    {
        cout<<"Nu ai ce sa faci fara ciuperci.\n";
        string i;
        cout<<"Press any key to go back!";
        cin>>i;
        system("CLS");
        return;
    }
    list<string>::iterator it;
    for(it = antiCiuperci.begin(); it != antiCiuperci.end(); ++it)
        cout<<*it<<endl;
    string i;
    cout<<"Press any key to go back!";
    cin>>i;
    system("CLS");

}


void Kitchen::whatOnPage()
{
    system("CLS");
    int n;
    cout<<"What is the number of the page of the dish recipe you want to see? ";
    cin>>n;
    try
    {
        if(n>=recipes.size()) throw range_error("You do not even have this many pages in your Jamila Cooking Book!\n");
    }
    catch(range_error& e)
    {
        cout<<e.what();
        string i;
        cout<<"Press 1 to try again or any key to go back!\n";
        cin>>i;
        if(i != "1") return;
        if(i == "1")
        {
            K.whatOnPage();
            return;
        };
    }
    cout<<recipes[n];
    string i;
    cout<<"Press any key to go back!\n";
    cin>>i;
    system("CLS");

}

void Kitchen::newStuffInMyFridge()
{
    Ingredients I;
    cin>>I;
    for(int i = 0; i < fridge.size(); i++)
        if(fridge[i].getName() == I.getName())
        {
            fridge[i].setGrams(I.getGrams());
            return;
        }

    fridge.push_back(I);
    system("CLS");
}

void Kitchen::whatIsInMyFridge()
{
    if(fridge.size() == 0)
    {
        int i;
        cout<<"Your fridge is empty :(\nPress 0 to go back!";
        cin>>i;
        system("CLS");
    }

    for(int i = 0; i < fridge.size(); i++)
        cout << fridge[i] << '\n';
    int i;
    cout<<"Press 0 to go back!";
    cin>>i;
    system("CLS");
}

void Kitchen::showRecipes()
{
    if(recipes.size() == 0)
    {
        int i;
        cout<<"Your Jamila Cooking Book is empty right now :(\nPress 0 to go back!";
        cin>>i;
        system("CLS");
    }
    for(int i = 0; i < recipes.size(); i++)
        cout << recipes[i] << '\n';
    int i;
    cout<<"Press 0 to go back!";
    cin>>i;
    system("CLS");
}

void Kitchen::showRecipesCombos()
{
    if(recipes.size() == 0)
    {
        int i;
        cout<<"Your Jamila Cooking Book is empty right now :(\nPress 0 to go back!";
        cin>>i;
        system("CLS");
    }
    for(int i = 0; i < recipes.size(); i++)///sa incerc cu &e
        ///cout << recipes[i] << '\n';
        try
        {
            Combo* obj2;
            obj2 = dynamic_cast<Combo*>(recipes[i].getDish2());
            if(obj2)
            {
                obj2->wouldJET();
            }
            else
            {
                throw bad_cast();
            }
            ///throw runtime_error("a");
            cout << recipes[i] << '\n';
        }
        catch(bad_cast& e)
        {
            cout<<"Page "<<i<<" is not a combo :(\n\n";
        }

    string i;
    cout<<"Press any key to go back!";
    cin>>i;
    system("CLS");

}

void Kitchen::jamilaHelp()
{
    int ok3 = 0;
    for(int i = 0; i < recipes.size(); i++)///fiecare reteta
    {
        int ok2 = 1;
        for(int j = 0; j < recipes[i].getDish().getSize(); j++)///fiecare ingredient din reteta
        {
            int ok = 0;
            for(int p = 0; p < fridge.size(); p++)///vad ce am eu in frigider
                if(recipes[i].getDish()[j].getName() == fridge[p].getName())
                {
                    if(recipes[i].getDish()[j].getGrams() <= fridge[p].getGrams())
                    {
                        ok = 1;
                        break;
                    }
                }
            if(ok == 0)
            {
                ok2 = 0;
                break;
            }

        }
        if(ok2 == 1)
        {
            cout<<recipes[i];
            cout<<"------------------\n";
            ok3 = 1;
        }
    }
    if(ok3 == 0)
    {
        int i;
        cout<<"Nu ai ce mancare sa faci, esti sarac la frigider :(\nPress 0 to go back!";
        cin>>i;
        system("CLS");
    }
    if(ok3 == 1)
    {
        int i;
        cout<<"\nAcestea sunt retele recomandate de Jamila, pofta buna :)\nPress 0 to go back!";
        cin>>i;
        system("CLS");
    }


}



class meniu
{
private:
    static meniu *obiect;
    string data;

    meniu() = default;
    meniu(meniu&) = delete;
    meniu& operator=(meniu&) = delete;

public:
    static meniu* getInstance()
    {
        if(!obiect)
            obiect=new meniu();
        return obiect;
    }
    string getData()
    {
        return this->data;
    }
    void setData(string a)
    {
        this->data=a;
    }

    void meniuStart()
    {
        int k=1;
        int i=0;
        while(k==1)
        {
            {
                system("CLS");
                cout << "1. What is in my fridge?\n";
                cout << "2. Jamila, what can my mom cook for me?\n";
                cout << "3. I want some new stuff!\n";
                cout << "4. Stop\n";
                int c;
                cin >> c;
                system("CLS");
                switch(c)
                {
                case 1:
                {
                    K.whatIsInMyFridge();
                    break;
                }

                case 2:
                {
                    K.jamilaHelp();
                    break;
                }
                case 3:
                {
                    K.addOnWishlist();
                    break;
                }
                default:
                {
                    k = 0;
                    break;
                }
                }
            }
        }

    }

};



class meniuAdmin
{
private:
    static meniuAdmin *obiect;
    string data;

    meniuAdmin() = default;
    meniuAdmin(meniuAdmin&) = delete;
    meniuAdmin& operator=(meniuAdmin&) = delete;
public:
    static meniuAdmin* getInstance()
    {
        if(!obiect)
            obiect=new meniuAdmin();
        return obiect;
    }
    string getData()
    {
        return this->data;
    }
    void setData(string a)
    {
        this->data=a;
    }
    void meniuStart()
    {


        int k=1;
        int i=0;
        while(k==1)
        {
            {
                system("CLS");
                cout << "1. New recipe\n";
                cout << "2. Show my recipes\n";
                cout << "3. What is in my fridge?\n";
                cout << "4. I went shopping\n";
                cout << "5. Jamila, what can i cook?\n";
                cout << "6. Let's add on the wishlist!\n";
                cout << "7. What is on the wishlist?\n";
                cout << "8. What is on page X in my Jamila Cooking Book\n";
                cout << "9. Recipes without mushrooms? (My kid does not like mushrooms)\n";
                cout << "10. Recipes that are a combo? (I am very hungry)\n";
                cout << "11. Stop\n";
                int c;
                cin >> c;
                system("CLS");
                switch(c)
                {
                case 1:
                {
                    K.addRecipe();
                    break;
                }

                case 2:
                {
                    K.showRecipes();
                    break;
                }

                case 3:
                {
                    K.whatIsInMyFridge();
                    break;
                }

                case 4:
                {
                    K.newStuffInMyFridge();
                    break;
                }
                case 5:
                {
                    K.jamilaHelp();
                    break;
                }
                case 6:
                {
                    K.addOnWishlist();
                    break;
                }
                case 7:
                {
                    K.seeWishlist();
                    break;
                }
                case 8:
                {
                    K.whatOnPage();
                    break;
                }
                case 9:
                {
                    K.hasMushroom();
                    break;
                }
                case 10:
                {
                    K.showRecipesCombos();
                    break;
                }
                default:
                {
                    k = 0;
                    break;
                }
                }
            }
        }

    }

};

meniu *MainMenu = MainMenu->getInstance();
meniuAdmin *MainMenuAdmin = MainMenuAdmin->getInstance();
loginSystem <meniu>sesiune;
loginSystem <meniuAdmin>sesiuneAdmin;

void citire_parole()
{
    pass parol;

    fstream file;
    char file_name[] = "parole.bin";
    file.open(file_name, ios::binary | ios::in);

    try
    {
        if(strcmp(file_name, "parole.bin") !=0)
        {
            throw std::invalid_argument("Wrong file to read. Please call the operator!");
        }
        while(file>>parol.tip>>parol.user>>parol.pp)
        {
            //cout<<parol.tip<<' '<<parol.user<<' '<<parol.pp<<endl;
            if(strcmp(parol.tip,"Mama") == 0)
                sesiuneAdmin.registerUser(parol.user, parol.pp);
            else
                sesiune.registerUser(parol.user, parol.pp);
        }
    }
    catch(std::invalid_argument& e)
    {
        cout<<e.what();
        cout<<"\nPress any key to go back.";
        string x;
        cin>>x;
    }

    file.close();



//    string usr, pas, acc_type;
//    while(f>>acc_type>>usr>>pas)
//    {
//        if(acc_type == "Copil")
//            sesiune.registerUser(usr, pas);
//        else
//            sesiuneAdmin.registerUser(usr, pas);
//    }
}

template<class T>
void parolaNoua()
{
    string tip;
    if(strcmp(typeid(T).name(), "5meniu") == 0)
        tip = "Copil";
    else tip = "Mama";
    ///cout <<endl<<typeid(T).name()<<endl;
    string usr, pss;
    cout<<"New username: ";
    cin>>usr;
    cout<<"\nNew password: ";
    cin>>pss;
    try
    {
        if(usr.length()>49 || pss.length()>49) throw length_error("Your username or password is too long! The maximum characters allowed is 50!\n");
        string cop = "Copil";
        if(tip == "Copil")
            sesiune.registerUser(usr, pss);
        else
            sesiuneAdmin.registerUser(usr, pss);
        system("CLS");
        cout<<"New "<<tip<<" account created!";

        fstream file;
        char file_name[] = "parole.bin";

        try
        {
            if(strcmp(file_name, "parole.bin") !=0)
            {
                throw std::invalid_argument("\nPassword is saved temporarily, only used this session.\nCall the operator for help!");
            }
            file.open(file_name, ios::binary | ios::app);
            file<<tip<<" "<<usr<<" "<<pss<<"\n";
        }
        catch(std::invalid_argument& e)
        {
            cout<<e.what();
        }

        cout<<"\nPress anything to continue.";
        file.close();

        //gparole << "Copil "<<usr<<' '<<pss;

        string x;
        cin>>x;
        return;
    }
    catch(length_error& e)
    {
        cout<<e.what();
        cout<<"Press any key to go back. ";
        string x;
        cin>>x;
        return;

    }
}


meniu* meniu::obiect=0;
meniuAdmin* meniuAdmin::obiect=0;

int main()
{

    citire_parole();

    int k=1;
    while(k==1)
    {
        {
            system("CLS");
            cout << "Welcome to `CeAvemDeMancare?` ~ Beta version\n";
            cout << "1. Login as Copil\n";
            cout << "2. Login as Mama\n";
            cout << "3. Logout Copil\n";
            cout << "4. Logout Mama\n";
            cout << "5. New Copil account\n";
            cout << "6. New Mama account\n";
            cout << "7. Stop\n";
            int c;
            cin >> c;
            system("CLS");
            switch(c)
            {
            case 1:
            {
                sesiune.login();
                break;
            }

            case 2:
            {
                sesiuneAdmin.login();
                break;
            }

            case 3:
            {
                sesiune.logout();
                break;
            }

            case 4:
            {
                sesiuneAdmin.logout();
                break;
            }
            case 6:
            {
                parolaNoua<meniuAdmin>();
                break;
            }
            case 5:
            {
                parolaNoua<meniu>();
                break;


            }
            default:
            {
                k = 0;
                break;
            }
            }
        }
    }




    //sesiune.login();

//    meniu *MainMenu = MainMenu->getInstance();
//    MainMenu->meniuStart();
    return 0;
}
///TODO:
///1 3 PuiGratarSiTartaLamaie 1 pui 0 150 1 piper 0 10 1 lamaie 0 50 1 biscuiti 0 350 1 lapte_condensat 1 200 0 30 40 1 4 pui 0 150 4 lamaie 0 80 4 biscuiti 0 350 4 lapte_condensat 0 250 4 piper 0 9

