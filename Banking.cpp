#include <bits/stdc++.h>
using namespace std;

class account {
    int a;
    string name;
    int d;
    char t;

public:
    void createacc();
    void showacc() const;
    void modify();
    void dep(int);
    void draw(int);
    void report() const;
    int retacc() const;
    int retdep() const;
    char rettype() const;
};

void account::createacc() {
    cout << "\nEnter Account no: ";
    cin >> a;
    cin.ignore();
    cout << "\nName of person: ";
    getline(cin, name);
    cout << "\nEnter type of account (C for current or S for saving): ";
    cin >> t;
    t = toupper(t);
    cout << "\nEnter initial amount (>=1000 for saving and >=2000 for current): ";
    cin >> d;
    cout << "\n\n\nAccount created";
}

void account::showacc() const {
    cout << "\nAccount no: " << a;
    cout << "\nAccount holder: " << name;
    cout << "\nAccount type: " << t;
    cout << "\nBalance amount: " << d;
}

void account::modify() {
    cout << "\nAccount no: " << a;
    cin.ignore();
    cout << "\n\nName of person: ";
    getline(cin, name);
    cout << "\nEnter type of account (C for current or S for saving): ";
    cin >> t;
    t = toupper(t);
    cout << "\nEnter amount: ";
    cin >> d;
}

void account::dep(int x) {
    d += x;
}

void account::draw(int x) {
    d -= x;
}

void account::report() const {
    cout << a << setw(10) << " " << name << setw(10) << " " << t << setw(6) << d << "\n";
}

int account::retacc() const {
    return a;
}

int account::retdep() const {
    return d;
}

char account::rettype() const {
    return t;
}

void writeacc();
void display(int);
void modifyacc(int);
void deleteacc(int);
void displayall();
void depositwithdraw(int, int);
void intro();

int main() {
    char ch;
    int num;
    intro();
    do {
        cout << "\n\n\n\tMAIN MENU";
        cout << "\n\n\t1. NEW ACCOUNT";
        cout << "\n\n\t2. DEPOSIT AMOUNT";
        cout << "\n\n\t3. WITHDRAW AMOUNT";
        cout << "\n\n\t4. BALANCE";
        cout << "\n\n\t5. LIST OF PEOPLE";
        cout << "\n\n\t6. CLOSE ACCOUNT";
        cout << "\n\n\t7. MODIFY ACCOUNT";
        cout << "\n\n\t8. EXIT";
        cout << "\n\n\tChoose (1-8): ";
        cin >> ch;
        switch (ch) {
            case '1':
                writeacc();
                break;
            case '2':
                cout << "\n\n\tEnter account number: ";
                cin >> num;
                depositwithdraw(num, 1);
                break;
            case '3':
                cout << "\n\n\tEnter account number: ";
                cin >> num;
                depositwithdraw(num, 2);
                break;
            case '4':
                cout << "\n\n\tEnter account number: ";
                cin >> num;
                display(num);
                break;
            case '5':
                displayall();
                break;
            case '6':
                cout << "\n\n\tEnter account number: ";
                cin >> num;
                deleteacc(num);
                break;
            case '7':
                cout << "\n\n\tEnter account number: ";
                cin >> num;
                modifyacc(num);
                break;
            case '8':
                cout << "\n\n\tThank you";
                break;
            default:
                cout << "\a";
        }
    } while (ch != '8');
    return 0;
}

void writeacc() {
    account ac;
    ofstream outfile;
    outfile.open("account.dat", ios::binary | ios::app);
    ac.createacc();
    outfile.write(reinterpret_cast<char*>(&ac), sizeof(account));
    outfile.close();
}

void display(int n) {
    account ac;
    int flag = 0;
    ifstream infile;
    infile.open("account.dat", ios::binary);
    if (!infile) {
        cout << "\nCannot open file";
        return;
    }
    cout << "\nBALANCE DETAILS";
    while (infile.read(reinterpret_cast<char*>(&ac), sizeof(account))) {
        if (ac.retacc() == n) {
            ac.showacc();
            flag = 1;
        }
    }
    infile.close();
    if (flag == 0) {
        cout << "\n\nAccount does not exist";
    }
}

