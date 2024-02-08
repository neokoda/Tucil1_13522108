import random

num_tokens = 0
tokens = []

buffer_size = 0
buffer = []

matrix_size = []
matrix = []

num_sequence = 0
sequences = []
max_sequence_size = 0

class Sequence:
    def __init__(self, sequence_array, size, reward):
        self.sequence_array = sequence_array
        self.size = size
        self.reward = reward

def display_matrix(matrix):
    for i in range(len(matrix)):
        for j in range(len(matrix[i])):
            print(matrix[i][j], end=' ')
        print()

def generate_sequence():
    global max_sequence_size, tokens

    sequence_size = random.randint(2, max_sequence_size) 
    sequence_array = [tokens[random.randint(0, (num_tokens - 1))] for i in range(sequence_size)]
    reward = random.randint(10, 50)

    sequence = Sequence(sequence_array, sequence_size, reward)
    return sequence

def read_from_input():
    global num_tokens, tokens, buffer_size, matrix_size, num_sequence, max_sequence_size, matrix

    num_tokens = int(input())
    tokens = input().split()
    buffer_size = int(input())
    matrix_size = list(map(int, input().split()))
    num_sequence = int(input())
    max_sequence_size = int(input())

    matrix = [['' for i in range(matrix_size[1])] for j in range(matrix_size[0])]
    for i in range(matrix_size[0]):
        for j in range(matrix_size[1]):
            matrix[i][j] = tokens[random.randint(0, (num_tokens - 1))]

    for i in range(num_sequence):
        sequences.append(generate_sequence())

def display_info():
    global num_tokens, tokens, buffer_size, matrix_size, num_sequence, max_sequence_size, matrix

    print("num_tokens:", num_tokens)
    print("tokens:", tokens)

    print("buffer_size:", buffer_size)
    print("buffer:", buffer)

    print("matrix_size:", matrix_size)
    print("matrix:")
    display_matrix(matrix)

    print("num_sequence:", num_sequence)
    print("sequences:")
    for i in range(num_sequence):
        display_sequence_info(seq)
    print("max_sequence_size:", max_sequence_size)

    

read_from_input()
display_info()