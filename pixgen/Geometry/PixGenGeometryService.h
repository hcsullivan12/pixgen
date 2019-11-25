//////////////////////////////////////////////////////////////////////
/// \file  PixGenGeometryService.h
/// \brief Service for pixel geometry information.
///
/// \author  hsulliva@fnal.gov
//////////////////////////////////////////////////////////////////////

#ifndef PIXGEO_PIXSIMGEOMETRYSERVICE_H
#define PIXGEO_PIXSIMGEOMETRYSERVICE_H

#include "pixgen/Geometry/PixGenGeometry.h"
#include "pixgen/Geometry/DetectorGeometryService.h"

#include "fhiclcpp/ParameterSet.h"
#include "art/Framework/Services/Registry/ServiceMacros.h"

namespace pixgeo 
{

class PixGenGeometryService : public geo::DetectorGeometryService
{
  public:
    using provider_type = PixGenGeometry; ///< type of the service provider

    // Standard art service constructor
    PixGenGeometryService(fhicl::ParameterSet const&, art::ActivityRegistry&);

    /// Return a pointer to a (constant) detector properties provider
   // provider_type const* provider() const { return fProvider.get(); }
    virtual const provider_type* provider() const override { return fProvider.get();}
    
    virtual void   reconfigure(fhicl::ParameterSet const& pset) override;

 
  private:
    std::unique_ptr<PixGenGeometry> fProvider; ///< owned provider
    std::string fGDMLPath;

}; // class PixGenGeometryService

}
DECLARE_ART_SERVICE_INTERFACE_IMPL(pixgeo::PixGenGeometryService, geo::DetectorGeometryService, LEGACY)

#endif
