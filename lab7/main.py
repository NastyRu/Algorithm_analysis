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

def forming_d(pattern):
    """ Формируем массив d."""
    d = [len(pattern) for i in range(256)]
    new_p = pattern[::-1]

    for i in range(len(new_p)):
        if d[ord(new_p[i])] != len(new_p):
            continue
        else:
            d[ord(new_p[i])] = i
    return d


def search(string, pattern):
    """ Поиск Бойера - Мура."""

    d = forming_d(pattern)
    # x - начало прохода по string
    # j - проход по pattern
    # k - проход по string
    len_p = x = j = k = len(pattern)
    # число смещений
    counter = 0

    while x <= len(string) and j > 0:
        if pattern[j - 1] == string[k - 1]:
            j -= 1
            k -= 1
        else:
            x += d[ord(string[k - 1])]
            k = x
            j = len_p
            counter += 1

    if j <= 0:
        return "Нашли. Число смещений равно %d." % counter
    else:
        return "Не нашли!"

def main():
    print("Введите строку 1")
    s1 = input()
    print("Введите строку 2")
    s2 = input()
    print(KMP(s1, s2))
    print(search(s1, s2))

if __name__ == "__main__":
    main()
