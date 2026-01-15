from login import showLogin
from dashboard import open_dashboard

def main():
    #importing username form showlogin() function in login.py
    username = showLogin()
    if username:
        #opening dashboard if username exists
        open_dashboard(username)

if __name__ == "__main__":
    main()