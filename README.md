# Capture the flag

A binary named _server_ was provided without execution instructions or a description of what it does. The idea was to discover by our own means using reverse engineering how to interact with it.
Once we understood how the binary works, we had to develop a C program that replicates the behavior of the provided binary as well as a C program to interact with it.

## Requirements 📋
The following image is needed to compile and run the files inside:

```
docker pull agodio/itba-so:1.0
```
## Compilation 🛠️
Create a container with the project's folder as its root:
```
docker run -v "${PWD}:/root" --security-opt seccomp:unconfined -ti agodio/itba-so:1.0
```

Once inside the container, into root and then run:
```
make all
```

## Execution 🚀
First, run the server in background

```
./server &
```


After that execute the client

```
./client
```