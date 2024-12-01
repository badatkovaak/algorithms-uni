from typing import Dict, List, Tuple
from copy import deepcopy
from sys import setrecursionlimit


setrecursionlimit(100000)


def calculate(
    goal: int, n: int, cache: Dict[int, Tuple[int, List[int]]], depth: int
) -> Tuple[int, List[int]]:
    res1, res2, res3 = (100001, []), (100001, []), (100001, [])

    if n in cache:
        # print("returned early 11", n)
        return deepcopy(cache[n])

    if depth >= cache[0][0]:
        # print("returned early 22", n)
        return deepcopy(cache[0])

    if n >= goal:
        result = (0, [n])
        return result

    if 3 * n <= goal:
        res1 = calculate(goal, 3 * n, cache, depth + 1)

    if 2 * n <= goal:
        res2 = calculate(goal, 2 * n, cache, depth + 1)

    if n + 1 <= goal:
        res3 = calculate(goal, n + 1, cache, depth + 1)

    result = min(res1, res2, res3, key=lambda x: x[0])

    result = (result[0] + 1, result[1])
    result[1].append(n)

    # print(n, result[0], depth, cache[0])

    # assert len(result[1]) == result[0] + 1

    # if n in cache:
    #     cache[n] = min(cache[n], result, key=lambda x: x[0])
    # else:
    cache[n] = deepcopy(result)

    if cache[0][0] > result[0] + depth:
        cache[0] = (result[0] + depth, [])

    return result


# class Direction(Enum):
#     Backward = auto()
#     Forward = auto()


# def calculate_stack(goal: int) -> Tuple[int, List[int]]:
#     cache: Dict[int, Tuple[int, List[int]]] = {}
#     stack = deque([(Direction.Forward, 1)])
#
#     while len(stack) > 0:
#         (type, n) = stack.pop()
#
#         match type:
#             case Direction.Forward:
#                 if n in cache:
#                     continue
#
#                 if n >= goal:
#                     cache[n] = (0, [n])
#                     continue
#
#                 stack.append((Direction.Backward, n))
#
#                 if 3 * n <= goal:
#                     stack.append((Direction.Forward, 3 * n))
#                 if 2 * n <= goal:
#                     stack.append((Direction.Forward, 2 * n))
#                 if n + 1 <= goal:
#                     stack.append((Direction.Forward, n + 1))
#
#             case Direction.Backward:
#                 if n in cache and cache[n][0] == 0:
#                     continue
#
#                 a = filter(
#                     lambda x: x is not None,
#                     [cache.get(3 * n), cache.get(2 * n), cache.get(n + 1)],
#                 )
#
#                 result = deepcopy(min(a, key=lambda x: x[0]))
#                 result = (result[0] + 1, result[1])
#                 result[1].append(n)
#
#                 if n in cache:
#                     cache[n] = min(result, cache[n], key=lambda x: x[0])
#                 else:
#                     cache[n] = result
#
#     return cache[1]


with open("input.txt") as f:
    n = int(f.readline()[:-1])

# n = int(input())
cache = {0: (100001, [])}
result = calculate(n, 1, cache, 0)
# result = calculate_stack(n)
print(cache[0])

print(result[0])

for i in reversed(result[1]):
    print(i, end=" ")

print()
