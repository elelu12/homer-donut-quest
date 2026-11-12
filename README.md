## Organizzazione delle cartelle

- `src/`: implementazioni C++, incluso `main.cpp`.
- `include/`: dichiarazioni delle classi e strutture (`.h`).
- `shader/`: programmi GLSL.
- `dependencies_GL_GLFW/`: librerie del laboratorio.
- `build/`: file generati dalla compilazione, esclusi da Git.

Compilare e avviare dalla cartella principale con `make run`.
I percorsi del progetto Visual Studio sono aggiornati, ma la sua configurazione
conserva i segnaposto del template e deve ancora essere completata e provata su Windows.

# Interactive 2D World — base del progetto

Repository locale inizializzata a partire da `laboratori/Laboratorio 8 Ottobre 2026-20261008/OpenGL_CLASSI`.
## Avvio su Mac

Servono Xcode Command Line Tools, GLFW e GLM. Il Makefile cerca Homebrew in `/opt/homebrew`: su Mac Intel potrebbe essere necessario adattare i percorsi a `/usr/local`. Dalla cartella di questo README:

```sh
make
make run
```

Avviare dalla cartella del progetto perché gli shader sono caricati con percorsi relativi. `build/` e `app` sono generati dalla compilazione e sono esclusi da Git.

## Cosa offre la base

- `main.cpp`: inizializzazione finestra e contesto, caricamento shader, ciclo di rendering e rilascio risorse.
- `MeshData`, `ShapeGenerator`, `Geometry`: dati e creazione delle forme, caricamento e disegno della geometria.
- `Scene`, `Renderer`, `Shader`, `ShaderMaker`: contenitore della scena, disegno e gestione shader.
- `Input`, `Gui`: callback GLFW e pannello ImGui per colore di sfondo e wireframe.
- `shader/`: shader degli oggetti; `dependencies_GL_GLFW/`: componenti del materiale di laboratorio.

La cancellazione a colore uniforme non è uno shader di sfondo. Homer è ancora composto da ellissi: le forme Hermite devono essere aggiunte. La scena attuale non dimostra le istanze indipendenti richieste. I file Visual Studio provengono dal template e contengono segnaposto: **manca una soluzione `.sln` pronta e la build Windows va sistemata e verificata**.

## Documentazione di progetto

La proposta iniziale, i requisiti, la mappa delle modifiche e le questioni aperte sono in [IDEA_E_REQUISITI.md](IDEA_E_REQUISITI.md). L'idea scelta è un gioco ambientato a Springfield con Homer, ciambelle e verdure; è una scelta progettuale, non un requisito della docente.

## Prima versione di Homer

`Homer.cpp` compone testa, corpo, arti e dettagli usando le ellissi di `ShapeGenerator`. Ogni parte riutilizza una geometria per colore e ha una matrice locale; una matrice comune permette di trasformare l’intero personaggio. Questa è una prima bozza statica: movimento, Hermite e meccaniche sono ancora da realizzare.

## Movimento di Homer

Frecce o WASD muovono Homer; Esc chiude la finestra. `Input` legge i tasti,
`Player` conserva posizione e velocità e produce la matrice comune di Homer.
Il movimento usa delta time, normalizza le diagonali e limita il personaggio ai bordi.
Quando ImGui cattura la tastiera o la finestra perde il focus il movimento si ferma.
La scena usa ancora coordinate da -1 a +1: il mantenimento delle proporzioni al
ridimensionamento della finestra resta da implementare. Raccolta e animazione degli arti
non sono ancora presenti.

## Percorso a scorrimento laterale

Il mondo va da x=0 a x=10. Homer cammina sulla strada con frecce o WASD;
la camera lo segue orizzontalmente e si ferma ai confini. `Camera` calcola vista
 e proiezione ortografica rispettando le proporzioni della finestra.
`Landscape` costruisce le prime facciate stilizzate della casa e di Moe's.
Le cinque ciambelle e la Duff sono distribuite lungo la strada; il broccolo
pattuglia la zona centrale. Le collisioni usano coordinate del mondo, non dello schermo.
Ricomincia ripristina anche la camera attraverso la posizione iniziale del giocatore.
Il cielo è ancora un colore uniforme: shader dedicato e camminata animata restano da aggiungere.
