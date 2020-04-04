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

#include  "idft.h"

// constructor
// --------------------
t_idft::t_idft(const vector<double> & data)
{
  
  // Set data
  this-> _setData(data);
  
  // fidft
  this->_idft();
}

/// Forward Discrete Fourier Transformation
void t_idft::_idft()
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
}

/// Put data into the protected container
void t_idft::_setData( const vector<double> & data)
{
  
  _data = data;  //data.clear(); Ako sa tych dat potom zbavit?
}