p = 1_000_000_007
x_inv = 836501907


def my_hash(s: str) -> int:
    res: int = 0
    x = 1

    for c in s:
        res = (res + ord(c) * x) % p
        x = (x * 263) % p

    return res % p


def compute_power(y: int, k: int) -> int:
    x = 1

    for _ in range(k - 1):
        x = (x * y) % p

    return x


def recompute_hash(h: int, x: int, prev: str, new: str) -> int:
    return ((h - ord(prev)) * x_inv + ord(new) * x) % p


def main():
    with open("input.txt") as f:
        s = f.readlines()
        pattern = s[0][:-1]
        text = s[1][:-1]

    pattern_hash = my_hash(pattern)
    pattern_len = len(pattern)
    current_hash = my_hash(text[0:pattern_len])
    x = compute_power(263, pattern_len)

    for i in range(len(text) - pattern_len + 1):
        if current_hash == pattern_hash:
            if text[i : i + pattern_len] == pattern:
                print(i, end=" ")

        if i == len(text) - pattern_len:
            break

        current_hash = recompute_hash(current_hash, x, text[i], text[i + pattern_len])

    print()


if __name__ == "__main__":
    main()
