# setup/importing libraries
import codesters, random, time
from codesters import StageClass
stage = StageClass()
stage.disable_all_walls()
stage.set_background('purpbg')

# setup ship
ship = codesters.Sprite('ship')
ship.goto(0,-200)
ship.set_size(2)

game_over = False

# controls
def left():
    ship.move_left(3)
def right():
    ship.move_right(3)

ship.event_key('a', left)
ship.event_key('d', right)

# defining functions and ball setup
def ballfall():
    global object_speed

    if game_over == False:
        ball = codesters.Sprite('ball')
        ball.set_size(random.randint(2,3))
        ball.set_position(random.randint(-215, 215), 250)
        ball.set_y_speed(random.randint(2,3) * -1)

def collision(ship, ball):
    pass

# for i in range(10):
#     ballfall()
#     time.sleep(1)
stage.event_interval(ballfall,3)