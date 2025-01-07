import turtle as t

t.penup()
t.goto(-100, -100)
t.color("purple")
t.pendown()
t.speed(10)

for i in range(360):
    t.forward(300)
    t.left(94)

t.exitonclick()