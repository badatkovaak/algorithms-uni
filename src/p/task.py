from typing import List


with open("input.txt") as f:
    s = list(map(str.split, f.readlines()))
    m = int(s[0][0])
    s = s[2:]

table: List[List[str]] = [[] for _ in range(m)]
p = 1_000_000_007


def my_hash(s: str, m: int) -> int:
    res: int = 0
    x = 1

    for c in s:
        res = (res + ord(c) * x) % p
        x = (x * 263) % p

    return (res % p) % m


for command in s:
    match command[0]:
        case "add":
            if table[my_hash(command[1], m)].count(command[1]) == 0:
                table[my_hash(command[1], m)].insert(0, command[1])
        case "del":
            table[my_hash(command[1], m)] = list(
                filter(lambda x: x != command[1], table[my_hash(command[1], m)])
            )
        case "find":
            if table[my_hash(command[1], m)].count(command[1]) > 0:
                print("yes")
            else:
                print("no")
        case "check":
            # for item in table[int(command[1]) % m]:
            #     print(item, end=" ")
            print(" ".join(table[int(command[1]) % m]))
