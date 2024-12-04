#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <unistd.h>

#define WIDTH 80
#define HEIGHT 40
#define TWO_PI 6.28318530717958647692

// Function to plot a donut shape on the terminal
int main() {
    double A = 0.0, B = 0.0;   // Angles for rotation
    double sin_A, cos_A, sin_B, cos_B;
    double x, y, z, ooz, px, py; // 3D coordinates and projection
    char buffer[WIDTH * HEIGHT + 1];
    char donut[] = ".,-~:;=!*#$@";  // Characters to represent the donut surface
    int k;  // Declare k properly here to fix the undeclared variable error
    
    while(1) {
        // Clear the buffer
        for (int i = 0; i < WIDTH * HEIGHT; i++) {
            buffer[i] = ' ';
        }

        // Calculate the sine and cosine of angles A and B
        sin_A = sin(A);
        cos_A = cos(A);
        sin_B = sin(B);
        cos_B = cos(B);
        
        // Loop through all possible points on the donut's surface
        for (double theta = 0; theta < TWO_PI; theta += 0.07) {
            for (double phi = 0; phi < TWO_PI; phi += 0.02) {
                // 3D coordinates for the donut
                x = cos_A * (1 + cos_B * cos(phi) - sin_B * sin_A * sin(phi));
                y = sin_A * (1 + cos_B * cos(phi) - sin_B * sin_A * sin(phi));
                z = cos_B * cos(phi) + sin_B * sin_A * sin(phi);

                ooz = 1.0 / z;  // Inverse of z (for perspective)
                px = (int)(WIDTH / 2 + WIDTH / 4 * x * ooz);
                py = (int)(HEIGHT / 2 - HEIGHT / 4 * y * ooz);

                // Determine the character to print based on the "distance"
                k = (int)(8 * ooz);  // Scale the distance to character index
                if (py >= 0 && py < HEIGHT && px >= 0 && px < WIDTH && ooz > 0) {
                    if (buffer[py * WIDTH + px] == ' ') {
                        buffer[py * WIDTH + px] = donut[k % 10];  // Use donut shape characters
                    }
                }
            }
        }

        // Print the buffer to the console
        printf("\x1b[H");  // Move the cursor to the top left
        for (int i = 0; i < HEIGHT; i++) {
            for (int j = 0; j < WIDTH; j++) {
                putchar(buffer[i * WIDTH + j]);
            }
            putchar('\n');
        }
        
        A += 0.04;  // Update angle A for rotation
        B += 0.02;  // Update angle B for rotation

        usleep(50000);  // Control the speed of animation (in microseconds)
    }

    return 0;
}
