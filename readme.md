# CPP study repository

- This is a study/sandbox C++ repository


## How to operate the repository
- To format the complete code base with clang-format:
```bash
./bbuild.sh -f
```

- To build the helloworld:
```bash
./bbuild.sh -b helloworld
```

- To rebuild the helloworld:
```bash
./bbuild.sh -r helloworld
```

- To execute the built binary of the helloworld:
```bash
./bbuild.sh -e helloworld
```

- To format, build and execute the helloworld:
```bash
./bbuild.sh -f -b -e helloworld
```

- Examples: 
```bash
./bbuild.sh -v -f -r -e helloworld # To format, rebuild and execute the helloworld in verbose mode
```

- To check all options available:
```bash
./bbuild.sh --help
```
