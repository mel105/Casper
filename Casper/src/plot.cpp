/************************************************************************************************** 
 Casper - software development library
  
 (c) 2019 Michal Elias
  
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

#include "gnuplot.h"
#include "plot.h"

void t_plot::acf()
{
   // declaration
   t_gnuplot plot;
   
   // output
   string out = "~/Work/gitHub/Casper/Casper/gnuplot/eps/acf.eps";
   
   // plot
   plot("set term post eps color solid 'Helvetica,25'");
   plot(("set output '"+out+"'").c_str());
   plot("set size 1.0,1.0");
   plot("set style line 11 lc rgb '#808080' lt 1");
   plot("set border 3 back lt -1");
   plot("set tics nomirror");
   plot("set yrange [-1:1]");
   plot("set ytics 0.2");
   plot("set noborder");
   plot("set ylabel 'ACF' font 'Arial-Bold,bold,40' offset 1.5,0 rotate by 90");
   plot("set xtics 10 offset 0,-6.0");
   plot("set xlabel 'LAG' font 'Arial-Bold,bold,20'");
   plot("set xtics axis");
   plot("set xzeroaxis lt -1 lw 2");
   plot("set yzeroaxis lt -1 lw 2");
   plot("set ytics axis");
   plot("unset grid");
   plot("plot \'~/Work/gitHub/Casper/Casper/gnuplot/acf.pt\' u 1:2 not ' ' w impulses lc rgb 'black' lw 7");
}

void t_plot::line()
{
   // declaration
   t_gnuplot plot;
   
   // output
   string out = "~/Work/gitHub/Casper/Casper/gnuplot/eps/line.eps";
   
   // plot
   plot("set term postscript eps");
   plot(("set output '"+out+"'").c_str());
   plot("plot \'~/Work/gitHub/Casper/Casper/gnuplot/line\' u 1:2 not w l");
}

void t_plot::tline()
{
   // declaration
   t_gnuplot plot;
   
   // output
   string out = "~/Work/gitHub/Casper/Casper/gnuplot/eps/line-synt.eps";
   
   // plot
   plot("set term postscript eps");
   plot(("set output '"+out+"'").c_str());
   plot("set xdata time");
   plot("set timefmt \'%Y-%m-%d %H:%M:%S\'");
   plot("set format x \'%Y\'");
  plot("set xtics rotate by 0");
  plot("set xlabel \'TIME\' offset 1.0,0 rotate by 0 font \'Arial-Bold, bold, 40\'");
  plot("plot \'~/Work/gitHub/Casper/Casper/gnuplot/line\' u 1:3 not w l");
}

void t_plot::magnitude()
{
  
  // declaration
  t_gnuplot plot;
  
  // output
  string out = "~/Work/gitHub/Casper/Casper/gnuplot/eps/magnitude.eps";
  
  // plot
  plot("set term postscript eps");
  plot(("set output '"+out+"'").c_str());
  plot("set xlabel \'Frequency [Hz]\' offset 1.0,0 rotate by 0 font \'Arial-Bold, bold, 40\'");
  plot("set ylabel \'Magnitude Spectrum\' offset 1.0,0 rotate by 90 font \'Arial-Bold, bold, 40\'");
  plot("plot \'~/Work/gitHub/Casper/Casper/gnuplot/magnitude\' u 1:2 not w l");
}


void t_plot::phase()
{
  
  // declaration
  t_gnuplot plot;
  
  // output
  string out = "~/Work/gitHub/Casper/Casper/gnuplot/eps/phase.eps";

  // plot
  plot("set term postscript eps");
  plot(("set output '"+out+"'").c_str());
  plot("set xlabel \'Frequency [Hz]\' offset 1.0,0 rotate by 0 font \'Arial-Bold, bold, 40\'");
  plot("set ylabel \'Phase Spectrum\' offset 1.0,0 rotate by 90 font \'Arial-Bold, bold, 40\'");
  plot("plot \'~/Work/gitHub/Casper/Casper/gnuplot/phase\' u 1:2 not w l");
}


void t_plot::realSpec()
{
  
  // declaration
  t_gnuplot plot;
  
  // output
  string out = "~/Work/gitHub/Casper/Casper/gnuplot/eps/real.eps";
  
  // plot
  plot("set term postscript eps");
  plot(("set output '"+out+"'").c_str());
  plot("set xlabel \'Frequency [Hz]\' offset 1.0,0 rotate by 0 font \'Arial-Bold, bold, 40\'");
  plot("set ylabel \'Real Spectrum\' offset 1.0,0 rotate by 90 font \'Arial-Bold, bold, 40\'");
  plot("plot \'~/Work/gitHub/Casper/Casper/gnuplot/real\' u 1:2 not w l");
}

void t_plot::imagSpec()
{
  
  // declaration
  t_gnuplot plot;
  
  // output
  string out = "~/Work/gitHub/Casper/Casper/gnuplot/eps/imag.eps";
  
  // plot
  plot("set term postscript eps");
  plot(("set output '"+out+"'").c_str());
  plot("set xlabel \'Frequency [Hz]\' offset 1.0,0 rotate by 0 font \'Arial-Bold, bold, 40\'");
  plot("set ylabel \'Imaginary Spectrum\' offset 1.0,0 rotate by 90 font \'Arial-Bold, bold, 40\'");
  plot("plot \'~/Work/gitHub/Casper/Casper/gnuplot/imag\' u 1:2 not w l");
}