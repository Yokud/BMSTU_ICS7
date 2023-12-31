from random import randint

N = int(input('Введите количество элементов(не более 10 тыс.): '))

if N <= 0 or N > 10000:
    raise SystemExit()

L = [0] * N
for i in range(N):
    L[i] = randint(-1000000, 1000000)

with open('my_data.txt', 'w') as file:
    file.write(str(N) + ' ')

    for i in range(N):
        if i < N - 1:
            file.write(str(L[i]) + ' ')
        else:
            file.write(str(L[i]))
    
