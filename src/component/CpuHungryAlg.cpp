// # Include files
// Standart:
#include <unistd.h>
#include <math.h>
// Gaudi:
#include "GaudiKernel/AlgFactory.h"
// Local:
#include "CpuHungryAlg.h"

// Register algorithm
DECLARE_ALGORITHM_FACTORY(CpuHungryAlg)

CpuHungryAlg::CpuHungryAlg(const std::string& name, ISvcLocator* pSvcLocator)
  : GaudiAlgorithm(name, pSvcLocator),m_nevent(0)
{
  declareProperty("Loops", m_loops = 1000000);
}


CpuHungryAlg::~CpuHungryAlg() {}

/// Initialization.
StatusCode CpuHungryAlg::initialize() {
  StatusCode sc = GaudiAlgorithm::initialize(); // must be executed first
  if ( sc.isFailure() ) return sc; // error printed already by GaudiAlgorithm

  if ( msgLevel(MSG::DEBUG) ) debug() << "==> Initialize" << endmsg;
  return StatusCode::SUCCESS;
}

/// Execute.
double CpuHungryAlg::mysin() {
  double result = 0;
  for(long i=0; i <= m_loops; ++i) {
      result += sin(i);
  }
  return result;
}

double CpuHungryAlg::mycos() {
  double result = 0;
  for(long i=0; i<=m_loops; ++i) {
      result += cos(i);
  }
  return result;
}

double CpuHungryAlg::mytan() {
  double result = 0;
  for(long i=0; i<=m_loops; ++i) {
      result += tan(i);
  }
  result  += myatan();
  return result;
}

double CpuHungryAlg::myatan() {
  double result = 0;
  for(long i=0; i<=m_loops; ++i) {
      result += tan(i);
  }
  return result;
}

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

/// Finalize
StatusCode CpuHungryAlg::finalize() {
  if ( msgLevel(MSG::DEBUG) ) debug() << "==> Finalize" << endmsg;

  return GaudiAlgorithm::finalize(); // must be called after all other actions
}

// ============================================================================
