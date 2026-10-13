'''
Adam Henze Chapter 3 Project Assignment
Cpt 135 Section N09
Summer 2022
'''
#import ceil function
from math import ceil

#Initial variables and dictionaries.
gallonsqft = 350 #Coverage of a single gallon of paint
colorcost = {'red': 35,'blue': 25,'green': 23} #Dictionary of paint color prices

#Begin prompt for user input of wall dimensions
print("Enter wall height (feet):")
x = int(input())
print("Enter wall width (feet):")
y = int(input())
print("Wall area:",x*y,"square feet" ) #Area = height * width

#Begin paint portion of program 
gallons = float((x*y) / gallonsqft) #Gallons needed = to Area / gallon coverage
print("Paint needed: %f gallons" %gallons)
cans = ceil(gallons) #round gallons up to integer, stored as cans
print("Cans needed: %d can(s)" %cans)
print("\nChoose a color to paint the wall:")
color = input()#ask user for color input
print("Cost of purchasing %s paint:" %color)
print("$%d" %colorcost[color])#return dictionary value based on user color input
#end of program