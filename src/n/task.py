from collections import deque
from typing import Dict, List, Tuple
from copy import deepcopy
from enum import Enum, auto


# def calculate(n: int):
#     cache = {}
#     temp = []
#     n_original = n
#
#     while n % 3 == 0:
#         temp.append(n)
#         n = n // 3
#
#     while n % 2 == 0:
#         temp.append(n)
#         n = n // 2
#
#     print(temp)
#
#     (num, trace) = calculate_inner(n, 1, cache)
#     trace = list(reversed(trace))
#     trace.extend(temp)
#     # r = (res[0],)
#     return (num + len(temp), trace)
#


def calculate(
    goal: int, n: int, cache: Dict[int, Tuple[int, List[int]]]
) -> Tuple[int, List[int]]:
    res1, res2, res3 = (10000, []), (10000, []), (10000, [])

    if n in cache:
        return deepcopy(cache[n])

    if n >= goal:
        result = (0, [n])
        return result

    if 3 * n <= goal:
        res1 = calculate(goal, 3 * n, cache)

    if 2 * n <= goal:
        res2 = calculate(goal, 2 * n, cache)

    if n + 1 <= goal:
        res3 = calculate(goal, n + 1, cache)

    result = min(res1, res2, res3, key=lambda x: x[0])
    result = (result[0] + 1, result[1])
    result[1].append(n)

    # if n in cache:
    #     cache[n] = min(cache[n], result, key=lambda x: x[0])
    # else:
    cache[n] = result

    return result


class Direction(Enum):
    Backward = auto()
    Forward = auto()


def calculate_stack(goal: int) -> Tuple[int, List[int]]:
    cache: Dict[int, Tuple[int, List[int]]] = {}
    stack = deque([(Direction.Forward, 1)])

    while len(stack) > 0:
        (type, n) = stack.pop()

        match type:
            case Direction.Forward:
                if n in cache:
                    continue

                if n >= goal:
                    cache[n] = (0, [n])
                    continue

                stack.append((Direction.Backward, n))

                if 3 * n <= goal:
                    stack.append((Direction.Forward, 3 * n))
                if 2 * n <= goal:
                    stack.append((Direction.Forward, 2 * n))
                if n + 1 <= goal:
                    stack.append((Direction.Forward, n + 1))

            case Direction.Backward:
                if n in cache and cache[n][0] == 0:
                    continue

                a = filter(
                    lambda x: x is not None,
                    [cache.get(3 * n), cache.get(2 * n), cache.get(n + 1)],
                )

                result = deepcopy(min(a, key=lambda x: x[0]))
                result = (result[0] + 1, result[1])
                result[1].append(n)

                if n in cache:
                    cache[n] = min(result, cache[n], key=lambda x: x[0])
                else:
                    cache[n] = result

    return cache[1]


with open("input.txt") as f:
    n = int(f.readline()[:-1])

# n = int(input())
result = calculate(n, 1, {})
# result = calculate_stack(n)

print(result[0])

for i in reversed(result[1]):
    print(i, end=" ")

print()
