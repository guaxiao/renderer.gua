# renderer.gua
software 3D renderer

## Screenshots
![Jelly Cube](https://raw.githubusercontent.com/guaxiao/renderer.gua/dev/screenshots/jellycube.png)
![Illidan Wireframe](https://raw.githubusercontent.com/guaxiao/renderer.gua/dev/screenshots/illidan_wireframe.png)
![Illidan](https://raw.githubusercontent.com/guaxiao/renderer.gua/dev/screenshots/illidan.png)


## Usage

### OS X
```shell
sh install_mac_sdl.sh 
make osx
./gua3d
```

### Windows (MinGW32)
```shell
build_win_mingw.bat
gua3d
```

### Windows (Visual Studio 2013 / Visual Studio 2015)
double click `projects/vs2013/renderer.gua.sln` or `projects/vs2015/renderer.gua.sln`

then press `F5` to lunch it

note: `Debug` config will have a console window, `Release` config won't

tested with `vs2013` and `vs2015` under `winodws 8.1`

### Linux
```shell
# Depends on libsdl1.2-dev. For Ubuntu: sudo apt-get install libsdl1.2-dev.
make linux
./gua3d
```

## Licence
Apache 2.0

