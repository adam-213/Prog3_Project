Semestralny Projekt
Inteligentna chladnicka
Adam Chrenko

Projekt rozdeleny do ~6 subproblemov
Vela class je rozdelenych medzi viac .cpp suborov - nerad scrollujem aj ked to bolo stale nutne.

1) Datumy
Pre datumy je vytvorena trieda s plne definovanymi porovnavacimi operaciami,
Datum je ulozeny vo formate Dni od zaciatku roku, rok - tento format bol vybrany pretoze ho nezaujimaju mesiace
Ako main format mimo tejto classy je string DD-MM-YYYY,  Samozrejme class Date pouziva tento format ako vstup aj vystup.

2) Predmet
Zakladny stavebny blok celeho projektu
Vcelku jednoduchy objekt, ktory vie svoj datum expiracie, svoje meno a kolko dni bol *vonku.
Vie Nam povedat zopar veci o sebe - napr kolko dni mu chyba do expiracie alebo ci je pokazeny.
Objekt predmet nepozna kopirovanie - len presuvanie, pretoze predmety sa nedaju kopirovat.

3) Policka
Ako naznacuje nazov je to policka v chladnicke.
Tato policka ma definovanu kapacitu - kapacita sa pocita v pocte charakterov v menach jednotivych predmetov.
Taktiez policka vie kolko ma este volnej kapacity - aktualizovane priebezne 
Samozrejme vie co ma v sebe - objetky Predmet, ktore tam boli presunute - nenachadzaju sa nikde inde.

4) Chladicka 
Trieda chladnicka je najvacsia trieda projektu, z vela definovanymi funkciami napr. inventar, objednaj x, alebo poved mi co je po zaruke.
Chladnicka ma prehlad o svojich polickach, dnesnom datume,o objednavkach a o objednavkach co sa nezmestili.
Taktiez vsetky pouzivatelske funkcie maju "cenu" - cena je v akciach - v jeden den je mozne vykonat 3 akcie,
  po prekroceni tohto limitu, den sa automaticky presuva na dalsi - Chladnicka sa doplni o objednavky co maju prist v ten den.

5) Objednavky 
Objednavky funguju na zaklade nahodnych generatorov, ktore vygeneruju datum prichodu a datum expiracie.
Objednat je mozne predmet alebo viac predmetov podla mena.
Ked datum dosiahne datum prichodu - tieto predmety sa automaticky vlozia do chladnicky
  alebo ak na ne nie je miesto tak do policky mimo chladnicky z "nekonecnou" kapacitou.
Na tejto vonkajsej policke vsetky predmety expiruju 2x rychlejsie.
Predmety na tejto vonkajsej policke su prioritizovane na vklad do chladnicky 
Tato policka nie je pristupna pouzivatelovy.
 
6) Subory
Je mozne celu chladnicku vratane objednavok, datumov... vlozit do txt suboru.
Tak isto je mozne nacitat chladnicku z tohto suboru - zakladna detekcia errorov..