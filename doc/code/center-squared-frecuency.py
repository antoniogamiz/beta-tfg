import matplotlib.pyplot as plt
import collections

plt.style.use('seaborn-whitegrid')


limit = 100000
n = len(str(limit))
lower_bound = int(n/2-n/4)
upper_bound = int(n/2+n/4)


def center_squared_method(seed):
    generated = set()
    counter = 0
    number = seed
    while number not in generated:
        counter += 1
        generated.add(number)
        number = int(str(number * number).zfill(n)[lower_bound:upper_bound])
    return counter


frequency = []
for i in range(1, limit):
    frequency.append(center_squared_method(i))

# plt.plot(range(1, limit), frequency, 'o', color='black')
# plt.ylabel('Periodo')
# plt.show()

# ============ BARRAS ==================

c = collections.Counter(frequency)
c = sorted(c.items())
months_num = [i[0] for i in c]
freq = [i[1] for i in c]

plt.bar(months_num, freq)
plt.ylabel("Frecuencia")
plt.xlabel("Periodo")
plt.show()
