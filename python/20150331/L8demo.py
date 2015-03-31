"""

"""

from geometry import *


print("-> Testing Program For Geometry Module")

print("-> Point Default")
point = Point()
print(point)

print("-> Rectangle Default")
rect = Rectangle()
print(rect)

print("-> point")
point.update(2, 3)
print(point)

print("-> Rectangle")
rect.update((1, 1), 5, 8)
print(rect)

print("-> New rectangle: rect1")
rect1 = Rectangle()
rect1.update((3, 2), 7, 3)
print(rect1)
print("-> The area is of rect1 is %d" % rect1.area())

print("-> Checking get_coords on rect1...")
coords = rect1.get_coords()
for p in coords:
	print(p)

print("-> Testing coords_to_rectangle...")
coords1 = [Point(), Point(), Point(), Point()]
coords1[0].update(1, 1)
coords1[1].update(2, 1)
coords1[2].update(3, 1)
coords1[3].update(4, 1)
coords2 = [Point(), Point(), Point(), Point()]
coords2[0].update(1, 1)
coords2[1].update(1, 4)
coords2[2].update(6, 4)
coords2[3].update(6, 1)
print("-> The following coords are not a rectangle.")
for p in coords1:
	print(p)
print("-> The result of the function on the list above was:")
print(coords_to_rectangle(rect1, coords1))
print("-> The following coords give the following rectangle.")
for p in coords2:
	print(p)
coords_to_rectangle(rect1, coords2)
print("-> The rectangle it describes is:")
print(rect1)

rect1.update((3, 2), 7, 3)
if (rect1.is_square()):
	print("-> The following rectangle is a square")
else:
	print("-> The following rectangle is not a square")
print(rect1)
rect1.update((3, 2), 3, 3)
if (rect1.is_square()):
	print("-> The following rectangle is a square")
else:
	print("-> The following rectangle is not a square")
print(rect1)

print("-> Drawing rectangle:")
rect1.update((3, 2), 7, 3)
print(rect1)
print(rect1.get_visual())
print("-> Drawing rectangle:")
rect1.update((3, 2), 3, 3)
print(rect1)
print(rect1.get_visual())


