#include <iostream>
#include <fstream>
#include <string>
#include <sstream> // Added for stringstream
using namespace std;

class hotel {
private:
    struct node {
        int id = 0;
        string checkindate;
        string checkoutdate;
        string ac;
        string name;
        string phone;
        char roomtype = 0;
        node* next = NULL;
        string payment_method;
        string account_number;
    };
    struct foodOrder {
        string customerName;
        string roomNumber;
        string items;
        int totalPrice;
    };
    node* head;
    
    void showFoodMenu() {
        cout << "\n\t\t\t\t--- Food Menu ---\n";
        cout << "\t\t\t\t1. Sandwich (RS 150)\n\t\t\t\t2. Burger (RS 200)\n\t\t\t\t3. Pizza (RS 500)\n\t\t\t\t4. Coffee (RS 100)\n";
    }

    void placeFoodOrder() {
    foodOrder order;
    int choice, quantity;
    order.totalPrice = 0;
    
    // Input Customer Name and Room Number
    cin.ignore();
    cout << "\t\t\t\tEnter Customer Name: ";
    getline(cin, order.customerName);
    cout << "\t\t\t\tEnter Room Number: ";
    getline(cin, order.roomNumber);

    // Validate User and Room
    if (!isValidUserRoom(order.customerName, stoi(order.roomNumber))) {
        cout << "\t\t\t\tInvalid Customer Name or Room Number! Please try again.\n";
        return;
    }

    // Menu and Order Placement
    do {
        showFoodMenu();
        cout << "\t\t\t\tChoose an item (1-4) 0 to finish: ";
        cin >> choice;
        if (choice == 0) break;
        cout << "\t\t\t\tEnter Quantity: ";
        cin >> quantity;
        stringstream ss;
        switch (choice) {
            case 1: 
                ss << quantity;
                order.items += "Sandwich x" + ss.str() + ", "; 
                order.totalPrice += 150 * quantity; 
                break;
            case 2: 
                ss.str(""); ss.clear();
                ss << quantity;
                order.items += "Burger x" + ss.str() + ", "; 
                order.totalPrice += 200 * quantity; 
                break;
            case 3: 
                ss.str(""); ss.clear();
                ss << quantity;
                order.items += "Pizza x" + ss.str() + ", "; 
                order.totalPrice += 500 * quantity; 
                break;
            case 4: 
                ss.str(""); ss.clear();
                ss << quantity;
                order.items += "Coffee x" + ss.str() + ", "; 
                order.totalPrice += 100 * quantity; 
                break;
            default: 
                cout << "\t\t\t\tInvalid choice!\n";
        }
    } while (true);

    // Order Summary
    cout << "\t\t\t\tOrder placed successfully!\n";
    cout << "\t\t\t\tCustomer: " << order.customerName << "\n\t\t\t\tRoom: " << order.roomNumber 
         << "\n\t\t\t\tItems: " << order.items << "\n\t\t\t\tTotal Price: RS " << order.totalPrice << "\n";
}

bool isValidUserRoom(const string& name, int roomNumber) {
    ifstream file("rooms.txt");
    if (!file) {
        cout << "\t\t\t\tError: Could not open room data file!\n";
        return false;
    }

    int id;
    string roomType, ac, customerName, phone, checkIn, checkOut, payment, account;
    while (file >> id >> roomType >> ac >> customerName >> phone >> checkIn >> checkOut >> payment >> account) {
        if (id == roomNumber && customerName == name) {
            return true;
        }
    }

    return false;
}


    bool isValidName(const string& name) {
        for (size_t i = 0; i < name.length(); i++) {
            if (!isalpha(name[i]) && name[i] != ' ') {
                return false;
            }
        }
        return true;
    }

    bool isValidPhone(const string& phone) {
        if (phone.length() != 11) {
            return false;
        }
        for (size_t i = 0; i < phone.length(); i++) {
            if (!isdigit(phone[i])) {
                return false;
            }
        }
        return true;
    }

