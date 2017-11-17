// Generated by dia2code
#ifndef STATE__CONSTRUCTION__H
#define STATE__CONSTRUCTION__H

#include <vector>

#include "ConstructionTypeId.h"

namespace state {

  /// class Construction - 
  class Construction {
    // Attributes
  protected:
    int level;
    int productionByTurn;
    int ressourcesToBuild;
    std::vector<int> list;
    // Operations
  public:
    Construction ();
    virtual bool isProducing () const = 0;
    virtual ConstructionTypeId getConstructionId () const = 0;
    int getCost () const;
    virtual ~Construction ();
    // Setters and Getters
    int getLevel() const;
    void setLevel(int level);
    int getProductionByTurn() const;
    void setProductionByTurn(int productionByTurn);
    int getRessourcesToBuild() const;
    void setRessourcesToBuild(int ressourcesToBuild);
    const std::vector<int>& getList() const;
    void setList(const std::vector<int>& list);
  };

};

#endif
