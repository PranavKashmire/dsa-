
#using quadratic probing

class HashTable:
    def __init__(self):
        self.size = int(input("Enter the size of the hash table: "))
        self.table = [0] * self.size
        self.element_count = 0
        self.comparisons = 0

    def is_full(self):
        return self.element_count == self.size

    def hash_function(self, element):
        return element % self.size

    def quadratic_probing(self, element, position):
        pos_found = False
        limit = 50
        i = 1
        while i <= limit:
            new_position = position + (i ** 2)
            new_position = new_position % self.size
            if self.table[new_position] == 0:
                pos_found = True
                break
            i += 1
        return pos_found, new_position

    def insert(self, element):
        if self.is_full():
            print("Hash Table Full")
            return False
        is_stored = False
        position = self.hash_function(element)
        if self.table[position] == 0:
            self.table[position] = element
            print(f"Element {element} at position {position}")
            is_stored = True
            self.element_count += 1
        else:
            print(f"Collision has occurred for element {element} at position {position}. Finding new position.")
            is_stored, position = self.quadratic_probing(element, position)
            if is_stored:
                self.table[position] = element
                self.element_count += 1
        return is_stored

    def search(self, element):
        found = False
        position = self.hash_function(element)
        self.comparisons += 1
        if self.table[position] == element:
            return position
        else:
            limit = 50
            i = 1
            new_position = position
            while i <= limit:
                new_position = position + (i ** 2)
                new_position = new_position % self.size
                self.comparisons += 1
                if self.table[new_position] == element:
                    found = True
                    break
                elif self.table[new_position] == 0:
                    found = False
                    break
                else:
                    i += 1
            if found:
                return new_position
            else:
                print("Element not Found")
                return False

    def remove(self, element):
        position = self.search(element)
        if position is not False:
            self.table[position] = 0
            print(f"Element {element} is Deleted")
            self.element_count -= 1
        else:
            print("Element is not present in the Hash Table")

    def display(self):
        print("\n")
        for i in range(self.size):
            print(f"{i} = {self.table[i]}")
        print(f"The number of elements in the table are: {self.element_count}")


# main function
table1 = HashTable()
# storing elements in table
table1.insert(12)
table1.insert(26)
table1.insert(31)
table1.insert(17)
table1.insert(90)
table1.insert(28)
table1.insert(88)
table1.insert(40)
table1.insert(77)  # element that causes collision at position 0
# displaying the Table
table1.display()
print()
# printing position of elements
print("The position of element 31 is:", table1.search(31))
print("The position of element 28 is:", table1.search(28))
print("The position of element 90 is:", table1.search(90))
print("The position of element 77 is:", table1.search(77))
print("The position of element 1 is:", table1.search(1))
print("\nTotal number of comparisons done for searching =", table1.comparisons)

print()
table1.remove(90)
table1.remove(12)
table1.display()