    bool isValidDate(const string& date) {
        if (date.length() != 10 || date[2] != '/' || date[5] != '/')
            return false;
        string dayStr = date.substr(0, 2);
        string monthStr = date.substr(3, 2);
        string yearStr = date.substr(6, 4);

        int day = stringToInt(dayStr);
        int month = stringToInt(monthStr);
        int year = stringToInt(yearStr);

        if (day < 1 || day > 31 || month < 1 || month > 12 || year < 1000 || year > 9999)
            return false;
        if ((month == 4 || month == 6 || month == 9 || month == 11) && day > 30)
            return false;
        if (month == 2) {
            bool leapYear = (year % 4 == 0 && (year % 100 != 0 || year % 400 == 0));
            if (day > 29 || (day == 29 && !leapYear))
                return false;
        }
        return true;
    }

    int stringToInt(const string& str) {
        stringstream ss(str);
        int num;
        ss >> num;
        return num;
    }

    bool adminLogin() {
        string username, password, fileUsername, filePassword;
        ifstream file("admin_credentials.txt");
        if (!file) {
            cout << "\t\t\t\tError: Admin credentials file not found!\n";
            return false;
        }

        cout << "\t\t\t\tEnter Admin Username: ";
        cin >> username;
        cout << "\t\t\t\tEnter Admin Password: ";
        cin >> password;

        while (file >> fileUsername >> filePassword) {
            if (username == fileUsername && password == filePassword) {
                cout << "\t\t\t\tLogin Successful!\n";
                return true;
            }
        }

        cout << "\t\t\t\tInvalid Username or Password!\n";
        return false;
    }

public:
    hotel() : head(NULL) {}
    void adminMenu();
    void userMenu();
    void insert();
    void update();
    void search();
    void del();
    void show();
    void save();
    void load();
    bool isRoomBooked(int id);
    void start();
};

void hotel::start() {
	load(); // Load data at startup
    //cout << "\n--- Debug: Displaying All Rooms After Loading ---\n";
    //show();
    int role;
    do {
        cout << "\t\t\t\t1. Admin\n\t\t\t\t2. User\n\t\t\t\t3. Exit\n\t\t\t\tSelect role: ";
        cin >> role;
        system("cls");

        switch (role) {
            case 1:
                if (adminLogin())
                    adminMenu();
                break;
            case 2:
                userMenu();
                break;
            case 3:
                cout << "Exiting program...\n";
                return;
            default:
                cout << "\t\t\t\tInvalid role selected! Please try again.\n";
                break;
        }
    } while (true);
}

void hotel::adminMenu() {
    int choice;
    do {
        cout << "\n\t\t\t\t-------------ADMIN MENU-------------------\n";
        cout << "\t\t\t\t1\tAllocate room\n\t\t\t\t2\tSearch room\n\t\t\t\t3\tUpdate room\n";
        cout << "\t\t\t\t4\tEmpty room\n\t\t\t\t5\tShow All Data\n\t\t\t\t6\tBack to Main Menu\n";
        cout << "\t\t\t\tEnter your choice: ";
        cin >> choice;
        system("cls");
        switch (choice) {
            case 1: insert(); break;
            case 2: search(); break;
            case 3: update(); break;
            case 4: del(); break;
            case 5: show(); break;
            case 6: return;
            default: cout << "\t\t\t\tInvalid Choice! Please try again.\n";
        }
    } while (true);
}

void hotel::userMenu() {
    int choice;
    do {
        cout << "\n\t\t\t\t-------------USER MENU-------------------\n";
        cout << "\t\t\t\t1\tView All Rooms\n\t\t\t\t2\tSearch Room\n\t\t\t\t3\tOrder Food\n\t\t\t\t4\tBack to main\n";
        cout << "\t\t\t\tEnter your choice: ";
        cin >> choice;
        system("cls");
        switch (choice) {
            case 1: show(); break;
            case 2: search(); break;
            case 3: placeFoodOrder(); break;
            case 4: cout << "\t\t\t\tExiting User Menu...\n"; return;
            default: cout << "\t\t\t\tInvalid Choice! Please try again.\n";
        }
    } while (true);
}

bool hotel::isRoomBooked(int id) {
    node* ptr = head;
    while (ptr != NULL) {
        if (ptr->id == id) {
            return true;
        }
        ptr = ptr->next;
    }
    return false;
}

