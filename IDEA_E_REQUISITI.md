# Idea e requisiti — prima bozza

## Idea scelta: Homer a caccia di ciambelle

A Springfield, Homer raccoglie almeno cinque ciambelle evitando verdure in movimento. Le birre danno punti extra; Burns è una possibile aggiunta successiva, soltanto dopo aver completato i requisiti fondamentali. Frecce o WASD controllano Homer. Al contatto con una verdura Homer torna al punto iniziale e riceve un messaggio visibile. Il contatore mostra ciambelle raccolte e punteggio; la vittoria scatta quando tutte e cinque le ciambelle sono state raccolte.

- **Homer:** personaggio composto da almeno tre parti distinguibili, per esempio testa, corpo, braccia e gambe. Le parti sono disegnate con trasformazioni locali rispetto a una trasformazione comune; durante il movimento le gambe oscillano.
- **Due forme Hermite:** una parte riconoscibile del contorno di Homer e una verdura, per esempio un broccolo. La parte di Homer deve muoversi insieme al personaggio: così almeno una delle forme Hermite ha un ruolo dinamico. Verificare che le due forme siano distinguibili e spiegabili in sede di discussione.
- **Istanze:** almeno cinque ciambelle condividono una mesh e hanno posizione, trasformazione e stato di raccolta indipendenti. Quelle raccolte scompaiono.
- **Sfondo:** shader separato con gradiente del cielo e una variazione cromatica leggera nel tempo. Case e centrale stilizzate possono arricchire Springfield.
- **Animazioni:** gambe di Homer mentre cammina e oscillazione o movimento di una verdura; aggiornamento basato sul delta time.
- **Meccanica aggiuntiva:** verdure come ostacoli, con collisioni approssimate tramite cerchi o rettangoli, reset della posizione e feedback visibile. Le birre sono un bonus facoltativo: 2 punti ciascuna, mentre una ciambella vale 1 punto.

## Requisiti della specifica

- C++ con OpenGL e GLSL; possono essere utilizzati GLFW, GLAD, GLM e ImGui e il codice dei laboratori, rendendo riconoscibile il proprio contributo.
- Un oggetto composto da almeno tre parti geometriche distinguibili, assemblate tramite trasformazioni; almeno due oggetti distinti modellati con curve cubiche di Hermite, di cui almeno uno interattivo o dinamico. È ammesso campionare e triangolare i contorni oppure usare il modellatore ed esportare OBJ/MTL.
- Traslazione, rotazione, scala e una composizione non banale con matrici omogenee e model matrix, senza riscrivere la mesh a ogni frame; almeno tre istanze simultanee della stessa geometria, con stato e trasformazioni indipendenti.
- Almeno due shader program con effetti differenti: uno dedicato allo sfondo con effetto riconoscibile e uno o più per gli oggetti, con attributi, matrici e uniform gestiti correttamente.
- Due comportamenti animati, uno legato all'elemento controllato e uno a un altro elemento, entrambi indipendenti dal frame rate tramite delta time.
- Controllo dell'elemento principale; raccolta di almeno cinque oggetti con cambio di stato o scomparsa e indicatore visibile; una meccanica aggiuntiva, come ostacoli. Collisioni e feedback appropriati.
- Separare ragionevolmente geometrie, scena/istanze, shader/renderer, input, animazione e logica, evitando duplicazioni e dipendenze globali superflue.
- Verificare avvio, shader, geometrie, trasformazioni/istanze, animazioni, interazioni e collisioni prima della consegna.

## Da modificare rispetto al template

1. Introdurre una distinzione tra mesh condivisa e stato delle istanze; il `Scene` originale contiene geometrie, non il modello di istanze richiesto.
2. Creare forme e dati di gioco, oggetto composto e due contorni Hermite; decidere se importarli dal modellatore o generarli direttamente.
3. Aggiungere model matrix e uniform agli shader degli oggetti; comporre trasformazioni di Homer e delle singole parti.
4. Aggiungere shader e passaggio di rendering dedicati allo sfondo.
5. Implementare input continuo, delta time, animazioni, collisioni, stato delle ciambelle, ostacoli e contatore; separare logica e disegno.
6. Adattare GUI e controlli, documentare contributi e scelte e verificare tutte le funzionalità richieste.
7. Sistemare e provare il progetto Visual Studio con soluzione `.sln`, risorse e dipendenze; il template copiato non è una soluzione Windows già pronta.

## Dubbi tecnici e decisioni da prendere

- **Aspetto e controlli:** definire stile di Homer, disposizione della scena e controlli esatti; partire da forme semplici e riconoscibili.
- **Hermite:** verificare il formato esatto esportato dal modellatore del 5 novembre e scegliere importazione OBJ/MTL oppure generazione diretta; controllare triangolazione delle forme concave.
- **Collisioni:** scegliere raggi o bounding box coerenti con scala e posizione; decidere se il contatto con un ostacolo azzera solo la posizione o anche la raccolta; per ora la proposta conserva le ciambelle già raccolte.
- **Coordinate e ridimensionamento:** scegliere proiezione e gestione aspect ratio prima di posizionare gli oggetti, mantenendo coordinate di gioco coerenti.
- **Windows:** il `.vcxproj` contiene segnaposto da template e non è stato verificato; predisporre `.sln`, controllare dipendenze e percorsi e compilare su Visual Studio prima della consegna.

## Consegna e discussione

Il documento di consegna richiede condivisione su OneDrive entro **24 novembre 2026**, includendo `.sln` e cartella dei sorgenti `.cpp` e `.h`. La specifica richiede inoltre uno ZIP con progetto Visual Studio, sorgenti C++ e GLSL, eventuali OBJ/MTL e risorse, README e una relazione tecnica di circa 3–5 pagine con immagini e spiegazione delle scelte; escludere file temporanei. Predisporre entrambi gli insiemi di materiali e verificare con la docente se lo ZIP vada condiviso insieme ai file esplicitamente richiesti.

La discussione è indicata per il **26 novembre 2026**: preparare PowerPoint su obiettivo, funzionalità, classi, eventi, collisioni e parti significative del codice, oltre alla verifica orale di teoria. Le date sono quelle riportate nei documenti disponibili.
