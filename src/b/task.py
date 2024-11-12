def fib(n):
    r1 = 1
    r2 = 1
    for _ in range(n - 2):
        r2, r1 = (r1 + r2) % 10, r2
    return r2


n = int(input())
print(fib(n))
