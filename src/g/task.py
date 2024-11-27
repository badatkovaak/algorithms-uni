def helper(x):
    return (x[0], x[1])


with open("input.txt") as f:
    s = f.readlines()

segments = list(map(lambda x: helper(list(map(int, x.split(" ")))), s[1:-1]))
points = list(map(int, s[-1].split(" ")))

all = []
for segment in segments:
    all.append((segment[0], 0, 0))
    all.append((segment[1], 2, 0))

for i, point in enumerate(points):
    all.append((point, 1, i))

all.sort(key=lambda x: 5 * x[0] + x[1])

points_with_results = list(map(lambda x: (x, -1), points))

opened = 0
closed = 0

for item in all:
    match item[1]:
        case 0:
            opened += 1
        case 2:
            closed += 1
        case 1:
            points_with_results[item[2]] = (item[0], opened - closed)

for point in points_with_results:
    print(point[1], end=" ")

print()
