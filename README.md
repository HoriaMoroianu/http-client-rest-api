**Nume: Horia-Valentin MOROIANU**\
**Grupa: 324 CA**

# Tema 4 - Client Web

### 1. Structura temei:
Am folosit drept suport de cod scheletul din laboratorul 9, pe care l-am modificat minor pentru a functiona pentru limbajul C++. 

Am adaugat si fisierul `json.hpp` care se ocupa de parsarea datelor. Aceasta alegere a fost facuta deoarece biblioteca [nlohmann](https://github.com/nlohmann/json) a fost usor de integrat si a oferit modalitati simple de a prelucra string-urile in obiecte json si viceversa.

---
### 2. Implementare si dificultati intampinate:
Am reimplementat funtiile din fisierul `requests.cpp` pentru a lucra cu string-uri in loc de char* , adaugand si o functie de generare a unui delete request pentru stergerea unei carti din biblioteca. Acestea au fost implementate minimal, continand strictul necesar pentru rezolvarea cerintelor temei.

Initial, datele introduse de utilizator erau verificate de erori dupa fiecare camp completat si oprite cand se depista un input invalid. Am observat ca ascest lucru genera erori pe checker, asa ca am decis sa fac verificarile dupa completarea tuturor campurilor.

Pentru interactiunea cu server-ul, am creat o functie care primeste mesajul de request si returneaza raspunsul primit de la acesta. Din cauza faptului ca am pastrat implementarea originala a functiei `receive_from_server`, care continea alocari de memorie, am copiat datele intr-o alta variabila si am eliberat memoria alocata, evitand aparitia leak-urilor.

Din raspunsurile server-ului am extras status code-ul si in funtie de acesta am afisat starea de succes a comenzilor. Am ales pentru unele erori sa afisez textul primit de la server, insa pentru altele mi s-a parut ca ofera utilizatorului informatii despre implementare, ceea ce nu ar trebui sa se intample, asa ca le-am schimbat cu altele mai *"user friendly"*.

In ceea ce priveste autentificarea si accesul la bilioteca:
- Comanda `register` poate fi data oricand, neschimband starea de conectivitate a utilizatorului.
- Dupa un `login` esuat, se pastreaza starea de conectivitate a utilizatorului.
- Dupa un `login` efectuat cu succes, utilizatorul va fi autentificat cu noul cont dar pierde accesul la bilioteca.
- Pentru `logout`, similar cu `login`, in caz de succes, utilizatorul este deconectat si pierde accesul la bilioteca, altfel se pastreaza starea anterioara comenzii.

---
### 3. Comentarii asupra temei:
*Am considerat ca nu mai e nevoie de comentarii suplimentare intrucat codul este, din punctul meu de vedere, destul de simplu si de sugestiv!*

Aceasta a fost tema mea preferata din toate cele propuse la PCom. Mi-a placut tematica propusa, a fost explicata bine si a oferit flexibilitate in implementare. De asemenea nu a fost foarte dificila, lucru care a ajutat enorm avand in vedere perioada foarte incarcata de la finalul semestrului.
