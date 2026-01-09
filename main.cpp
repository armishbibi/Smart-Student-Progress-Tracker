/**
 Smart Student Progress Tracker (Final Submission)
 CS-110 (Introduction to Computer Programming)
 By:Armish Bibi
    Mahum Akmal
    Zainab Kamal
    BESE-16A
 */

#include <iostream> //for input output handling
#include <fstream>  // For File Handling
#include <string>   // For string operations
#include <iomanip>  // For formatting output 
#include <cmath>    // For math functions
#include <cstdio>   // For remove() function

using namespace std;

// define global constants
const int MAX_LOGS = 100; // study sessions limit
const int MAX_TASKS = 10; // deadlines limit

// Data structure for study sessions
struct Session {
    string subject;
    double hours;
    int date;
};

// Study Schedule Manager using 2D Arrays
class ScheduleManager {
private:
    string timeTable[8][5];  // 8 Time Slots for 5 workdays Days

public:
    ScheduleManager() {
        timeTable[0][0] = "Free Slot ";
        timeTable[0][1] = "FOCP Lab  ";
        timeTable[0][2] = "FOCP Thry ";
        timeTable[0][3] = "FOCP Thry ";
        timeTable[0][4] = "Calculus  ";

        timeTable[1][0] = "AoICT Lab ";
        timeTable[1][1] = "FOCP Lab  ";
        timeTable[1][2] = "FOCP Thry ";
        timeTable[1][3] = "Calculus  ";
        timeTable[1][4] = "AP Lab    ";

        timeTable[2][0] = "AoICT Lab ";
        timeTable[2][1] = "FOCP Lab  ";
        timeTable[2][2] = "Islamiat  ";
        timeTable[2][3] = "AoICT Thry";
        timeTable[2][4] = "AP Lab    ";

        timeTable[3][0] = "AoICT Lab ";
        timeTable[3][1] = "Calculus  ";
        timeTable[3][2] = "Islamiat  ";
        timeTable[3][3] = "AoICT Thry";
        timeTable[3][4] = "AP Lab    ";

        timeTable[4][0] = "Lunch     ";
        timeTable[4][1] = "Lunch     ";
        timeTable[4][2] = "Lunch     ";
        timeTable[4][3] = "Lunch     ";
        timeTable[4][4] = "Lunch     ";

        timeTable[5][0] = "Free Slot ";
        timeTable[5][1] = "Quran-I   ";
        timeTable[5][2] = "ICoP      ";
        timeTable[5][3] = "Free Slot ";
        timeTable[5][4] = "Free Slot ";

        timeTable[6][0] = "AP Thry   ";
        timeTable[6][1] = "Quran-I   ";
        timeTable[6][2] = "ICoP      ";
        timeTable[6][3] = "AP Thry   ";
        timeTable[6][4] = "Free Slot ";

        timeTable[7][0] = "Free Slot ";
        timeTable[7][1] = "Quran-I   ";
        timeTable[7][2] = "Free Slot ";
        timeTable[7][3] = "Free Slot ";
        timeTable[7][4] = "Free Slot ";
    }

    void displaySchedule() {
        string times[8] = {
            "09:00-09:50", "10:00-10:50", "11:00-11:50", "12:00-12:50",
            "13:00-14:00", "14:00-14:50", "15:00-15:50", "16:00-16:50"
        };

        cout << "\nx.x.x.x.x.x.x.x.x.x.x.x.x.x.x.x.x.x.x.x.x.x.x.x.x.x.x.x.x.x.x.x.x.x.x.x.x.x.x.x.x"<<endl;
        cout << "                                       TIMETABLE"<<endl;
        cout << "x.x.x.x.x.x.x.x.x.x.x.x.x.x.x.x.x.x.x.x.x.x.x.x.x.x.x.x.x.x.x.x.x.x.x.x.x.x.x.x.x.x"<<endl;
        cout << "     TIME    |   MONDAY   |   TUESDAY  |  WEDNESDAY |   THURSDAY |    FRIDAY  |"<<endl;
        cout << "__________________________________________________________________________________"<<endl;

        for (int row = 0; row < 8; row++) {
            cout << " " << times[row] << " |";
            for (int col = 0; col < 5; col++) {
                cout << " " << setw(9) << left << timeTable[row][col] << " |";
            }
            cout << endl;
        }

        cout << "______________________________________________________________________________________\n";
    }
};

// Deadline Manager using Arrays
class DeadlineManager {
private:
    string taskNames[MAX_TASKS];
    int dates[MAX_TASKS]; 
    int count;

public:
    DeadlineManager() {
        count = 0;
    }

    void addDeadline() {
        if (count >= MAX_TASKS) {
            cout << "\nTask list full! Delete old tasks first."<<endl;
            return;
        }
        cout << "\n    ADD UPCOMING DEADLINE/EXAM    "<<endl;
        cout << "Event Name : "; 
        cin.ignore();
        getline(cin, taskNames[count]);

        cout << "Due Date (Day 1-31):  "; 
        cin >> dates[count];
        
        count++;
        cout << ">> Successfully Added."<<endl;
    }

