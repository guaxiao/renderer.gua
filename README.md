# renderer.gua
software 3D renderer


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

### Linux
First of all, you should install libsdl-1.2.25 by yourself.

In Debian, you can use commands below to install it:
```
sudo apt-get install libsdl1.2debian libsdl1.2-dev
```

Then, you can run ```make``` to compile the renderer.

After compilation, you can use ```./gua3d ``` to launch it.

## Licence
Apache 2.0

