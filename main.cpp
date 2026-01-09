/**
 Smart Student Progress Tracker (Real-Time Version)
 CS-110 (Introduction to Computer Programming)
 By: Armish Bibi, Mahum Akmal, Zainab Kamal
 BESE-16A
*/

#include <iostream>
#include <fstream>
#include <string>
#include <iomanip>
#include <cmath>
#include <ctime>
#include <cstdio>

using namespace std;

const int MAX_LOGS = 100;
const int MAX_TASKS = 10;

// Structure for study sessions
struct Session {
    string subject;
    double hours;
    time_t timestamp; // store actual datetime
};

// Structure for deadlines
struct Deadline {
    string taskName;
    time_t dueDate;
};

// Study Schedule Manager (same as before)
class ScheduleManager {
private:
    string timeTable[8][5];

public:
    ScheduleManager() {
        string slots[8][5] = {
            {"Free Slot", "FOCP Lab", "FOCP Thry", "FOCP Thry", "Calculus"},
            {"AoICT Lab", "FOCP Lab", "FOCP Thry", "Calculus", "AP Lab"},
            {"AoICT Lab", "FOCP Lab", "Islamiat", "AoICT Thry", "AP Lab"},
            {"AoICT Lab", "Calculus", "Islamiat", "AoICT Thry", "AP Lab"},
            {"Lunch", "Lunch", "Lunch", "Lunch", "Lunch"},
            {"Free Slot", "Quran-I", "ICoP", "Free Slot", "Free Slot"},
            {"AP Thry", "Quran-I", "ICoP", "AP Thry", "Free Slot"},
            {"Free Slot", "Quran-I", "Free Slot", "Free Slot", "Free Slot"}
        };

        for (int i = 0; i < 8; i++) {
            for (int j = 0; j < 5; j++) {
                timeTable[i][j] = slots[i][j];
            }
        }
    }

    void displaySchedule() {
        string times[8] = {
            "09:00-09:50", "10:00-10:50", "11:00-11:50", "12:00-12:50",
            "13:00-14:00", "14:00-14:50", "15:00-15:50", "16:00-16:50"
        };

        cout << "\n==================== TIMETABLE ====================\n";
        cout << "     TIME    |   MONDAY   |  TUESDAY  | WEDNESDAY | THURSDAY |  FRIDAY  |\n";
        cout << "---------------------------------------------------------------\n";

        for (int i = 0; i < 8; i++) {
            cout << " " << times[i] << " |";
            for (int j = 0; j < 5; j++) {
                cout << " " << setw(10) << left << timeTable[i][j] << " |";
            }
            cout << endl;
        }

        cout << "============================================================\n";
    }
};

// Deadline Manager using real-time
class DeadlineManager {
private:
    Deadline tasks[MAX_TASKS];
    int count;

public:
    DeadlineManager() {
        count = 0;
    }

    void addDeadline() {
        if (count >= MAX_TASKS) {
            cout << "Task list full! Delete old tasks first.\n";
            return;
        }

        cout << "\nEvent Name: ";
        cin.ignore();
        getline(cin, tasks[count].taskName);

        int d, m, y;
        cout << "Due Date (dd mm yyyy): ";
        cin >> d >> m >> y;

        tm due = {};
        due.tm_mday = d;
        due.tm_mon = m - 1;
        due.tm_year = y - 1900;
        due.tm_hour = 0;
        due.tm_min = 0;
        due.tm_sec = 0;

        tasks[count].dueDate = mktime(&due);
        count++;

        cout << ">>> Deadline Added!\n";
    }

    void deleteDeadline() {
        if (count == 0) {
            cout << "No deadlines to delete.\n";
            return;
        }

        cout << "\nCurrent Deadlines:\n";
        for (int i = 0; i < count; i++) {
            tm *t = localtime(&tasks[i].dueDate);
            cout << "[" << i + 1 << "] " << tasks[i].taskName 
                 << " (Due: " << t->tm_mday << "/" << t->tm_mon + 1 
                 << "/" << t->tm_year + 1900 << ")\n";
        }

        int choice;
        cout << "Enter number to delete (0 to cancel): ";
        cin >> choice;

        if (choice < 1 || choice > count) {
            return;
        }

        for (int i = choice - 1; i < count - 1; i++) {
            tasks[i] = tasks[i + 1];
        }
        count--;

        cout << ">>> Deadline deleted.\n";
    }

    void showCountdown() {
        if (count == 0) {
            cout << "No upcoming deadlines.\n";
            return;
        }

        time_t now = time(0);

        cout << "\n================= DEADLINE TRACKER =================\n";
        cout << " EVENT NAME           | DUE DATE  | DAYS LEFT | STATUS\n";
        cout << "-----------------------------------------------------\n";

        for (int i = 0; i < count; i++) {
            int daysLeft = (int)difftime(tasks[i].dueDate, now) / (60 * 60 * 24);
            tm *t = localtime(&tasks[i].dueDate);

            cout << setw(20) << left << tasks[i].taskName
                 << "| " << t->tm_mday << "/" << t->tm_mon + 1 
                 << "/" << t->tm_year + 1900
                 << " | " << setw(9) << daysLeft << " | ";

            if (daysLeft < 0) {
                cout << "OVERDUE";
            } else if (daysLeft == 0) {
                cout << "TODAY!";
            } else if (daysLeft <= 3) {
                cout << "URGENT";
            } else {
                cout << "Upcoming";
            }
            cout << endl;
        }

        cout << "====================================================\n";
    }
};

