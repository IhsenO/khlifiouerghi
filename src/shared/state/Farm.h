// Generated by dia2code
#ifndef STATE__FARM__H
#define STATE__FARM__H


namespace state {
  class Construction;
}

#include "ConstructionTypeId.h"
#include "Construction.h"

namespace state {

  /// class Farm - 
  class Farm : public state::Construction {
    // Operations
  public:
    Farm ();
    bool isProducing () const;
    ConstructionTypeId getConstructionId () const;
    // Setters and Getters
  };

};

#endif
