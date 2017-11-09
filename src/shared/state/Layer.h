// Generated by dia2code
#ifndef STATE__LAYER__H
#define STATE__LAYER__H

#include <vector>
#include <string>

namespace state {
  class Element;
}

namespace state {

  /// class Layer - 
  class Layer {
    // Attributes
  private:
    std::vector<Element*> tab;
    int width;
    int height;
    // Operations
  public:
    Layer (int width, int height);
    void set (int x, int y, Element* e);
    Element* get (int x, int y) const;
    virtual ~Layer ();
    void loadLayer (const std::string fileName);
    void add (Element* e);
    Layer ();
    int getWidth () const;
    int getHeight () const;
    // Setters and Getters
  };

};

#endif
