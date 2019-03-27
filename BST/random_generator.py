from random import randint, seed
input_set = set()
seed(341)
while len(input_set) < 10:
    input_set.add(randint(-1000, 1000))
with open("input.txt", "w") as file:
    for num in input_set:
        file.write("{}\n".format(num))