void modifyacc(int n) {
    int found = 0;
    account ac;
    fstream file;
    file.open("account.dat", ios::binary | ios::in | ios::out);
    if (!file) {
        cout << "\nFile cannot be opened";
        return;
    }
    while (file.read(reinterpret_cast<char*>(&ac), sizeof(account)) && found == 0) {
        if (ac.retacc() == n) {
            ac.showacc();
            cout << "\n\nEnter new details:" << "\n";
            ac.modify();
            int pos = (-1) * static_cast<int>(sizeof(account));
            file.seekp(pos, ios::cur);
            file.write(reinterpret_cast<char*>(&ac), sizeof(account));
            cout << "\n\n\tRecord updated";
            found = 1;
        }
    }
    file.close();
    if (found == 0) {
        cout << "\n\nRecord not found";
    }
}

void deleteacc(int n) {
    account ac;
    ifstream infile;
    ofstream outfile;
    infile.open("account.dat", ios::binary);
    if (!infile) {
        cout << "\nCannot open file";
        return;
    }
    outfile.open("Temp.dat", ios::binary);
    infile.seekg(0, ios::beg);
    while (infile.read(reinterpret_cast<char*>(&ac), sizeof(account))) {
        if (ac.retacc() != n) {
            outfile.write(reinterpret_cast<char*>(&ac), sizeof(account));
        }
    }
    infile.close();
    outfile.close();
    remove("account.dat");
    rename("Temp.dat", "account.dat");
    cout << "\n\n\tRecord deleted";
}

void displayall() {
    account ac;
    ifstream infile;
    infile.open("account.dat", ios::binary);
    if (!infile) {
        cout << "\nCannot open file";
        return;
    }
    cout << "\n\n\tLIST:";
    cout << "=====================================\n";
    cout << "A/c no.    NAME     Type Balance\n";
    cout << "=====================================\n";
    while (infile.read(reinterpret_cast<char*>(&ac), sizeof(account))) {
        ac.report();
    }
    infile.close();
}

void depositwithdraw(int n, int option) {
    int amt, found = 0;
    account ac;
    fstream file;
    file.open("account.dat", ios::binary | ios::in | ios::out);
    if (!file) {
        cout << "\nCannot open file";
        return;
    }
    while (file.read(reinterpret_cast<char*>(&ac), sizeof(account)) && found == 0) {
        if (ac.retacc() == n) {
            ac.showacc();
            if (option == 1) {
                cout << "\n\n\tTO DEPOSIT AMOUNT";
                cout << "\n\nEnter amount to be deposited: ";
                cin >> amt;
                ac.dep(amt);
            }
            if (option == 2) {
                cout << "\n\n\tTO WITHDRAW AMOUNT";
                cout << "\n\nEnter amount to be withdrawn: ";
                cin >> amt;
                int bal = ac.retdep() - amt;
                if ((bal < 1000 && ac.rettype() == 'S') || (bal < 2000 && ac.rettype() == 'C')) {
                    cout << "\nInsufficient balance";
                } else {
                    ac.draw(amt);
                }
            }
            int pos = (-1) * static_cast<int>(sizeof(ac));
            file.seekp(pos, ios::cur);
            file.write(reinterpret_cast<char*>(&ac), sizeof(account));
            cout << "\n\n\tRecord Updated";
            found = 1;
        }
    }
    file.close();
    if (found == 0) {
        cout << "\n\nRecord not found";
    }
}

void intro() {
    cout << "\n\n\n\tBANK";
    cout << "\n\n\tMANAGEMENT";
    cout << "\n\n\tSYSTEM";
    cout << "\n\n\n\nMADE BY: RAJAT KUMAR";
}
