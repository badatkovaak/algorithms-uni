def compute_sum(n):
    sum = 0

    for k in range(1, n + 1):
        sum += k * (n - k)

    return sum


def compute_sum2(n):
    sum = 0

    for k in range(1, n + 1):
        sum += k * (n - k) ** 3 - k * n + k * k

    return sum


s = 1

for i in range(4, 100):
    prev = s
    s = compute_sum2(i)
    print(i, s, s - (i**5 - 5 * i**3 + 4 * i) // 20)
