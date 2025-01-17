import queue
import threading
import turtle

turtle.Screen().bgcolor('#4C585B')
colors = ['#FFFDEC', '#FFE2E2', '#FFCFCF']

def tes1():
    for _ in range(999999999):
        turtle1.color(colors[_%3])
        # graphics.put(turtle1.forward)
        # graphics.put(turtle1.left)
        turtle1.forward(10 + _)
        turtle1.left(60 + 1)

def tes2():
    for _ in range(9999999999):
        turtle2.color(colors[_%3])
        # graphics.put(turtle2.forward)
        # graphics.put(turtle2.right)
        turtle2.forward(10 + _)
        turtle2.right(60 + 1)

def process_queue():
    while not graphics.empty():
        (graphics.get())(1)

    if threading.active_count() > 1:
        turtle.ontimer(process_queue, 100)

graphics = queue.Queue(2)  # size = number of hardware threads you have - 1

turtle1 = turtle.Turtle()
turtle1.speed(0)
thread1 = threading.Thread(target=tes1)
thread1.daemon = True  # thread dies when main thread (only non-daemon thread) exits.
thread1.start()

turtle2 = turtle.Turtle()
turtle2.speed(0)
thread2 = threading.Thread(target=tes2)
thread2.daemon = True  # thread dies when main thread (only non-daemon thread) exits.
thread2.start()

process_queue()

turtle.exitonclick()