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

#include "managerSpectrogram.h"
#include "convTDtoDD.h"
#include "logger.hpp"
#include "plot.h"
#include "dft.h"
#include "workingdir.h"

// contructor
// -----------
t_managerSpectrogram::t_managerSpectrogram(t_setting* setting,  t_coredata* coredata)
{
  
  /// Get setting & create log info
  vector<string> inpSett = setting->getLoadSetting(); _fmt  = inpSett[2];
  string outputName = setting->getOutputName(); _out = outputName;
  string outputHist = setting->getOutputHist(); _hst = outputHist;
  string plotOnOff = setting->getPlotOnOff(); _plot = plotOnOff;

  bool conv = setting->getInputConvTdDd(); _conv = conv;
  double res = setting->getInputResolution(); _res = res;
  
  /// Get actual working folder path
  t_workingDir workingDir; _gnp = workingDir.GetCurrentWorkingDir();
  
  LOG1(":...t_managerSpectrogram::......Loaded Spectrogram settings!");
  
  /// Get data from coredata & create log info.
  if (_fmt == "dd") {
    
    _data = coredata -> getData("origval");
    
    if(!_data.empty()) {
      
      LOG1(":...t_managerSpectrogram::......Loaded data container. Data size: ", _data.size());
    }
    else{
      
      ERR(":...t_managerSpectrogram::......Data container is empty!"); return;
    }
  }
  else if (_fmt == "td" && conv == true ) {
    
    _Data = coredata -> getTimeData("origval");
    
    if(!_Data.empty()) {
      
      LOG1(":...t_managerSpectrogram::......Loaded data container. Data size: ", _Data.size());
      
    }
    else{
      
      ERR(":...t_managerSpectrogram::......Data container is empty!"); return;
    }
  }
  else if (_fmt == "td" && conv == false ) {
  
    _data = coredata -> getData("origval");

    if(!_data.empty()) {
      
      LOG1(":...t_managerSpectrogram::......Loaded data container. Data size: ", _data.size());
      
    }
    else{
      
      ERR(":...t_managerSpectrogram::......Data container is empty!"); return;
    }
  }  
  else {
    
    ERR(":...t_managerSpectrogram::......Requested data format is not supported!");
  }
  
  /// dft manager
  this -> _procSpectrogram();
}

/// Protected methods

/// @detail
///   - Spectrogram
void t_managerSpectrogram::_procSpectrogram()
{
  
  vector<double> dataVec;
  
  if (_fmt == "dd") {
    
    dataVec.clear();
    for(map<double, double>::iterator it = _data.begin(); it != _data.end(); ++it) {
      
      dataVec.push_back(it->second);
    }
  }
  else if (_fmt == "td" && _conv == true) {
    
    t_fromTDtoDD fromTDtoDD;  m_dd convOut = fromTDtoDD.FromTDtoDD(_Data);
    
    dataVec.clear();
    for(m_dd::iterator it = convOut.begin(); it != convOut.end(); ++it) {
      
 #ifdef DEBUG
      cout << it->first << "  " << it->second << endl;
 #endif      
      dataVec.push_back(it->second);
    }
  }
  else if (_fmt == "td" && _conv == false) {
    
    // AK MAM TD A CONV FALSE, TAK LEN OD PRVEJ HODNTY ODCITAT PRVU HDNOTU.    
    // conv false == key val => mjd
    dataVec.clear();
    
    for(m_dd::iterator it = _data.begin(); it != _data.end(); ++it) {
      
#ifdef DEBUG
      cout << it->first << "  " << it->second << endl;
#endif
      dataVec.push_back(it->second);
    }
  }
  else { 
    
    ERR(":...t_managerSpectrogram::......Requested data format is not supported!");
  }
  
  size_t N = dataVec.size();

  // TU BY SOM MAL PREMYSLIET, AKO BUDEM SPEKTROGRAM SPRACOVAVAT. OVERENIE PODMIENOK ATP A VOLAM 
  // LEN JEDEN KONSTRUKTOR S PREDDEFINOVANYMI VSTUPNYMI PARAMETRAMI.
 
  cout << "tu poriesim spektrogram" << endl;
  // Na vstupe by som mal mat:
  //  x ... input data vector, resp. input signal
  //  window ... custom window ot length of Hamming window
  //  nOverlap ... samples of overlap between adjoining segments0
  //  nFFT ... n-point disrete Fourier Transform
  //  fs ... sampling frequency
  //  freqRange ... frequency range: onesided, twosided, centered or default.
  // Na vystupe
  //  get Short-Time Fourier Transform
  //  get frequency vector
  //  get vector of time instants at which spectogram is computed
  //  get estimates of power spectral density PSD.
  
  //t_dft dft(dataVec);
  
  /*
  /// If requested, then plot figures
  if (_plot == "on") {
    
    LOG1(":...t_managerSpectrogram::......Request for plot!");
    t_plot mplot;
    
    if(_fmt == "dd") {
      
      ofstream mLine((_gnp + "/Casper/gnuplot/line"));
      for (m_dd::iterator i = _data.begin(); i != _data.end(); ++i) {
        
        mLine << i->first << "  " << i->second << endl;
      }
      
      mLine.close();
      
      /// double plot
      mplot.line();
      LOG1(":...t_managerSpectrogram::......Line plot created (time-stamp::double)!");
    }
    else { // tt
      
      ofstream mLine((_gnp + "/Casper/gnuplot/line"));
      for (m_td::iterator i = _Data.begin(); i != _Data.end(); ++i) {
        
        t_timeStamp epo = i->first;
        mLine << epo.timeStamp() << "  " << i->second << endl;
      }
      
      mLine.close();
      
      // time-string plot
      mplot.tline();
      LOG1(":...t_managerSpectrogram::......Line plot created (time-stamp::t_gtime)!");
      
      
      // Magnitude vs freq.
      ofstream mMagnitude((_gnp + "/Casper/gnuplot/magnitude"));
      for (int i = 0; i< magnitude.size(); ++i) {
        
        mMagnitude << frequency[i] << "  " << magnitude[i] << endl;
      }
      mMagnitude.close();
      
      mplot.magnitude();
      LOG1(":...t_managerSpectrogram::......Magnitude spectrum plot created!");

      // phase vs freq.
      ofstream mPhase((_gnp + "/Casper/gnuplot/phase"));
      for (int i = 0; i< phase.size(); ++i) {
        
        mPhase << frequency[i] << "  " << phase[i] << endl;
      }
      mPhase.close();
      
      mplot.phase();
      LOG1(":...t_managerSpectrogram::......Phase spectrum plot created!");
      
      // real vs freq.
      ofstream mReal((_gnp + "/Casper/gnuplot/real"));
      for (int i = 0; i< realCoefs.size(); ++i) {
        
        mReal << frequency[i] << "  " << realCoefs[i] << endl;
      }
      mReal.close();
      
      mplot.realSpec();
      LOG1(":...t_managerSpectrogram::......Real spectrum plot created!");

      
      // imaginary vs freq.
      ofstream mImag((_gnp + "/Casper/gnuplot/imag"));
      for (int i = 0; i< imagCoefs.size(); ++i) {
        
        mImag << frequency[i] << "  " << imagCoefs[i] << endl;
      }
      mImag.close();
      
      mplot.imagSpec();
      LOG1(":...t_managerSpectrogram::......Imaginary spectrum plot created!");

    }
    
  } */
}
