
class CalcFile:

    FILE = None
    LOC  = 0
    NCNB = 0
    EXEC = 0
    COMMENTS = 0

    def __init__(self, path):
        self.FILE = open(path, 'r', encoding="utf8")
        self.calc()


    def calc(self):
        wasPrevComm = False

        for line in self.FILE:
            line = line.strip()

            self.LOC +=1
            
            # jeżeli pusta linia, leć dalej
            if line == "": 
                continue

            # jeżeli komentarz, zanotuj i leć dalej
            if line.startswith("//"):
                self.COMMENTS += 1
                continue

            # obsługa komentarzy blokowych
            if line.startswith("/*"):
                wasPrevComm = True
                self.COMMENTS += 1
                continue

            if wasPrevComm:
                self.COMMENTS += 1
                if line.endswith("*/"):
                    wasPrevComm = False
                continue

            # komentarze i puste linie wykluczone, więc można
            # zwiększyć licznik
            self.NCNB += 1

            # liczenie linii EXEC
            if line.startswith(("for", "while", "{", "}", "if")):
                continue

            self.EXEC += 1