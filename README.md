# Svg

A debug utility library to aid in visualizing problems.  

## Testing

The Test directory is setup to work with [googletest](https://github.com/google/googletest).

## Building

![A1](https://github.com/chcly/Module.Svg/actions/workflows/build-linux.yml/badge.svg)
![A2](https://github.com/chcly/Module.Svg/actions/workflows/build-windows.yml/badge.svg)

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