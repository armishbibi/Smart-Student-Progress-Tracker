import tkinter as tk
from tkinter import messagebox
from tkinter import simpledialog
from tkinter import ttk
from datetime import datetime
import time
import os 

def open_dashboard(username):
    #for creation of main window 
    root = tk.Tk() #setting variable for the main window
    root.title(f"Dashboard:{username} ") #the title that appears at the top tab of the window
    root.geometry("700x700") #the dimensions of the main window, can be variable

    #adding label
    label = tk.Label(root, text= f"Smart Student Progress Tracker\nDashboard: {username}", font= ("Arial", 16, "bold"))
    label.pack(pady=20)

    #button functions
    def logBtn():
        #asking user for subject
        subject = tk.simpledialog.askstring("Log Study Session", "Enter Subject:")
        if not subject: 
            messagebox.showerror("Error", "Subject cant be empty")
            return
        
        #asking user for hours
        hours_s=(tk.simpledialog.askstring("Log Study Session"," Enter Number of Hours: "))

        if hours_s is None:
            return #user pressed cancel

        try:
            hours = float(hours_s)
            if hours <= 0:
                raise ValueError
        except:
            messagebox.showerror("Error", "Enter Valid Number of Hours")
            return 
        #adding filepath
        fileName = f"{username}.txt"

        #adding data to file
        with open(fileName, "a") as f:
            f.write(f"{subject}\n{hours} {int (time.time())}\n")
        
        #message after successfully adding data
        messagebox.showinfo("Successful",f"logged {hours} hours for {subject} ")
    
    def viewBtn():
        file_name = f"{username}.txt"
        if not os.path.exists(file_name):
            messagebox.showinfo("Info", "No study data found.")
            return

        subject_hours = {}      # total hours per subject
        subject_dates = {}      # list of dates per subject

        with open(file_name, "r") as f:
            lines = f.readlines()

        # Read file and sum hours per subject
        i = 0
        while i < len(lines):
            subject = lines[i].strip()
            try:
                hours_s, timestamp_s = lines[i + 1].split()
                hours = float(hours_s)
                timestamp = int(timestamp_s)
                date_str = time.strftime("%d-%m-%Y ", time.localtime(timestamp))
            except:
                hours = 0
                date_str = "Unknown"

            subject_hours[subject] = subject_hours.get(subject, 0) + hours
            if subject not in subject_dates:
                subject_dates[subject] = []
            subject_dates[subject].append(date_str)

            i += 2

        if not subject_hours:
            messagebox.showinfo("Info", "No study sessions logged.")
            return

        # New window
        win = tk.Toplevel(root)
        win.title("Study Performance")
        win.geometry("600x450")

        tk.Label(win, text="Study Performance", font=("Arial", 16, "bold")).pack(pady=10)

        # Max hours for scaling bars
        max_hours = 24
        #max_hours = max(subject_hours.values())

        for subject, hours in subject_hours.items():
            frame = tk.Frame(win)
            frame.pack(fill="x", padx=20, pady=5)

            # Subject name
            tk.Label(frame, text=subject, width=12, anchor="w", font=("Arial", 11)).pack(side="left")

            # Progress bar
            bar = ttk.Progressbar(frame, length=300, maximum=max_hours, value=hours)
            bar.pack(side="left", padx=10)

            # Total hours
            tk.Label(frame, text=f"{hours:.1f}h", width=6).pack(side="left")

            # Dates
            dates_str = ", ".join(subject_dates[subject])
            tk.Label(frame, text=dates_str, anchor="w").pack(side="left", padx=5)
    def timeBtn():
        timetable_window=tk.Toplevel(root)
        timetable_window.title("TimeTable") 
        timetable_window.geometry("1000x450")
        tk.Label(
            timetable_window,
            text = "Weekly TimeTable",
            font = ("Arial", 16, "bold")
            ).grid(row = 0, column = 0, columnspan = 6, pady=10)
        days = ["Time", "Monday", "Tuesday", "Wednesday", "Thursday", "Friday"]
        times = [
            "09:00-09:50", "10:00-10:50", "11:00-11:50", "12:00-12:50",
            "13:00-14:00", "14:00-14:50", "15:00-15:50", "16:00-16:50"]
        timetable = [
        ["Free Slot", "FOCP Lab", "FOCP Thry", "FOCP Thry", "Calculus"],
        ["AoICT Lab", "FOCP Lab", "FOCP Thry", "Calculus", "AP Lab"],
        ["AoICT Lab", "FOCP Lab", "Islamiat", "AoICT Thry", "AP Lab"],
        ["AoICT Lab", "Calculus", "Islamiat", "AoICT Thry", "AP Lab"],
        ["Lunch", "Lunch", "Lunch", "Lunch", "Lunch"],
        ["Free Slot", "Quran-I", "ICoP", "Free Slot", "Free Slot"],
        ["AP Thry", "Quran-I", "ICoP", "AP Thry", "Free Slot"],
        ["Free Slot", "Quran-I", "Free Slot", "Free Slot", "Free Slot"]
        ]
        for col, day in enumerate(days):
            tk.Label(
                timetable_window,
                text = day,
                font = ("Arial", 12, "bold"),
                borderwidth=1,
                relief= "solid",
                width = 15
            ).grid(row = 1, column = col, sticky="nsew")
        for row in range (len(times)):
            tk.Label(
                timetable_window,
                text = times[row],
                font = ("Arial", 12, "bold"),
                borderwidth=1,
                relief= "solid",
                width = 15
            ).grid(row = row+2, column= 0, sticky="nsew")
        row = 0
        for col in range(5):
            for row in range (8):
                tk.Label(
                    timetable_window,
                    text = timetable[row][col],
                    borderwidth=1,
                    relief= "solid",
                    width = 15
                ).grid(row = row+2, column= col + 1, sticky="nsew")
    
    def predictBtn():
        win= tk.Toplevel(root)
        win.title("Syllabus tracker")
        win.geometry("400x350")

        tk.Label(win, text = "Syllabus Predictor", font = ("Arial", 16, "bold")).pack(pady=10)

        tk.Label(win, text = "Enter Total Lectures : ", font = ("Arial", 12) ).pack()
        total_lectures = tk.Entry(win, font = ("Arial", 12))
        total_lectures.pack(pady = 5)

        tk.Label(win, text = "Enter Completed Lectures : ", font = ("Arial", 12) ).pack()
        completed_lectures = tk.Entry(win, font = ("Arial", 12))
        completed_lectures.pack(pady = 5)
        
        tk.Label(win, text = "Enter Avg Speed(lec/day) : ", font = ("Arial", 12) ).pack()
        speed_lectures = tk.Entry(win, font = ("Arial", 12))
        speed_lectures.pack(pady = 5)

        result_label = tk.Label(win, text="", font=("Arial", 12))
        result_label.pack(pady=15)


        def calculate():
            try:
                total = int(total_lectures.get())
                completed = int( completed_lectures.get())
                speed = float (speed_lectures.get())
                if total <= 0 or completed < 0 or speed <= 0:
                    raise ValueError
                if completed > total:
                    messagebox.showerror("Error", "Completed lectures cant\n be more than total lectures")
                days_needed = (total - completed)/speed
                if days_needed >= 7:
                    status = "On Track"
                else:
                    status = "Behind Schedule"
                result_label.config(
                    text = f"Estimated Days Needed : {days_needed}\nStatus: {status}"
                )
            except:
                messagebox.showerror("Error", "Enter Valid Values")
        calcBtn = tk.Button(win, text = "Predict: ",font = ("Arial", 12), width=15, command=calculate).pack(pady=10)
    def profileBtn():
        profile_window = tk.Toplevel(root)
        profile_window.title("Profile View")
        profile_window.geometry("400x800")

        file_name = f"{username}.txt"
        tk.Label(
            profile_window,
            text = f"User: {username} ",
            font = ("Arial", 14, "bold")
        ).pack(pady = 10)
        
        if not os.path.exists(file_name):
            tk.Label(
                profile_window,
                text = "No Study Data logged",
                font = ("Arial", 12)
            )
            return 
        total_hours = 0
        total_sessions = 0
        subject = set()
         
        with open (file_name, "r") as f:
            lines = f.readlines()

        i = 0
        
        while i < len(lines):
            subjects = lines[i].strip()
            try:
                hours_str, _ = lines[i+1].split()
                hours = float(hours_str)
            except Exception as e:
                hours = 0
                
            total_hours += hours
            total_sessions += 1
            subject.add(subjects)
            i += 2

        tk.Label(
            profile_window,
            text = f"Total Study Hours : {total_hours:.1f}",
            font = ("Arial", 12)
        ).pack(pady=5)

        tk.Label(
            profile_window,
            text = f"Total Study Sessions : {total_sessions:.1f}",
            font = ("Arial", 12)
        ).pack(pady=5)

        tk.Label(
            profile_window,
            text = f"Subjects Studied: ",
            font = ("Arial", 1, "bold")
        ).pack(pady=5)

        tk.Label(
            profile_window,
            text = ", ".join(subject),
            font = ("Arial", 11),
            wraplength=350,
            justify = "center"
        ).pack(pady=5)
    def addBtn():
        win = tk.Toplevel(root)
        win.title("Add Deadline")
        win.geometry("400x350")

        tk.Label(win,  text = "Add New Deadline", font = ("Arial ", 16, "bold")).pack()
        tk.Label(win,  text = "Task Name: ", font = ("Arial ", 12)).pack(pady=10)
        task_entry = tk.Entry(win, font = ("Arial", 12))
        task_entry.pack(pady=5)

        tk.Label(win,  text = "Due Date(DD-MM-YYYY): ", font = ("Arial ", 12)).pack(pady=10)
        date_entry = tk.Entry(win, font = ("Arial", 12))
        date_entry.pack(pady=5)

        tk.Label(win,  text = "Notes(Optional): ", font = ("Arial ", 12)).pack(pady=10)
        notes_entry = tk.Entry(win, font = ("Arial", 12))
        notes_entry.pack(pady=5)

        def save_deadline():
            file_name = f"{username}_deadline.txt"

            task = task_entry.get().strip()
            date = date_entry.get().strip()
            note = notes_entry.get().strip()

            if not task or not date:
                messagebox.showerror("Error", "Enter Task Name and Due Date")
                return 

            try: 
                time.strptime(date, "%d-%m-%Y")
            except:
                messagebox.showerror("Error", "Date must be in DD-MM-YYYY format")
                return
            
            with open(file_name, "a") as f:
                f.write(f"{task} | {date} | {note}\n")
            
            messagebox.showinfo("Success ", "Successfully Added New Deadline")
            win.destroy()
        
        tk.Button(win, text = "Save Deadline", font = ("Arial", 12, "bold"), command= save_deadline).pack(pady=5)

    def trackBtn():
        win = tk.Toplevel(root)
        win.title("Deadline Tracker")
        win.geometry("500x500")

        tk.Label(win,  text = "Deadline Tracker", font = ("Arial", 16, "bold")).pack()

        file_name = f"{username}_deadline.txt"
        if not os.path.exists(file_name):
            tk.Label(win,  text = "No Upcoming deadline", font = ("Arial", 14)).pack(pady=5)
            return 
        
        today = datetime.today()

        with open(file_name, "r") as f:
            lines = f.readlines()

        found = False

        for line in lines:
            if not line.strip():
                continue
            try: 
                task, date_string, note = line.strip().split(" | ")
                date = datetime.strptime(date_string, "%d-%m-%Y")
                days_left = (date - today).days
            except:
                continue
            tk.Label(win, text = line, font = ("Arial", 12)).pack()
            if days_left == 0:
                tk.Label(win, text = "Due Today", font = ("Arial", 12)).pack()
            elif days_left < 0:
                tk.Label(win, text = f"Overdue by {-days_left} days", font = ("Arial", 12)).pack()
            elif days_left > 0:
                tk.Label(win, text = f" {days_left} days left", font = ("Arial", 12)).pack()
            
            found = True

        if not found:
            tk.Label(win, text = "No Deadlines Found", font = ("Arial", 12 )).pack()
      
    def dltBtn():
        win = tk.Toplevel(root)
        win.title("Remove Deadline")
        win.geometry("500x500")

        tk.Label(win,  text = "Delete Deadline", font = ("Arial", 16, "bold")).pack()

        file_name = f"{username}_deadline.txt"
        if not os.path.exists(file_name):
            tk.Label(win, text = "No Deadlines Found", font = ("Arial", 12 )).pack()
            return
        
        with open(file_name, "r") as f:
            lines = [ line.strip() for line in f if line.strip()]
            
        if not lines:
            tk.Label(win, text = "No Deadlines Found", font = ("Arial", 12 )).pack()
            return 

        line_text = ""
        for index,line in enumerate(lines):
            line_text += f"{index+1}.{line}\n"
        tk.Label(win, text = "Deadlines:", font = ("Arial", 12 )).pack()
        tk.Label(win, text = line_text, font = ("Arial", 12 )).pack()

        def dltTask():
            try:
                choice = int(simpledialog.askstring("Delete Deadline", "Enter the Deadline Number to Delete"))
                if choice<1 or choice>len(lines):
                    raise ValueError
                
                removed = lines.pop(choice - 1)
                
                with open(file_name, "w") as f:
                    f.write("\n".join(lines))

                messagebox.showinfo("Successful", f"Removed \n{removed} successfully")
                win.destroy()

            except:
                messagebox.showerror("Error", "Invalid choice!")
        tk.Button(win, text = "Delete a Deadline", font=("Arial", 12), command = dltTask).pack()

    def logoutBtn():
        choice = messagebox.askyesno("Logout", "Are you sure you want to logout?")
        if choice:
            root.destroy()
            from login import showLogin
            showLogin()

    def exitBtn():
        choice = messagebox.askyesno("Exit", "Are you sure you want to Exit?")
        if choice:
            root.quit()
   
    #adding buttons
    buttons = [
        ("Log Study Session", logBtn),
        ("View Performance", viewBtn),
        ("View Timetable", timeBtn),
        ("Syllabus Predictor", predictBtn),
        ("View Profile", profileBtn),
        ("Add New Deadline", addBtn),
        ("Deadline Tracker", trackBtn),
        ("Delete a Deadline", dltBtn),
        ("Logout", logoutBtn),
        ("Exit", exitBtn)
        ]
    
    for text,func in buttons:
        tk.Button(root, text=text, width = 25, font = ("Arial", 12), command=func).pack(pady=10)
    root.mainloop()



