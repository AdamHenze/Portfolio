'''
Adam Henze Chapter 4 Project Assignment
Cpt 135 Section N09
Summer 2022
'''

#declare initial service and price dictionary
prices = {"Oil change": 35, "Tire rotation": 19, "Car wash": 7, "Car wax": 12}

#print opening statements of services and prices
print("Davy's auto shop services")
print("Oil change -- $35")
print("Tire rotation -- $19")
print("Car wash -- $7")
print("Car wax -- $12\n")

#prompt user input for services
print("Select first service:")
service1 = input()
print("Select second service:")
service2 = input()

#begin invoice
print("\nDavy's auto shop invoice\n")
#declare total cost float
total = float(0.00)

#check for inputs to match service dictionary
if service1 in prices:
    #print service selected and update total
    print("Service 1: %s, $%d" %(service1, prices[(service1)]))
    total = total + prices[service1]
else:
    #unrecognized services bypass receipt total
    print("Service 1 not recognized")
if service2 in prices:
    #print service selected and update total
    print("Service 2: %s, $%d" %(service2, prices[(service2)]))
    total = total + prices[service2]
else:
    #unrecognized services bypass receipt total
    print("Service 2 not recognized")

#print total costs    
print("Total: $%.2f" %total)    
#end program