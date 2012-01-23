Intel Profiler Simple Example
================================================================================
This is a simple Gaudi algorithms for test  [Intel Profiler][profiler].

Installation
--------------------------------------------------------------------------------
1. You need to compile Intel Profiler. Instruction is [here][profiler].
2. Clone IntelProfilerExample repository to your project directory and compile it:

```sh
$> cd ~/cmtuser/Gaudi_HEAD
$> git clone git://github.com/mazurov/IntelProfilerExample.git
$> make -j
```

Run
--------------------------------------------------------------------------------
```sh
$> intelprofiler -o ~/profiler IntelProfilerExample/options/IntelProfilerExample.py 
```

Analyze
--------------------------------------------------------------------------------
### GUI
```sh
$> amplxe-gui ~/profiler/r000hs
```

### Command line



[profiler]: https://github.com/mazurov/IntelProfiler