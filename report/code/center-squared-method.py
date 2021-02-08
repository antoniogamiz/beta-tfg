seed = 123
number = seed
generated = set()
counter = 0

while number not in generated:
    counter += 1
    generated.add(number)
    number = int(str(number * number).zfill(8)[2:6])
    print(f"#{counter}: {number}")
