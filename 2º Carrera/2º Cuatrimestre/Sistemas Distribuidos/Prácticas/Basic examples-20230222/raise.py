# Raising an exception

x = "hello"

# Checking if x is an integer
if not type(x) is int:
  # If it is not an integer, raising TypeError exception
  raise TypeError("Only integers are allowed")