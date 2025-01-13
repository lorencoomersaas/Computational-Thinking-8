# import libraries
import turtle as t

# set up
t.penup()
t.goto(0, 0)
t.color("purple")
t.pendown()
t.speed(0)

# setting bg
t.Screen().bgcolor('#4C585B')

colors = ['#FFFDEC', '#FFE2E2', '#FFCFCF']

# for loop
for i in range(99999999999999999999999):
    t.color(colors[i%3])
    t.forward(10 + i)
    t.left(60 + 1)

# end
t.exitonclick()