'''
Adam Henze Chapter 8 Project Assignment
Cpt 135 Section N09
Summer 2022
'''



#Ambitiously I had tried to program a version that would store names and the entry position in a nested list. 
#I was able to challenge myself a bit with operating on the nested list but the program had gone beyond the project parameters quite a bit, and was much more complex for similar operations here.
#Out of time, I ultimately decided to walk the program back to a working version that clearly met the project parameters. 

#Define function for user input. This is done because I intended to further define other functions and had for calculations and printing but did not have a chance to optimize in this way.
def getinput():
    weighttable = []#define a list the we will use for our weights
    pop = int(input("Enter the number of weighed individuals:\n"))#Although the project called for 4 individuals I saw that it was rather easy to expand this to work with any number. We ask the user for the group size and define pop as this number.
    count = 0#define a counter to check against population
    while (count < pop):#while count less than pop
        weight = float(input("Enter a weight for Individual %d:\n" %count))#prompt user to enter a weight for the current individual
        weight = round(weight,2)#use round function to reduce to two decimal places
        weighttable.append(weight)#append this weight to the list of weights
        count = count + 1 #add count and loop
   
    print("----------------------------------------------------------------")#spacer
    print("Your list of weights is:")
    print(weighttable)    #print current table before operations
    print("----------------------------------------------------------------")#spacer    
    print('The average weight of the group is %.2f.' %(sum(weighttable) / pop)) #retrieve average weight by dividing sum of all weights over population 
    print("The heaviest individual weighs %.2f." %max(weighttable))#print the max value of weight table for heaviest individual
    print("----------------------------------------------------------------")#spacer    
    selection = int(input("select a number between 1 and %d to display the weight of that individual:\n" %pop))#ask user a position to retrieve from original table. store as variable
    print("That individual weighs %.2f." %weighttable[selection - 1])#print weighttable(selection - 1) to retrieve position declared by user as table positions start with 0
    print("----------------------------------------------------------------")#spacer    
    print("The weights from lightest to heaviest are:")
    weighttable.sort()#sort table based on values, since our table is only numbers this will very easily list our items from smallest to largest.
    print(weighttable)#print sorted table

#run input function to run program     
getinput()
#end