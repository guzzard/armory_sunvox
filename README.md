# SunVox in Armory

Simple example implementation to play [SunVox](http://www.warmplace.ru/soft/sunvox/) modules within [Armory](http://armory3d.org/)/[Kha](http://kha.tech/). See [JS demo](http://warmplace.ru/soft/sunvox/jsplay/) of SunVox.

Download the [SunVox library for developers](http://www.warmplace.ru/soft/sunvox/) and put library and a sample song in folder 'Bundled'.

# SunVox in Kha

The library is usable in any Kha based project. After placing [SunVox library for developers](http://www.warmplace.ru/soft/sunvox/) into `kha_example/Assets`, open terminal at `kha_example/` and execute `node path/to/Kha/make --run`. Note: on Windows, sunvox.dll depends on `libgcc_s_sjlj-1.dll` available from [here](https://sourceforge.net/projects/mingw-w64/files/Toolchains%20targetting%20Win32/Personal%20Builds/mingw-builds/7.1.0/threads-posix/sjlj/i686-7.1.0-release-posix-sjlj-rt_v5-rev2.7z).
