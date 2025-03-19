
# miniRT

miniRT est un moteur de raytracing minimaliste écrit en C, basé sur la bibliothèque MiniLibX. Il permet de générer des scènes 3D simples avec gestion de la lumière et des ombres

![Box](https://github.com/Itraya/miniRT/blob/master/imgs/2.png?raw=true)


## Features

- Rendu en raytracing de scènes 3D basiques

- Gestion des objets suivants :
    - Sphères
    - Plans
    - Cylindres

- Lumière ambiante et directionnelle
## Installation

### Prérequis

- Un système macOS

### Compilation

```bash
git clone https://github.com/Itraya/miniRT.git
cd miniRT
make
```

## Utilisation

Lancez le programme avec un fichier de scène :

```bash
./miniRT scenes/test.rt
```

Intéractions :

- L : active/désactive la lumière ambiante
- K : active/désactive la source de lumière
- R : change la couleur de la source de lumière
- Échap : quitter le programme
## Captures d'écran

![Sus](https://github.com/Itraya/miniRT/blob/master/imgs/3.png?raw=true)

![Color](https://github.com/Itraya/miniRT/blob/master/imgs/1.png?raw=true)



## Authors

- [Itraya](https://www.github.com/Itraya)
- [Qwazertyx](https://www.github.com/Qwazertyx)

