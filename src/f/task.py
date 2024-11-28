def merge_sort(array, start=0, end=None):
    if end is None:
        end = len(array)

    if end - start <= 1:
        return []

    mid = start + (end - start) // 2

    merge_sort(array, start, mid)
    merge_sort(array, mid, start)

    for k in range(start, end):
        if 
    

with open("input.txt") as f:
    s = f.readlines()

array = list(map(int, s[1].split(" ")))
print(merge_sort(array))
