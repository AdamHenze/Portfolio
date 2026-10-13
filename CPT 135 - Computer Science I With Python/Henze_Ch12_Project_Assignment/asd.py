# Python 3
# Author: Nancy Barton, Thomas Cholak, Adam Henze
# August 30th, 2023
# CMP_SCI-4500

import random
from prettytable import PrettyTable


# This function creates the movements for the players
def PROTOCOL_4(position, dim):
    x, y = position

    direction = random_direction1()

    if direction == 'north' and y < dim - 1:
        return x, y + 1
    elif direction == 'south' and y > 0:
        return x, y - 1
    elif direction == 'east' and x < dim - 1:
        return x + 1, y
    elif direction == 'west' and x > 0:
        return x - 1, y
    return x, y


def PROTOCOL_8(position, dim):
    x, y = position

    while True:

        direction = random_direction2()

        if direction == 'north':
            if y == dim:
                continue
            else:
                return x, y + 1
        elif direction == 'south':
            if y == 0:
                continue
            else:
                return x, y - 1
        elif direction == 'east':
            if x == dim:
                continue
            else:
                return x + 1, y
        elif direction == 'west':
            if x == 0:
                continue
            else:
                return x - 1, y
        elif direction == 'southeast':
            if y == 0 or x == dim:
                continue
            else:
                return x + 1, y - 1
        elif direction == 'northwest':
            if y == dim or x == 0:
                continue
            else:
                return x - 1, y + 1
        elif direction == 'southwest':
            if x == 0 or y == 0:
                continue
            else:
                return x - 1, y - 1
        elif direction == 'northeast':
            if y == dim or x == dim:
                continue
            else:
                return x + 1, y + 1


# This will generate the random direction for both players
def random_direction1():  # for PROTOCOL_4
    directions = ['north', 'south', 'east', 'west']
    return random.choice(directions)


def random_direction2():  # for PROTOCOL_8
    directions = ['north', 'south', 'east', 'west', 'southeast',
                  'southwest', 'northeast', 'northwest']
    return random.choice(directions)


# This will create the game, grid and players.
# This will also indicate if the both player either landed on the same spot or not.
def play_game(dimension, maxMoves, P):
    # this needed to be explicitly scoped to work with the rest
    dim = int(dimension)
    moves = int(maxMoves)
    turns = 0

    if P == 4:  # Assigns a different protocol depending on the 'P' value
        protocol = PROTOCOL_4
    else:
        protocol = PROTOCOL_8

    # start the players at their initial spots
    personA_pos = (0, 0)
    personB_pos = (dim, dim)

    # this while loop will continue to run and give each player their turn
    # it will stop after the maxMoves have been met
    while moves > 0:

        moves -= 1
        turns += 1

        personA_pos = protocol(personA_pos, dim)  # PersonA moves

        if personA_pos == personB_pos:
            return turns

        personB_pos = protocol(personB_pos, dim)  # PersonB moves

        # Prints coordinates
        # print(f"Person A: {personA_pos}, Person B: {personB_pos}")

        # if statement t check if the players landed on the same spot.
        if personA_pos == personB_pos:
            return turns

    return turns


# function below is from: https://www.geeksforgeeks.org/python-program-to-find-largest-element-in-an-array/
def largest(arr, n):
    arr.sort()
    return arr[n - 1]


def experiment_1(D, P, R, M):
    stack = []
    lists = []

    length = len(D)  # Measures the length of the 'D' array

    for i in range(length):
        for j in range(R):
            stack.append(play_game(D[i], P, P))

    # for-loop below modified from: https://geeksforgeeks.org/break-list-chunks-size-n-python/
    for i in range(0, len(stack), R):
        x = i
        lists.append(stack[x:x + R])

    Lo, Hi, Av = sorting(length, lists)

    x = PrettyTable()
    x.field_names = ["Dimensions", "Maximum Moves", "Number of Repeats", "Protocol",
                     "Lowest Moves", "Highest Moves", "Average Moves"]

    for i in range(length):
        x.add_row([D[i], P, R, M, Lo[i], Hi[i], Av[i]], divider=True)

    with open("outdata.txt", "w") as file:
        file.write("Experiment #1\n")
        file.write(str(x))


def experiment_2(R, D, M, P):
    stack = []
    lists = []


    # https: // www.geeksforgeeks.org / python - converting - all - strings - in -list - to - integers /
    R_array = [eval(i) for i in R]
    length = len(R_array)  # Measures the length of the 'D' array

    for i in range(length):
        for j in range(R_array[i]):
            stack.append(play_game(D, M, P))

    start = 0

    # array modified from: https://www.askpython.com/python/examples/colon-in-python
    for i in range(length):  # Subdivides into arrays of 'R[n]' length
        end = start + (R_array[i])
        lists.append(stack[start:end])
        start = end

    Lo, Hi, Av = sorting(length, lists)

    x = PrettyTable()
    x.field_names = ["Number of Repeats", "Dimensions", "Maximum Moves", "Protocol",
                     "Lowest Moves", "Highest Moves", "Average Moves"]

    for i in range(length):
        x.add_row([R_array[i], D, M, P, Lo[i], Hi[i], Av[i]], divider=True)

    with open("outdata.txt", "a") as file:
        file.write("\nExperiment #2\n")
        file.write(str(x))

def experiment_3(P, D, M, R):
    stack = []
    lists = []

    length = len(P)  # Measures the length of the 'D' array

    for i in range(length):
        for j in range(R):
            stack.append(play_game(D, M, P))

    # for-loop below modified from: https://geeksforgeeks.org/break-list-chunks-size-n-python/
    for i in range(0, len(stack), R):
        x = i
        lists.append(stack[x:x + R])

    Lo, Hi, Av = sorting(length, lists)

    x = PrettyTable()
    x.field_names = ["Protocol", "Dimensions", "Maximum Moves", "Repeats",
                     "Lowest Moves", "Highest Moves", "Average Moves"]

    for i in range(length):
        x.add_row([P[i], D, M, R, Lo[i], Hi[i], Av[i]], divider=True)

    with open("outdata.txt", "a") as file:
        file.write("\nExperiment #3\n")
        file.write(str(x))

def sorting (data_len, data_list):

    Lo = []
    Hi = []
    Av = []

    for i in range(data_len):
        Hi.append(largest(data_list[i], len(data_list[i])))

    for i in range(data_len):  # sorts by least to greatest and then returns first value
        data_list[i].sort()
        Lo.append(data_list[i][0])

    for i in range(data_len):
        Av.append(round((sum(data_list[i]) / len(data_list[i])), 3))

    return Lo, Hi, Av

if __name__ == '__main__':

    with open('indata.txt') as f:
        lines = [line.rstrip('\n') for line in f]

    output = []

    for item in lines:
        parts = item.split(',')
        output.append(parts)

    D1 = list(output[0])
    P1 = int(output[1][1])
    R1 = int(output[1][2])
    M1 = int(output[1][0])

    R2 = list(output[2])
    D2 = int(output[3][0])
    M2 = int(output[3][2])
    P2 = int(output[3][1])

    P3 = list(output[4])
    D3 = int(output[5][0])
    M3 = int(output[5][1])
    R3 = int(output[5][2])

    experiment_1(D1, P1, R1, M1)

    experiment_2(R2, D2, M2, P2)

    experiment_3(P3, D3, M3, R3)
