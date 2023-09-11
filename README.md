<p>Instrukcja by ETI PG</p>
<p>Celem zadania jest napisanie prostego silnika przetwarzającego CSS-y. W ramach zadania należy wczytać ze standardowego wejścia sekcje CSS przeplatane sekcjami komend. Sekcje CSS należy sparsować i umieścić w odpowiednich strukturach, sekcje komend należy sparsować i wykonać wypisując na standardowe wyjście ew. rezultaty (po  ==).</p>

<p><b>CSS</b></p>
<ul>
<li>Przetwarzanie rozpoczyna się wczytania deklaracji CSS. CSS jest syntaktycznie poprawny i składa się bloku atrybutów ew. poprzedzonych selektorami. Brak selektorów jest legalny (oznaczałby atrybuty aplikowane do wszystkiego). </li>
<li>Selektory (selectors) są separowane przecinkami. Dopuszczalne są selektory legalne dla CSS, ale można założyć, że nie zawierają znaków przecinka ani nawiasów klamrowych.</li>
<li>Blok atrybutów ujęty jest w nawiasy klamrowe.</li>
<li>Atrybuty są oddzielone średnikami i składają się z nazwy (property) i wartości (value) oddzielonych dwukropkiem. Po ostatnim atrybucie w bloku może, ale nie musi  nastąpić średnik.</li>
<li>Jako wartości atrybutów mogą występować legalne dla CSS konstrukcje, jednak dla uproszczenia można bezpiecznie założyć, że ew. napisy nie są złośliwe tj. nie zawierają escapowanych znaków cudzysłowu, nawiasów klamrowych lub średników.</li>
<li>Jeśli konkretny atrybut (nazwa) w bloku występuje więcej niż raz należy potraktować to jako jedno wystąpienie, przy czym znacząca jest ostatnia wartość). </li>
<li>Zarówno selektory, nazwy atrybutów jak i wartości atrybutów nie wymagają interpretacji semantycznej tj. traktujemy je (po odrzuceniu skrajnych białych znaków, jako wartość. Tj. np.: 'margin-left : 8px', 'margin: 4px 7px 4px 7px' traktujemy jako oddzielne, niezwiązane atrybuty o nazwach odpowiednio 'margin-left' i 'margin' i  wartościach '8px' oraz '4px 7px 4px 7px' Podobnie, selektory są traktowane jako wartość i nie wymagają interpretacji tj. np.: 'h1' i 'h1.theme' traktujemy jako oddzielne, niepowiązane selektory.</li>
<li>Uproszczenie: CSS nie zawiera komentarzy, ani selektorów typu @, bloki nie mogą się zagnieżdżać.</li>
<li>Dla potrzeb testów można założyć, że żaden selektor ani atrybut nie jest podzielony na kilka linii (ciągle w jednej linii może być kilka separatorów/ i lub atrybutów).</li>
</ul>
<p><b>Komendy </b></p>
<i>W poniższych komendach i oraz j to dodatnie liczby całkowite (mieszczą się w int), natomiast n to legalna nazwa atrybutu.
???? – początek sekcji komend;
</i>
<ul>
<li>**** - wznów czytanie CSS;</li>
<li>? – wypisz liczbę bloków CSS;</li>
<li>i,S,? – wypisz liczbę selektorów dla bloku nr i (numery zaczynają się od 1), jeśli nie ma takiego bloku pomiń;</li>
<li>i,A,?  - wypisz liczbę atrybutów dla bloku nr i, jeśli nie ma takiego bloku lub bloku pomiń;</li>
<li>i,S,j – wypisz j-ty selector dla i-tego bloku (numery bloków oraz atrybutów zaczynają się od 1) jeśli nie ma bloku lub selektora pomiń;</li>
<li>i,A,n – wypisz dla i-tego bloku wartość atrybutu o nazwie n, jeśli nie ma takiego pomiń;</li>
<li>n,A,? – wypisz łączną (dla wszystkich bloków) liczbę wystąpień atrybutu nazwie n. (W ramach pojedynczego bloku duplikaty powinny zostać usunięte na etapie wczytywania). Możliwe jest 0;</li>
<li>z,S,? – wypisz łączną (dla wszystkich bloków) liczbę wystąpień selektora z. Możliwe jest 0;</li>
<li>z,E,n – wypisz wartość atrybutu o nazwie n dla selektora z, w przypadku wielu wystąpień selektora z bierzemy ostatnie. W przypadku braku pomiń;</li>
<li>i,D,* - usuń cały blok nr i (tj. separatory+atrybuty), po poprawnym wykonaniu wypisz deleted;</li>
<li>i,D,n – usuń z i-tego bloku atrybut o nazwie n, jeśli w wyniku operacji pozostaje pusty blok powinien zostać również usunięty (wraz z ew. selektorami), po poprawnym wykonaniu wypisz deleted.</li>
</ul>
<p><b>Uwagi implementacyjne</b></p>
<p>Selektory oraz atrybuty powinny być przechowywane jako listy.
Poszczególne bloki CSS powinny być zorganizowane jako lista dwustronna (aby efektywnie realizować komendę E – ostatnie wystąpienie atrybutu). Aby lepiej wykorzystać pamięć lista powinna obejmować tablicę T=8 struktur reprezentujących blok (gdzie T jest stałą możliwą do zmiany w czasie kompilacji) oraz licznik zajętych aktualnie struktur (z uwagi na ew. kasowanie elementów). Liczniki warto wykorzystać dla przyśpieszenia operacji parametryzowanych numerem komórki tj. i.</p>
<p>Przy alokowaniu nowego węzła tworzona jest tablica T elementowa. Przy dodawaniu elementów, o ile jest wolne miejsce w węźle listy, należy je wykorzystać zanim alokowane zostaną nowe węzły. Jeżeli w przypadku usuwania elementów pozostanie pusta tablica należy węzeł usunąć. Nie trzeba przesuwać elementów miedzy węzłami, łączyć węzłów itd.</p>
 
