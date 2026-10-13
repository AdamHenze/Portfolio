'''
Adam Henze Chapter 6 Project Assignment
Cpt 135 Section N09
Summer 2022
'''
#Define a function for user input, retrieves hours worked and pay rate of employee from user.
def getsalary():
    hours = float(input("Please enter hours worked: \n"))#input hours worked
    rate = float(input("Please enter your rate of pay: \n"))#input rate of pay of employee
    print("\nYour weekly salary is $%.2f." %calcsalary(hours, rate))#we begin a print function to return the total pay. Within the print function we call the calcsalary function to run our calculations on the user inputs.
   
#Define a function to calculate the salary of the employee based on two inputs, hours and pay.    
def calcsalary(x,y):
    pay = float(x * y)#in the most basic sense our pay is hours * rate. expressed here as the inputs x * y.
    if (x > 40):#what if we worked overtime? If we worked more than 40 hours we need to run more calculations. So if hours was greater than 40 then...
        pay = pay + ((x - 40) * (y * .5))#we find hours over 40 by taking (hours - 40). then we multiply those remaining hours by half pay and add that to the current pay total.
    #NOTE: We only need to multiply the overtime hours by .5, instead of 1.5, because we already added the (hours * pay) initially. Meaning we only need to add the remaining (.5 * pay) to achieve an accurate overtime pay of 'Time-and-a-half'
    return pay#return the calculated total pay of the employee
     
#begin program
#note: no variables are declared outside of functions
#call getsalary, all portions of program run therein     
getsalary()
#End program
