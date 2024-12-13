#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>  // For sleep()
#include <termios.h> // For non-blocking input handling
#include <fcntl.h>   // For fcntl()

#define SCREEN_WIDTH 80
#define SCREEN_HEIGHT 20
#define GRAVITY 1
#define JUMP_STRENGTH 3

// Define the player character and the platform character
#define PLAYER_CHAR 'P'
#define PLATFORM_CHAR '#'

// The player structure
typedef struct {
    int x, y;
    int dx, dy;
    int on_ground;
} Player;

char screen[SCREEN_HEIGHT][SCREEN_WIDTH];

// Platforms (simple hardcoded ones for this example)
int platforms[5][2] = {
    {10, 15}, // platform at (x, y)
    {30, 12},
    {50, 10},
    {20, 5},
    {60, 8}
};

// Forward declarations of the non-blocking input functions
int kbhit(void);
char getch_unix(void);

// Function to initialize the screen with spaces
void initialize_screen() {
    for (int i = 0; i < SCREEN_HEIGHT; i++) {
        for (int j = 0; j < SCREEN_WIDTH; j++) {
            screen[i][j] = ' ';
        }
    }
}

// Function to draw the player and platforms to the screen
void draw_screen(Player *player) {
    initialize_screen();
    
    // Draw platforms
    for (int i = 0; i < 5; i++) {
        int plat_x = platforms[i][0];
        int plat_y = platforms[i][1];
        for (int j = plat_x; j < plat_x + 5 && j < SCREEN_WIDTH; j++) {
            if (plat_y < SCREEN_HEIGHT) {
                screen[plat_y][j] = PLATFORM_CHAR;
            }
        }
    }
    
    // Draw player
    if (player->y < SCREEN_HEIGHT && player->x < SCREEN_WIDTH) {
        screen[player->y][player->x] = PLAYER_CHAR;
    }

    // Clear screen and render it
    system("clear");
    for (int i = 0; i < SCREEN_HEIGHT; i++) {
        for (int j = 0; j < SCREEN_WIDTH; j++) {
            printf("%c", screen[i][j]);
        }
        printf("\n");
    }
}

// Function to update the player based on input and physics
void update_player(Player *player) {
    // Handle non-blocking input using termios
    if (kbhit()) {
        char ch = getch_unix();
        
        if (ch == 'a' || ch == 'A') {
            player->dx = -1;  // Move left
        } else if (ch == 'd' || ch == 'D') {
            player->dx = 1;   // Move right
        } else if (ch == 'w' || ch == 'W') {
            if (player->on_ground) {
                player->dy = -JUMP_STRENGTH; // Jump
                player->on_ground = 0;
            }
        }
    }

    // Apply gravity
    if (!player->on_ground) {
        player->dy += GRAVITY;
    }

    // Update player position
    player->x += player->dx;
    player->y += player->dy;

    // Check for collision with platforms (simple collision detection)
    player->on_ground = 0;
    for (int i = 0; i < 5; i++) {
        int plat_x = platforms[i][0];
        int plat_y = platforms[i][1];
        if (player->y == plat_y - 1 && player->x >= plat_x && player->x <= plat_x + 5) {
            player->y = plat_y;   // Place the player on top of the platform
            player->dy = 0;       // Stop downward movement
            player->on_ground = 1;  // Mark that player is on the ground
        }
    }

    // Prevent player from going out of bounds
    if (player->x < 0) player->x = 0;
    if (player->x >= SCREEN_WIDTH) player->x = SCREEN_WIDTH - 1;
    if (player->y < 0) player->y = 0;
    if (player->y >= SCREEN_HEIGHT) player->y = SCREEN_HEIGHT - 1;
}

int kbhit(void) {
    struct termios oldt, newt;
    int ch;
    int oldf;

    tcgetattr(STDIN_FILENO, &oldt);
    newt = oldt;
    newt.c_lflag &= ~(ICANON | ECHO);  // Disable canonical mode and echo
    newt.c_cc[VMIN] = 1;
    newt.c_cc[VTIME] = 0;
    tcsetattr(STDIN_FILENO, TCSANOW, &newt);
    oldf = fcntl(STDIN_FILENO, F_GETFL, 0);
    fcntl(STDIN_FILENO, F_SETFL, oldf | O_NONBLOCK);

    ch = getchar();

    tcsetattr(STDIN_FILENO, TCSANOW, &oldt);
    fcntl(STDIN_FILENO, F_SETFL, oldf);

    if(ch != EOF) {
        ungetc(ch, stdin);
        return 1;
    }

    return 0;
}

char getch_unix(void) {
    struct termios oldt, newt;
    char ch;
    tcgetattr(STDIN_FILENO, &oldt);
    newt = oldt;
    newt.c_lflag &= ~(ICANON | ECHO);  // Disable canonical mode and echo
    newt.c_cc[VMIN] = 1;
    newt.c_cc[VTIME] = 0;
    tcsetattr(STDIN_FILENO, TCSANOW, &newt);
    ch = getchar();
    tcsetattr(STDIN_FILENO, TCSANOW, &oldt);
    return ch;
}

int main() {
    // Initialize player
    Player player = { SCREEN_WIDTH / 2, SCREEN_HEIGHT - 2, 0, 0, 1 }; // Start on the ground
    
    while (1) {
        draw_screen(&player);
        update_player(&player);
        usleep(100000); // Sleep for 100 milliseconds
    }

    return 0;
}
