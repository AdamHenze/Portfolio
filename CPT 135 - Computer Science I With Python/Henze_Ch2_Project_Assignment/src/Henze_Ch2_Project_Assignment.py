'''
Adam Henze Chapter 2 Project Assignment
Cpt 135 Section N09
Summer 2022
'''
try:
    #Begin print and input statements for first item of receipt
    print("Enter food item name:")
    item1 = str(input())#name
    print("Enter item price:")
    item1p = float(input())#price float
    print("Enter item quantity:")
    item1q = int(input())#quantity 
except ValueError:
    print("Invalid inputs on item 1 lines. Please rerun program and check for input errors.")
    exit()
    
#total item costs based on price * quantity
item1total = float(item1p * item1q)

#print receipt 
print("\nRECEIPT")
print("%d %s @ $ %.2f = $ %.2f" %(item1q, item1, item1p, item1total))

#Total receipt costs and print
receipttotal = float(item1total)
print("Total cost: $ %.2f" %receipttotal)

try:
    #Begin print and input statements for second item of receipt
    print("\nEnter second food item name:")
    item2 = str(input())
    print("Enter item price:")
    item2p = float(input())
    print("Enter item quantity:")
    item2q = int(input())
except ValueError:
    print("Invalid inputs on item 2 lines. Please rerun program and check for input errors.")
    exit()
#total item costs based on price * quantity
item2total = float(item2p * item2q)
#Total receipt costs
receipttotal = float(item1total + item2total)

#print total receipt
print("\nRECEIPT")
print("%d %s @ $ %.2f = $ %.2f" %(item1q, item1, item1p, item1total))
print("%d %s @ $ %.2f = $ %.2f" %(item2q, item2, item2p, item2total))
print("Total cost: $ %.2f" %receipttotal)

#multiply total by gratuity percentage to receive tip amount
gratutity = float(receipttotal * 0.15)

#Total receipt costs plus gratuity and print
print("\n15%% gratuity: %.2f" %gratutity)
print("Total with tip: $ %.2f" %(receipttotal+gratutity))
#end program