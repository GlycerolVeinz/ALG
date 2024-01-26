from collections import deque
from typing import List, Tuple

def findShortestPath(maze: List[List[int]]) -> int:
    num_rows, num_cols = len(maze), len(maze[0])
    directions = [(0, -1), (-1, 0), (0, 1), (1, 0)] # Left, Up, Right, Down

    # Step 1: Create a copy of the playing field
    field_copy = [[maze[i][j] for j in range(num_cols)] for i in range(num_rows)]

    # Step 2: Start BFS traversal from the top left corner
    queue = deque([(num_rows - 1, num_cols - 1, 0)]) # (row, col, steps)
    visited = set((num_rows - 1, num_cols - 1, 0))
    while queue:
        row, col, steps = queue.popleft()

        # If reached the bottom right corner, return the number of steps
        if row == 0 and col == 0:
            return steps

        # Check the neighbours
        for dr, dc in directions:
            nr, nc = row + dr, col + dc
            if 0 <= nr < num_rows and 0 <= nc < num_cols and field_copy[nr][nc] != 1:
                # Step 3: Perform a BFS traversal for each colour
                if field_copy[nr][nc] == 2: # Pressure plate
                    # Step 4: Update the walls and the pressure plates
                    queue.append((nr, nc, steps + 1))
                    visited.add((nr, nc, steps + 1))
                    field_copy[nr][nc] = 0
                else:
                    # Step 5: Continue the BFS traversal
                    queue.append((nr, nc, steps + 1))
                    visited.add((nr, nc, steps + 1))

    # If no path is found, return -1
    return -1

def readInput():
    # Initialize the array to store the maze
    maze = []

    # Read the dimensions of the maze
    dimensions = list(map(int, input().split()))

    # Create the maze array with the given dimensions
    for _ in range(dimensions[0]):
        maze.append([0] * dimensions[1])

    # Read the maze grid from std input and store it in the array
    for i in range(dimensions[0]):
        maze[i] = list(map(int, input().split()))

    # Return the maze array
    return maze

def main():
    maze = readInput()
    print(findShortestPath(maze))

if __name__ == "__main__":
    main()