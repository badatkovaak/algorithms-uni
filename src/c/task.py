from typing import List


def find_pattern(m: int):
    pattern: List[int] = [0, 1]
    i: int = 2

    while True:
        f = (pattern[i - 1] + pattern[i - 2]) % m
        pattern.append(f)

        if pattern[i] == 0:
            j = 1
            for _ in range(i - 1):
                f = (pattern[i + j - 1] + pattern[i + j - 2]) % m

                if f != pattern[j]:
                    break

                pattern.append(f)
                j += 1
            else:
                return pattern[:i]

        i += 1


s = list(map(int, input().split(" ")))
n = s[0]
m = s[1]

p = find_pattern(m)
print(p[n % len(p)])
