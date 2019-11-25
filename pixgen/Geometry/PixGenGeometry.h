/**
 * @file PixGenGeometry.h
 * @brief Interface to pixel geometry information.
 * 
 * @author H. Sullivan (hsulliva@fnal.gov)
 */

#ifndef PIXGEO_PIXSIMGEOMETRY_H
#define PIXGEO_PIXSIMGEOMETRY_H

// framework libraries
#include "fhiclcpp/ParameterSet.h"
#include "fhiclcpp/types/Sequence.h"
#include "fhiclcpp/types/Table.h"
#include "fhiclcpp/types/Atom.h"
#include "fhiclcpp/types/OptionalAtom.h"

// LArSoft includes
#include "larcore/Geometry/Geometry.h" // Point_t

// pixgen includes
#include "pixgen/Geometry/DetectorGeometry.h"

// C++ includes
#include <set>

namespace pixgeo
{
  using UShort2_t = unsigned short;
  using ULong4_t = unsigned long;
  using ULong8_t = unsigned long long;

/// Configuration parameter documentation goes here
class PixGenGeometry : public geo::DetectorGeometry
{
  public:

    /// Structure for configuration parameters
    struct Configuration_t 
    {
      using Name = fhicl::Name;
      using Comment = fhicl::Comment;

      fhicl::Atom<std::string> DetectorName
      {
        Name("Name"),
        Comment("Name of detector")
      };

      fhicl::Atom<std::string> GDML         
      {
        Name("GDML"),
        Comment("Name of GDML file for pixel geometry")
      };

      fhicl::Atom<bool> UseSimpleGeometry
      {
        Name("UseSimpleGeometry"),
        Comment("Option to simplify the pixel geometry.")
      };

      fhicl::Atom<double> PixelSpacing
      {
        Name("PixelSpacing"),
        Comment("Pixel spacing")
      };
      
    };

    PixGenGeometry();
    /// Constructor: reads the configuration from a parameter set
    PixGenGeometry(fhicl::ParameterSet const& pset,
                  std::set<std::string> const& ignore_params = {});
    PixGenGeometry(PixGenGeometry const&) = delete;
    virtual ~PixGenGeometry() = default;

    /// Method to validate parameter set
    void ValidateAndConfigure(
        fhicl::ParameterSet const& p,
        std::set<std::string> const& ignore_params = {});

    Configuration_t ValidateConfiguration(
        fhicl::ParameterSet const& p,
        std::set<std::string> const& ignore_params = {});

    /// Extracts the relevant configuration from the specified object
    void Configure(Configuration_t const& config);        

    std::string GDMLFile()         const { return fGDMLPath;            }
    std::string ROOTFile()         const { return GDMLFile();           }
    std::string OpDetGeoName()     const { return fOpDetVolName;        }
    std::string DetectorName()     const { return fDetectorName;        }
    size_t      NOpDets()          const { return fNOpDets;             }
    size_t      Ncryostats()       const { return fNCryo;               }
    size_t      NTPC()             const { return fNTpc;                }
    size_t      NAuxDets()         const { return 0;                    }
    size_t      NSensitiveVolume() const { return 1;                    }
    double      DetHalfWidth()     const { return 0.5*DetDriftLength(); }
    double      DetHalfHeight()    const { return fDetHalfY;            }
    double      DetDriftLength()   const { return fDriftLength;         }
    double      DetLength()        const { return fDetLength;           }
    float       PixelSpacing()     const { return fPixelSpacing;        }
    int         NPixels()          const { return fNPixels;             }
    int         NReadoutNodes()    const { return NPixels();            }
    size_t      Nchannels()        const { return NPixels();            }
    float       ChannelSpacing()   const { return fPixelSpacing;        }

    const std::vector<double> PlaneLocation(size_t const& p) const { return std::vector<double>(3, 0); }

    int           DriftDirection() const { return -1; }
    size_t        Nplanes() const { return 1; };
    double        PlanePitch(size_t const& p1=0, size_t const& p2=1) const { return 0.; };

