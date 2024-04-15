# Matching Engine


## Background


## Features


## Requirements

- C++20 compatible compiler
- CMake (version 3.12 or higher)
- python3
- Dependencies that need to be installed
    - [sbepp](https://github.com/OleksandrKvl/sbepp/tree/main)
- Other dependencies already included in the repo (as header files or git submodules)
    - [spdlog](https://github.com/gabime/spdlog)
    - [pybind11](https://github.com/pybind/pybind11/tree/stable)

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
```
import matching_engine as engine

# create matching engine
eng = engine.Engine()

# instruments that can be traded on the exchange
instruments = ['AAPL','GOOG','MSFT','TSLA','AMZN','NFLX','META','JNJ','V','BA']

# Add file where orders and trades will be written to (sbe format)
eng.addEventListener('/tmp/exchange-data', 'file')

# start the engine
eng.start(instruments)

# submit some orders
eng.submitOrder("AAPL", 2055, 3000, "limit", 'B', "trader1"); 
eng.submitOrder("AAPL", 2055, 33000, "limit", 'B', "trader1"); 
eng.submitOrder("AAPL", 2059, 400, "limit", 'B', "trader1"); 
eng.submitOrder("AAPL", 2056, 1100, "limit", 'B', "trader1"); 
eng.submitOrder("AAPL", 2055, 2000, "limit", 'S', "trader2");

# read the exchange data in as a pandas dataframe
order, trade = engine.decodeFile('/tmp/exchange-data', 0)
order = pd.DataFrame(order)
trade = pd.DataFrame(trade)
```

## Contributing

Contributions are welcome! If you find any issues or have suggestions for improvement, please let me know.

## License

## Additional Information

### Single Binary Encoding

The Single Binary Encoding (SBE) code was generated using https://github.com/OleksandrKvl/sbepp . Great tool that's very easy to install and use from the C++ developer perspective (in comparison to the offical RealLogic version). Recommend checking it out!

Command used to generate the code:
    - `sbeppc --output-dir test/ schemas/schemas.xml`