    void deleteDeadline() {
        if (count == 0) {
            cout << "\nNo deadlines to delete."<<endl;
            return;
        }
        cout << "\n   CURRENT DEADLINES     "<<endl;
        for (int i = 0; i < count; i++) {
            cout << " [" << i+1 << "] " << taskNames[i] << " (Due: " << dates[i] << ")\n";
        }
        int choice;
        cout << "Enter Number to Delete (0 to Cancel): ";
        cin >> choice;

        if (choice < 1 || choice > count) return; 

        int index = choice - 1;
        for (int i = index; i < count - 1; i++) {
            taskNames[i] = taskNames[i+1];
            dates[i] = dates[i+1];
        }
        count--; 
        cout << ">>> Deadline deleted.\n";
    }

    void sortDeadlines() {
        for (int i = 0; i < count - 1; i++) {
            for (int j = 0; j < count - i - 1; j++) {
                if (dates[j] > dates[j + 1]) {
                    int tempDate = dates[j];
                    dates[j] = dates[j + 1];
                    dates[j + 1] = tempDate;

                    string tempName = taskNames[j];
                    taskNames[j] = taskNames[j + 1];
                    taskNames[j + 1] = tempName;
                }
            }
        }
    }

    void showCountdown() {
        if (count == 0) {
            cout << "\n No upcoming deadlines. Relax! "<<endl;
            return;
        }
        int currentDay;
        cout << "\n    DEADLINE TRACKER     "<<endl;
        cout << "Enter Today's Date (Day 1-31): ";
        cin >> currentDay;

        sortDeadlines(); 

        cout << "\n_________________________________________________________________"<<endl;
        cout << " EVENT NAME             | DUE DATE | DAYS LEFT | STATUS "<<endl;
        cout << "-----------------------------------------------------------------\n";

        for (int i = 0; i < count; i++) {
            int daysLeft = dates[i] - currentDay;

            cout << " " << left << setw(23) << taskNames[i] 
                 << "| " << setw(8) << dates[i] 
                 << "| " << setw(9) << daysLeft << " | ";

            if (daysLeft < 0) cout << "OVERDUE";
            else if (daysLeft == 0) cout << "TODAY!";
            else if (daysLeft <= 3) cout << "URGENT";
            else cout << "Upcoming";

            cout << endl;
        }
        cout << "=================================================================\n";
    }
};

// study Tracker Class
class StudyTracker {
private:
    Session logs[MAX_LOGS]; 
    int count;
    string userFileName;

    int calculateTotalXP(int index) {
        if (index < 0) return 0; 
        int currentXP = (int)(logs[index].hours * 100);
        return currentXP + calculateTotalXP(index - 1); 
    }

public:
    StudyTracker(string username) {
        count = 0;
        userFileName = username + ".txt"; 
        loadData();
    }

    void loadData() {
        ifstream file(userFileName.c_str());
        if (!file) return; 
        
        count = 0;
        while (count < MAX_LOGS && getline(file, logs[count].subject)) {
            if (logs[count].subject.empty()) continue; 
            if (!(file >> logs[count].hours >> logs[count].date)) break;
            file.ignore();
            count++;
        }
        file.close();
    }

    void saveData() {
        ofstream file(userFileName.c_str());
        for (int i = 0; i < count; i++) {
            file << logs[i].subject << endl;
            file << logs[i].hours << " " << logs[i].date << endl;
        }
        file.close();
    }

    void deleteSession() {
        if (count == 0) {
            cout << "\n No study sessions to delete.\n";
            return;
        }
        cout << "\n    YOUR STUDY HISTORY "<<endl;
        for (int i = 0; i < count; i++) {
            cout << " [" << i+1 << "] " << left << setw(15) << logs[i].subject 
                 << " (" << logs[i].hours << "h on Day " << logs[i].date << ")"<<endl;
        }

        int choice;
        cout << "\nEnter Number to Delete (0 to Cancel): ";
        cin >> choice;

        if (choice < 1 || choice > count) return;

        int index = choice - 1;
        for (int i = index; i < count - 1; i++) {
            logs[i] = logs[i+1];
        }
        count--; 
        saveData(); 
        cout << ">>> Session deleted successfully.\n";
    }

    bool deleteData() {
        char confirm;
        cout << "\n>> This will PERMANENTLY DELETE '" << userFileName << "' and LOG YOU OUT."<<endl;
        cout << "Are you sure? (y/n): ";
        cin >> confirm;

        if (confirm == 'y' || confirm == 'Y') {
            count = 0; 
            if (remove(userFileName.c_str()) == 0)
                cout << ">>> Successfully deleted user data file."<<endl;
            else
                cout << ">>> Memory cleared "<<endl;
            return true; 
        }
        cout << ">>> Operation cancelled"<<endl;
        return false;
    }

