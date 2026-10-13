'''
Adam Henze Chapter 5 Project Assignment
Cpt 135 Section N09
Summer 2022
'''

#begin while loop to display 1-10 and the squares of 1-10
i = 1#define counter variable
while( i <= 10):#count to 10
    icubed = i * i#return i * i finding square of current count
    print("The square of %d is %d" %(i, icubed))#print values
    i = i + 1#increase count and loop

#begin factorial portion of project    
x = int(input("\nPlease Enter a number to display the factorial of:\n"))#user input of an integer as x, we could use x as a counter however we would like to return the users initial input later on
y = x #set y as counter equal to user input
z = x #define z as the factorial value to be returned, set to x for if x == 1 then no factorial multiplication occurs

#Personal Addition: Ask user to show the math of the integer multiplied by the integer values trending to 0
#this was initially added to help me check the math involved so I wrote an IF statement around it rather than remove the code
print("\nWould you like to have math shown? Note:(Larger integers will produce longer strings of multiplications)")
print("Enter Y for yes or N for no")
showmath = input()#user answer
showmath = showmath.lower().strip()#normalize string, learned in project 7

if( showmath == "y"):#if math is to be shown then print lines of descending integers multiplying initial value x
    print("\nThe factorial of %d is %d multplied by..." %(y,y))#print the users input

#begin mathematical factorial function. A factorial as an integer multiplied by all integers below it greater than zero.
#creating a loop that counts down from the initial value and multiplies by the current count will reproduce a factorial function.  
while( y > 1):#remember y was set as our counter above. NOTE: the loop does not run on a Y value of 1 as there is no mathematical need to multiply by 1
    y = y - 1#begin by reducing y by one so we do not multiply the initial integer by itself, giving an incorrect value.
    z = z * y#z is the final factorial value we seek to return, since z was set to x, we multiply by the descending y values down to 2, again no need to multiply by 1 as it returns the same value.
    if( showmath == "y"):#if math is to be shown then the loop checks and prints the current integer multiplication
        print("multiplied by %d is %d..." %(y,z))#print current factor and return value


print("\nThe factorial of %d is equal to %d" %(x,z))#print final factorial
#end program