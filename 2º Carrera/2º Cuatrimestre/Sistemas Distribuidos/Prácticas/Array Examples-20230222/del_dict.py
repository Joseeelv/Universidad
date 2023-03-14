# Python Program to Delete an Element From a Dictionary
my_dict = {31: 'a', 21: 'b', 14: 'c'}
print(my_dict)

# Using del keyword
del my_dict[31]
print(my_dict)

# Using pop()
print(my_dict.pop(21))
print(my_dict)