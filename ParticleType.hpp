//
//  ParticleType.hpp
//  laboratorio_c++_root
//
//  Created by Matteo Barbieri on 16/10/2020.
//

#ifndef ParticleType_hpp
#define ParticleType_hpp

#include <iostream>
#include <string>

class ParticleType {
public:
  ParticleType(const std::string name, const double mass, const int charge);
  ParticleType();
  std::string GetName() const;
  double GetMass() const;
  int GetCharge() const;
  virtual void Print() const;
  virtual double GetWidth() const;
  virtual ~ParticleType() = default;

private:
  std::string const fName;
  double const fMass;
  int const fCharge;
};

#endif /* ParticleType_hpp */
