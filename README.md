# Memory-Game
A console-based Memory Matching Game built in C++ with Visual Studio Code.
The player flips cards on a grid to find matching pairs. The objective is to match all pairs before running out of lives. 

Difficulty can be customized by choosing different grid sizes, themes, and time limits.

# How to Play
- At the start, the player chooses the grid size, theme, and time limit.
- A completed grid is briefly shown, allowing the player to memorize card positions. After the timer runs out, the grid is hidden.
- The game begins with all cards face down and the player has 3 lives to reveal the whole board.
- On each turn, the player selects two hidden cards to flip over:
  - If the cards match, they remain face up.
  - If the cards do not match, the player loses 1 life.
  
# Features
- Customizable grid sizes: 4x4, 6x6, 8x8.
- Multiple themes: Colors, Anime Characters, and Animals.
- Timer settings: Control how long the grid is revealed (2s, 4s, 6s).
- Replay option: Play multiple rounds without restarting the program.
- Turn counter: Track the number of attempts made.
- 3 lives system: Adds challenge and replay value.
- Input validation: Prevents invalid or repeated guesses.

# Purpose
- Test and improve memory skills by challenging players to remember card positions.
- Practice C++ programming concepts including functions, modularity, arrays and file I/O.
- Gain experience with problem-solving, debugging and program structure in a medium-scale project.
- Explore how games can demonstrate logic, interactivity and algorithm design.

# How to Run
- Download and install Visual Studio Code (VS Code).
- Install the C++ extension pack in VS Code.
- Clone or download the repository.
- Open the project in VS Code.
- Build and run the program to play the game in the terminal.
  - Ensure that the .txt files are in the output folder for the project.

# Known Issues / Limitations
- Output edge cases: Non-numeric input or very large numbers may cause unexpected behavior.
- Limited UI: Console-based visuals only; no colors or GUI.
- Platform differences: Screen-clearing may behave differently on Windows, macOS, and Linux.
- Game statistics: Replay works, but player stats (wins/losses over multiple sessions) aren’t tracked.
- Scalability: Large grids may look cluttered in console output.
