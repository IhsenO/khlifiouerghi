// Generated by dia2code
#ifndef STATE__CITY__H
#define STATE__CITY__H

#include <vector>

namespace state {
  class Construction;
  class StaticElement;
}

#include "TypeID.h"
#include "StaticElement.h"
#include "Construction.h"

namespace state {

  /// class City - 
  class City : public state::StaticElement {
    // Associations
    // Attributes
  protected:
    int defense;
    std::vector<Construction*> listConst;
    bool building;
    bool free;
    // Operations
  public:
    City ();
    TypeID getTypeID () const;
    bool isFree () const;
    bool isBuilding () const;
    bool isAccessible () const;
    bool isInteractive () const;
    bool isStatic () const;
    void addConstruction (Construction* construction);
    bool canBuild (int id) const;
    City (int defense, bool free);
    ~City ();
    // Setters and Getters
    int getDefense() const;
    void setDefense(int defense);
    const std::vector<Construction*>& getListConst() const;
    void setListConst(const std::vector<Construction*>& listConst);
    bool getBuilding() const;
    void setBuilding(bool building);
    bool getFree() const;
    void setFree(bool free);
  };

};

#endif
