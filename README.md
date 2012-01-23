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

, that we would like to profile. Execution of this functions depends on
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
At the end you should see something like that:

```
...
ntelProfilerAu...   INFO Start profiling (event #1)
IntelProfilerAu...  DEBUG   Skip component TopSequence
IntelProfilerAu...  DEBUG     Start profiling component TopSequence SubSequence
IntelProfilerAu...  DEBUG     Start event type 2 for TopSequence SubSequence
IntelProfilerAu...  DEBUG     Pause event 2
IntelProfilerAu...  DEBUG       Start profiling component TopSequence SubSequence Alg1
IntelProfilerAu...  DEBUG       Start event type 3 for TopSequence SubSequence Alg1
IntelProfilerAu...  DEBUG       End event for Alg1
IntelProfilerAu...  DEBUG     Resume event for 2
IntelProfilerAu...  DEBUG       Skip component Alg2
IntelProfilerAu...  DEBUG     Resume
IntelProfilerAu...  DEBUG     Pause event 2
IntelProfilerAu...  DEBUG       Start profiling component TopSequence SubSequence Alg3
IntelProfilerAu...  DEBUG       Start event type 4 for TopSequence SubSequence Alg3
IntelProfilerAu...  DEBUG       End event for Alg3
IntelProfilerAu...  DEBUG     Resume event for 2
IntelProfilerAu...  DEBUG     End event for SubSequence
IntelProfilerAu...  DEBUG   Pause
IntelProfilerAu...  DEBUG     Skip component Alg4
IntelProfilerAu...  DEBUG  Pause
IntelProfilerAu...   INFO Stop profiling (event #2)
ApplicationMgr       INFO Application Manager Stopped successfully
EventLoopMgr         INFO Histograms converted successfully according to request.
ApplicationMgr       INFO Application Manager Finalized successfully
ApplicationMgr       INFO Application Manager Terminated successfully
Using result path `/data/amazurov/Amplifier/IntelProfilingExample/r050hs`
```
, where ``Using result path `/data/amazurov/Amplifier/IntelProfilingExample/r050hs` `` 
is our profiling database.

Analyze
--------------------------------------------------------------------------------
### GUI
```sh
$> amplxe-gui ~/profiler/r000hs
```

### Command line

#### Hot spots report:

```sh
amplxe-cl -report hotspots -r ~/profiler/r000hs
```

If options file looks like this:

```python
#!/usr/bin/env gaudirun.py

from Gaudi.Configuration import *
from GaudiConf.Configuration import *
from Configurables import EventSelector, AuditorSvc, ChronoAuditor, MessageSvc,\
  ApplicationMgr

MessageSvc().OutputLevel = INFO

### GaudiPython ###
from GaudiPython.Bindings import AppMgr
from Configurables import IntelProfilerAuditor, CpuHungryAlg


alg1 = CpuHungryAlg("Alg1")
alg2 = CpuHungryAlg("Alg2")
alg3 = CpuHungryAlg("Alg3")
alg4 = CpuHungryAlg("Alg4")

alg1.Loops = alg2.Loops = alg3.Loops = alg4.Loops = 5000000

app = ApplicationMgr()
app.EvtSel = 'NONE'
app.EvtMax = 3

subtop = Sequencer('SubSequence', Members = [alg1, alg2, alg3], StopOverride = True )
top = Sequencer('TopSequence', Members = [subtop, alg4], StopOverride = True )

app.TopAlg += [top]

profiler = IntelProfilerAuditor()
profiler.OutputLevel = DEBUG
profiler.StartFromEventN = 1
profiler.StopAtEventN = 2
profiler.ComponentsForTaskTypes = []
profiler.IncludeAlgorithms = ["SubSequence"]
profiler.ExcludeAlgorithms = ["Alg2"]
AuditorSvc().Auditors +=  [profiler]

app.AuditAlgorithms = True
```

, as a result we can see the following:

```
Function        Module  CPU Time
CpuHungryAlg::mysin     libIntelProfilerExample.so      0.410
CpuHungryAlg::myatan    libIntelProfilerExample.so      0.380
CpuHungryAlg::mytan     libIntelProfilerExample.so      0.370
CpuHungryAlg::mycos     libIntelProfilerExample.so      0.250
[Import thunk tan]      libIntelProfilerExample.so      0.010
```

#### Report by algorithm chain:

```sh
$> amplxe-cl -report hotspots -r ~/profiler/r000hs --group-by task
```

Result:

```
Task Type       CPU Time
TopSequence SubSequence Alg3    0.759
TopSequence SubSequence Alg1    0.410
TopSequence SubSequence 0.250
```

#### Report by algorithm chain with function's name:

```sh
$> amplxe-cl -report hotspots -r ~/profiler/r000hs --group-by task-function
```

Result:

```
Function        Task Type       CPU Time
CpuHungryAlg::mysin     TopSequence SubSequence Alg1    0.410
CpuHungryAlg::myatan    TopSequence SubSequence Alg3    0.380
CpuHungryAlg::mytan     TopSequence SubSequence Alg3    0.370
CpuHungryAlg::mycos     TopSequence SubSequence 0.250
[Import thunk tan]      TopSequence SubSequence Alg3    0.010
```


[profiler]: https://github.com/mazurov/IntelProfiler