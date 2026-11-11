# Lezione 8 ottobre: VS Code su Mac

Apri in VS Code questa cartella OpenGL_CLASSI con File → Apri cartella.

- main.cpp: punto di ingresso del programma.
- File .h e .cpp nella cartella principale: classi della lezione, già incluse.
- shader/: shader GLSL.
- dependencies_GL_GLFW/: librerie fornite dal docente.
- build/ e app: risultati della compilazione.

## Compilare e avviare

Dal menu Terminale → Esegui attività scegli «Avvia lezione 8 ottobre».
Per compilare soltanto: Cmd+Shift+B.
In alternativa, nel terminale integrato di questa cartella: `make run`.

Servono GLFW e GLM installati con Homebrew. I file .vcxproj e .vstemplate sono per Visual Studio su Windows; su Mac si usa il Makefile aggiunto.

## Aggiungere una classe

In Esplora file di VS Code crea NomeClasse.h e NomeClasse.cpp nella stessa cartella di main.cpp. Nel .h scrivi la dichiarazione della classe; nel .cpp includi "NomeClasse.h" e scrivi le implementazioni. Includi "NomeClasse.h" nei file che la usano. Il Makefile include automaticamente tutti i .cpp di questa cartella.

Le classi del materiale (Geometry, Scene, Renderer, Shader, ShapeGenerator, Input, Gui e ShaderMaker) sono già presenti: non occorre ricrearle o registrarle in VS Code. MeshData.h contiene la struttura dei dati della mesh.
