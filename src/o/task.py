book = {}

with open("input.txt") as f:
    s = f.readlines()[1:]


for command in map(lambda x: x[:-1].split(" "), s):
    num = int(command[1])
    match command[0]:
        case "add":
            book[num] = command[2]
        case "del":
            if num in book:
                book.pop(num)
        case "find":
            if num in book:
                print(book[num])
            else:
                print("not found")