// Study Tracker using real-time timestamps
class StudyTracker {
private:
    Session logs[MAX_LOGS];
    int count;
    string userFileName;

    int calculateTotalXP(int index) {
        if (index < 0) {
            return 0;
        }

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
        if (!file) {
            return;
        }

        count = 0;
        while (count < MAX_LOGS && getline(file, logs[count].subject)) {
            if (logs[count].subject.empty()) {
                continue;
            }

            long long ts;
            if (!(file >> logs[count].hours >> ts)) {
                break;
            }

            logs[count].timestamp = ts;
            file.ignore();
            count++;
        }

        file.close();
    }

    void saveData() {
        ofstream file(userFileName.c_str());
        for (int i = 0; i < count; i++) {
            file << logs[i].subject << endl;
            file << logs[i].hours << " " << logs[i].timestamp << endl;
        }
        file.close();
    }

    void logSession() {
        if (count >= MAX_LOGS) {
            cout << "Memory Full! Delete old data.\n";
            return;
        }

        cout << "\nSubject: ";
        cin.ignore();
        getline(cin, logs[count].subject);

        cout << "Duration (hours): ";
        while (!(cin >> logs[count].hours)) {
            cin.clear();
            cin.ignore(100, '\n');
        }

        logs[count].timestamp = time(0);
        count++;
        saveData();

        cout << ">>> Session logged!\n";
    }

    void showAnalytics() {
        if (count == 0) {
            cout << "No sessions logged.\n";
            return;
        }

        cout << "\n================ STUDY PERFORMANCE =================\n";

        for (int i = 0; i < count; i++) {
            string name = logs[i].subject;
            if (name.length() > 12) {
                name = name.substr(0, 9) + "...";
            }

            tm *t = localtime(&logs[i].timestamp);

            cout << left << setw(13) << name
                 << " [" << t->tm_mday << "/" << t->tm_mon + 1 
                 << "/" << t->tm_year + 1900 << "]: ";

            int bars = (int)(logs[i].hours * 2);
            cout << "[";
            for (int b = 0; b < bars; b++) {
                cout << "|";
            }
            cout << "] (" << logs[i].hours << "h)\n";
        }

        cout << "====================================================\n";
    }

    void predictSyllabus() {
        double totalLectures = 33.0, completed, speed;

        cout << "Lectures completed: ";
        cin >> completed;

        cout << "Avg speed (lec/day): ";
        cin >> speed;

        if (speed <= 0) {
            cout << "Speed must be positive!\n";
            return;
        }

        double daysNeeded = (totalLectures - completed) / speed;

        cout << "Est. days to finish: " << ceil(daysNeeded) << " days\n";
        cout << "Status: " << (daysNeeded > 7 ? "Behind Schedule" : "On Track") << endl;
    }

    void showProfile() {
        int totalXP = calculateTotalXP(count - 1);
        int level = (totalXP / 500) + 1;

        cout << "\n================ STUDENT PROFILE =================\n";
        cout << "TOTAL XP: " << totalXP << "\nCURRENT LEVEL: " << level << endl;

        string rank = (level == 1) ? "Beginner" : (level <= 3) ? "Intermediate" : "Advanced Scholar";
        cout << "ACADEMIC RANK: " << rank << "\n================================================\n";
    }
};

// Main
int main() {
    bool appRunning = true;

    while (appRunning) {
        system("cls");

        string username;
        cout << "================ SMART STUDENT TRACKER ================\n";
        cout << "Enter User ID (or type 'exit'): ";
        cin >> username;

        if (username == "exit" || username == "EXIT") {
            break;
        }

        StudyTracker tracker(username);
        ScheduleManager scheduler;
        DeadlineManager deadlineMgr;

        bool loggedIn = true;

        while (loggedIn) {
            system("cls");

            cout << "================ DASHBOARD: " << username << " ================\n";
            cout << "[1] Log Study Session\n";
            cout << "[2] View Performance\n";
            cout << "[3] Syllabus Predictor\n";
            cout << "[4] Weekly Timetable\n";
            cout << "[5] My Profile\n";
            cout << "[6] Deadline Tracker\n";
            cout << "[7] Add Deadline\n";
            cout << "[8] Delete Deadline\n";
            cout << "[9] Logout\n";
            cout << "[10] Exit App\n";
            cout << "Select Option: ";

            int choice;
            cin >> choice;

            switch (choice) {
                case 1:
                    tracker.logSession();
                    break;
                case 2:
                    tracker.showAnalytics();
                    break;
                case 3:
                    tracker.predictSyllabus();
                    break;
                case 4:
                    scheduler.displaySchedule();
                    break;
                case 5:
                    tracker.showProfile();
                    break;
                case 6:
                    deadlineMgr.showCountdown();
                    break;
                case 7:
                    deadlineMgr.addDeadline();
                    break;
                case 8:
                    deadlineMgr.deleteDeadline();
                    break;
                case 9:
                    loggedIn = false;
                    break;
                case 10:
                    loggedIn = false;
                    appRunning = false;
                    break;
                default:
                    cout << "Invalid Option.\n";
            }

            cout << "Press Enter to continue...";
            cin.ignore();
            cin.get();
        }
    }

    return 0;
}
