
# peaks([0,1,-1,3,8,4,3,5,4,3,8]) returns [1, 8, 5]


def peaks(iterable):
    iter_raw = iter(iterable)
    isUp = False
    num_pre = None
    result = []
    while True:
        try:
            num = next(iter_raw)
            if num_pre is not None:
                if num_pre < num:
                    isUp = True
                elif num_pre > num and isUp:
                    result.append(num_pre)
                    isUp = False
                else:
                    isUp = False
            num_pre = num
        except(StopIteration):
            break
    return result

print(peaks([0,1,-1,3,8,4,3,5,4,3,8]))

def is_prime(num):
    if num < 2:
        return False
    return not [num%i for i in range(2, num) if num%i == 0]


def compress(vit,bit):
    iter_v = iter(vit)
    iter_b = iter(bit)
    while True:
        v = next(iter_v)
        if next(iter_b):
            yield v

for i in compress('abcdefghijklmnopqrstuvwxyz', (is_prime(i) for i in range(1,40))):
    print(i, end='')
print()

def stop_when(iterable,p):
    iter_raw = iter(iterable)
    while True:
        item = next(iter_raw)
        if p(item):
            break
        yield item

for i in stop_when('combustible', lambda x : x >= 'q'):
    print(i, end="")
print()

def start_when(iterable,p):
    iter_raw = iter(iterable)
    isStart = False
    while True:
        item = next(iter_raw)
        if not isStart and p(item):
            isStart = True
        if isStart:
            yield item

for i in start_when('combustible', lambda x : x >= 'q'):
    print(i, end="")
print()               