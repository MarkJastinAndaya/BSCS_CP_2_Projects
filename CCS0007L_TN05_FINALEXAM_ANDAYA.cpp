#include <iostream>
#include <string>
#include <fstream>
#include <iomanip>

using namespace std;

struct weeklyTemperature {
    string location;
    string day[7] = {"Monday", "Tuesday", "Wednesday", "Thursday", "Friday", "Saturday", "Sunday"};
    double temperature[7];
    double minTemp, maxTemp, aveTemp;
    weeklyTemperature* next;
};

void getTemperature(weeklyTemperature*& head);
void getmin_max_aveTemperature(weeklyTemperature& wt);
void displayInputData(weeklyTemperature* head);
void displaySortedData(weeklyTemperature* head);
void saveTemperature(weeklyTemperature* head);
void displayMenu();
void Horline(char symbol = '-', int count = 50);
void Center_Text(const string& text, int totalLength);

int main() {
    weeklyTemperature* head = NULL;

    int choice;
    do {
        cout << "\n\n";
        displayMenu();
        cin >> choice;
        switch (choice) {
            case 1:
                getTemperature(head);
                saveTemperature(head);
                break;
            case 2:
                if (head) {
                    getmin_max_aveTemperature(*head);
                    displayInputData(head);
                } else {
                    cout << "No data available!" << endl;
                }
                break;
            case 3:
                displayInputData(head);
                break;
            case 4:
                if (head) {
                    displaySortedData(head);
                } else {
                    cout << "No data available!" << endl;
                }
                break;
            case 5:
                saveTemperature(head);
                exit(0);
                break;
            default:
                cout << "Invalid choice!" << endl;
        }

        cout << "Press 1 to continue: ";
        cin >> choice;
        
    } while (choice == 1);

    while (head) {
        weeklyTemperature* temp = head;
        head = head->next;
        delete temp;
    }

    return 0;
}

void displayMenu() {
    Horline('=', 52);
    Center_Text("Input Weekly Temperature ", 50);
    Horline('=', 52);

    Center_Text("[1] Input temperature                         ", 50);
    Center_Text("[2] Get minimum, maximum & average temperature", 50);
    Center_Text("[3] Display input data                        ", 50);
    Center_Text("[4] Display sorted data                       ", 50);
    Center_Text("[5] Save data & Exit                          ", 50);

    Horline('=', 52);
    cout << "--[";
}

void getTemperature(weeklyTemperature*& head) {
    weeklyTemperature* newNode = new weeklyTemperature;

    Horline('-', 52);
    Center_Text("Input Temperature Data", 50);
    Horline('-', 52);

    cout << "  Location: ";
    cin.ignore();
    getline(cin, newNode->location);

    if (!newNode->location.empty()) {
        newNode->location[0] = toupper(newNode->location[0]);
    }

    cout << "\n  Weekly temperature in Degree Celsius " << newNode->location << endl;
    string days[] = {"Monday", "Tuesday", "Wednesday", "Thursday",
                     "Friday", "Saturday", "Sunday"};
    for (int i = 0; i < 7; i++) {
        cout << left << "   " << setw(9) << days[i] << ": ";
        cin >> newNode->temperature[i];
    }
    cin.ignore();

    newNode->next = head;
    head = newNode;

    getmin_max_aveTemperature(*newNode);

    Horline('-', 52);
    Center_Text("Temperature data successfully saved", 50);
    Horline('-', 52);
}

void getmin_max_aveTemperature(weeklyTemperature& wt) {
    double sum = 0;
    wt.minTemp = wt.temperature[0];
    wt.maxTemp = wt.temperature[0];

    for (int i = 0; i < 7; i++) {
        sum += wt.temperature[i];
        if (wt.temperature[i] < wt.minTemp) {
            wt.minTemp = wt.temperature[i];
        }
        if (wt.temperature[i] > wt.maxTemp) {
            wt.maxTemp = wt.temperature[i];
        }
    }

    wt.aveTemp = sum / 7;
}

