////////////////////////////////////////////////////////////////////////
/// \file  IonizationAndScintillationAction.cxx
/// \brief Use Geant4's user "hooks" to determine the number of ionization
///        electrons and scintillation photons for each step
///
/// \author  brebel@fnal.gov
////////////////////////////////////////////////////////////////////////

#include "pixgen/LArG4/IonizationAndScintillationAction.h"
#include "pixgen/LArG4/IonizationAndScintillation.h"


#include "Geant4/G4Step.hh"

#include <algorithm>

namespace pixgeng4 {

  //----------------------------------------------------------------------------
  // Constructor.
  IonizationAndScintillationAction::IonizationAndScintillationAction()
  {
  }

  //----------------------------------------------------------------------------
  // Destructor.
  IonizationAndScintillationAction::~IonizationAndScintillationAction()
  {
  }

  //----------------------------------------------------------------------------
  // With every step, calculate the number of ionization electrons and
  // scintillation photons using the IonizationAndScintillation singleton.
  void IonizationAndScintillationAction::SteppingAction(const G4Step* step)
  {
    pixgeng4::IonizationAndScintillation::Instance()->Reset(step);

    return;
  }

} // namespace PixGenG4
