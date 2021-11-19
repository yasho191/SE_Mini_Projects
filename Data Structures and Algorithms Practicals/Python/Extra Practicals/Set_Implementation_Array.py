# set implementation

class Set:
    # constructor
    def __init__(self, arr):
        self.acc_set = arr
        self.initialize_set()

    # overriding default methods of a class
    # getitem will return value at some index of the set
    def __getitem__(self, item):
        # print(self.acc_set[item])
        return self.acc_set[item]

    # delitem will delete the given value from our set
    def __delitem__(self, value):
        if value in self.acc_set:
            self.acc_set.remove(value)

    # subtracts one set from another
    def __sub__(self, sec_set):
        diff = []
        for i in range(len(self.acc_set)):
            if self.acc_set[i] not in sec_set.acc_set:
                diff.append(self.acc_set[i])
        return diff

    def __or__(self, sec_set):
        union_set = [i for i in self.acc_set]
        for i in range(len(sec_set.acc_set)):
            if sec_set.acc_set[i] not in self.acc_set:
                union_set.append(sec_set.acc_set[i])
        return union_set

    def __and__(self, sec_set):
        intersection_set = []
        i = 0
        if len(self.acc_set) > len(sec_set.acc_set):
            while i < len(self.acc_set):
                if self.acc_set[i] in sec_set.acc_set:
                    intersection_set.append(self.acc_set[i])
                i += 1
        else:
            while i < len(sec_set.acc_set):
                if sec_set.acc_set[i] in self.acc_set:
                    intersection_set.append(sec_set.acc_set[i])
                i += 1
        return intersection_set

    # initially given an input it will convert a list to a set
    def initialize_set(self):
        x = self.acc_set
        self.acc_set = []
        for i in x:
            if i not in self.acc_set:
                self.acc_set.append(i)

    # add items to the set
    def add(self, value):
        if value not in self.acc_set:
            self.acc_set.append(value)

    def delete_value(self, value):
        if value in self.acc_set:
            self.acc_set.remove(value)

    # print set in traditional way {}
    def show_set(self):
        print("{", end='')
        for i in range(len(self.acc_set)):
            if i == len(self.acc_set) - 1:
                print(self.acc_set[i], end="")
            else:
                print(self.acc_set[i], end=", ")
        print("}")

    # union of two sets
    def union(self, sec_set):
        union_set = [i for i in self.acc_set]
        for i in range(len(sec_set.acc_set)):
            if sec_set.acc_set[i] not in self.acc_set:
                union_set.append(sec_set.acc_set[i])
        return union_set

    # intersection of two sets
    def intersection(self, sec_set):
        # collect common elements
        intersection_set = []
        i = 0
        if len(self.acc_set) > len(sec_set.acc_set):
            while i < len(self.acc_set):
                if self.acc_set[i] in sec_set.acc_set:
                    intersection_set.append(self.acc_set[i])
                i += 1
        else:
            while i < len(sec_set.acc_set):
                if sec_set.acc_set[i] in self.acc_set:
                    intersection_set.append(sec_set.acc_set[i])
                i += 1
        return intersection_set

    # checks if one is subset of other or not
    def subset(self, sec_set):
        # s1 = {1, 3, 5, 7}
        # s2 = {1, 3}
        # s1.subset(s2) = True
        # counter = 0 check if 1 is in acc_set yes counter += 1
        # check if 3 is in acc_set yes counter += 1
        # counter = 2 = len(sec_set.acc_set)
        counter = 0
        for i in range(len(sec_set.acc_set)):
            if sec_set.acc_set[i] in self.acc_set:
                counter += 1

        if counter == len(sec_set.acc_set):
            return True
        else:
            return False


set1 = Set([1, 1, 1, 1, 4, 3, 5, 6, 6, 7, 8, 9, 0, 0, 2])

set2 = Set([11, 1, 2, 3, 4, 17, 18, 0])

print(set1.acc_set)
print(set2.acc_set)
print(set1 - set2)
print(set2 - set1)

print(set1.subset(set2))
