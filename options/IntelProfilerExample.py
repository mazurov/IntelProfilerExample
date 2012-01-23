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