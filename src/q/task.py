with open("input.txt") as f:
    s = f.readlines()
    pattern = s[0][:-1]
    text = s[1][:-1]

pos = 0
end = len(text)
pt_len = len(pattern)
indicies = []

# if

while pos < end:
    for i, v in enumerate(pattern):
        if pos >= end:
            break

        if text[pos] != v:
            pos -= i
            break

        pos += 1
    else:
        indicies.append(pos - len(pattern))
        pos -= len(pattern)

    pos += 1

for i in indicies:
    print(i, end=" ")
print()
