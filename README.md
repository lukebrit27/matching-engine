# Matching Engine


## Background


## Features


## Requirements

- C++20 compatible compiler
- CMake (version 3.12 or higher)
- python3 

## Build and Install

1. Clone the repository or download the source code.
2. Navigate to the project directory.
3. Run `python3 matching-engine/setup.py bdist_wheel` to build. This will produce a wheel file in the `dist` directory.
4. Create a new python venv in a directory of your choosing e.g. 
```
mkdir matching-engine-pytest;
cd matching-engine-pytest;
python3 -m venv .venv;
```
5. Install the wheel file:
```
./.venv/bin/pip install ../../c++proj/matching-engine/dist/matching_engine-0.0.1-cp310-cp310-linux_x86_64.whl
```
6. Start python with `./.venv/bin/python3` and import the newly installed library `import matching_engine as engine`


## Usage


## Contributing

Contributions are welcome! If you find any issues or have suggestions for improvement, please let me know.

## License

## Additional Information

### Single Binary Encoding

The Single Binary Encoding (SBE) code was generated using https://github.com/OleksandrKvl/sbepp . Great tool that's very easy to install and use from the C++ developer perspective (in comparison to the offical RealLogic version). Recommend checking it out!

Command used to generate the code:
    - `sbeppc --output-dir test/ schemas/schemas.xml`
