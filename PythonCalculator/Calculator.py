from math import pi


a = 0   #int(input("please input the lower limit of the integration\n"))
b = 1   #int(input("please input the upper limit of the integration\n"))
#text = input("please input the function express here, using proper options(with varieble x)\n")
#func = eval("lambda x: " + text)
func = lambda x: 1 / (1 + x ** 2)

c = (a + b) / 2
interval = lambda x, y: (y - x) / 6 * (func(x) + 4 * func((x + y) / 2) + func(y))
epsilon = 10
ditch = 0.1

while (epsilon > 0.0001):
    epsilon = interval(a, a + 2 * ditch) + interval(a + 2 * ditch, a + ditch) - interval(a, a + ditch)
    ditch /= 10

result = 0
for i in range(int(1/ditch)):
    i *= ditch
    result += ditch / 6 * (func(i) + 4 * func(i + ditch / 2) + func(i + ditch))

print(result, pi / 4)