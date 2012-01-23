Intel Profiler Simple Example
================================================================================
This is a simple Gaudi algorithms for test  [Intel Profiler][profiler].
CpuHungryAlg algorithms define 4 functions:

```cpp
  double mysin();
  double mycos();
  double mytan();
  double myatan();
```

, which we would like to profile. Execution of this functions depends on
name of algorithm.

```cpp
StatusCode CpuHungryAlg::execute() {
  m_nevent++;
  double result = 0;
  if (name() == "Alg1") {
    result = mysin();
  }else if (name() == "Alg2") {
    result = mycos();
  }else {
    result = mytan();
  }
  return StatusCode::SUCCESS;
}
```


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
* Hot spots report:
```sh
amplxe-cl -report hotspots -r ~/profiler/r000hs
```

As a result you can see something like this:

```
Executing actions 74 % Generating a report                                     
Function        Module  CPU Time
CpuHungryAlg::myatan    libIntelProfilerExample.so      0.389
CpuHungryAlg::mytan     libIntelProfilerExample.so      0.380
CpuHungryAlg::mysin     libIntelProfilerExample.so      0.267
CpuHungryAlg::mycos     libIntelProfilerExample.so      0.250
check_cast<extends2<Service, IMessageSvc, IInactiveMessageCounter>>::operator()<Gaudi::InterfaceId<IInterface, (unsigned long)0, (unsigned long)0>>     libGaudiSvc.so  0.023
Executing actions 99 % done   
```

* Report by algorithm chain:

```sh
$> amplxe-cl -report hotspots -r ~/profiler/r000hs --group-by task
```

Result:

```
Executing actions 74 % Generating a report                                     
Task Type       CPU Time
TopSequence SubSequence Alg3    0.769
TopSequence SubSequence Alg1    0.267
TopSequence SubSequence Alg2    0.250
Executing actions 99 % done
```


[profiler]: https://github.com/mazurov/IntelProfiler