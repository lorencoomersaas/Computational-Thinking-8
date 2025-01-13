import turtle

def draw_circle(x, y, radius, color):
    turtle.penup()
    turtle.goto(x, y - radius)
    turtle.pendown()
    turtle.begin_fill()
    turtle.fillcolor(color)
    turtle.circle(radius)
    turtle.end_fill()

def draw_rectangle(x, y, width, height, color):
    turtle.penup()
    turtle.goto(x, y)
    turtle.pendown()
    turtle.begin_fill()
    turtle.fillcolor(color)
    for _ in range(2):
        turtle.forward(width)
        turtle.left(90)
        turtle.forward(height)
        turtle.left(90)
    turtle.end_fill()

turtle.speed(1)

draw_circle(0, 100, 100, "#D69A6C")

draw_circle(-40, 150, 15, "white")
draw_circle(40, 150, 15, "white")
draw_circle(-40, 150, 7, "black")
draw_circle(40, 150, 7, "black")

turtle.penup()
turtle.goto(-40, 80)
turtle.pendown()
turtle.width(3)
turtle.setheading(-60)
turtle.circle(50, 120)

turtle.penup()
turtle.goto(-5, 40)
turtle.setheading(0)
turtle.pendown()
draw_rectangle(-5, 40, 10, 30, "white")

turtle.penup()
turtle.goto(5, 40)
turtle.setheading(0)
turtle.pendown()
draw_rectangle(5, 40, 10, 30, "white")

turtle.hideturtle()
turtle.done()