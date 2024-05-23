
# Pacman Game

This Pacman game is a simple implementation of the classic arcade game. It features a grid-based map where the player controls Pacman, navigating through a maze while avoiding ghosts and collecting dots. The objective is to clear all the dots from the maze without being caught by the ghosts. Pacman Code in C++. Runs in the output window. Video link of program working can be viewed on youtube: https://youtu.be/-ey5chYDgpY.

## Getting Started

To run the game, you need a C++ compiler installed on your system. Follow these steps:

1. Clone this repository to your local machine.
2. Navigate to the directory containing the source code files.
3. Compile the source code using your C++ compiler. For example:
    ```bash
    g++ apsc143project.cpp -o pacman_game
    ```
4. Run the compiled executable:
    ```bash
    ./pacman_game
    ```

## Gameplay

- Use the following keys to control Pacman:
  - `W`: Move up
  - `A`: Move left
  - `S`: Move down
  - `D`: Move right

- Avoid colliding with the ghosts (`G`) roaming the maze.
- Collect all the dots (`.`) to win the game.
- If Pacman collides with a ghost, you lose the game.

## Files

- `apsc143project.cpp`: Contains the main code for the Pacman game.
- `colours.cpp` and `colours.h`: Provide functions for changing text colors in the console. (You don't need to edit these files.)

## Notes

- This game is a simplified version of Pacman and lacks some features found in the original game.
- Feel free to modify the code to add more features or customize the gameplay.
