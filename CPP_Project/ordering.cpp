#include <iostream>
#include <string>
#include <vector>
#include <iomanip>
#include <ctime>
using namespace std;

struct Item {
    int id;
    string name;
    double price;
};

struct OrderLine {
    int itemId;
    string itemName;
    int qty;
    double lineTotal;
};

struct Order {
    int userId;
    string userName;
    string timestamp;
    vector<OrderLine> lines;
    double subtotal, tax, total;
};

string nowTime() {
    time_t t = time(nullptr);
    string s = ctime(&t);
    s.pop_back();
    return s;
}

vector<Item> getCatalog() {
    return {
        {1, "Burger", 60},
        {2, "Fries", 25},
        {3, "Soda", 18},
        {4, "Pizza Slice", 75},
        {5, "Ice Cream", 35}
    };
}

void printReceipt(const Order& o) {
    cout << "\n===== RECEIPT =====\n";
    cout << "User " << o.userId << ": " << o.userName << endl;
    cout << "Time: " << o.timestamp << "\n\n";

    cout << left << setw(4) << "ID" << setw(15) << "Item"
         << setw(6) << "Qty" << "Total\n";
    cout << "---------------------------\n";

    for (auto &l : o.lines)
        cout << left << setw(4) << l.itemId
             << setw(15) << l.itemName
             << setw(6) << l.qty
             << l.lineTotal << endl;

    cout << "---------------------------\n";
    cout << "Subtotal: " << o.subtotal << endl;
    cout << "Tax (8%): " << o.tax << endl;
    cout << "Total: " << o.total << endl;
    cout << "===========================\n";
}

int main() {
    vector<Item> catalog = getCatalog();
    int nextUser = 1;

    while (true) {
        cout << "\n=== Ordering System ===\n";
        cout << "1) Start new order\n";
        cout << "2) View history\n";
        cout << "3) Quit\n";
        cout << "Choice: ";

        string choice;
        getline(cin, choice);

        if (choice == "3") break;

        if (choice == "1") {
            Order o;
            o.userId = nextUser++;

            cout << "Customer name: ";
            getline(cin, o.userName);
            o.timestamp = nowTime();

            while (true) {
                cout << "\nMenu:\n";
                for (auto &i : catalog)
                    cout << i.id << ") " << i.name << " - " << i.price << endl;

                cout << "0) Finish\n";
                cout << "Select ID: ";

                string s;
                getline(cin, s);
                int id = stoi(s);

                if (id == 0) break;

                cout << "Qty: ";
                int qty;
                cin >> qty;
                cin.ignore();

                Item it = catalog[id - 1];
                OrderLine l{it.id, it.name, qty, qty * it.price};
                o.lines.push_back(l);
            }

            o.subtotal = 0;
            for (auto &x : o.lines) o.subtotal += x.lineTotal;
            o.tax = o.subtotal * 0.08;
            o.total = o.subtotal + o.tax;

            printReceipt(o);
        }
    }

    return 0;
}
