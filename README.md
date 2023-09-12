# Random File Generator
This app allows you to generate random files, of random sizes.
## Usage
### Windows
```
> rfg.exe -s 512 -o randomFile.ext
> rfg.exe --size 2048 --out randomFile2.ext
```
### Linux
```
$ ./rfg -s 512 -o randomFile.ext
$ ./rfg --size 2048 --out randomFile2.ext
```
## Download
- [Windows(x64)](https://github.com/korayustundag/RandomFileGenerator/releases)
- [Linux(amd64)](https://github.com/korayustundag/RandomFileGenerator/releases)
## Build From Source
### Requirements
#### Windows
- [Visual Studio](https://visualstudio.microsoft.com/)
#### Linux
- [GCC and G++](https://gcc.gnu.org/)
- [Make](https://www.gnu.org/software/make/)
### Build (Linux)
```bash
#Debug
$ make

#Release
$ make release

#Pack
$ make pack
```
## License
Random File Generator is licensed under the GPLv3 License. See the [LICENSE](https://github.com/korayustundag/RandomFileGenerator/blob/main/LICENSE) file for details.
