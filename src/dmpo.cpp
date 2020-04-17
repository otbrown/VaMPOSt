#include <cstdio>
#include "dmpo.h"
#include "itensor/index.h"

namespace vampost{

  void DMPO::Initialise() {
    const std::size_t MIDPT = NUM_SITES / 2;
    std::size_t dim_v1 = PHYS_DIM * PHYS_DIM;
    itensor::Index row, col;
    const itensor::Index& ket = pIndex.at(0);
    const itensor::Index& bra = pIndex.at(1);
    char link_id[12];
    std::size_t site;

    // first site
    col = itensor::Index(dim_v1, "Link,l0");
    vIndex.push_back(col);
    sites.emplace_back(col, ket, bra);
    
    // up to mid point
    for (site = 1; site < MIDPT; ++site) {
      row = col;
      
      dim_v1 *= PHYS_DIM;
      std::snprintf(link_id, 11, "Link,l%u", site+1);
      col = itensor::Index(std::min(dim_v1,MAX_DIM), link_id);
      
      vIndex.push_back(col);
      sites.emplace_back(row, col, bra, ket);
    }

    // mid point 
    site = MIDPT;
    row = col;
    std::snprintf(link_id, 11, "Link,l%u", site+1);
    col = itensor::Index(std::min(dim_v1,MAX_DIM), link_id);
    vIndex.push_back(col);
    sites.emplace_back(row, col, bra, ket);    

    // to before end
    for (site = MIDPT+1; site < NUM_SITES-1; ++site) {
      row = col;
      
      dim_v1 /= PHYS_DIM;
      std::snprintf(link_id, 11, "Link,l%u", site+1);
      col = itensor::Index(std::min(dim_v1,MAX_DIM), link_id);

      vIndex.push_back(col);
      sites.emplace_back(row, col, bra, ket);
    }

    // end site
    row = col;
    sites.emplace_back(row, bra, ket);    

    return;
  }

  void DMPO::SetProductState(const std::vector<std::pair<State,State>>& STATES)
  {
    itensor::IndexVal ket, bra, row, col;

    // first site
    sites.at(0).fill(0.0);
    col = itensor::IndexVal(vIndex.at(0), 1);
    ket = itensor::IndexVal(pIndex.at(0), STATES.at(0).first);
    bra = itensor::IndexVal(pIndex.at(1), STATES.at(0).second);
    sites.at(0).set(col, ket, bra, 1.0);

    // middle sites
    for (std::size_t n = 1; n < NUM_SITES-1; ++n) {
      sites.at(n).fill(0.0);

      row = col;
      col = itensor::IndexVal(vIndex.at(n), 1);
      ket = itensor::IndexVal(pIndex.at(0), STATES.at(n).first);      
      bra = itensor::IndexVal(pIndex.at(1), STATES.at(n).second);      

      sites.at(n).set(row, col, ket, bra, 1.0);
    } 

    // end site
    row = col;
    ket = itensor::IndexVal(pIndex.at(0), STATES.at(NUM_SITES).first);
    bra = itensor::IndexVal(pIndex.at(1), STATES.at(NUM_SITES).second);
    sites.at(NUM_SITES).set(row, bra, ket, 1.0);

    return;
  }

}