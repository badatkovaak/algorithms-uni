with open("input.txt") as f:
    s = list(map(str.split, f.readlines()))
    m = int(s[0][0])
    s = s[2:]

table = [None for _ in range(m)]
p = 1_000_000_007


def my_hash(s: str, m: int):
    res = 0
    x = 1

    for i in range(len(s)):
        res += (ord(s[i]) * x) % p
        x = (x * 263) % p

    return res % m


for command in s:
    print(command[1], my_hash(command[1], m))
    print(command)
    match command[0]:
        case "add":
            v = table[my_hash(command[1], m)]

            if v is None:
                table[my_hash(command[1], m)] = (command[1],)
            else:
                table[my_hash(command[1], m)] = (command[1], v)

        case "del":
            v = table[my_hash(command[1], m)]

            if v is not None and len(v) > 1 and v[1] is not None:
                v_next = v[1]
            elif v is not None:
                if v[0] == command[1]:
                    table[my_hash(command[1], m)] = None

        case "find":
            v = table[my_hash(command[1], m)]

            while v is not None and len(v) > 1 and v[1] is not None:
                if v[0] == command[1]:
                    break

                v = v[1]

            if v is not None and v[0] == command[1]:
                print("yes")
            else:
                print("no")

        case "check":
            v = table[int(command[1]) % m]

            while v is not None and len(v) > 1 and v[1] is not None:
                print(v[0], end=" ")
                v = v[1]

            if v is not None:
                print(v[0])
