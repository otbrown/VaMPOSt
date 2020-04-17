#ifndef DMPO_H
#define DMPO_H

// Density Matrix Product Operator
#include <vector>
#include "itensor/itensor.h"
#include "datatypes.h"

namespace vampost {

  class DMPO {
    protected:
      const std::size_t NUM_SITES;
      const State PHYS_DIM;
      const std::size_t MAX_DIM;
      std::vector<itensor::ITensor> sites;
      const std::array<itensor::Index,2> pIndex;
      std::vector<itensor::Index> vIndex;

      void Initialise();

    public:
      DMPO(const std::size_t N, const State HILBY, const std::size_t CHI)
      : NUM_SITES(N), PHYS_DIM(HILBY), MAX_DIM(CHI), 
        pIndex( {
          itensor::Index(PHYS_DIM, "Site,ket"), 
          itensor::Index(PHYS_DIM, "Site,bra") } ) 
      { 
        sites.reserve(NUM_SITES);
        vIndex.reserve(NUM_SITES-1);
        Initialise();
      };
      DMPO(const std::size_t N, const State HILBY, const std::size_t CHI, 
      const std::vector<std::pair<State,State>>& STATES) : DMPO(N, HILBY, CHI) 
      { SetProductState(STATES); };

      inline const std::size_t GetNumSites() const { return NUM_SITES; }
      inline const std::size_t GetMaxDim() const { return MAX_DIM; }
      inline const std::size_t GetPhysDim() const { return PHYS_DIM; }
      inline itensor::ITensor& GetSite(std::size_t n) { return sites.at(n); } 
      inline std::vector<itensor::ITensor>& GetSites() { return sites; }  

      void SetProductState(const std::vector<std::pair<State,State>>&);
  };
}

#endif