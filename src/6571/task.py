with open("input.txt") as f:
    s = f.readlines()[1:]


if __name__ == "__main__":
    queue = list()

    for command in map(lambda x: x[:-1].split(" "), s):
        match command[0]:
            case "Insert":
                num = int(command[1])

                for i, v in enumerate(queue):
                    if num > v:
                        queue.insert(i, num)
                        break
                else:
                    queue.append(num)

            case "ExtractMax":
                print(queue[0])
                del queue[0]
