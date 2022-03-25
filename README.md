# vd-najmanji-zaklapajuci-pravougaonik
### Za dati skup 𝑆 tačaka u ravni, potrebno je odrediti pravougaonik najmanje površine koji obuhvata sve tačke iz S

Za dati skup 𝑆 tačaka u ravni, potrebno je odrediti pravougaonik najmanje površine koji 
obuhvata sve tačkeiz 𝑆. Najprije dokazati da jedna stranica tog pravouganika sadrži bar dvije 
tačkeiz 𝑆,a zatim implementirati što optimalniji algoritamkoji pronalazi ovaj pravougaonik 
(broj bodova zavisi od optimalnosti algoritma).Analizirati vremensku i prostornu složenost 
algoritma. Stranice pravougaonika ne moraju biti paralelne koordinatnim osama. Obavezno 
izvršitivizualizaciju.
Dokaz:
Neka je zadat konveksni omotač P.Pretopstavimo suprotno da ne postoji najmanji pokrivajući 
pravougaonik K takav da sadrži jednu od ivica omotača.
Trivijalno je dokazati da pravougaonik mora sadržati bar 4 tačke skupa S ( još uvije nismo 
dokazali da sadrži ivicu u ovom trenutku), jer inače bi ga uvijek mogli smanjiti za dio između 
jedne od ivica I njoj najbliže tačke ( mogli bi smo smanjiti širinu, odnosno visinu kako bi 
dobili pravougaonik koja zaklapa sve tačke manje površine). 


Neka je izabrani pravougaonik K takav da se poklapa sa nekim od pravougaonika dobijenih 
algoritmom Rotating calipers ( koji radi na principu da od svake ivice računa najmanji 
poklapajući pravougaonik) time on sadrži ivicu čime dokaz je gotov.
Sad razmortimo I drugi slučaj. Ukoliko je pravougaonik K izabran tako da sadrži 4 vrha (npr. 
nađimo pravougaonik koji je paralelan x I y osama. Njega lako mozemo naći pomoću 
koordinata extrema datog pravougaonika. To znači tački u kojima omotač ima najveće, 
odnosno najmanje vrijednosti po x I y osama) ali ne I stranicu tada pristupamo rotiranju 
pravougaonika. To radimo tako ( odnosno sve dok ne dobijemo ) da je jedna od ivica omotača 
podudarajuća sa stranicom minimalnog zaklapajućeg pravougaonika. Nakon rotiranja 
primjetimo da smo zadržali tri tačke koje su bile u prethodnom ( početnom pravougaoniku a u 
kojim je dodirivao omotač) a preostalu tačku je potrebno naći. Ovim smo dobili kontradikciju 
sa pretpostavkom da ne postoji najmanji pokrivajući pravougaonik takav da sadrži stranicu 
konveksnog omotača. Znači postoji. Q.e.d.
Napomena: ovim postupkom je također moguće I smanjiti površinu drugim. 

## Algoritam: 

+ Najprije odredimo konvexni omotač zadanog skupa tačaka S. Njega možemo odrediti u 
vremenu O (n log n) pomoću algoritma Graham Scan koji smo implementirali na 
vježbama.
+ For petljom prođi kroz ivice omotača. To možemo uraditi na način da prođemo kroz sve 
tačke omotača I sa svakom tačkom spojimo joj prethodnog susjeda. Kako prolazimo kroz 
sve tačke omotača (neka ih ima n) to ćemo vršiti I n spajanja sa prethodnom. Znači imamo 
provjeru za n duži. Prolazak kroz svih n tačaka petljom uzima O(n) vremena. 
+ Za svaku ivicu omotača odredimo najudaljeniju tačku od nje (po euklidovoj metrici). To 
radimo efikasno pomoću binarne pretrage ( bitoniče). Ova binarna pretraga je specifična 
po tome što radi za vrijednosti koje nisu sortirane od najmanje ka najvećoj, već 
vrijednosti imaju osobinu da rastu dok ne dosegnu svoj maksimum te nakon toga opadaju. 
Binarna pretraga nam vraća upravoj taj elemenat ( extrem) nakon kojeg se mijenja 
ponašanje vrijedosti. Kako je u pitanju ipak binarna pretraga (iako malo modifikovana) 
njena vremenska složenost je O(log n), kako u svakom koraku možemo odbaciti pola 
vrijedosti ( odnosno zanemariti ih). Binarna pretraga zahtijeva tri pokazivača prema 
elementima, bez obzira na veličinu niza. Stoga, prostorna složenost binarnog 
pretraživanja je O(1).
+ Provjerimo da li je najudaljenija tačka, krajnja desno. Odnosno da li se sve ostale tačke 
nalaze lijevo od nje. Ukoliko da imamo specijalan slučaj. To radimo poću provjere 
udaljenosti njene projekcije I projekcija njenih susjeda.
+ Razmotrimo slučaj ukoliko tačka nije specijalni slučaj. Tad pozivamo ponovo binarnu 
pretragu u odnosu na pravu koja sadrži najudaljeniju tačku, te tačku njene projekcije na 
posmatranu ivicu. Kako trebamo naći dva ekstrema, to je pozivamo dva puta. Jednom za 
stranu od početka posmatrane ivice do najudaljenije. Drugi put obratno. Što se tiče 
složenosti sve je već I ranije spomenuto.
+ U drugom slučaju tražimo samo sa jedne strane najdalju tačku od prave koja sadrži 
najudaljeniju I njenu projekciju. Nakon što smo je našli iz nje povučemo projekciju na
posmatranu ivicu, te od nje (projekcije) I orginala (najudaljenije, odnosno trećeg 
ekstrema) tražimo preostali ekstrem kao najudaljenu. Projekcija se vrši u konstantnom 
vremenu a pretraga za najudaljenijim pomoću već spomenute binarne pretrage, tako da 
što se tiče složenosti I dalje ostaje ista. 
+ Do sad smo ispitali slučajeve I našli tačke ekstrema čijim spajanjem dobijamo visinu I 
širinu pravougaonika. Provjerimo da li je trenutna površina datog pravougaonika manja od 
do sad najmanje. Te ukoliko jeste do sad najmanju površ postavimo na trenutnu, te 
spasimo tačke extrema ( čijim projekcijama ćemo dobiti konačni pravougaonik). Kako se 
sve vrši u konstantnom vremenu, ovdje možemo navesti čitavu složeost algoritma. 
Vremenska složenost: Prolaskom za n tačaka ( odnosno n ivica) imamo O(n). Primjenom 
svake binarne pretrage imamo dodatno O( logn). Kako se niti jedna binarna pretraga ne 
poziva unutar druge , a n puta ih pozivamo to krajnje vrijeme daje O(nlogn). Prostorna 
složenost je pak n (samo čuvamo vektor od n elemenata).
+ Na kraju spojimo samo susjedne ekstreme, tj njihove projekcije kako bi dobili traženi 
pravougaonik.

![Primjer 1.](https://user-images.githubusercontent.com/96734106/160119697-abcaa789-f188-4db4-a312-8e12ab090d57.png)
![Primjer 2.](https://user-images.githubusercontent.com/96734106/160119767-05277d71-b913-4c95-b952-8e061de4644b.png)
![Primjer 3.](https://user-images.githubusercontent.com/96734106/160119828-3423c79b-c3fa-44cd-8634-6209199860e8.png)

