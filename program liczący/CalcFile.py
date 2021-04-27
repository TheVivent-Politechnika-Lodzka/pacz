
class CalcFile:

    FILE = None

    def __init__(self, path):
        self.FILE = open(path, 'r')