# setup/importing librairies
import codesters, random
from codesters import StageClass
stage = StageClass()
stage.disable_floor()
stage.set_background("purpbg")
ship = codesters.sprite("ship")
ball = codesters.sprite("ball")

# setup ship
ship.goto(0,-250)


# defining functions
def ballfall(n):
    for i in range(n):
        pass