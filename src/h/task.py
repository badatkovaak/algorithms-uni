with open("input.txt") as f:
    s = f.readlines()[1]

values = [0 for _ in range(11)]

for i in map(int, s.split(" ")):
    values[i] += 1

for i, value in enumerate(values):
    for j in range(value):
        print(i, end=" ")

print()
