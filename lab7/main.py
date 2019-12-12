def shift_array(x):
    d = [0] * len(x)
    for i in range(1, len(x)):
        j = d[i - 1]
        while j > 0 and x[j] != x[i]:
            j = d[j - 1]
        d[i] = j + 1
    return d

def KMP(s, x):
    d = shift_array(x)
    i = j = 0
    while i < len(s) and j < len(x):
        if x[j] == s[i]:
            i += 1
            j += 1
        elif 0 == j:
            i += 1
        else:
            j = d[j - 1]

    if j == len(x):
        return i - j + 1
    return -1

def jump_array(x):
    d = [len(x) for i in range(256)]
    new_x = x[::-1]

    for i in range(len(new_x)):
        d[ord(new_x[i])] = i
    return d


def BM(s, x):
    d = jump_array(x)
    i = j = k = len(x)
    while k <= len(s) and j > 0:
        if x[j - 1] == s[i - 1]:
            j -= 1
            i -= 1
        else:
            k += d[ord(s[i - 1])]
            i = k
            j = len(x)

    if j <= 0:
        return i + 1
    else:
        return -1

def main():
    print(ord('z'))
    print("Введите строку 1")
    s1 = input()
    print("Введите строку 2")
    s2 = input()
    print(KMP(s1, s2))
    print(BM(s1, s2))

if __name__ == "__main__":
    main()
