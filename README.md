
# The PAC-MAN Game

## Table of Contents
* [General info](#general-info)
* [Technologies](#technologies)
* [Rules](#rules)
* [Run Locally](#run-locally)
* [Running Examples](#running-examples)

## General Info
Hey Guys,

Welcome to Pacman Game!

The main goal of this project is to exercise the using of OOP with C++.

I've implemented the OOP principles, using classes, inheritence and polymorphism.

Also, I put my effforts on buliding "Strategy" design pattern.

Personally, it was my breakthrough in this project. Since then, adding objects and features became easier and more practical.

Another nice thing to mention is that in order to instruct the ghosts to chase the Pac-Man (in professional diffculty level -> see down below in the rules), I've used BFS algorithem, that checks in every single move what's the shortest possible path from the ghost to the Pac-Man.

For optimal game experience, set your console resolution to 25X80.

Enjoy!

## Technologies
- C++ Programming language 
- Visual Studio 2019 on Windows 10

## Rules
The rules are short and simple.

The Pac-Man goal is to eat all the breadcrumbs, in order to finish a single board.

The boards will load one-by-one until losing or finishing all the boards.

*Note that you could choose the first board.

Only after completing all boards, the Pac-Man will be the winner.

Starting with 3 lives. each collision with the ghost will reduce the the lives by one.

"Special" breadcrumbs, (a number between 5 to 9) will appear sometimes on the board.
If the Pac-Man eats this special breadcrumb it gets the points as the value of the digit (5 to 9).
*Note that eating a breadcrumb with the value of "9" (The max), will add lives to the Pac-Man by one.

In some boards, there are "Invisible-Tunnels". Namely, a tunnel that only the Pac-Man can go through. 

The game has 3 diffculty levels. Beginner, Amatuer, Professional.

In Beginner mode -> ghosts are moving randomally.

In Amatuer mode -> ghosts are half moving randomally, and half moving smart (chasing the Pac-Man)

In Professional mode -> ghosts are chasing the Pac-Man consistently.

Keys:

LEFT -> a or A

RIGHT -> d or D

UP -> w or W

Down -> x or X

STAY -> s or S

PAUSE GAME -> Esc


## Run Locally

Clone the project

```bash
  git clone https://github.com/AmirAnckonina/Pacman-Game.git
```

Go to the project directory

```bash
  cd Pacman-Game
```

Run Solution ->
```bash
pacman_project.sln
```

Run Executable ->
```bash
pacman_project.exe
```

## Running Examples

Main Menu

![App Screenshot](https://github.com/AmirAnckonina/Pacman-Game/blob/c832fa59aeedf8c0e997cbc2ab4afc989e73b8ab/Screenshots/MainMenu.jpg)

Boards Examples:

![App Screenshot](https://github.com/AmirAnckonina/Pacman-Game/blob/c832fa59aeedf8c0e997cbc2ab4afc989e73b8ab/Screenshots/BoardSelection.jpg)


![App Screenshot](https://github.com/AmirAnckonina/Pacman-Game/blob/c832fa59aeedf8c0e997cbc2ab4afc989e73b8ab/Screenshots/Board.jpg)


![App Screenshot](https://github.com/AmirAnckonina/Pacman-Game/blob/c832fa59aeedf8c0e997cbc2ab4afc989e73b8ab/Screenshots/Board2.jpg)


![App Screenshot](https://github.com/AmirAnckonina/Pacman-Game/blob/c832fa59aeedf8c0e997cbc2ab4afc989e73b8ab/Screenshots/Board3.jpg)


![App Screenshot](https://github.com/AmirAnckonina/Pacman-Game/blob/c832fa59aeedf8c0e997cbc2ab4afc989e73b8ab/Screenshots/InvalidBoard.jpg)


![App Screenshot](https://github.com/AmirAnckonina/Pacman-Game/blob/c832fa59aeedf8c0e997cbc2ab4afc989e73b8ab/Screenshots/TinyBoard.jpg)
