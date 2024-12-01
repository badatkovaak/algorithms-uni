with open("input.txt") as f:
    s = f.readlines()

items = list(map(lambda x: tuple(map(int, x.split(" "))), s[1:]))
items = sorted(
    map(lambda x: (x[0] / x[1], x[1]), filter(lambda x: x[0] > 0, items)),
    key=lambda x: -x[0],
)

volume = tuple(map(float, s[0].split(" ")))[1]
total_price = 0.0

for item in items:
    if volume <= 0.0:
        break

    volume_to_take = min(item[1], volume)
    total_price += item[0] * volume_to_take
    volume -= volume_to_take

print(f"{total_price:.3f}")
