#ifndef INTELPROFILINGEXAMPLE_SRC_COMPONENT_CPUHUNGRYALG
#define INTELPROFILINGEXAMPLE_SRC_COMPONENT_CPUHUNGRYALG
// # Include files
// Gaudi:
#include "GaudiAlg/GaudiAlgorithm.h"


/// Algorithm which consume a lot of CPU.
///
/// Author: Alexander Mazurov (alexander.mazurov@gmail.com)
class CpuHungryAlg: public GaudiAlgorithm {
public:
  /// Standard constructor
  CpuHungryAlg(const std::string& name, ISvcLocator* pSvcLocator);
  /// ... and desctructor
  virtual ~CpuHungryAlg(); ///< Destructor

  virtual StatusCode initialize();    ///< Algorithm initialization
  virtual StatusCode execute   ();    ///< Algorithm execution
  virtual StatusCode finalize  ();    ///< Algorithm finalization

private:
  double mysin();
  double mycos();
  double mytan();
  double myatan();
private:
  long m_loops;
  int m_nevent;
};

#endif // INTELPROFILINGEXAMPLE_SRC_COMPONENT_CPUHUNGRYALG
