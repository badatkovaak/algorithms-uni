from math import floor, sqrt

n = int(input())

# s(s+1)/2 = n
# s^2 + s - 2n = 0

d = 1 + 8 * n
x = (-1 + sqrt(d)) / 2
k = int(floor(x))
s = k * (k + 1) // 2
diff = n - s

print(k)

for i in range(1, k):
    print(i, end=" ")

print(k + diff)
