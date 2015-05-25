from functools import reduce # for code_metric; map and filter do not need to be imported


def is_sorted(s):
    if not s or len(s) == 1:
        return True
    if s[0] > s[1]:
        return False
    return is_sorted(s[1:])


def merge (l1,l2):
    result = []
    if not l1 and not l2:
        pass
    elif not l1:
        result += l2
    elif not l2:
        result += l1
    elif l1[0] >= l2[-1]:
        result += l2 + l1
    elif l2[0] >= l1[-1]:
        result += l1 + l2
    else:
        if l1[0] < l2[0]:
            result.append(l1[0])
            result += merge(l1[1:], l2)
        else:
            result.append(l2[0])
            result += merge(l1, l2[1:])
    return result


def sort(l):
    len_l = len(l)
    if not l or len_l == 1:
        return l
    return merge(sort(l[:len_l//2]), sort(l[len_l//2:]))


def compare(a,b):
    if a == '' and b == '':
        return '='
    if a == '' and b != '':
        return '<'
    if a != '' and b == '':
        return '>'
    if a[0] > b[0]:
        return '>'
    if a[0] < b[0]:
        return '<'
    return compare(a[1:], b[1:])


def code_metric(file):
    lines = filter(lambda line: line != '\n', open(file))
    lines = map(lambda line: (1, len(line.rstrip())), lines)
    return reduce(lambda x, y: (x[0]+y[0], x[1]+y[1]), lines)




if __name__=="__main__":
    import predicate,random,driver
    from goody import irange
    
    print('\nTesting is_sorted')
    print(is_sorted([]))
    print(is_sorted([1,2,3,4,5,6,7]))
    print(is_sorted([1,2,3,7,4,5,6]))
    print(is_sorted([1,2,3,4,5,6,5]))
    print(is_sorted([7,6,5,4,3,2,1]))
    
    print('\nTesting merge')
    print(merge([],[]))
    print(merge([],[1,2,3]))
    print(merge([1,2,3],[]))
    print(merge([1,2,3,4],[5,6,7,8]))
    print(merge([5,6,7,8],[1,2,3,4]))
    print(merge([1,3,5,7],[2,4,6,8]))
    print(merge([2,4,6,8],[1,3,5,7]))
    print(merge([1,2,5,7,10],[1,2,6,10,12]))


    print('\nTesting sort')
    print(sort([1,2,3,4,5,6,7]))
    print(sort([7,6,5,4,3,2,1]))
    print(sort([4,5,3,1,2,7,6]))
    print(sort([1,7,2,6,3,5,4]))
    l = list(range(20))  # List of values 0-19
    for i in range(10):  # Sort 10 times
        random.shuffle(l)
        print(sort(l),sep='-->')


    print('\nTesting compare')
    print(compare('',''))
    print(compare('','abc'))
    print(compare('abc',''))
    print(compare('abc','abc'))
    print(compare('bc','abc'))
    print(compare('abc','bc'))
    print(compare('aaaxc','aaabc'))
    print(compare('aaabc','aaaxc'))


    print('\nTesting code_metric')
    print(code_metric('cmtest.py'))
    print(code_metric('collatz.py'))
    print(code_metric('q5solution.py'))  # A function analyzing the file it is in
