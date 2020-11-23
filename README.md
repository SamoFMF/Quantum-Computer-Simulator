# Simulator kvantnega računalnika v jeziku C++

## Vpeljani tipi

Vpeljemo dva nova tipa, vektor in matrika (vektor vektorjev).

```cpp
typedef vector<complex<double>> vec;
typedef vector<vec> matrix;
```

## Inicializacija

Najprej inicializiramo `qcs` objekt, ki sprejme bodisi niz vrednosti qubitov (vsak `char` predstavlja svoj qubit in lahko zavzame bodisi `0` bodisi `1`), ali pa matriko (`matrix`), kjer je vsaka vrstica svoj qubit. Na spodnjem primeru inicializiramo `qcs` s kubitoma `|0>` in `|1>`

```cpp
qcs qc = qcs("01");
```

```cpp
qcs qc = qcs({{1,0},{0,1}});
```

## Logična vrata

### Hadamard
Hadamardova logična vrata pretvorijo qubit iz stanja `|0>` ali `|1>` v superpozicijo. Vrata lahko uporabimo na tri načine:
* podamo indeks qubita na katerem želimo uporabiti kvantna logična vrata;
* podamo vektor indeksov nad katerimi se uporabijo vrata;
* dodamo pripono `_all`, da se izvede na vseh kubitih.

```cpp
qc.H(3);
qc.H({0,1});
qc.H_all()
```

## Pauli-X,Y,Z
Paulijeva X, Y in Z vrata so rotacija okoli x, y in z osi za `pi` stopinj. `Pauli-X` je znan tudi kot negacija. Uporabimo jih lahko na enem ali več qubitih.

```cpp
qc.X(0);
qc.X({2,4});
```

```cpp
qc.Y(0);
qc.Y({2,4});
```

```cpp
qc.Z(0);
qc.Z({2,4});
```

## Koren negacije (Square root NOT)
Negira in nato koreni. Uporaba je identična kot pri negaciji `X`.
```cpp
qc.SQX(0);
qc.SQX({2,4});
```

## Vrata faznega zamika
Fazni zamik kubita za željen kot `phi`. Uporabimo lahko na željenem qubitu ali seznamu qubitov, ki so vsi zamaknjeni za isto fazo.

```cpp
qc.R(2, 3.14);
qc.R({0,1,3},1.507);
```

## Zamenjava (SWAP)
S temi vrati lahko zamenjamo sosednja qubita. Implementirana je še posplošitev, ki zamenja poljubna qubita. Posledično lahko:
* vnesemo indeks qubita, ki ga želimo zamenjati s qubitom za njim (ki ima indeks za 1 večji);
* vnesemo seznam indeksov, kjer se opravi zgornji korak;
* dva indeksa, ki predstavljata qubita, ki ju zamenjamo med seboj.

```cpp
qc.SWP(3);
qc.SWP({0,2});
qc.SWP(1, 4);
```

## Kontrolirana negacija (Controlled NOT)
Vežemo na dva qubita. Prvi je kontrolni, torej se ne spremeni, drugi pa v primeru, da je prvi 0, ostane enak, sicer se negira. Uporaba je identična vratom `SWAP`.

```cpp
qc.CX(3);
qc.CX({0,2});
qc.CX(1, 4);
```

## Controlled NOT - reverse order
Identično `CNOT`, vendar je drugi qubit kontrolni.

```cpp
qc.CX2(3);
qc.CX2({0,2});
qc.CX2(1, 4);
```

## Kontroliran fazni zamik (Controlled Phase Shift)
Podobno kot `CNOT` naredi na `X`, naredi `CR` na `R`.
```cpp
qc.CR(3, 0.14);
qc.CR({0,2}, 1.2);
qc.CR(1, 4, 3.14);
```
## Toffolijeva vrata
Toffolijeva vrata, tudi `CCNOT` vrata. Sprejmejo indeks ali seznam indeksov qubitov, ki predstavljajo prvi vhod, naslednji zaporedni indeksi predstavljajo preostale vhode.

