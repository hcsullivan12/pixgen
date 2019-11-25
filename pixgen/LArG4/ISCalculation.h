////////////////////////////////////////////////////////////////////////
/// \file  ISCalculation.h
/// \brief Interface to algorithm class for a specific detector channel mapping
///
/// \author  brebel@fnal.gov
////////////////////////////////////////////////////////////////////////
#ifndef LARG4_ISCALCULATION_H
#define LARG4_ISCALCULATION_H

#include "Geant4/G4Step.hh"
#include "Geant4/G4UserLimits.hh"

namespace pixgeng4{

 class ISCalculation{

 public:

   ISCalculation();
   virtual ~ISCalculation();

   virtual void                 Initialize()                                            = 0;
   virtual void                 Reset()                            		        = 0;
   virtual void                 CalculateIonizationAndScintillation(const G4Step* step) = 0;
   virtual double               StepSizeLimit()              const 		        = 0;

   double                 EnergyDeposit()              const { return fEnergyDeposit;   }
   double       	        NumberIonizationElectrons()  const { return fNumIonElectrons; }
   double       	        NumberScintillationPhotons() const { return fNumScintPhotons; }
   double       	        VisibleEnergyDeposit()       const { return fVisibleEnergyDeposition; }
   std::vector<G4ThreeVector> const& StepPoints() { return fStepPointVec; }
   std::vector<int> const&           StepScint()  { return fStepScintVec; }

   //Method to get electric field
   double EFieldAtStep(double fEfield, const G4Step* step) const; //value of field with any corrections for this step

 protected:

   double fEnergyDeposit;   ///< total energy deposited in the step
   double fNumIonElectrons; ///< number of ionization electrons for this step
   double fNumScintPhotons; ///< number of scintillation photons for this step
   double fVisibleEnergyDeposition; ///Scalling factor for energy to photons
   std::vector<G4ThreeVector> fStepPointVec;
   std::vector<int>           fStepScintVec;

 };
}
#endif // LARG4_ISCALCULATION_H

