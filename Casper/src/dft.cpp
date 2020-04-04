/************************************************************************************************** 
 Casper - software development library
  
 (c) 2020 Michal Elias
  
 This file is part of the Casper C++ library.
  
 This library is free software; you can redistribute it and/or  modify it under the terms of the GNU
 General Public License as  published by the Free Software Foundation; either version 3 of the 
 License, or (at your option) any later version.
  
 This library is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY; without 
 even the implied warranty of  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU
 General Public License for more details.
  
 You should have received a copy of the GNU General Public License  along with this program; if not,
 see <http://www.gnu.org/licenses>.
***************************************************************************************************/

#include  "dft.h"

// constructor
// --------------------
t_dft::t_dft(const vector<double> & data)
{
  
  // Set data
  this-> _setData(data);
  
  // fDFT
  this->_dft();
}

// Get functions
vector <double> t_dft::getRe() { if (!_re.empty()) { return _re; }}
vector <double> t_dft::getIm() { if (!_im.empty()) { return _im; }}
vector <double> t_dft::getMagnitudeSpectrum() { if (!_magSpec.empty()) { return _magSpec; }}
vector <double> t_dft::getPhaseSpectrum() { if (!_phaSpec.empty()) { return _phaSpec; }}
vector <double> t_dft::getPowerSpectrum() { if (!_powSpec.empty()) { return _powSpec; }}

// Magnitude Spectrum
void t_dft::_magnitudeSpectrum() 
{
  
  if ( !_re.empty() && !_im.empty() ) {
    
    for (int i = 0; i<_re.size(); i++) {
      
      _magSpec.push_back(sqrt( _re[i]*_re[i] + _im[i]*_im[i]));
    }
  }
}

// Power Spectrum
void t_dft::_powerSpectrum() 
{
  
  if ( !_re.empty() && !_im.empty() ) {
    
    for (int i = 0; i<_re.size(); i++) {
      
      _powSpec.push_back( _re[i]*_re[i] + _im[i]*_im[i] );
    }
  }
}
  
// Phase Spectrum
void t_dft::_phaseSpectrum()
{
  
  if ( !_re.empty() && !_im.empty() ) {
    
    for (int i = 0; i<_re.size(); i++) {
      
      if ( _re[i] > 0 ) {
        
        _phaSpec.push_back( atan2(_im[i], _re[i]));
      }
      else if ( _re[i] < 0 && _im[i] >= 0 ) {
        
        _phaSpec.push_back( atan2(_im[i], _re[i]) + G_PI );
      }
      else if ( _re[i] < 0 && _im[i] < 0 ) {
        
        _phaSpec.push_back( atan2(_im[i], _re[i]) - G_PI );
      }
      else if ( _re[i] == 0 && _im[i] > 0 ) {
        
        _phaSpec.push_back( G_PI/2 );
      }
      else if ( _re[i] == 0 && _im[i] < 0 ) {
        
        _phaSpec.push_back( -G_PI/2 );
      }
      else {
        
        _phaSpec.push_back(-999);
      }
    }
  }
}
  
// Forward Discrete Fourier Transformation
void t_dft::_dft()
{

  size_t N = _data.size();
  
  for (int k=0; k<=N/2; ++k) {
    
    double a = 0.0;
    double b = 0.0;
    
    // x = index vzorku
    for (int x = 0; x < N; ++x) {
      
      a += _data[x] * cos( 2 * G_PI * k * x / N );
      b += _data[x] * sin( 2 * G_PI * k * x / N );
    }
    
    a *= (k == 0 || k == N / 2) ? 1. / N : 2. / N;
    b *= 2. / N;
    
    _re.push_back(a);
    _im.push_back(b);
  }
  
  this->_magnitudeSpectrum();
  this->_phaseSpectrum();
  this->_powerSpectrum();
}

/// Put data into the protected container
void t_dft::_setData( const vector<double> & data )
{
  
  _data = data;  //data.clear(); Ako sa tych dat potom zbavit?
}
