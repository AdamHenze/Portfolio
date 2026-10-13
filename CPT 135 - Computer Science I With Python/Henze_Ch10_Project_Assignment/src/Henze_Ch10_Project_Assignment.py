'''
Adam Henze Chapter 10 Project Assignment
Cpt 135 Section N09
Summer 2022
'''

#The chapter 10 assignment rubric specifically stated to download and use our previous chapter 2 assignment and add try exceptions to that program.
#Below is my exact assignment 2 program that has had try exceptions added as error handling. This has been commented out in order to run a more updated code.
#I could not implement other features I wanted into the program to challenge myself without rewriting the old code. 
#If you would like to see the old chapter 2 program run with try exceptions please de-comment this code and comment out the new program. Thank you.
#I did not want to take extreme liberties on the project without also turning in another instance of the program that clearly met guidelines. 

#------------------------------------------------------------------------Old Program--------------------------------------------------------------------

'''
#begin the first try statement for the first item on the receipt
try:
    #Begin print and input statements for first item of receipt
    print("Enter food item name:")
    item1 = str(input())#name
    print("Enter item price:")
    item1p = float(input())#price float
    print("Enter item quantity:")
    item1q = int(input())#quantity 
except ValueError:#if input fail due to value error print error statement and quit.
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
#begin the try statement for the item on the receipt
try:
    #Begin print and input statements for second item of receipt
    print("\nEnter second food item name:")
    item2 = str(input())
    print("Enter item price:")
    item2p = float(input())
    print("Enter item quantity:")
    item2q = int(input())
except ValueError:#if input fail due to value error print error statement and quit.
    print("Invalid inputs on item 2 lines. Please rerun program and check for input errors.")
    exit()

#Note: If receipt item 1 and 2 both pass their try commands then we know the values will work for further arithmetic so no other code additions seem to be needed

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
'''

#------------------------------------------------------------------------New Program--------------------------------------------------------------------
#using the tools weve learned in new chapters I wanted to update this old project to have more features and to challenge myself.



#defining an object for receipt items creates a very useful class we can use to simply store the similar data of all receipt items.
class receipt_item:
    def __init__(self, number):#we pass the initializer an integer from the while loop below to store item position on receipts
        self.number = number#item position
        self.name = ''#item name
        self.price = 0#item price
        self.quant = 0#item quantity
        self.total = 0#total cost of item price * quantity

    def setdata(self,x,y,z):#sets data of receipt item based on information passed to function
        self.name = x
        self.price = float(y)
        self.quant = int(z)
        self.total = self.price * self.quant #price * quantity == total
    
    def printdata(self):#function to print item receipt info.
        #declare placeholder variables for proper formatting in print statement 
        itemq = self.quant
        item = self.name
        itemp = self.price
        itemtotal = self.total
        print(f'{"%d %s @ $ %.2f = $ %.2f":>50}' %(itemq, item, itemp, itemtotal)) #align 50 characters to the right for readability
    
def collectdata(receipt_item):#function to collect data from user for individual receipt item
    try:#try except
        name = input('name:\n     ')
        price = float(input('price:\n     '))
        quant = int(input('quantity:\n     '))
        receipt_item.setdata(name, price, quant)#if all inputs clear without error then we proceed to set data of item 
    except:
        print('Invalid input on item lines. Please check for input errors and continue:')#if error occurs we issue error statement to user
        print('--------------------------------------------------------------------------------------')#spacer
        collectdata(receipt_item)#NOTE:If an error occurs the exception will recall the function to attempt to retry with the user correcting their inputs, rather than having to rerun the program
        #I know what recursion is but that is about all I know. I was very proud to eventually have the function call itself to allow the program to keep running. 
    
def runtime():#define function to run program
    try:#try for user input of item quantity, users can input any number of items
        x = int(input('Input the total number of items:\n     '))
        y = 0#while counter
        receipt = []
        
        while (y < x):#loop for the number of items, each loop appends new object into receipt
            y = y + 1  
            item = receipt_item(y)#we pass y to declaration function to store item position
            print('Item number:', item.number)#print position
            collectdata(item)#collect data for item
            receipt.append(item)#add receipt item object to receipt list
            item.printdata()#print item financial data
            print('--------------------------------------------------------------------------------------')#spacer and loop
         
        total = 0#declare total cost
        print()
        print(f'{"RECEIPT":>32}')    
        for i in receipt:#loop through receipt list of objects, print data, update total cost value with item totals
            i.printdata()
            total = float(total + i.total) 
               
        print('--------------------------------------------------------------------------------------')   
        print(f'{"Total cost: $ %.2f":>50}' %total)#print total without tip calc
        
        gratutity = float(total * 0.15)#declare gratuity to store tip %
        print('--------------------------------------------------------------------------------------')
        #Total receipt costs plus gratuity and print
        print(f'{"15%% gratuity: %.2f":>50}' %gratutity)
        print(f'{"Total with tip: $ %.2f":>50}' %(total+gratutity))
    except:#if user input caused crash then runtime is recalled during the exception to allow the program to continue
        print('Invalid input on item quantity. Please check for input errors and continue:')
        print('--------------------------------------------------------------------------------------')
        runtime()#rerun runtime

runtime()#call runtime to run program
