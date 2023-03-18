# Neo Studio

This program aims to be a modding tool for Dragon Ball Z: Budokai Tenkaichi 2.

As of yet, Neo Studio can only edit general, melee and ki blast related character parameters.

This program is **not** a replacement for Sparking Studio, but rather meant to be an Open-Source alternative to it, which focusses on the second entry of this series specifically. I do not have plans of making this program support Tenkaichi 3, nor is it meant to compete with Sparking Studio in any way.

## Usage

Neo Studio uses either character files in the .pak, or singular parameter sections via the .dat format.

If you don't own these files, there are AFL files in the **"AFLs"** folder. Use these with AFS Explorer and their respective AFS file to extract the .pak files.

As for .dat files, those require the character .pak to have been unpacked via [HiroTex's SpikeSoft tool](https://github.com/hirotex/SpikeSoft).

## Download Requirements

To use the application, go on the **Releases** tab and download the latest version.

There isn't much else to say, using it shouldn't be an issue.

## Build Requirements
To build the application, you need:

- Qt5 (5.15)
- CMake 2.8.11 (or higher)


### Build Instructions

Go into the project directory and type

```
cmake ./
make
```

after this is finished, you should have a Neo Studio executable.

## Credits

- [HiroTex](https://github.com/hirotex) for supplying the AFL files and knowledge of the .pak file structure
- [ViveTheModder](https://github.com/ViveTheModder) for giving feedback and pointing out mistakes

