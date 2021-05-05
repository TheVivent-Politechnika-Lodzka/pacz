import os
from CalcFile import CalcFile
import lizard as lz


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
FILES_CC = []
for root, dirs, files in os.walk(PATH):
    for f in files:
        if f.endswith(tuple(EXT)):
            filename = os.path.join(root, f)
            FILES.append(CalcFile(filename))
            if not filename.endswith(".h"):
                FILES_CC.append(lz.analyze_file(filename))
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

CP = (COMMENTS / (COMMENTS + NCNB)) * 100

OMEGA_DICT = {}

# CC and WMC
# potężny kawałek kodu (nie myśleć. głowa może wybuchnąć)
CCsum = 0
CCi = 0

WMCsum = 0
WMCi = 0
for f in FILES_CC:
    WMCi += 1
    WMC = 0
    functions = []
    for fun in f.function_list:
        CCcurr = fun.__dict__['cyclomatic_complexity']
        CCi += 1
        CCsum += CCcurr
        WMCsum += CCcurr
        WMC += CCcurr
        functions.append({
            'name': fun.__dict__['name'],
            'CC': CCcurr
        })
    
    tail = os.path.split(f.__dict__['filename'])[1]
    tail = os.path.splitext(tail)[0]
    OMEGA_DICT[tail] = {'WMC': WMC, 'functions' : functions}

CCavg = CCsum / CCi
WMCavg = WMCsum / WMCi


#########################
os.system("cls")
print("Z prezentacji:")
print("LOC  [Lines of Code] - wszystkie linie")
print("NCNB [Non-comment non-blank] - kod (bez komentarzy i pustych)")
print("EXEC [Executable statements] - NCNB, bez ifów, forów itp (tylko linie które coś robią)")
print("CP   [Comment percentage] - Współczynnik ilości komentarzy względem aktywnego kodu")
print("CC   [Cyclomatic Complexity] - złożoność cykliczna")
print("WMC  [Weighted method per class] - nwm")
### to trzeba ręcznie VVVVV
print("RFC  [Response for a class] - lepiej policzyć ręcznie")
print("LCOM [Lack of cohesion of methods] - chujowe")
print("CBO  [Coupling between object classes] - nwm")
print("DIT  [Depth of inheritance tree] - to chyba ręcznie się policzy")
print("NOC  [Number of children] - to chyba też ręcznie")
print()


print("LOC    - {}".format(LOC))
print("NCNB   - {}".format(NCNB))
print("EXEC   - {}".format(EXEC))
print("CP     - {}%".format(round(CP, 2)))
print("CC_avg  - {}".format(round(CCavg, 2)))
print("WMC_avg - {}".format(round(WMCavg, 2)))

print()

import pprint
pp = pprint.PrettyPrinter(indent=4)
pp.pprint(OMEGA_DICT)