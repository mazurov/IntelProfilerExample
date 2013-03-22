#!/usr/bin/env gaudirun.py

from Gaudi.Configuration import *
from Configurables import CpuHungryAlg

MessageSvc().OutputLevel = INFO

alg1 = CpuHungryAlg("Alg1")
alg2 = CpuHungryAlg("Alg2")
alg3 = CpuHungryAlg("Alg3")
alg4 = CpuHungryAlg("Alg4")

alg1.Loops = alg2.Loops = alg3.Loops = alg4.Loops = 5000000

subtop = Sequencer(
    'SubSequence', Members=[alg1, alg2, alg3], StopOverride=True)
top = Sequencer('TopSequence', Members=[subtop, alg4], StopOverride=True)


ApplicationMgr(EvtMax=3,
               EvtSel='NONE',
               HistogramPersistency='NONE',
               TopAlg=[top],
               AuditAlgorithms=True)
