class Banana:
    def __init__(self):
        self.length = 0
        self.colour = "Yellow"


if __name__ == "__main__":
    b = Banana()

    b.length = 5
    b.colour = "Orange"


    b2 = Banana()

    b2.length = 6
    b2.colour = "Green"


    print("{}, {}".format(b.colour, b.length))
    print("{}, {}".format(b2.colour, b2.length))