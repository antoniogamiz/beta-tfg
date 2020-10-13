import matplotlib.pyplot as plt

def center_squared_method(seed):
    generated = set()
    counter = 0
    number = seed
    while number not in generated:
        counter += 1
        generated.add(number)
        number = int(str(number * number).zfill(8)[2:6])
    return counter


frequency = []
for i in range(1, 1001):
    frequency.append(center_squared_method(i))

plt.plot(range(1,1001), frequency)
plt.ylabel('Periodo')
plt.show()