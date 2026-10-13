'''
Adam Henze Chapter 7 Project Assignment
Cpt 135 Section N09
Summer 2022
'''

#begin program
word = input("Please input a word to check if it is a palindrome:\n")#user input of string
word = word.strip().lower()#normalize string, removing surrounding white-spaces and case shifting to lowercase
#I was initially going to check the strings individual characters on both ends moving towards the center character, and if all characters displayed symmetry over the center point then that would indicate a palindrome
#However after much trial and error I realized it would be much much easier to flip the string and then check if it is equal to itself once reversed
#Since there is no built in function to reverse a string we need to come up with some way to do so. 
#the simplest way I could find to reverse a string is to slice it, with no upper and lower bounds, with an interval of negative one
#the returned string will be one built by the initial string but starting from the back moving towards the beginning of the string, effectively reversing it 
reverse = word[::-1]#so we slice with no bounds on an interval of -1
print("The word you entered was %s." %word)#return initial string
print("The word you entered reversed is %s." %reverse)#return reversed string

if (word == reverse):#check to see if both strings match
    print("Your word is a palindrome.")#yes == palindrome
else:
    print("your word is not a palindrome.")#no != palindrome
#end program 