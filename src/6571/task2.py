from typing import List, Callable


class Heap[T]:
    data: List[T]
    length: int
    compare: Callable[[T, T], int]  # b - a

    # def are_in_wrong_order(self, i, j):
    #     if i >= self.length or j >= self.length:
    #         return False
    #
    #     return self.compare(self[i], self[j])

    def fix(self, i):
        if 2 * i >= self.length:
            return

        if 2 * i + 1 >= self.length:
            if self.compare(self.data[i], self.data[2 * i]) > 0:
                self[i], self[2 * i] = self[2 * i], self[i]
            return

        # if self.compare(self.data[2*i], self.data[2*i + 1])


# def fix_heap(heap: List[T], i: int):
