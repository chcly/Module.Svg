# Svg

A debug utility library to aid in visualizing problems.  

## Testing

The Test directory is setup to work with [googletest](https://github.com/google/googletest).

## Building

Building with CMake and Make.

```sh
mkdir build
cd build
cmake .. -DSvg_BUILD_TEST=ON -DSvg_AUTO_RUN_TEST=ON
make
```

### Optional defines

| Option                        | Description                                          | Default |
| :---------------------------- | :--------------------------------------------------- | :-----: |
| Svg_BUILD_TEST         | Build the unit test program.                         |   ON    |
| Svg_AUTO_RUN_TEST      | Automatically run the test program.                  |   OFF   |
| Svg_USE_STATIC_RUNTIME | Build with the MultiThreaded(Debug) runtime library. |   ON    |