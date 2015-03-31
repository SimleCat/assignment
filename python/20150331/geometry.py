"""

"""

class Point:
	'''Point Class
	   The class contains two attributes(abscissa(x), ordinate(y))
	'''
	def __init__(self):
		self.x = 0
		self.y = 0

	def __repr__(self):
		'''Return coordinate information in string format.
		'''
		return "%d %d" % (self.x, self.y)

	def update(self, x, y):
		'''Update the coordinate.
		'''
		self.x = x
		self.y = y


class Rectangle:
	def __init__(self):
		self.origin = Point()
		self.width = 1
		self.height = 1

	def __repr__(self):
		'''Return rectangle information in string format.
		'''
		return "%s\n%d\n%d" %(self.origin, self.width, self.height)

	def update(self, origin, width, height):
		'''Update the parameter of rectangle.
		   The origin is a tuple,which have two items(abscissa and ordinate) 
		'''
		self.origin.update(origin[0], origin[1])
		self.width = width
		self.height = height

	def area(self):
		'''Return the (numeric) area of the rectangle
		'''
		return self.width * self.height

	def is_square(self):
		'''returns True if the rectangle is a square and False otherwise.
        '''
		if (self.width == self.height):
			return True
		return False

	def get_coords(self):
		'''Return a list with the corner coordinates of the rectangle in
		   the following order: lower left, upper left, upper right, and 
		   lower right. 
		   The list contain four Point objects.
        '''
		coords = [Point(), Point(), Point(), Point()]
		coords[0].update(self.origin.x, self.origin.y)
		coords[1].update(self.origin.x, self.origin.y+self.height)
		coords[2].update(self.origin.x+self.width, self.origin.y+self.height)
		coords[3].update(self.origin.x+self.width, self.origin.y)
		return coords

	def get_visual(self):
		'''Return a string representation of the rectangle as an unfilled
		   rectangle. 
		   Use ‘–‘ for the top and bottom lines, ‘|’ for the sides, and ‘+’
		   for the corners.
        '''
		visual = "+" + "-"*(self.width-2) + "+\n"
		for i in range(self.height-2):
			visual += "|" + " "*(self.width-2) + "|\n"
		visual += "+" + "-"*(self.width-2) + "+"
		return visual

def coords_to_rectangle(rect, coords):
	'''This function updates the origin, width, and height of the rect
       parameter (a Rectangle) based on the coordinates (Points) given 
       in the list.
       It returns False if the coordinates do not describe a rectangle 
       and True if they do. 
    '''
	if coords[0].x != coords[1].x or coords[0].y != coords[3].y:
		return False
	height = coords[1].y - coords[0].y
	if height <= 0 or height != coords[2].y - coords[0].y:
		return False
	width = coords[2].x - coords[0].x
	if width <= 0 or width != coords[3].x - coords[0].x:
		return False
	rect.update((coords[0].x, coords[0].y), width, height)
	return True

