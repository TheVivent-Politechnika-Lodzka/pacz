import os
from CalcFile import CalcFile


PATH = input("Podaj ścieżkę do projektu: ")
EXT = []
tmp = 'a'
print("Podaj rozszerzenia plików do analizy. Każde rozszerzenie potwierdź wciśnięciem `enter`, a zakończ wpisująć `stop`")
while True:
    tmp = input("# ")
    if tmp.lower() == "stop": break
    if tmp[0] != '.': tmp = "." + tmp
    EXT.append(tmp.lower())

FILES = []
for root, dirs, files in os.walk(PATH):
    for file in files:
        if file.endswith(tuple(EXT)):
            FILES.append(CalcFile(os.path.join(root, file)))
            #  print(os.path.join(root, file))

LOC  = 0
NCNB = 0
EXEC = 0
COMMENTS = 0

for f in FILES:
    LOC += f.LOC 
    NCNB += f.NCNB 
    EXEC += f.EXEC 
    COMMENTS += f.COMMENTS 

#########################
os.system()
print("Z prezentacji:")
print("LOC  [Lines of Code] - wszystkie linie")
print("NCNB [Non-comment non-blank] - kod (bez komentarzy i pustych)")
print("EXEC [Executable statements] - NCNB, bez ifów, forów itp (tylko linie które coś robią)")
### tego jeszcze nie ma VVVVV
print("CC   [Cyclomatic Complexity] - liczy się per metoda / nie chcę mi się myśleć jak")
print("CP   [Comment percentage] - to w sumie prawie jest, tylko zrobić procenty")
print("WMC  [Weighted method per class] - nwm")
print("RFC  [Response for a class] - nwm")
print("LCOM [Lack of cohesion of methods] - nwm")
print("CBO  [Coupling between object classes] - nwm")
print("DIT  [Depth of inheritance tree] - to chyba ręcznie się policzy")
print("NOC  [Number of children] - to chyba też ręcznie")
print()
print("Własne:")
print("COMM [Comments] - komentarze")


print("LOC  - {}".format(LOC))
print("NCNB - {}".format(NCNB))
print("EXEC - {}".format(EXEC))
print("COMM - {}".format(COMMENTS))