void displayInputData(weeklyTemperature* head) {
    Horline('=', 64);
    Center_Text("Weekly Temperature", 62);
    Horline('=', 64);

    cout << left << setw(15) << "Location"
         << setw(5) << "Mon" << setw(5) << "Tue" << setw(5) << "Wed"
         << setw(5) << "Thu" << setw(5) << "Fri" << setw(5) << "Sat"
         << setw(5) << "Sun" << setw(5) << "Min" << setw(5) << "Max"
         << setw(5) << "Ave" << endl;

    Horline('-', 64);

    weeklyTemperature* current = head;
    while (current != NULL) {
        getmin_max_aveTemperature(*current);

        cout << left << setw(15) << current->location;

        for (int i = 0; i < 7; i++) {
            cout << setw(5) << static_cast<int>(current->temperature[i]);
        }

        cout << setw(5) << static_cast<int>(current->minTemp)
             << setw(5) << static_cast<int>(current->maxTemp)
             << setw(5) << fixed << setprecision(1) << current->aveTemp
             << endl;

        current = current->next;
    }
    Horline('=', 64);
}

void displaySortedData(weeklyTemperature* head) {
    if (!head) {
        cout << "No data available!" << endl;
        return;
    }

    int count = 0;
    weeklyTemperature* temp = head;
    while (temp) {
        count++;
        temp = temp->next;
    }

    for (int i = 0; i < count - 1; i++) {
        weeklyTemperature* current = head;
        weeklyTemperature* nextNode = head->next;

        for (int j = 0; j < count - i - 1; j++) {
            if (current->location > nextNode->location) {
                swap(current->location, nextNode->location);
                for (int k = 0; k < 7; k++) {
                    swap(current->temperature[k], nextNode->temperature[k]);
                }
                swap(current->minTemp, nextNode->minTemp);
                swap(current->maxTemp, nextNode->maxTemp);
                swap(current->aveTemp, nextNode->aveTemp);
            }
            current = nextNode;
            nextNode = nextNode->next;
        }
    }

    Horline('=', 64);
    Center_Text("Sorted Weekly Temperature", 62);
    Horline('=', 64);

    cout << left << setw(15) << "Location"
         << setw(5) << "Mon" << setw(5) << "Tue" << setw(5) << "Wed"
         << setw(5) << "Thu" << setw(5) << "Fri" << setw(5) << "Sat"
         << setw(5) << "Sun" << setw(5) << "Min" << setw(5) << "Max"
         << setw(5) << "Ave" << endl;

    Horline('-', 64);

    weeklyTemperature* current = head;
    while (current != NULL) {
        getmin_max_aveTemperature(*current);

        cout << left << setw(15) << current->location;

        for (int i = 0; i < 7; i++) {
            cout << setw(5) << static_cast<int>(current->temperature[i]);
        }

        cout << setw(5) << static_cast<int>(current->minTemp)
             << setw(5) << static_cast<int>(current->maxTemp)
             << setw(5) << fixed << setprecision(1) << current->aveTemp
             << endl;

        current = current->next;
    }
    Horline('=', 64);
}

void saveTemperature(weeklyTemperature* head) {
    ofstream file("dailyTemperature.txt");
    if (!file) {
        cerr << "Error opening file for writing!" << endl;
        return;
    }

    file << "====================================================\n"
         << "|                Weekly Temperature                |\n"
         << "====================================================\n"
         << left << setw(15) << "Location"
         << setw(5) << "Mon" << setw(5) << "Tue" << setw(5) << "Wed"
         << setw(5) << "Thu" << setw(5) << "Fri" << setw(5) << "Sat"
         << setw(5) << "Sun" << setw(5) << "Min" << setw(5) << "Max"
         << setw(5) << "Ave" << endl;

    weeklyTemperature* current = head;

    while (current != NULL) {
        file << left << setw(15) << current->location;
        for (int i = 0; i < 7; i++) {
            file << setw(5) << static_cast<int>(current->temperature[i]);
        }
        file << setw(5) << static_cast<int>(current->minTemp)
             << setw(5) << static_cast<int>(current->maxTemp)
             << setw(5) << fixed << setprecision(1) << current->aveTemp
             << endl;
        current = current->next;
    }

    file << "====================================================\n";

    file.close();
    cout << "Data successfully saved to dailyTemperature.txt" << endl;
}

void Horline(char symbol, int count) {
    for (int i = 0; i < count; i++) {
        cout << symbol;
    }
    cout << endl;
}

void Center_Text(const string& text, int totalLength) {
    int textLength = text.length();
    int paddingLeft = (totalLength - textLength) / 2;
    int paddingRight = totalLength - textLength - paddingLeft;

    cout << "|" << string(paddingLeft, ' ') << text << string(paddingRight, ' ') << "|" << endl;
}