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
    
    // Major radius and minor radius of the donut
    double R = 3.0;  // Larger radius of the donut's central circle (increased from 2.0)
    double r = 1.5;  // Larger radius of the tube (increased from 1.0)

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
        for (double theta = 0; theta < TWO_PI; theta += 0.04) {  // Reduced step size for more density
            for (double phi = 0; phi < TWO_PI; phi += 0.01) {    // Reduced step size for more density
                // 3D coordinates for the donut before rotation
                x = (R + r * cos(phi)) * cos(theta);
                y = (R + r * cos(phi)) * sin(theta);
                z = r * sin(phi);

                // Rotate the point around the X axis (apply rotation A)
                double x_rot = x;
                double y_rot = y * cos_A - z * sin_A;
                double z_rot = y * sin_A + z * cos_A;

                // Rotate the point around the Y axis (apply rotation B)
                x = x_rot * cos_B - z_rot * sin_B;
                y = y_rot;
                z = x_rot * sin_B + z_rot * cos_B;

                // Now calculate the perspective projection
                // Fix the "view distance" by adjusting the scaling factors
                ooz = 1.0 / (z + 5);  // Add a constant value to z to simulate camera distance
                int px_int = (int)(WIDTH / 2 + (WIDTH / 4) * x * ooz);  // Adjust the scaling
                int py_int = (int)(HEIGHT / 2 - (HEIGHT / 4) * y * ooz); // Adjust the scaling

                // Determine the character to print based on the "distance"
                k = (int)(8 * ooz);  // Scale the distance to character index
                if (py_int >= 0 && py_int < HEIGHT && px_int >= 0 && px_int < WIDTH && ooz > 0) {
                    if (buffer[py_int * WIDTH + px_int] == ' ') {
                        buffer[py_int * WIDTH + px_int] = donut[k % 10];  // Use donut shape characters
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

        usleep(25000);  // Control the speed of animation (in microseconds)
    }

    return 0;
}