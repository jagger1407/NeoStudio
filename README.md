# Neo Studio

This program aims to be a modding tool for Dragon Ball Z: Budokai Tenkaichi 2.

As of yet, Neo Studio can only edit general character parameters. The ground work is set however, and once I'm able to resume my work on this program, adding melee, ki blast and movement parameters will be very easy.


## Usage

Neo Studio uses character files in the .pak format.

If you don't own these files, there are AFL files in the **"AFLs"** folder. Use these with AFS Explorer and their respective AFS file to extract the .pak files.


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

