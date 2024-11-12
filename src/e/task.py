with open("input.txt") as f:
    s = f.readlines()

array = list(map(int, s[0].split(" ")[1:]))
values = map(int, s[1].split(" ")[1:])
length = len(array)
en_array = list(enumerate(array))

for value in values:
    for i, v in en_array:
        if v == value:
            print(i + 1, end=" ")
            break
    else:
        print(-1, end=" ")
