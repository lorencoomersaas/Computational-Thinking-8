import math
import time

# Constants
A, B = 0, 0
WIDTH, HEIGHT = 80, 24
CHARS = ".,-~:;=!*#$@"

def main():
    global A, B
    while True:
        z = [0] * (WIDTH * HEIGHT)
        b = [' '] * (WIDTH * HEIGHT)
        for j in range(0, 628, 7):
            for i in range(0, 628, 2):
                c = math.sin(i)
                d = math.cos(j)
                e = math.sin(A)
                f = math.sin(j)
                g = math.cos(A)
                h = d + 2
                D = 1 / (c * h * e + f * g + 5)
                l = math.cos(i)
                m = math.cos(B)
                n = math.sin(B)
                t = c * h * g - f * e
                x = int(WIDTH / 2 + 40 * D * (l * h * m - t * n))
                y = int(HEIGHT / 2 + 20 * D * (l * h * n + t * m))
                o = int(x + WIDTH * y)
                N = int(8 * ((f * e - c * d * g) * m - c * d * e - f * g - l * d * n))
                if 0 <= y < HEIGHT and 0 <= x < WIDTH and D > z[o]:
                    z[o] = D
                    b[o] = CHARS[N if N > 0 else 0]

        print('\x1b[H' + ''.join(b))
        A += 0.04
        B += 0.02
        time.sleep(0.03)

if __name__ == '__main__':
    main()