```cpp
qc.CCX(0);
qc.CCX({0,1});
```

## Kvantna Fourierjeva transformacija
Uporabi kvantno Fourierovo transformacijo na željenem qubitu in njemu naslednjimi, dokler se ne doseže željena velikost.

```cpp
qc.QFT(1, 3); // Na qubitih 1,2 in 3 se uporabi kvantna Fourierjeva transformacija
qc.QFT({0,4},2);
```

## Inverzna kvantna Fourierjeva transformacija
Podobno kot zgoraj, le inverzna operacija (kot je negiran).
```cpp
qc.QFTi(1, 3);
qc.QFTi({0,4},2);
```

## Poljuben oracle
Podobno kot na primerih zgoraj, lahko poljubna vrata zapišemo v matrični obliki in navedemo indeks (ali indekse) na katerem(-ih) se izvedejo željena vrata. Naj bosta `M1` in `M2` torej neka poljubna oracle-a v matrični obliki, zanju je uporaba sledeča:

```cpp
qc.useOracle(2, M1); // Prvi vhod oracle-a bo qubit z indeksom 2, če je vhodov več, bodo to zaporedno naslednji qubiti
qc.useOracles({0,3}, M1); // Zgornja vrstica se bo izvedla na prvem in četrtem qubitu
qc.useOracles({0,3}, {M1,M2}); // Na prvem qubitu (in potencialno zaporednih naslednjih) se izvede oracle M1, na četrtem (...) pa oracle M2
```

# Meritve
Imamo dve vrsti meritev. Invazivno ter neinvazivno.

## Neinvazivna meritev
Vrnemo vsa možna stanja superpozicije qubitov v sistemu ter njihove pripadajoče verjetnosti. To meritev opravimo s klicem metode `results` in jo lahko pokličemo poljubno mnogokrat, ker ne spremeni stanj. (Za več možnosti glede uporabe te metode glejte dokumentacijo v kodi.)

```cpp
qcs qc = qcs("01");
qc.H(0);
qc.results();
```
Output:
```shell
State : Probability
01 : 0.5
11 : 0.5
```

## Invazivno merjenje
Primerljivo z merjenjem v praksi. Zaradi invazivnosti, nam meritev nekega qubita le-tega prisili v stanje bodisi `|0>` bodisi `|1>`. Ta meritev je ireverzibilna, lahko pa se algoritem po njej še nadaljuje. Kličemo jo lahko na željenih qubitih. (Za več možnosti glede uporabe te metode glejte dokumentacijo v kodi.)

```cpp
qcs qc = qcs("01");
qc.H(0);
qc.measure(0);
```
Output:
```shell
Measured qubits: 0
```

### Invazivno merjenje s shranjevanjem
Simulator omogoča tudi shranjevanje meritev v klasičen register.

```cpp
qc.measureAndSave(0, 1); // Izmeri qubit 0 in njegovo vrednost shrani v register 1
```

# Primeri implementiranih vezij
Implementirana so že vezja za kvantno tuneliranje `quantumTeleportationCircuit()`, Deutsch-Jozsca algoritem `algorithmDeutschJozsa` ter "superdense" kodiranje `superdenseCoding`. Pri slednjem lahko podamo poljubno velik niz (v mejah zmogljivosti računalnika - nad 10 qubitov zna povzročati že težave), ki ga dobimo kot rezultat tudi na koncu vezja.

![alt text](https://github.com/SamoFMF/Quantum-Computer-Simulator/blob/main/QuantumTeleportation.png?raw=true)
![alt text](https://github.com/SamoFMF/Quantum-Computer-Simulator/blob/main/DeutschJozsaAlgorithm.png?raw=true)
![alt text](https://github.com/SamoFMF/Quantum-Computer-Simulator/blob/main/SuperdenseCoding.png?raw=true)


