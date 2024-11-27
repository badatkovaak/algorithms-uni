with open("input.txt") as f:
    s = f.readlines()

intervals = list(map(lambda x: tuple(map(int, x.split(" "))), s[1:]))
intervals.sort(key=lambda x: x[1])

points = []

for interval in intervals:
    if len(points) == 0 or points[-1] < interval[0]:
        points.append(interval[1])

print(len(points))

for point in points:
    print(point, end=" ")

print()