    double      TotalMass(std::string const& vol) const 
      { TGeoVolume *gvol = gGeoManager->FindVolumeFast(vol.c_str());
        if (gvol) return gvol->Weight();
        throw cet::exception("DetectorGeometry") << "could not find specified volume '"
                                                 << vol
                                                 << " 'to determine total mass\n";
      }
         

    /**
     * @brief Find pixel ID from simplified geometry.
     * @warning Assumes simple containers are ordered.
     * 
     * @param point The point on readout plane
     * @return int The ID of pixel which contains the point
     */
    int FindSimpleID(geo::Point_t const& point) const;
    int FindSimpleID(TVector3 const& point) const
      { return FindSimpleID(geo::vect::toPoint(point)); }

    /**
     * @brief Find nearest pixel ID. Will call FindSimpleID 
     *        if using simplified geometry. 
     * 
     * @param point point The point on readout plane
     * @return int The ID of pixel which contains the point
     */
    int NearestPixelID(geo::Point_t const& point) const;
    int NearestPixelID(TVector3 const& point) const
      { return NearestPixelID(geo::vect::toPoint(point)); }
   
    int NearestReadoutNodeID(TVector3 const& point) const
      { return NearestPixelID(point); }

    int NearestChannel(double* xyz, 
                       size_t const& p, 
                       size_t const& tpc,
                       size_t const& cryo) const 
      { return NearestPixelID(TVector3(xyz[0], xyz[1], xyz[2])); };

 
    /// Name of active volume
    std::string GetLArTPCVolumeName() const { return fLArTPCVolName; }

    TGeoManager* ROOTGeoManager() const { return gGeoManager; }

    void GetOpDetCenter(double* xyz) const;
    
    /**
     * @brief Name of volume that contains point
     * 
     * @return std::string Volume name 
     */
    std::string VolumeName(geo::Point_t const& point) const;
    std::string VolumeName(TVector3 const& point) const
      { return VolumeName(geo::vect::toPoint(point)); }

  
    std::vector<float> GetChannelPosition(const int& ch) const;
    void GetChannelPositions(std::vector<float>& d1, std::vector<float>& d2) const
      { d1 = fSimpleGeoY; d2 = fSimpleGeoZ; }

  private:

    /**
     * @brief Initialize the geometry information.
     * 
     */
    void Initialize();

    /**
     * @brief Query a specific node in the geometry
     * 
     * @param currentNode The current node 
     * @param currentPath The full path to the current node
     */
    void LookAtNode(TGeoNode const* currentNode, std::string const& currentPath);

    /**
     * @brief Method to construct a simplied pixel geometry component
     * 
     * The purpose of this method is to construct a pixel geometry component
     * from specifying only the pixel spacing. The pixelization scheme constructed
     * preserves the symmetry of the pixel plane, placing equal amounts of pixels
     * above/below and left/right of symmetery axes. This reduces overhead and allows 
     * for a more efficient method to lookup pixel IDs.  
     * 
     */
    void LoadSimpleGeometry();

    std::vector<std::string> fNodePaths;         ///< Container of full paths to geo nodes
    std::vector<float>       fSimpleGeoZ;        ///< Ordered container of columns for simplified geometry
    std::vector<float>       fSimpleGeoY;        ///< Ordered container of rows for simplified geometry
    std::string              fGDMLPath;          ///< Full path to gdml file
    std::string              fDetectorName;      ///<
    std::string              fLArTPCVolName;     ///< 
    std::string              fOpDetVolName;      ///< 
    ULong8_t                 fNPixels;           ///< Number of pixels 
    TGeoVolume*              fPixelPlane;        ///< Pointer to pixel plane volume
    size_t                   fNOpDets;           ///<
    size_t                   fNCryo;             ///<
    size_t                   fNTpc;              ///<
    double                   fDetHalfY;          ///< Y half length of readout plane
    double                   fDriftLength;       ///< Drift length
    double                   fDetLength;         ///< Length of active volume in beam direction
    float                    fPixelSpacing;      ///< Pixel spacing for simplified geometry
    bool                     fUseSimpleGeometry; ///< Option to use simplified geometry
}; // class PixGenGeometry

}

#endif
