# setup
import codesters
from codesters import StageClass
import keyboard
stage = StageClass()

# set bg and sprite
stage.set_background("moon")
s1 = codesters.Sprite("person1", 0, -200)
s1.set_size(0.5)

# controls
def up(sprite):
    sprite.move_up(3)
def down(sprite):
    sprite.move_down(3)
def left(sprite):
    sprite.move_left(3)
def right(sprite):
    sprite.move_right(3)

# hide and show
def hide(sprite):
    sprite.hide()
def show(sprite):
    sprite.show()

# more controls
s1.event_key("w", up)
s1.event_key("s", down)
s1.event_key("a", left)
s1.event_key("d", right)
s1.event_key("h", hide)
s1.event_key("g", show)

# while True:
#     if keyboard.is_pressed("w"):
#         s1.set_position(x, y + 1)
#     if keyboard.is_pressed("s"):
#         s1.set_position(x, y - 1)
#     if keyboard.is_pressed("a"):
#         s1.set_position(x - 1, y)
#     if keyboard.is_pressed("d"):
#         s1.set_position(x + 1, y)