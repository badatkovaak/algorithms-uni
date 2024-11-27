with open("input.txt") as f:
    s = f.readlines()

array = list(map(int, s[0].split(" ")[1:]))
values = map(int, s[1].split(" ")[1:])
length = len(array)


for value in values:
    left = 0
    right = length

    while True:
        mid = left + (right - left) // 2

        if mid >= length:
            print(-1, end=" ")
            break

        if left > right:
            print(-1, end=" ")
            break

        t = array[mid]

        if t == value:
            print(mid + 1, end=" ")
            break
        elif t > value:
            right = mid - 1
        elif t < value:
            left = mid + 1

print()
