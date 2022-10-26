//
//  ResonanceType.hpp
//  laboratorio_c++_root
//
//  Created by Matteo Barbieri on 16/10/2020.
//

#ifndef ResonanceType_hpp
#define ResonanceType_hpp

#include "ParticleType.hpp"
#include <stdio.h>

class ResonanceType : public ParticleType {
public:
  ResonanceType(const std::string name, const double mass, const int charge,
                const double width);
  ResonanceType();
  double GetWidth() const;
  void Print() const;
  virtual ~ResonanceType() = default;

private:
  double const fWidth;
};

#endif /* ResonanceType_hpp */
