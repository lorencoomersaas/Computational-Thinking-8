# setup/importing libraries
import codesters, random
from codesters import StageClass
stage = StageClass()
stage.disable_all_walls()
stage.set_background('purpbg')

# setup ship
ship = codesters.Sprite('ship')
ship.goto(0,-200)
ship.set_size(2)

game_over = False

# defining functions and ball setup
def ballfall():
    global object_speed

    if game_over == False:
        ball = codesters.Sprite('ball')
        ball.set_size(random.randint(2,3))
        ball.set_y_speed(random.randint(2,3) * -1)

def collision(ship, ball):
    pass

ballfall()