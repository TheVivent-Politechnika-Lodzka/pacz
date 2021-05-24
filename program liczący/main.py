import os
from CalcFile import CalcFile
import lizard as lz
import re
from numpy import exp

from Projects import Aquarium
from Projects import Sudoku

PATH = input("Podaj ścieżkę do projektu: ")
EXT = []
tmp = 'a'
print("Podaj rozszerzenia plików do analizy. Każde rozszerzenie potwierdź wciśnięciem `enter`, a zakończ wpisująć `stop`")
while True:
    tmp = input("# ")
    if tmp.lower() == "stop": break
    if tmp[0] != '.': tmp = "." + tmp
    EXT.append(tmp.lower())

OMEGA_DICT_SIMP = Sudoku
if ".cpp" in EXT: OMEGA_DICT_SIMP = Aquarium

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
        name = fun.__dict__['name']
        name = re.sub(r'^.*?\:', ':', name)
        name = name.replace("::", '')
        functions.append({
            'name': name,
            'CC': CCcurr
        })
    
    tail = os.path.split(f.__dict__['filename'])[1]
    tail = os.path.splitext(tail)[0]
    # OMEGA_DICT[tail] = {'WMC': WMC, 'functions' : functions}


    OMEGA_DICT[tail] = {'functions' : functions}
    try: OMEGA_DICT_SIMP[tail]['WMC'] = WMC
    except: pass

CCavg = CCsum / CCi
WMCavg = WMCsum / WMCi


#########################
os.system("cls")
# print("Z prezentacji:")
# print("LOC  [Lines of Code] - wszystkie linie")
# print("NCNB [Non-comment non-blank] - kod (bez komentarzy i pustych)")
# print("EXEC [Executable statements] - NCNB, bez ifów, forów itp (tylko linie które coś robią)")
# print("CP   [Comment percentage] - Współczynnik ilości komentarzy względem aktywnego kodu")
# print("CC   [Cyclomatic Complexity] - złożoność cykliczna")
# print("WMC  [Weighted method per class] - złożoność cykliczna klasowa")
# ### to trzeba ręcznie VVVVV
# print("RFC  [Response for a class] - lepiej policzyć ręcznie")
# print("LCOM [Lack of cohesion of methods] - chujowe")
# print("CBO  [Coupling between object classes] - nwm")
# print("DIT  [Depth of inheritance tree] - to chyba ręcznie się policzy")
# print("NOC  [Number of children] - to chyba też ręcznie")
# print()

# print()

OUTFILE = open("out.html", 'w')
OUTFILE.write("""
<style>
    table {
        margin: 10px;
        width: 600px;
        border-collapse: collapse;
    }

    td, th{
        border: 1px solid black;
        margin: 0;
        padding: 5px;
    }
    .CC{
        width:90px
    }
    .fun{
        text-align: left;
    }
    tr:nth-child(2n+1){
        background: rgb(232, 232, 232);
    }
    tr:nth-child(1), table:nth-child(2n) tr:nth-child(2){
        background: rgba(0,0,0,0);
    }
    tr:nth-child(1), tr:nth-child(2){
        background: rgb(201, 245, 243);
    }

</style>
""")


for key in OMEGA_DICT:

    OUTFILE.write("<table>")
    OUTFILE.write("  <tr>")
    OUTFILE.write("    <th colspan='2'>{}</th>".format(key))
    OUTFILE.write("  </tr>")

    OUTFILE.write("  <tr class='fun'>")
    OUTFILE.write("    <th>nazwa funkcji</th><th>CC</th>")
    OUTFILE.write("  </tr>")
    functions = OMEGA_DICT[key]['functions']
    for i in range(len(functions)):
        OUTFILE.write("<tr>")

        OUTFILE.write("<td>{}</td>".format(functions[i]['name']))
        OUTFILE.write("<td class='CC'>{}</td>".format(functions[i]['CC']))
        
        OUTFILE.write("</tr>")

    OUTFILE.write("</table>")

    try:
        OUTFILE.write("<table>")
        OUTFILE.write("""
            <tr>
                <th colspan='2'>Podsumowanie {}</th>
            </tr>
        """.format(key))

        for key2 in OMEGA_DICT_SIMP[key]:
            OUTFILE.write("""
                <tr>
                    <td>{}</td>
                    <td class="CC">{}</td>
                </tr>
            """.format(key2, OMEGA_DICT_SIMP[key][key2]))

        OUTFILE.write("</table>")
    except:
        pass


OUTFILE.write("""<table>
                    <tr>
                        <th>Klasa</th>
                        <th>NAI</th>
                        <th>OCMEC</th>
                        <th>DIT</th>
                        <th>PI</th>
                    </tr>
                """)

for key in OMEGA_DICT_SIMP:
    tmp = OMEGA_DICT_SIMP[key]
    PI = round(1 / (1 + exp(-(-3.97 + 0.464 * tmp["NAI"] + 1.47 * tmp["OCMEC"] + 1.06 * (tmp["DIT"]-1) ))), 3)
    OUTFILE.write("""
        <tr>
            <td>{}</td>
            <td>{}</td>
            <td>{}</td>
            <td>{}</td>
            <td>{}</td>
        </tr>
        """.format(key, tmp["NAI"], tmp["OCMEC"], tmp["DIT"], PI))

OUTFILE.write("</table>")



OUTFILE.write("""

<table>
    <tr>
        <th colspan='2'>PODSUMOWANIE</th>
    </tr>
    <tr></tr>
    <tr>
        <td>LOC [Lines of Code]</td>
        <td class='CC'>{}</td>
    </tr>
    <tr>
        <td>NCNB [Lines of Code]</td>
        <td class='CC'>{}</td>
    </tr>
    <tr>
        <td>EXEC [Executable statements]</td>
        <td class='CC'>{}</td>
    </tr>
    <tr>
        <td>CP [Comment percentage]</td>
        <td class='CC'>{} %</td>
    </tr>
    <tr>
        <td>CCavg [average Cyclomatic Complexity]</td>
        <td class='CC'>{}</td>
    </tr>
    <tr>
        <td>WMCavg [average Weighted method per class]</td>
        <td class='CC'>{}</td>
    </tr>
<table>

""".format(LOC, NCNB, EXEC, round(CP, 2), round(CCavg, 2), round(WMCavg, 2)))


