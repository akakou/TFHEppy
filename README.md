# TFHEppy

## How to build

```sh
git clone  --recursive https://github.com/kenmaro3/TFHEppy
mkdir TFHEppy/build
cd TFHEppy/build
cmake ..
make
```

## How to run tutrial

```sh
# after build
# shell on git project root
cp tfheppy.cpython-39-x86_64-linux-gnu.so ./tutorial/
cd ./tutorial
python3 train.py && python3 t.py
```

## How to use development environment

To start working with this repository, you need to use Devcontainer.

1. Open this repository in Visual Studio Code.
2. From the Command Pallete, select *Remote-Containers: Open Folder in Container...* and open this repository.
3. After build, VSCode's window releoads and opens the folder inside a container.
