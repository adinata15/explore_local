import numpy as np

def input_file(path: str):
    inputs = np.empty(1000, dtype='U')
    with open(path, 'r') as file:
        for line in file:
            np.append(inputs, line)

    return inputs

def part1():
    res = 0
    curr = 50
    with open('input.txt', 'r') as file:
        for line in file:
            num = int(line[1:])
            if(line[0] == 'L'):
                curr = (curr + 100 - num) % 100 
            elif(line[0] == 'R'):
                curr = (curr + num) % 100 

            if(curr == 0): res += 1

    return res

def part2():
    res = 0
    curr = 50
    isZero = False
    with open('input.txt', 'r') as file:
        for line in file:
            num = int(line[1:])
            if(line[0] == 'L'):
                curr -= num
            elif(line[0] == 'R'):
                curr += num

            if(curr >= 100): res += abs(curr//100)
            elif(curr <= 0): res += (1 + abs(curr)//100 - isZero) 

            curr %= 100

            if(curr == 0): isZero = True
            else: isZero = False

    return res

print("F:", part2())