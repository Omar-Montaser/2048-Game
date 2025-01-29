# 2048 Console Game

A C++ implementation of the classic 2048 puzzle game with console-based gameplay and dynamic board scaling.

## Features
- Classic 2048 gameplay mechanics
- Dynamic board expansion (4x4 → 6x6 → 8x8) as score increases
- Persistent high score tracking
- Player ranking system
- Score-based difficulty progression
- Pause/resume functionality
- Arrow key controls

## How to Play
1. Use arrow keys to move tiles
2. Combine matching numbers to reach 2048
3. Game ends when no moves remain
4. Track your progress with live score updates

## Controls
- Arrow Keys: Move tiles
- Space: Pause game
- Esc: Exit game
- R: View rankings
- B: Return to menu

## Requirements
- Windows OS (uses conio.h)
- C++ compiler (tested with GCC/Mingw)

## Technical Highlights
- Object-oriented design with Game/Player structs
- Score-based board scaling system
- Bubble-sort ranking algorithm
- Tile merging logic with score tracking
- Console-based UI management
