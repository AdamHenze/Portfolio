'''
Adam Henze Chapter 12 Project Assignment
Cpt 135 Section N09
Summer 2022
'''
#Professor Deepika Jagmohan

#Thank you for the instruction and introduction into python this summer semester. 
#I found this course very entertaining, valuable, and look forward to further studies into programming.

#The project rubric was unclear as to whether or not the file should be opened a single time on startup and only written on quit. 
#So hopefully it was not too liberal for me to open and close the file more than once.
#One way to handle the current balance would be to retrieve it once from the file on start, store into a variable, close file, then write at the end of operations.
#to me this seemed rather simple and would also not save the file after every transaction, and would only save on exit. 
#Hypothetically what if the user deposits money, but the app or hypothetical machine fails before quit is called? 
#Then no change would occur to the users account balance and we would have lost the transaction, information, and hypothetical money.
#To me writing after every withdraw and deposit seemed like a safe method to secure the account value after every transaction.
#if the program was rewritten to append onto the text file, then store and output the sequential values therein, writing to the file after every transaction could then provide a transaction and account balance history
#the functions below also could be made more useful by allowing for input of the file name through function parameters to potentially declare any users file to be read 
 
#no global variables outside of functions
#functions progressively save file throughout operations for security

#function to run application
def runtime():
    print('***Welcome, Thank you for choosing our ATM***')#greet user with message on startup
    current = checkbalance()#call checkbalance to variable to set initial dollar amount of account for withdraws and deposits    
    userinput = 0#loop variable

    while( userinput == 0):#loop while x = 0, loops until appquit() exits application
        print('Please select an action:\n'
              '1: Check\n'
              '2: Deposit\n'
              '3: Withdraw\n'
              '4: Quit')
        userinput = (getint())#get input for action
        if (userinput == 1):#check balance
            current = checkbalance()#set current balance with checkbalance() 
        elif (userinput == 2):#deposit from account
            deposit()
            current = checkbalance()#set current balance with checkbalance()
        elif (userinput == 3):#withdraw from account
            withdraw()
            current = checkbalance()#set current balance with checkbalance()
        elif (userinput == 4):#quit application
            appquit(current)
        else:
            print('***Select 1-4 only please***')#error on unserinput != {1-4} and loop 
        userinput = 0
        print('---------------------------------------------')
    return

#function to deposit funds    
def deposit():
    current = checkbalance()#set current balance with checkbalance()
    print('Deposit amount:')#user prompt
    newdeposit = (getfloat())#get deposit amount
    total = current + newdeposit#add deposit to current amount
    inputfile = open('project_read.txt','w')#open file
    inputfile.write(str(total))#write new total to file
    inputfile.close()#close file
    return()

#function to withdraw funds    
def withdraw():
    current = checkbalance()#set current balance with checkbalance()
    print('Withdraw amount:')#user prompt
    newwithdraw = (getfloat())#get attempted withdraw amount
    if(newwithdraw > current):#if withdraw too large (greater than current) then make no changes, error statement, and return
        print('***TRANSACTION ABORTED: May not withdraw more than current balance***')#error
    else:#if pass to withdraw then...
        total = current - newwithdraw#subtract withdraw from current amount
        if total < 100:#if new total is less than 100 then...
            print('***WARNING: Balance less than $100***')#warning statement to user 
        inputfile = open('project_read.txt','w')#open file
        inputfile.write(str(total))#write new total to file
        inputfile.close()#close file
    return()

#function to check and return current balance
def checkbalance():
    inputfile = open('project_read.txt')#open file
    balance = float(inputfile.read())#set balance
    inputfile.close()#close file
    print('Your current balance is: $%.2f' %balance)#print balance from within balance inquiry to meet project rubric 
    return balance#return balance of account from file

#the project rubric was clear that the quit function should write to file. 
#Even though the other functions keep the file updated I still used quit to write the file to meet those guidelines.
#function to quit application, function passed current total to write final account total to file
def appquit(current):#pass current total for quit function to write to file
    #if other functions were rewritten to only perform mathematical operations on the variable that stores the account value, then appquit would still write the current total to file 
    print('Are you sure you would like to quit? \n1:Yes\n2:No')#user prompt
    x = 0
    while (x == 0):#keep asking till yes or no
        x = (getint())
        if (x == 1):#1 for yes and quit
            inputfile = open('project_read.txt','w')#open file
            inputfile.write(str(current))#write new total to file
            inputfile.close()#close file
            print('***Goodbye, Thank you for choosing our ATM***')#user salutations 
            print('Quitting Application...')
            exit()#end
        if (x == 2):#2 for no and simply exits function
            return
        else:
            print('***Select 1 or 2 only please***')#else for int inputs != 1 or 2
            x = 0
    return

#function to try for float input, error statement if not
def getfloat():
    try:
        x = float(input('    $:'))#try for float input
        round(x,2)#round float to 2 for simple handling of cent values.
    except:
        print('***Integer or Float input only please***')#error
        x = (getfloat())#loop on error
    return(x)

#function to try for int input, error statement if not
def getint():
    try:
        x = int(input('    #:'))#try for int input
    except:
        print('***Integer inputs only please***')#error
        x = (getint())#loop on error
    return(x)

runtime()#call runtime to run program
#end code
