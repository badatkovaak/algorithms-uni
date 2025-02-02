from typing import List


def merge(A, B, begin, mid, end) -> int:
    i = begin
    j = mid
    count = 0

    for k in range(begin, end):
        if i < mid and (j >= end or A[i] <= A[j]):
            B[k] = A[i]
            i += 1
        else:
            B[k] = A[j]
            if i < mid:
                count += mid - i
            j += 1

    return count


def merge_split(A, B, begin, end) -> int:
    if end - begin <= 1:
        return 0

    mid = (begin + end) // 2

    count = merge_split(B, A, begin, mid) + merge_split(B, A, mid, end)

    count += merge(A, B, begin, mid, end)

    return count


def count_inversions(A) -> int:
    B = [i for i in A]
    C = [i for i in A]
    return merge_split(C, B, 0, len(A))


with open("input.txt") as f:
    s = f.readlines()


array = list(map(int, s[1].split(" ")))
print(count_inversions(array))
