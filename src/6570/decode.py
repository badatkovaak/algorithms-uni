with open("input.txt") as f:
    s = f.readlines()

k, l = s[0].split()
codes = dict(map(lambda x: (x.split(":")[0], int(x.split(":")[1])), s[1:-1]))
string = s[-1]

i = 0
while True:
    pattern = ""

    while not pattern in codes:
        pattern += string[i]
        i += 1
