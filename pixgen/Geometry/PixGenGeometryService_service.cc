//////////////////////////////////////////////////////////////////////
/// \file  PixGenGeometryService_service.cxx
/// \brief Service for pixel geometry information.
///
/// \author  hsulliva@fnal.gov
//////////////////////////////////////////////////////////////////////

#include "PixGenGeometryService.h"

namespace pixgeo 
{

PixGenGeometryService::PixGenGeometryService
  (fhicl::ParameterSet const& pset, art::ActivityRegistry&)
  {
    fProvider = std::make_unique<pixgeo::PixGenGeometry>(pset);
  }


void PixGenGeometryService::reconfigure(fhicl::ParameterSet const& pset)
{

}
}
DEFINE_ART_SERVICE_INTERFACE_IMPL(pixgeo::PixGenGeometryService, geo::DetectorGeometryService)

