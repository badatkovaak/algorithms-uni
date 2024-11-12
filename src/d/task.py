n, m = map(int, input().split(" "))

if n > m:
    a, b = n, m
else:
    a, b = m, n

while a != 0 and b != 0:
    a, b = b, a % b

print(a)
