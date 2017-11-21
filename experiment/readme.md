# CPTCLD Experiment

## Usage
### Compile

- Using Makefile
Get into experiment folder, and try following command:

```bash
$ make
```

Once compiling process is done and successful, you will see a prompt as following:

```bash
> launch has been succesfully compiled
```

More `make` commands please read Makefiles.

- Manually Compile with g++
> g++ -std=c++11 -I ./include main.cpp ./src/tester.cpp ./src/scheduler.cpp ./src/[customized scheduler]* -o [target file]

e.g.
> g++ -std=c++11 -I ./include main.cpp ./src/tester.cpp ./src/scheduler.cpp ./src/scheduler_null.cpp -o test.exe

### Run

- 0 arg
> ./launch
- 1 arg
> ./launch [scheduling algorithm]
- 2 args
> ./launch [scheduling algorithm][testcase]
- 3 args
> ./launch [scheduling algorithm][testcase] [testresult]