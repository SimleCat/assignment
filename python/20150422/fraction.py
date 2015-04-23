from goody import irange
from goody import type_as_str

import math

class Fraction:
    @staticmethod
    # Call as Fraction._gcd(...); no self parameter
    # Helper method computes the Greatest Common Divisor of x and y
    def _gcd(x, y):
        assert x >= 0 and y >= 0, 'Fraction._gcd: x('+str(x)+') and y('+str(y)+') must be >= 0'
        while y != 0:
            x, y = y, x % y
        return x

    # Returns a string that is the decimal representation of a Fraction, with
    #   decimal_places digitst appearing after the decimal points.
    # For example: if x = Fraction(23,8), then x(5) returns '2.75000'
    def __call__(self, decimal_places):
        answer = ''
        num = self.num
        denom = self.denom
    
        # handle negative values
        if num < 0:
            num, answer = -num, '-'
    
        # handle integer part
        if num >= denom:
            answer += str(num//denom)
            num     = num - num//denom*denom
            
        # handle decimal part
        answer += '.'+str(num*10**decimal_places//denom)
        return answer
    
    @staticmethod
    # Call as Fraction._validate_arithmetic(..); no self parameter
    # Helper method raises exception with appropriate message if type(v) is not
    #   in the set of types t; the message includes the values of the strings
    #   op (operator), lt (left type) and rt (right type)
    # An example call (from my __add__ method), which checks whether the type of
    #   right is a Fraction or int is...
    # Fraction._validate_arithmetic(right, {Fraction,int},'+','Fraction',type_as_str(right))
    def _validate_arithmetic(v, t, op, lt, rt):
        if type(v) not in t:
            raise TypeError('unsupported operand type(s) for '+op+
                            ': \''+lt+'\' and \''+rt+'\'')        

    @staticmethod
    # Call as Fraction._validate_relational(..); no self parameter
    # Helper method raises exception with appropriate message if type(v) is not
    #   in the set of types t; the message includes the values of the strings
    #   op (operator), and rt (right type)
    def _validate_relational(v, t, op, rt):
        if type(v) not in t:
            raise TypeError('unorderable types: '+
                            'Fraction() '+op+' '+rt+'()')        


    def __init__(self,num=0,denom=1):
        assert isinstance(num, int) and isinstance(denom, int), 'Fraction.__init__: num and denom must be int'
        assert denom != 0, 'Fraction.__init__: denom must not be 0'
        # print("num=%d, denom=%d" % (num, denom))
        isPositive = True
        if denom < 0:
            num, denom = -num, -denom
        if num < 0:
            isPositive = False
            num = -num
        if num == 0:
            denom = 1
        else:
            factors = Fraction._gcd(num, denom)
            num = num//factors
            denom = denom//factors
        if not isPositive:
            self.num = -num
        else:
            self.num = num
        self.denom = denom


    def __repr__(self):
        return "Fraction(%d,%d)" % (self.num, self.denom)
    
    def __str__(self):
        return "%d/%d" % (self.num, self.denom)
   

    def __bool__(self):
        if self.num == 0:
            return False
        return True
    

    def __getitem__(self,i):
        if i not in [0, 1, 'n', 'num', 'numerator', 'd', 'denom', 'denominator']:
            raise TypeError(str(i) + " not in [0, 1, 'n', 'num', 'numerator', 'd', 'denom', 'denominator']")
        if i in [0, 'n', 'num', 'numerator']:
            return self.num
        return self.denom
    
 
    def __pos__(self):
        return Fraction(self.num, self.denom)
    
    def __neg__(self):
        return Fraction(-self.num, self.denom)
    
    def __abs__(self):
        return Fraction(abs(self.num), self.denom)
    

    def __add__(self,right):
        Fraction._validate_arithmetic(right, [int, Fraction], "+", "Fraction", right.__class__.__name__)
        num = self.num
        denom = self.denom
        if isinstance(right, int):
            num = self.num + self.denom * right
        elif isinstance(right, Fraction):
            num = right.num * self.denom + self.num * right.denom
            denom = self.denom * right.denom
        return Fraction(num, denom)


    def __radd__(self,left):
        Fraction._validate_arithmetic(left, [int, Fraction], "+", left.__class__.__name__, "Fraction")
        num = self.num
        denom = self.denom
        if isinstance(left, int):
            num = self.num + self.denom * left
        elif isinstance(left, Fraction):
            num = left.num * self.denom + self.num * left.denom
            denom = self.denom * left.denom
        return Fraction(num, denom)


    def __sub__(self,right):
        Fraction._validate_arithmetic(right, [int, Fraction], "-", "Fraction", right.__class__.__name__)
        num = self.num
        denom = self.denom
        if isinstance(right, int):
            num = self.num - self.denom * right
        elif isinstance(right, Fraction):
            num = self.num * right.denom - right.num * self.denom
            denom = self.denom * right.denom
        return Fraction(num, denom)
     
    def __rsub__(self,left):
        Fraction._validate_arithmetic(left, [int, Fraction], "-", left.__class__.__name__, "Fraction")
        num = self.num
        denom = self.denom
        if isinstance(left, int):
            num = self.denom * left - self.num
        elif isinstance(left, Fraction):
            num = left.num * self.denom - self.num * left.denom
            denom = self.denom * left.denom
        return Fraction(num, denom)

     
    def __mul__(self,right):
        Fraction._validate_arithmetic(right, [int, Fraction], "*", "Fraction", right.__class__.__name__)
        num = self.num
        denom = self.denom
        if isinstance(right, int):
            num = right * self.num
        elif isinstance(right, Fraction):
            num = self.num * right.num
            denom = self.denom * right.denom
        return Fraction(num, denom)

    def __rmul__(self,left):
        Fraction._validate_arithmetic(left, [int, Fraction], "*", left.__class__.__name__, "Fraction")
        num = self.num
        denom = self.denom
        if isinstance(left, int):
            num = left * self.num
        elif isinstance(left, Fraction):
            num = left.num * self.num
            denom = self.denom * left.denom
        return Fraction(num, denom)

    
    def __truediv__(self,right):
        Fraction._validate_arithmetic(right, [int, Fraction], "*", "Fraction", right.__class__.__name__)
        num = self.num
        denom = self.denom
        if isinstance(right, int):
            denom = right * self.denom
        elif isinstance(right, Fraction):
            num = self.num * right.denom
            denom = self.denom * right.num
        return Fraction(num, denom)


    def __rtruediv__(self,left):
        Fraction._validate_arithmetic(left, [int, Fraction], "*", left.__class__.__name__, "Fraction")
        num = self.num
        denom = self.denom
        if isinstance(left, int):
            num = left * self.denom
            denom = self.num
        elif isinstance(left, Fraction):
            num = left.num * self.denom
            denom = left.denom * self.num
        return Fraction(num, denom)


    def __pow__(self,right):
        Fraction._validate_arithmetic(right, [int], "**", "Fraction", right.__class__.__name__)
        num = self.num
        denom = self.denom
        if right < 0:
            num = self.denom
            denom = self.num
            right = -right
        num = num ** right
        denom = denom ** right
        return Fraction(num, denom)


    def __eq__(self,right):
        Fraction._validate_relational(right, [int, Fraction], "==", right.__class__.__name__)
        if isinstance(right, int):
            if right == self.num and self.denom == 1:
                return True
        elif self.num == right.num and self.denom == right.denom:
                return True
        return False
    

    def __lt__(self,right):
        Fraction._validate_relational(right, [int, Fraction], "<", right.__class__.__name__)
        if isinstance(right, int):
            if self.num < right * self.denom:
                return True        
        elif self.num * right.denom < right.num * self.denom:
            return True
        return False

    
    def __gt__(self,right):
        Fraction._validate_relational(right, [int, Fraction], ">", right.__class__.__name__)
        if isinstance(right, int):
            if self.num > right * self.denom:
                return True
        elif self.num * right.denom > right.num * self.denom:
            return True
        return False
    # Uncomment this method when you are ready to write/test it
    # If this is pass, then no attributes will be set
    def __setattr__(self,name,value):
        if name not in self.__dict__:
            object.__setattr__(self, name, value)
        else:
            raise NameError("%s is already in __dict__." % name)
 


##############################


# Newton: pi = 6*arcsin(1/2); see the arcsin series at http://mathforum.org/library/drmath/view/54137.html
# Check your results at http://www.geom.uiuc.edu/~huberty/math5337/groupe/digits.html
#   also see http://www.numberworld.org/misc_runs/pi-5t/details.html
def compute_pi(n):
    def prod(r):
        answer = 1
        for i in r:
            answer *= i
        return answer
    
    answer = Fraction(1,2)
    x      = Fraction(1,2)
    for i in irange(1,n):
        big = 2*i+1
        answer += Fraction(prod(range(1,big,2)),prod(range(2,big,2)))*x**big/big       
    return 6*answer





if __name__ == '__main__':
    # Put in simple tests for Fraction before allowing driver to run
 
    print()
    import driver
    
    driver.default_file_name = 'bsc1.txt'
#     driver.default_show_traceback = True
#     driver.default_show_exception = True
#     driver.default_show_exception_message = True
    driver.driver()