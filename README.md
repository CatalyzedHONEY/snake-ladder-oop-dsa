# Snake and Ladder Game (C++)

A console-based Snake and Ladder game built using:

- Linked Lists
- Object-Oriented Programming
- Dynamic Memory Allocation
- Pointers

## Features

- 100-square board
- Snakes and ladders implementation
- Two-player gameplay
- Dice rolling simulation
- Exact roll required to win

## Concepts Demonstrated

- Data Structures
- OOP Design
- Linked List Traversal
- Pointer Manipulation

## Class Structure

Node
 ├── position
 ├── next
 └── jump

Board
 ├── createBoard()
 ├── addSnakesAndLadders()
 └── getNode()

Player
 ├── move()
 └── hasWon()

Game
 ├── rollDice()
 ├── playTurn()
 └── start()