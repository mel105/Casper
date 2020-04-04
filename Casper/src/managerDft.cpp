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

#include "managerDft.h"
#include "convTDtoDD.h"
#include "logger.hpp"
#include "plot.h"
#include "dft.h"
#include "workingdir.h"

// contructor
// -----------
t_managerDft::t_managerDft(t_setting* setting,  t_coredata* coredata)
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
  
  LOG1(":...t_managerDft::......Loaded DFT settings!");
  
  /// Get data from coredata & create log info.
  if (_fmt == "dd") {
    
    _data = coredata -> getData("origval");
    
    if(!_data.empty()) {
      
      LOG1(":...t_managerDft::......Loaded data container. Data size: ", _data.size());
    }
    else{
      
      ERR(":...t_managerDft::......Data container is empty!"); return;
    }
  }
  else if (_fmt == "td" && conv == true ) {
    
    _Data = coredata -> getTimeData("origval");
    
    if(!_Data.empty()) {
      
      LOG1(":...t_managerDft::......Loaded data container. Data size: ", _Data.size());
      
    }
    else{
      
      ERR(":...t_managerDft::......Data container is empty!"); return;
    }
  }
  else if (_fmt == "td" && conv == false ) {
  
    _data = coredata -> getData("origval");

    if(!_data.empty()) {
      
      LOG1(":...t_managerDft::......Loaded data container. Data size: ", _data.size());
      
    }
    else{
      
      ERR(":...t_managerDft::......Data container is empty!"); return;
    }
  }  
  else {
    
    ERR(":...t_managerDft::......Requested data format is not supported!");
  }
  
  /// dft manager
  this -> _procDft();
}

/// Protected methods

/// @detail
///   - fDFT
///   - iDFT
void t_managerDft::_procDft()
{
  
  // Output setting
  ofstream hfile(_hst.c_str(), ios::out | ios::app);
  ofstream ofile(_out.c_str(), ios::out | ios::app);
  ofile << "# ********************************************* \n";
  ofile << "#                    DFT                        \n";
  ofile << "# ********************************************* \n\n";
    
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
    
    ERR(":...t_managerDft::......Requested data format is not supported!");
  }
  
  size_t N = dataVec.size();

  // fdft
  t_dft dft(dataVec);
  
  vector<double> realCoefs = dft.getRe(); 
  vector<double> imagCoefs = dft.getIm(); 
  vector<double> magnitude = dft.getMagnitudeSpectrum(); 
  vector<double> phase = dft.getPhaseSpectrum(); 
  vector<double> power = dft.getPowerSpectrum();
  vector<double> frequency;
  
  // frequency in [Hz]
  double sampleRate = 1.0 / _res;
  double freqRate = sampleRate / realCoefs.size();
 
  for (int i = 0; i<realCoefs.size(); ++i) {
    
    frequency.push_back( static_cast<double>(i) * freqRate  );
  }
     
     
 
  /// If requested, then plot figures
  if (_plot == "on") {
    
    LOG1(":...t_managerDft::......Request for plot!");
    t_plot mplot;
    
    if(_fmt == "dd") {
      
      ofstream mLine((_gnp + "/Casper/gnuplot/line"));
      for (m_dd::iterator i = _data.begin(); i != _data.end(); ++i) {
        
        mLine << i->first << "  " << i->second << endl;
      }
      
      mLine.close();
      
      /// double plot
      mplot.line();
      LOG1(":...t_managerDft::......Line plot created (time-stamp::double)!");
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
      LOG1(":...t_managerDft::......Line plot created (time-stamp::t_gtime)!");
      
      
      // Magnitude vs freq.
      ofstream mMagnitude((_gnp + "/Casper/gnuplot/magnitude"));
      for (int i = 0; i< magnitude.size(); ++i) {
        
        mMagnitude << frequency[i] << "  " << magnitude[i] << endl;
      }
      mMagnitude.close();
      
      mplot.magnitude();
      LOG1(":...t_managerDft::......Magnitude spectrum plot created!");

      // phase vs freq.
      ofstream mPhase((_gnp + "/Casper/gnuplot/phase"));
      for (int i = 0; i< phase.size(); ++i) {
        
        mPhase << frequency[i] << "  " << phase[i] << endl;
      }
      mPhase.close();
      
      mplot.phase();
      LOG1(":...t_managerDft::......Phase spectrum plot created!");
      
      // real vs freq.
      ofstream mReal((_gnp + "/Casper/gnuplot/real"));
      for (int i = 0; i< realCoefs.size(); ++i) {
        
        mReal << frequency[i] << "  " << realCoefs[i] << endl;
      }
      mReal.close();
      
      mplot.realSpec();
      LOG1(":...t_managerDft::......Real spectrum plot created!");

      
      // imaginary vs freq.
      ofstream mImag((_gnp + "/Casper/gnuplot/imag"));
      for (int i = 0; i< imagCoefs.size(); ++i) {
        
        mImag << frequency[i] << "  " << imagCoefs[i] << endl;
      }
      mImag.close();
      
      mplot.imagSpec();
      LOG1(":...t_managerDft::......Imaginary spectrum plot created!");

    }
  }
}
