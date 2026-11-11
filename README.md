# Interactive 2D World — base del progetto

Repository locale inizializzata a partire da `laboratori/Laboratorio 8 Ottobre 2026-20261008/OpenGL_CLASSI`. È un punto di partenza didattico: la scena mostra una prima versione di Homer composta da ellissi; **non è ancora il progetto d'esame**. I file originali dei laboratori restano nella cartella superiore.

## Avvio su Mac

Servono Xcode Command Line Tools, GLFW e GLM (ad esempio installati con Homebrew). Il Makefile cerca Homebrew in `/opt/homebrew`: su Mac Intel potrebbe essere necessario adattare i percorsi a `/usr/local`. Dalla cartella di questo README:

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