void hotel::insert() {
    node* new_node = new node;
    int amount;
    cout << "\n\t\t\t\tEnter Room Number: ";
    cin >> new_node->id;
    if (isRoomBooked(new_node->id)) {
        cout << "\t\t\t\tRoom " << new_node->id << " is already booked!\n";
        delete new_node;
        return;
    }
    cout << "\t\t\t\tChoose Room Type:\n1 - Single (RS 500)\n2 - Double (RS 800)\n3 - Luxury (RS 1200)\n";
    cout << "\t\t\t\tEnter Room Type (S/D/L): ";
    cin >> new_node->roomtype;
    switch (new_node->roomtype) {
        case 'S': amount = 500; break;
        case 'D': amount = 800; break;
        case 'L': amount = 1200; break;
        default: cout << "Invalid room type!\n"; delete new_node; return;
    }
    cout << "\t\t\t\tEnter AC/Non-AC (A/N): ";
    cin >> new_node->ac;

    do {
        cout << "\t\t\t\tEnter customer name (alphabets and spaces only): ";
        cin.ignore();
        getline(cin, new_node->name);
    } while (!isValidName(new_node->name));

    do {
        cout << "\t\t\t\tEnter Phone Number (11 digits): ";
        cin >> new_node->phone;
    } while (!isValidPhone(new_node->phone));

    do {
        cout << "\t\t\t\tEnter check-in date (dd/mm/yyyy): ";
        cin >> new_node->checkindate;
    } while (!isValidDate(new_node->checkindate));

    do {
        cout << "\t\t\t\tEnter check-out date (dd/mm/yyyy): ";
        cin >> new_node->checkoutdate;
    } while (!isValidDate(new_node->checkoutdate));

    cout << "Choose Payment Method: 1. JazzCash 2. EasyPaisa\n";
    int ch; cin >> ch;
    new_node->payment_method = (ch == 1) ? "JazzCash" : (ch == 2) ? "EasyPaisa" : "";
    if (new_node->payment_method.empty()) {
        cout << "\t\t\t\tInvalid payment method!\n"; delete new_node; return;
    }
    cout << "\t\t\t\tEnter Account Number: ";
    cin >> new_node->account_number;
    cout << amount << " has been deducted.\n";

    if (head == NULL) {
        head = new_node;
    } else {
        node* ptr = head;
        while (ptr->next != NULL) {
            ptr = ptr->next;
        }
        ptr->next = new_node;
    }
    cout << "\t\t\t\tNew Room Inserted!\n";
    save();
}

void hotel::search() {
    int t_id;
    cout << "\t\t\t\tEnter Room ID: ";
    cin >> t_id;
    node* ptr = head;
    while (ptr != NULL) {
        if (ptr->id == t_id) {
            cout << "\t\t\t\tRoom Number: " << ptr->id << "\n\t\t\t\tRoom Type: " << ptr->roomtype
                 << "\n\t\t\t\tAC/Non-AC: " << ptr->ac << "\n\t\t\t\tCustomer Name: " << ptr->name
                 << "\n\t\t\t\tPhone: " << ptr->phone << "\n\t\t\t\tFrom: " << ptr->checkindate
                 << "\n\t\t\t\tTo: " << ptr->checkoutdate << "\n\t\t\t\tPayment: " << ptr->payment_method
                 << "\n\t\t\t\tAccount: " << ptr->account_number << "\n";
            return;
        }
        ptr = ptr->next;
    }
    cout << "\t\t\t\tRoom not found!\n";
}

void hotel::update() {
    int t_id;
    cout << "\t\t\t\tEnter Room ID to update: ";
    cin >> t_id;
    node* ptr = head;
    while (ptr != NULL) {
        if (ptr->id == t_id) {
            cout << "\t\t\t\t1. Name 2. Phone 3. Check-in 4. Check-out 5. Payment 6. Account\n";
            int choice; cin >> choice;
            switch (choice) {
                case 1: do { cout << "\t\t\t\tEnter Name: "; cin.ignore(); getline(cin, ptr->name); } while (!isValidName(ptr->name)); break;
                case 2: do { cout << "\t\t\t\tEnter Phone: "; cin >> ptr->phone; } while (!isValidPhone(ptr->phone)); break;
                case 3: cout << "\t\t\t\tEnter Check-in Date (dd/mm/yyyy): "; cin >> ptr->checkindate; while (!isValidDate(ptr->checkindate)); break;
                case 4: cout << "\t\t\t\tEnter Check-out Date (dd/mm/yyyy): "; cin >> ptr->checkoutdate; while (!isValidDate(ptr->checkoutdate)); break;
                case 5: cout << "\t\t\t\tEnter Payment Method: "; cin >> ptr->payment_method; break;
                case 6: cout << "\t\t\t\tEnter Account Number: "; cin >> ptr->account_number; break;
                default: cout << "\t\t\t\tInvalid choice!\n"; break;
            }
            cout << "\t\t\t\tRoom details updated.\n";
            return;
        }
        ptr = ptr->next;
    }
    cout << "\t\t\t\tRoom not found!\n";
}

