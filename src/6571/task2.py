class Heap:
    def __init__(self, data, compare):
        self.data = data
        self.length = len(data)
        self.compare = compare
        self.results = []

    def fix(self, i, from_below=False):
        if i < 0:
            return

        if 2 * i + 1 >= self.length:
            # self.fix((i-1)//2)
            return

        if 2 * i + 2 >= self.length:
            if self.compare(self.data[i], self.data[2 * i + 1]) < 0:
                self.data[i], self.data[2 * i + 1] = self.data[2 * i + 1], self.data[i]
                self.results.append(f"{i} {2 * i + 1}")
                # self.fix((i-1)//2)
            return

        if self.compare(self.data[2 * i + 1], self.data[2 * i + 2]) > 0:
            min_child = 2 * i + 1
        else:
            min_child = 2 * i + 2

        if self.compare(self.data[i], self.data[min_child]) < 0:
            self.data[i], self.data[min_child] = self.data[min_child], self.data[i]
            self.results.append(f"{i} {min_child}")

        self.fix(2 * i + 1)
        self.fix(2 * i + 2)

    def tree_depth(self):
        l = len(self.data)
        count = 0

        while l >= 1:
            l = l >> 1
            count += 1

        return count

    def iter_over_levels(self):
        for i in range(self.tree_depth()):
            start = 2**i
            end = 2 ** (i + 1)
            for j in self.data[start - 1 : end - 1]:
                yield j

    def __repr__(self) -> str:
        res = ""
        depth = self.tree_depth()
        for i in range(depth):
            print("  " * (depth - i - 1), end="")
            for j in self.data[2**i - 1 : 2 ** (i + 1) - 1]:
                print(j, end="  ")
            print()

        return res


def comp(a, b):
    return b - a


if __name__ == "__main__":
    with open("input.txt") as f:
        s = f.readlines()[1]

    # data = list(map(int, s.split()))
    data = [7, 6, 5, 4, 3, 2, 1, 2]

    a = Heap(data, comp)
    # print(a.tree_depth())

    for i in range(a.length // 2, a.length, 2):
        a.fix(i)

    print(a)

    # print(len(a.results))
    #
    # for i in a.results:
    #     print(i)
