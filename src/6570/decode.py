with open("input.txt") as f:
    s = f.readlines()

k, l = map(int, s[0].split())
codes = dict(
    map(
        lambda x: (x.split(":")[0], int("1" + x.split(":")[1].replace(" ", ""), 2)),
        s[1:-1],
    )
)
string = s[-1]
longest_code_len = max(codes.items(), key=lambda x: x[1])[1]
lon = 1 << longest_code_len

huffman_table = [("", 0) for _ in range(lon)]

for ch, code in codes.items():
    count = 0
    lower_bound = code
    while lower_bound < lon:
        lower_bound = lower_bound << 1
        count += 1

    upper_bound = code
    while upper_bound < lon:
        upper_bound = (upper_bound << 1) + 1

    lower_bound = lower_bound ^ lon
    upper_bound = upper_bound ^ lon

    for i in range(lower_bound, upper_bound + 1):
        huffman_table[i] = (ch, longest_code_len - count)


i = 0
result = ""

while i < l:
    item_code = 0

    for j in range(0, longest_code_len):
        if i + j < l:
            item_code = (item_code << 1) + (string[i + j] == "1")
        else:
            item_code = item_code << 1

    item = huffman_table[item_code]
    result += item[0]
    i += item[1]

print(result)