void hotel::del() {
    int t_id;
    cout << "\t\t\t\tEnter Room ID to delete: ";
    cin >> t_id;
    node* ptr = head;
    node* prev = NULL;
    while (ptr != NULL) {
        if (ptr->id == t_id) {
            if (prev == NULL) {
                head = ptr->next;
            } else {
                prev->next = ptr->next;
            }
            delete ptr;
            cout << "\t\t\t\tRoom deleted!\n";
            save();
			return;
        }
        prev = ptr;
        ptr = ptr->next;
    }
    cout << "\t\t\t\tRoom not found!\n";
}

void hotel::show() {
    node* ptr = head;
    while (ptr != NULL) {
        cout << "\t\t\t\tRoom ID: " << ptr->id << "\n\t\t\t\tRoom Type: " << ptr->roomtype << "\n\t\t\t\tCustomer Name: " << ptr->name
             << "\n\t\t\t\tPhone: " << ptr->phone << "\n\t\t\t\tCheck-in: " << ptr->checkindate << "\n\t\t\t\tCheck-out: " << ptr->checkoutdate
             << "\n\t\t\t\tPayment: " << ptr->payment_method << "\n\t\t\t\tAccount: " << ptr->account_number << "\n\n";
        ptr = ptr->next;
    }
}

void hotel::save() {
    ofstream file("rooms.txt");
    if (!file) {
        cout << "\t\t\t\tError: Could not open file for saving!\n";
        return;
    }

    node* ptr = head;
    while (ptr != NULL) {
        file << ptr->id << " " << ptr->roomtype << " " << ptr->ac << " " << ptr->name << "\n"
             << ptr->phone << " " << ptr->checkindate << " " << ptr->checkoutdate << "\n"
             << ptr->payment_method << "\n" << ptr->account_number << "\n";
        ptr = ptr->next;
    }
    file.close();

    //cout << "Data saved to file successfully. Verify the file manually.\n";
}


void hotel::load() {
    ifstream file("rooms.txt");
    if (!file) {
        cout << "\t\t\t\tError: Could not open file 'rooms.txt'.\n";
        return;
    }

    // Clear the existing linked list
    while (head != NULL) {
        node* temp = head;
        head = head->next;
        delete temp;
    }

    //cout << "Loading data from file...\n";

    while (true) {
        node* new_node = new node; // Allocate memory for a new node
        file >> new_node->id >> new_node->roomtype >> new_node->ac;
        file.ignore(); // Skip whitespace before reading strings
        getline(file, new_node->name);
        file >> new_node->phone >> new_node->checkindate >> new_node->checkoutdate;
        file.ignore(); // Skip whitespace before reading strings
        getline(file, new_node->payment_method);
        file >> new_node->account_number;

        if (file.fail()) {
            delete new_node; // Clean up memory on failure
            break;          // Stop when reading ends or fails
        }

        new_node->next = NULL; // Initialize the next pointer

        // Debugging output for verification
        //cout << "Loaded Room ID: " << new_node->id << ", Name: " << new_node->name << "\n";

        // Insert the new node into the linked list
        if (head == NULL) {
            head = new_node; // First node in the list
        } else {
            node* ptr = head;
            while (ptr->next != NULL) {
                ptr = ptr->next;
            }
            ptr->next = new_node; // Append to the end of the list
        }
    }

    file.close();
    //cout << "Data loaded successfully from file.\n";
}



int main() {
    hotel h;
    h.start();
    return 0;
}

