def merge(A, B, begin, mid, end):
    i = begin
    j = mid

    print(i, j)
    print("before", B)

    for k in range(begin, end):
        if i < mid and (j >= end or A[i] <= A[j]):
            print("picked 1", A[i], i, j, k)
            B[k] = A[i]
            i += 1
        else:
            print("picked 2", A[j], i, j, k)
            B[k] = A[j]
            j += 1
    print("after", B)


def merge_split(A, B, begin, end):
    if end - begin <= 1:
        return

    mid = (begin + end) // 2

    print(B, begin, mid, end)

    merge_split(A, B, begin, mid)
    merge_split(A, B, mid, end)

    merge(A, B, begin, mid, end)


def merge_sort(A):
    B = [i for i in A]
    merge_split(A, B, 0, len(A))
    return B


with open("input.txt") as f:
    s = f.readlines()

array = list(map(int, s[1].split(" ")))
print(array)
print(merge_sort(array))
