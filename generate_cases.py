#fuck praxis
#actually generates randomized test cases
import math, multiprocessing, os, time
from random import *

num_to_generate = 1000000

f = open("words.txt", "r")
words = f.read().split('\n')
del words[len(words) - 1]
f.close()

def get_list_of_words(num):
    return sorted([words[randint(0, len(words) - 1)] for x in range(num)])

def get_list_of_weights(num):
    L = []
    max_num = 0.0
    for x in range(num):
        weight = round(uniform(0.0, 1000000.0), 3)
        max_num = max(max_num, weight)
        L.append(weight)
    return L, max_num


def generate_cases(L, R):
    print("STARTED")
    for x in range(L, R):
        case_size = randint(10, 10000)
        word_list = get_list_of_words(case_size)
        weights = get_list_of_weights(case_size)
        weight_list = weights[0]
        max_weight = weights[1]
        file_string = str(case_size) + '\n'

        for cnt, word in enumerate(word_list):
            file_string += ' ' * (len(str(case_size)) + 1 + (len(str(max_weight)) - len(str(weight_list[cnt]))))
            file_string += str(weight_list[cnt]) + '\t' + word + '\n'
        
        f = open("fuck_praxis\\fuck_praxis" + str(x + 1) + ".txt", "w+")
        f.write(file_string)
        f.close()

t0 = time.time()

if __name__ == '__main__':
    processes = []
    for x in range(os.cpu_count()):
        processes.append(multiprocessing.Process(target = generate_cases, args = (x * int(1000000 / os.cpu_count()), (x + 1) * int(1000000 / os.cpu_count()))))

    for x in range(os.cpu_count()):
        processes[x].start()

    for x in range(os.cpu_count()):
        processes[x].join()







