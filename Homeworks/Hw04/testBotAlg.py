from queue import Queue

# Function to initialize the start state
def initialize_start_state(game_state):
    for i in range(len(game_state)):
        for j in range(len(game_state[0])):
            if game_state[i][j] == 0:
                return {
                    'position': (i, j),
                    'game_state': tuple(tuple(row) for row in game_state),
                    'moves': 0
                }

# Function to check if the current state is the destination state
def is_destination_state(current_state, M, N):
    row, col = current_state['position']
    return row == 0 and col == N - 1

# Function to generate possible moves from the current state
def generate_moves(current_state):
    directions = [(-1, 0), (1, 0), (0, -1), (0, 1)]
    next_states = []

    for direction in directions:
        new_state = move_tom(current_state, direction)
        if new_state:
            next_states.append(new_state)

    return next_states

# Function to move Tom in a given direction and update the game state
def move_tom(current_state, direction):
    row, col = current_state['position']
    dr, dc = direction
    new_row, new_col = row + dr, col + dc

    if 0 <= new_row < len(current_state['game_state']) and 0 <= new_col < len(current_state['game_state'][0]):
        cell_value = current_state['game_state'][new_row][new_col]

        new_game_state = [list(row) for row in current_state['game_state']]
        new_game_state[row][col] = 0
        new_game_state[new_row][new_col] = 1

        if cell_value < 0:
            switch_color = abs(cell_value)
            switch_walls(new_game_state, switch_color)

        return {
            'position': (new_row, new_col),
            'game_state': tuple(tuple(row) for row in new_game_state),
            'moves': current_state['moves'] + 1
        }

    return None

# Function to switch walls based on the color of the switch
def switch_walls(game_state, switch_color):
    for i in range(len(game_state)):
        for j in range(len(game_state[0])):
            if game_state[i][j] == switch_color:
                game_state[i][j] *= -1

# Main BFS function
def bfs(start_state, M, N):
    queue = Queue()
    queue.put(start_state)
    visited_positions = set()

    while not queue.empty():
        current_state = queue.get()
        row, col = current_state['position']

        if (row, col) in visited_positions:
            continue

        visited_positions.add((row, col))

        if is_destination_state(current_state, M, N):
            return current_state['moves']

        next_states = generate_moves(current_state)

        for next_state in next_states:
            queue.put(next_state)

    return -1

# Read input
M, N, C = map(int, input().split())
game_state = [[int(x) for x in input().split()] for _ in range(M)]

# Call BFS with the initial state
start_state = initialize_start_state(game_state)
result = bfs(start_state, M, N)

# Output the result
print(result)
