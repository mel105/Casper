#ifndef DFT_H
#define DFT_H

/**************************************************************************************************
 @Founder: Michal Elias
 @Linux Ubuntu 18.4.2 LTS
 @Last revision: 2020-02-01 Author: Michal Elias  

 @Details: Method returns results of DFT.
  
 @Reference:
***************************************************************************************************/

#include <iostream>
#include <map>
#include <vector>
#include <algorithm>

#include <nlohmann/json.hpp>

#define G_PI 3.1415926535897932384626433832795028841971

using namespace std;

class t_dft
{
 public:
   
   t_dft(const vector<double> & data);
   virtual ~t_dft(){};
   
   vector<double> getRe();
   vector<double> getIm();
   vector<double> getMagnitudeSpectrum();
   vector<double> getPhaseSpectrum();
   vector<double> getPowerSpectrum();
   
 protected:
   
   // Functions
   void _setData( const vector<double> & data );
   void _dft();
   void _magnitudeSpectrum();
   void _phaseSpectrum();
   void _powerSpectrum();
   
   // Containers
   vector<double> _data;
   vector<double> _re;
   vector<double> _im;
   vector<double> _magSpec;
   vector<double> _phaSpec;
   vector<double> _powSpec;
};

#endif