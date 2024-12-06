#include <stdio.h>
#include <stdlib.h>
#include <conio.h> // For _kbhit() and _getch() functions for keyboard input
#include <unistd.h> // For usleep() function for delaying (change to windows.h in Windows)

#define SCREEN_WIDTH 40
#define SCREEN_HEIGHT 20
#define GROUND_Y 18
#define GRAVITY 1

// Game state variables
int playerX = 5;
int playerY = GROUND_Y;
int playerVelY = 0;
int onGround = 1;

// Function to draw the screen
void drawScreen() {
    system("cls"); // For Windows, use system("cls"), for Unix-like use system("clear")

    // Draw the screen with player and ground
    for (int y = 0; y < SCREEN_HEIGHT; y++) {
        for (int x = 0; x < SCREEN_WIDTH; x++) {
            if (y == GROUND_Y) {
                printf("="); // Ground
            } else if (x == playerX && y == playerY) {
                printf("@"); // Player character
            } else {
                printf(" "); // Empty space
            }
        }
        printf("\n");
    }
}

// Function to handle player input
void handleInput() {
    if (_kbhit()) { // Check for key press
        char key = _getch(); // Get the key

        // Player movement
        if (key == 'a' || key == 'A') { // Move left
            if (playerX > 0) {
                playerX--;
            }
        } else if (key == 'd' || key == 'D') { // Move right
            if (playerX < SCREEN_WIDTH - 1) {
                playerX++;
            }
        } else if (key == 'w' || key == 'W') { // Jump
            if (onGround) {
                playerVelY = -5; // Jump force
                onGround = 0;
            }
        }
    }
}

// Function to update the player's position (gravity and jumping)
void updatePlayer() {
    // Apply gravity
    playerVelY += GRAVITY;

    playerY += playerVelY;

    // Check for collision with ground
    if (playerY >= GROUND_Y) {
        playerY = GROUND_Y;
        playerVelY = 0;
        onGround = 1;
    }
}

// Main game loop
int main() {
    while (1) {
        handleInput();  // Handle user input
        updatePlayer(); // Update player physics (gravity, jumping)
        drawScreen();   // Draw the screen

        usleep(100000); // Delay to slow down the game loop (100ms)

        // Add any exit condition you like
        if (_kbhit() && _getch() == 'q') { // Press 'q' to quit the game
            break;
        }
    }

    return 0;
}