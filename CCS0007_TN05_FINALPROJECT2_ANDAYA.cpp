#include <iostream>
#include <chrono>
#include <ctime>
#include <thread>
#include <windows.h>

using namespace std;

int calculateDays(tm eventDate, tm currentDate);
void playAlarmSound();
void Center_Text(const string& text, int totalLength);

int main() {
    int ready;
    string eventTitle, eventFeedback;
    int eventYear, eventMonth, eventDay, eventHour, eventMinute;
    cout << "========================================\n"
         << "            EVENT SCHEDULER             \n"
         << "========================================\n\n"
         << " Are you ready to plan your next event? \n"
         << "              [1] Yes                   \n"
         << "              [2] No                    \n\n"
         << "----------------------------------------\n"
         << "--[";
    cin  >> ready;

    if (ready == 1) {
        system("cls");
        cout << "========================================\n"
             << "            EVENT SCHEDULER             \n"
             << "========================================\n"
             << "          Input Event Details           \n\n"
             << " Title   : "; 
        cin.ignore();
        getline(cin, eventTitle);
        cout << " Date   \n";
        cout << "   Year  : "; 
        cin  >> eventYear;
        cout << "   Month : "; 
        cin  >> eventMonth;
        cout << "   Day   : "; 
        cin  >> eventDay;
        cout << " Time   \n";
        cout << "   Hour  : "; 
        cin  >> eventHour;
        cout << "   Minute: "; 
        cin  >> eventMinute;
        cin.ignore();
        cout << " Feedback: "; 
        getline(cin, eventFeedback);

        if (eventMonth < 1 || eventMonth > 12) {
            cout << "Invalid month! Please enter a value between 1 and 12.\n";
            return 1;
        }

    } else {
        cout << "========================================\n"
            << "            EVENT SCHEDULER             \n"
            << "========================================\n\n"
            << "             Thank you!!!               \n"
            << "         System Shutting Down           \n\n"
            << "----------------------------------------\n";
        }
    
    system("cls");
    cout << "========================================\n";
    Center_Text("EVENT SCHEDULER", 40);
    cout << "========================================\n\n";
    Center_Text("Event Successfully Scheduled", 40);
    Center_Text("Press any keyboard key to track event.", 40);
    cout << "\n----------------------------------------\n\n";
    
    system("pause");
    
    time_t now = time(nullptr);
    tm currentDate = *localtime(&now);

    tm eventDate = {};
    eventDate.tm_year = eventYear - 1900;
    eventDate.tm_mon = eventMonth - 1;
    eventDate.tm_mday = eventDay;
    eventDate.tm_hour = eventHour;
    eventDate.tm_min = eventMinute;
    eventDate.tm_sec = 0;

    mktime(&eventDate);

    int daysToEvent = calculateDays(eventDate, currentDate);


    while (daysToEvent >= 0) {
        system("cls");
        cout << "========================================\n";
        Center_Text("EVENT SCHEDULER", 40);
        cout << "========================================\n";
        Center_Text("EVENT DETAILS", 40);
        cout << "\n";
        Center_Text(eventTitle, 40);

        string eventDate2Str = to_string(eventMonth) + "/" + to_string(eventDay) + "/" + to_string(eventYear);
        Center_Text(eventDate2Str, 40);

        string eventTimeStr = to_string(eventHour) + ":" + (eventMinute < 10 ? "0" : "") + to_string(eventMinute);
        Center_Text(eventTimeStr, 40);

        cout << "\n----------------------------------------\n";
        Center_Text("TRACKER", 40);

        cout << "\n";

        Center_Text("Present Date", 40);
        Center_Text("----------------", 40);
        string currentDateStr = asctime(&currentDate);
        currentDateStr.pop_back(); 
        Center_Text(currentDateStr, 40);

        cout << "\n";

        Center_Text("Scheduled Date", 40);
        Center_Text("----------------", 40);
        string eventDateStr = asctime(&eventDate);
        eventDateStr.pop_back();
        Center_Text(eventDateStr, 40);

        cout << "\n";

        Center_Text("Days Left To Event", 40);
        Center_Text("----------------", 40);
        string daysToEventStr = to_string(daysToEvent) + " days";
        Center_Text(daysToEventStr, 40);
    
        cout << "\n----------------------------------------\n";
    
        this_thread::sleep_for(chrono::seconds(1));
    
        now = time(nullptr);
        currentDate = *localtime(&now);
    
        if (daysToEvent == 0 && currentDate.tm_hour == eventHour && 
            currentDate.tm_min == eventMinute && currentDate.tm_sec == 0) 
        {
            Center_Text("THE TIME HAS COME!", 40);
            cout << "\n";
            Center_Text("-----------------------", 40);
            cout << "\n";
            Center_Text(eventFeedback, 40);
            string eventDateStr = asctime(&eventDate);
            eventDateStr.pop_back(); 
            Center_Text(eventDateStr, 40);
            playAlarmSound(); 
            cout << "\n";
            Center_Text("-----------------------\n", 40);
            Center_Text("MAY YOU HAVE A SUCCESSFUL EVENT!", 40);
            cout << "========================================\n";
            break;
        }
    
        daysToEvent = calculateDays(eventDate, currentDate);
    }

    system("pause");
    return 0;
}


int calculateDays(tm eventDate, tm currentDate) {
    time_t eventTime = mktime(&eventDate);
    time_t currentTime = mktime(&currentDate);
    double difference = difftime(eventTime, currentTime);
    return static_cast<int>(difference / (60 * 60 * 24));
}

void playAlarmSound() {
    Beep(1000, 1000);
}

void Center_Text(const string& text, int totalLength) {
    int textLength = text.length();
    int paddingLeft = (totalLength - textLength) / 2;
    int paddingRight = totalLength - textLength - paddingLeft;

    cout  << string(paddingLeft, ' ') << text << string(paddingRight, ' ') << endl;
}