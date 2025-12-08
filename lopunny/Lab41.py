import streamlit as st
import random

# -------------------------------------------------------------
# PAGE CONFIG
# -------------------------------------------------------------
st.set_page_config(
    page_title="Citizen Wellness Portal™",
    page_icon="🟧",
    layout="centered"
)

# -------------------------------------------------------------
# SESSION STATE INITIALIZATION
# -------------------------------------------------------------
if "users" not in st.session_state:
    st.session_state.users = {}   # {"username": "password"}

if "logged_in" not in st.session_state:
    st.session_state.logged_in = False

if "username" not in st.session_state:
    st.session_state.username = None

if "page" not in st.session_state:
    st.session_state.page = "login"   # or "register"

# -------------------------------------------------------------
# HELPERS
# -------------------------------------------------------------
def go_to_login():
    st.session_state.page = "login"

def go_to_register():
    st.session_state.page = "register"

def logout():
    st.session_state.logged_in = False
    st.session_state.username = None
    st.session_state.page = "login"
    st.success("You have been logged out.")


# -------------------------------------------------------------
# LOGIN PAGE
# -------------------------------------------------------------
def login_page():
    st.title("🟧 Citizen Wellness Portal™")
    st.subheader("Authentication Protocol")

    with st.form("login_form"):
        username = st.text_input("Username")
        password = st.text_input("Password", type="password")
        submitted = st.form_submit_button("Submit to The Algorithm")

    if submitted:
        if username in st.session_state.users and st.session_state.users[username] == password:
            st.session_state.logged_in = True
            st.session_state.username = username
            st.success(f"Welcome back, Citizen {username}!")
        else:
            st.error("Invalid credentials. The Algorithm is disappointed.")

    st.info("New citizen?")
    st.button("Register", on_click=go_to_register)


# -------------------------------------------------------------
# REGISTRATION PAGE
# -------------------------------------------------------------
def register_page():
    st.title("🟧 Citizen Wellness Portal™")
    st.subheader("Registration Protocol")

    with st.form("register_form"):
        username = st.text_input("Choose a Username")
        password = st.text_input("Choose a Password", type="password")
        confirm = st.text_input("Confirm Password", type="password")
        submitted = st.form_submit_button("Register Citizen")

    if submitted:
        if username.strip() == "":
            st.error("Username cannot be empty.")
        elif username in st.session_state.users:
            st.error("Username already taken—The Algorithm rejects duplicates.")
        elif len(password) < 4:
            st.error("Password must be at least 4 characters.")
        elif password != confirm:
            st.error("Passwords do not match.")
        else:
            st.session_state.users[username] = password
            st.success("Registration complete. Citizen added to The Algorithm.")
            st.button("Return to Login", on_click=go_to_login)

    st.button("Back to Login", on_click=go_to_login)


# -------------------------------------------------------------
# DASHBOARD PAGE
# -------------------------------------------------------------
def dashboard_page():
    st.title(f"Welcome, Citizen {st.session_state.username}!")
    st.subheader("Your Algorithmic Satisfaction Metrics™")

    # Generate random metrics (or use static if preferred)
    productivity = random.randint(60, 95)
    compliance = random.randint(90, 100)
    happiness = random.randint(50, 85)
    loyalty = random.randint(80, 100)

    col1, col2 = st.columns(2)
    with col1:
        st.metric("Productivity Score", f"{productivity}%")
        st.metric("Happiness Index", f"{happiness}%")

    with col2:
        st.metric("Compliance Rating", f"{compliance}%")
        st.metric("Loyalty Quotient", f"{loyalty}%")

    st.success("Status: WITHIN ACCEPTABLE PARAMETERS")

    st.button("Logout", on_click=logout)


# -------------------------------------------------------------
# MAIN APP FLOW
# -------------------------------------------------------------
if st.session_state.logged_in:
    dashboard_page()
else:
    if st.session_state.page == "login":
        login_page()
    elif st.session_state.page == "register":
        register_page() 
