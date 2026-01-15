import tkinter as tk
from tkinter import messagebox
import os

def showLogin():
    #creating the login window
    login_window = tk.Tk()
    login_window.title("Smart Student Progress Tracker")
    login_window.geometry("400x300")

    result = {"username" : None }

    #adding a label
    label = tk.Label(login_window, text= "Smart Student Progress Tracker", font = ("Arial", 16,  "bold"))
    label.pack(pady=10)

    #user id entry
    tk.Label(login_window, text = "Enter User Id: ", font = ("Arial", 14)).pack(pady=10)
    usernameEntry = tk.Entry(login_window, font = ("Arial", 14))
    usernameEntry.pack(pady=10)

    #login button
    def login():
        userName=usernameEntry.get().strip()
        if not userName:
            messagebox.showerror("Error" , "Enter a valid userID")
            return
        
        #creating new file for new users
        fileName = f"{userName}.txt"
        if not os.path.exists(fileName):
            with open(fileName, "w") as f:
                pass
        result["username"] = userName
        login_window.destroy()

    tk.Button(login_window, text = "Login", width = 20, font = ("Arial", 12), command = login).pack(pady = 20)       
    login_window.mainloop()
    return result["username"]  