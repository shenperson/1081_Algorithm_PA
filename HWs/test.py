def partition(array, low, high):
    pivot = array[low]
    i = low-1
    j = high+1
    while 1:
        # for k in array:
        #     print(k, end=' ')
        # print()
        i = i + 1
        while array[i] < pivot:
            i = i + 1
        j = j-1
        while array[j] > pivot:
            j = j-1

        if i >= j:
            # print(j)
            return j
        array[i], array[j] = array[j], array[i]


def quicksort(array, low, high):
    for k in array:
        print(k, end=' ')
    print()
    if low < high:
        p = partition(array, low, high)
        quicksort(array, low, p)
        quicksort(array, p + 1, high)


a = ['N','T_1','U','E_1','E_2','C','S','A','L','G','O','R','I','T_2','H','M']
# partition(a, 0, 15)
quicksort(a,0,15)