    void logSession() {
        if (count >= MAX_LOGS) {
            cout << "\n[ERROR] Memory Full! Delete Old Data."<<endl;
            return;
        }
        cout << "\n    LOG NEW SESSION "<<endl;
        cout << "Subject : "; 
        cin.ignore();
        getline(cin, logs[count].subject);

        cout << "Duration (Hours):  "; 
        while (!(cin >> logs[count].hours)) {
            cin.clear(); cin.ignore(100, '\n');
        }

        cout << "Date (Day 1-31):   ";
        while (!(cin >> logs[count].date)) {
            cin.clear(); cin.ignore(100, '\n');
        }

        count++;
        saveData(); 
        cout << ">>> Session Saved to " << userFileName << endl;
    }

    void showAnalytics() {
        if (count == 0) {
            cout << "\n No data found. Please Log a Session first."<<endl;
            return;
        }
        cout << "\n======================================================"<<endl;
        cout << "               STUDY PERFORMANCE GRAPH\n";
        cout << "======================================================"<<endl;
        
        for (int i = 0; i < count; i++) {
            string name = logs[i].subject; 
            if (name.length() > 12) name = name.substr(0, 9) + "...";

            cout << left << setw(13) << name 
                 << " [Day " << setw(2) << logs[i].date << "]: ";

            int bars = (int)(logs[i].hours * 2); 
            cout << "[";
            for (int b = 0; b < bars; b++) cout << "|";
            cout << "] (" << logs[i].hours << "h)"<<endl;
        }
        cout << "_________________________________________________________________"<<endl;
    }

    void predictSyllabus() {
        double totalLectures = 33.0; 
        double completed, speed;
        cout << "\n... SYLLABUS TRACKER ..."<<endl;
        cout << "Lectures Completed:  "; cin >> completed;
        cout << "Avg Speed (Lec/Day): "; cin >> speed;
        if (speed <= 0) {
            cout << "Speed must be positive!"<<endl;
            return;
        }
        double remaining = totalLectures - completed;
        double daysNeeded = remaining / speed;

        cout << ">>> Est. Days to Finish: " << ceil(daysNeeded) << " days" << endl;
        if (daysNeeded > 7) cout << "STATUS: Behind Schedule"<<endl;
        else cout << "STATUS: On Track"<<endl;
    }

    void showProfile() {
        int totalXP = calculateTotalXP(count - 1); 
        int level = (totalXP / 500) + 1;

        cout << "\n======================================================"<<endl;
        cout << "                   STUDENT PROFILE\n";
        cout << "======================================================"<<endl;
        cout << " TOTAL EXPERIENCE (XP): " << totalXP << endl;
        cout << " CURRENT LEVEL:         " << level << endl;

        string rank = (level == 1) ? "Beginner" :
                      (level <= 3) ? "Intermediate" : "Advanced Scholar";
        cout << " ACADEMIC RANK:         " << rank << endl;
        cout << "======================================================\n";
    }
};

// Main Function
int main() {
    bool appRunning = true; 

    while (appRunning) {
        system("cls");

        string username;
        cout << "======================================================"<<endl;
        cout << "           SMART STUDENT PROGRESS TRACKER\n";
        cout << "======================================================"<<endl;
        cout << "Enter User ID (or type 'exit' to close): ";
        cin >> username;

        if (username == "exit" || username == "EXIT") break;

        StudyTracker tracker(username);
        ScheduleManager scheduler;
        DeadlineManager deadlineMgr;

        bool loggedIn = true;
        int choice;

        while (loggedIn) {
            system("cls");

            cout << "======================================================"<<endl
                 << "              DASHBOARD: " << username <<endl
                 << "======================================================"<<endl
                 << " [1] Log Study Session"<<endl
                 << " [2] View Performance Graph"<<endl
                 << " [3] Syllabus Predictor"<<endl
                 << " [4] View Weekly Timetable"<<endl
                 << " [5] My Profile & Rank"<<endl
                 << " [6] Exam & Deadline Tracker"<<endl
                 << " [7] Add New Deadline"<<endl     
                 << " [8] Delete a Deadline"<<endl     
                 << " [9] Delete a Study Session"<<endl
                 << " [10] Delete My Account"<<endl
                 << " [11] Logout"<<endl
                 << " [12] Exit Application"<<endl
                 << "======================================================"<<endl
                 << " SELECT OPTION: ";

            cin >> choice;

            switch (choice) {
                case 1: tracker.logSession(); break;
                case 2: tracker.showAnalytics(); break;
                case 3: tracker.predictSyllabus(); break;
                case 4: scheduler.displaySchedule(); break;
                case 5: tracker.showProfile(); break;
                case 6: deadlineMgr.showCountdown(); break;
                case 7: deadlineMgr.addDeadline(); break;
                case 8: deadlineMgr.deleteDeadline(); break;
                case 9: tracker.deleteSession(); break;
                case 10: if (tracker.deleteData()) 
                            loggedIn = false; break;
                case 11: loggedIn = false; break;
                case 12: loggedIn = false; 
                            appRunning = false; break;
                default: cout << "Invalid Option."<<endl;
            }
            cout << "\nPress Enter to continue...";
            cin.ignore();
            cin.get();
        }
    }
    return 0;
}
//end of code  