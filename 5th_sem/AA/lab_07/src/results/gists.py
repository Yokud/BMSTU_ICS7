import matplotlib.pyplot as plt

x = []
y = []

with open("clust_search.txt") as in_file:
    loaded_txt = in_file.read().strip().split('\n')
    loaded_txt = [x for x in loaded_txt]

    for s in loaded_txt:
        ss = s.split()
        x.append(int(ss[0]))
        y.append(int(ss[1]))

for i in range(len(y) - 1):
    for j in range(len(y) - 1 - i):
        if y[j] > y[j + 1]:
            temp = y[j]
            y[j] = y[j + 1]
            y[j + 1] = temp

            temp = x[j]
            x[j] = x[j + 1]
            x[j + 1] = temp

# Построение графика
plt.ylabel("Индекс ключа")
plt.xlabel("Количество сравнений")
plt.bar(list(range(len(y))), height=y, label = "Частотный поиск")
plt.xticks(x)
plt.legend()
plt.show()

