unixpts = 0
humanpts = 0

answer = input("would you rather A) stay inside and code or B) go outside and do something")
if answer == "A":
    unixpts += 1
elif answer == "B":
    humanpts += 1

answer = input("would you rather A) touch grass or B) hiss at the sun")
if answer == "B":
    unixpts += 1
elif answer == "A":
    humanpts += 1

answer = input("would you rather A) help a grandma cross the street or B) cross yourself you need this new gaming chair")
if answer == "B":
    unixpts += 1
elif answer == "A":
    humanpts += 1

answer = input("would you rather A) eat Sid Mignone or B) eat a bagel")
if answer == "B":
    unixpts += 1
elif answer == "A":
    humanpts += 1

answer = input("would you rather A) yell at Sid Mignone or B) yell at Jack Nowka")
if answer == "B":
    unixpts += 1
elif answer == "A":
    humanpts += 1

if unixpts > humanpts:
    print("you prob play too much video games")
elif humanpts > unixpts:
    print("you are a goodie good")