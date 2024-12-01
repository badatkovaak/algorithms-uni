from copy import deepcopy
from typing import Dict, List


def biggest_non_increasing_subseq(
    array: List[int], start_index: int, cache: Dict[int, List[int]], start_value=10001
):
    if start_index in cache:
        return deepcopy(cache[start_index])

    if len(array) - start_index <= 1:
        if array[-1] <= start_value:
            return [start_index]
        else:
            return []

    local_start = array[start_index]

    result = []

    for i in range(1, len(array) - start_index):
        if array[start_index + i] <= local_start:
            c = biggest_non_increasing_subseq(
                array, start_index + i, cache, local_start
            )

            if len(c) > len(result):
                result = c

    result.append(start_index)

    cache[start_index] = deepcopy(result)

    return result


with open("input.txt") as f:
    s = f.readlines()

array = list(map(int, s[1].split(" ")))
result = []
cache = {}

if len(array) == 1:
    result = [1]

for i in reversed(range(len(array) - 1)):
    c = biggest_non_increasing_subseq(array, i, cache)
    if len(c) > len(result):
        result = c

l = len(result)

print(l)

for i in range(l):
    print(result[l - 1 - i] + 1, end=" ")
