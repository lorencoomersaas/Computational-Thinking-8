# importing libraries
import turtle as t
import random as r

# setting speed to 10
t.speed(10)

# setting bg
t.Screen().bgcolor('#EBD3F8')

# colors = ['red', 'blue', 'purple']
colors = ['#AD49E1', '#7A1CAC', '#2E073F']
# angles = [0, 72, 144, 216, 288]
# angles = [0, 60, 120, 180, 240, 300]
angles = [0, 90, 180, 270]

# for loop
for i in range(99999999999999999):
    t.color(colors[i%3])
    t.forward(10)
    t.right(r.choice(angles))

# end
t.exitonclick()