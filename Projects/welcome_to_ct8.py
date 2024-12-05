###############################################
### SETUP ###
import codesters
from codesters import StageClass
stage = StageClass()
###############################################


stage.set_background("laser")
mySprite = codesters.Sprite("theif")
mySprite.set_size(0.1)
mySprite.say("security's tight around here!")


#print("Welcome to CT8!")
#print("Great job correctly setting up this codespace")
#print("We will be using this site for the majority of the projects for this class")
#print("Make sure you bookmark this page using the STAR icon in the top right corner of your browser")
#input("\n---Press Enter when you have bookmarked the page---\n")


#print("\n\n")
#print("Now, try to view the display screen")
#print("To view the display screen:")
#print("\t1: click PORTS on the menu bar above this text")
#print("\t2: move your mouse over the words in blue that start with https://")
#print("\t3: a few icons should appear - click the globe")
#print("\t4: a new tab will open - click CONNECT")
print("\n\nWhen you have found the thief, press enter\n\n")
input()
print("good job!")
mySprite2 = codesters.Sprite("baseball",-210,210)