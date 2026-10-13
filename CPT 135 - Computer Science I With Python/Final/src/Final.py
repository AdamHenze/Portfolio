'''
Adam Henze Final: Question 11
Cpt 135 Section N09
Summer 2022
'''
#function for asking for input
def getinput(x):
    print(x,'Please Select 1, 2, or 3:\n'
            '1: ROCK\n'
            '2: PAPER\n'
            '3: SCISSORS')
    selection = (getint())
    return selection

#function for getting correct int input
def getint():
    try:
        userinput = int(input('    #:'))
    except:
        print('Invalid Input')
        userinput = (getint())
    if (userinput < 1 or userinput > 3):
        print('Please select 1 - 3.')
        userinput = (getint())
    return userinput

#function for comparing answers
def compare(p1, p2):
    #only 3 possible outcomes, draw, or either player wins. Using if/else to print winner to keep it fast and simple for final
    if (p1 == 1):
        if(p2 == 1):
            print('Draw...')#same inputs draw
        elif(p2 == 2):
            print('Player 2 Wins!')
        elif(p2 == 3):
            print('Player 1 Wins!')
    elif(p1 == 2):
        if(p2 == 1):
            print('Player 1 Wins!')
        elif(p2 == 2):
            print('Draw...')#same inputs draw
        elif(p2 == 3):
            print('Player 2 Wins!')
    elif(p1 == 3):
        if(p2 == 1):
            print('Player 2 Wins!')
        elif(p2 == 2):
            print('Player 1 Wins!')
        elif(p2 == 3):
            print('Draw...')#same inputs draw
    return 

#function for running program
def runtime():
    selection1 = getinput('Player 1')#get player one selection
    selection2 = getinput('Player 2')#get player two selection
    compare(selection1, selection2) #compare prints winner
    return

#call runtime to run game
runtime()
#end code