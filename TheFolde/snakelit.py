# app.py
import streamlit as st
import random
import time

# --- Game config ---
GRID_W = 16
GRID_H = 12
TICK_SECONDS = 0.12  # speed during automatic run

# Emoji/characters for display
EMPTY = "·"
SNAKE_CHAR = "🟩"
FOOD_CHAR = "🍎"
HEAD_CHAR = "🟦"

# --- Helpers ---
def init_state():
    st.session_state.setdefault("snake", [(GRID_W // 2, GRID_H // 2)])
    st.session_state.setdefault("direction", (1, 0))  # moving right
    st.session_state.setdefault("food", place_food(st.session_state["snake"]))
    st.session_state.setdefault("running", False)
    st.session_state.setdefault("score", 0)
    st.session_state.setdefault("speed", 0.12)

def place_food(snake):
    while True:
        pos = (random.randrange(0, GRID_W), random.randrange(0, GRID_H))
        if pos not in snake:
            return pos

def step():
    """Advance snake by one step. Handles collisions and food."""
    snake = st.session_state["snake"]
    dx, dy = st.session_state["direction"]
    head = snake[-1]
    new_head = ((head[0] + dx) % GRID_W, (head[1] + dy) % GRID_H)

    # collision with self?
    if new_head in snake:
        st.session_state["running"] = False
        st.session_state["message"] = f"Game over — collided with yourself. Score: {st.session_state['score']}"
        return

    # eat food?
    if new_head == st.session_state["food"]:
        snake.append(new_head)
        st.session_state["score"] += 1
        st.session_state["food"] = place_food(snake)
    else:
        # normal move: shift forward
        snake.append(new_head)
        snake.pop(0)
    st.session_state["snake"] = snake

def render_grid():
    grid = [[EMPTY for _ in range(GRID_W)] for _ in range(GRID_H)]
    for x, y in st.session_state["snake"][:-1]:
        grid[y][x] = SNAKE_CHAR
    hx, hy = st.session_state["snake"][-1]
    grid[hy][hx] = HEAD_CHAR
    fx, fy = st.session_state["food"]
    grid[fy][fx] = FOOD_CHAR

    # Render as preformatted text for monospace alignment
    rows = ["".join(row) for row in grid]
    txt = "\n".join(rows)
    st.markdown(f"```\n{txt}\n```")

def set_direction(dx, dy):
    current = st.session_state["direction"]
    # prevent 180-degree reversal
    if (dx, dy) == (-current[0], -current[1]) and len(st.session_state["snake"]) > 1:
        return
    st.session_state["direction"] = (dx, dy)

def restart():
    st.session_state["snake"] = [(GRID_W // 2, GRID_H // 2)]
    st.session_state["direction"] = (1, 0)
    st.session_state["food"] = place_food(st.session_state["snake"])
    st.session_state["running"] = False
    st.session_state["score"] = 0
    st.session_state["message"] = ""

# --- UI ---
st.set_page_config(page_title="Streamlit Snake", layout="centered")
st.title("🐍 Streamlit Snake")
st.caption("Press **Start** to play. Use the arrow buttons (or install optional arrow-key support).")

init_state()

# Top controls
col1, col2, col3 = st.columns([1, 2, 1])
with col1:
    if st.button("Start"):
        if not st.session_state["running"]:
            st.session_state["running"] = True
            st.session_state["message"] = "Running..."
with col2:
    if st.button("Restart"):
        restart()
with col3:
    st.write(f"Score: **{st.session_state['score']}**")

# Speed slider
st.session_state["speed"] = st.slider("Speed (lower = faster)", min_value=0.03, max_value=0.4, value=st.session_state.get("speed", TICK_SECONDS), step=0.01)

# Game area
game_area = st.empty()
controls = st.empty()
message = st.empty()

# Arrow controls row (guaranteed fallback)
with controls.container():
    c1, c2, c3 = st.columns([1, 1, 1])
    with c1:
        st.write("")  # spacer
    with c2:
        if st.button("↑", key="up_btn"):
            set_direction(0, -1)
    with c3:
        st.write("")
    c4, c5, c6 = st.columns([1, 1, 1])
    with c4:
        if st.button("←", key="left_btn"):
            set_direction(-1, 0)
    with c5:
        if st.button("·", key="noop"):
            pass
    with c6:
        if st.button("→", key="right_btn"):
            set_direction(1, 0)
    c7, c8, c9 = st.columns([1, 1, 1])
    with c7:
        st.write("")
    with c8:
        if st.button("↓", key="down_btn"):
            set_direction(0, 1)
    with c9:
        st.write("")

# Optional arrow key support note (see README)
st.info("Tip: to use your keyboard's arrow keys, install the optional dependency and uncomment the arrow-key block in `app.py`. See README.md.")

# Render + loop
render_grid()
message.write(st.session_state.get("message", ""))

# If running: advance automatically (this loop runs within the Streamlit rerun and yields updates)
if st.session_state["running"]:
    # Do one step, re-render, then sleep and trigger a rerun by sleeping and calling st.experimental_rerun()
    step()
    render_grid()
    message.write(st.session_state.get("message", ""))
    # Sleep then rerun so the UI updates automatically.
    time.sleep(st.session_state["speed"])
    st.experimental_rerun()
