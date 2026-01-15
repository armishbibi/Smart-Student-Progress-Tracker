#  Smart Student Progress Tracker (Python GUI)

A desktop application built using **Tkinter Library in Python** that helps students manage their study schedule, track their progress, manage deadlines, their study progress, manage deadlines and more.An upgrade of its C++ console 


## Features

###  Login System
- User login using User ID
- Creates file for new users
- Opens file of existing users

###  Log Study Sessions
- Inputs subject name and study hours
- Also stores date & time
- File handling is used to save data locally

### View Performance
- Displays total study hours per subject
- Visual progress bars 
- Shows study dates for each subject

### Timetable Viewer
- Weekly timetable displayed
- Hard-Coded academic schedule

###  Syllabus Predictor
- Inputs:
  - Total lectures
  - Completed lectures
  - Average speed (lectures/day)
- Predicts remaining days
- Shows progress status (On Track / Behind Schedule)

###  Profile View
- Total study hours
- Total study sessions
- Subjects studied

##  Deadline Management
- Add deadlines with task name, date, and notes(optional)
- View upcoming deadlines
- Delete deadlines easily

---

##  Technologies Used

- Python 
- Tkinter Library
- ttk 
- File Handling
- time and datetime modules

---

##  Project Structure
Smart-Student-Progress-Tracker/
├── main.py
├── login.py
├── dashboard.py

---

## To Run the Project

1. Install **Python 3**
2. Clone the repository:
   git clone https://github.com/armishbibi/Smart-Student-Progress-Tracker.git
3. Switch to the Python GUI branch:
    git checkout PythonGUI
4. Run the project:
    python main.py

