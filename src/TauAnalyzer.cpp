/** \file TauAnalyzer.cpp
 *
 * Implements the determination of the decay constants for a trace
 */

#include "param.h"
#include "TauAnalyzer.h"
#include "Trace.h"

#include <algorithm>
#include <iostream>
#include <iterator>
#include <string>

#include <cmath>

using namespace std;

TauAnalyzer::TauAnalyzer() : TraceAnalyzer()
{
    name="tau";
}

TauAnalyzer::~TauAnalyzer()
{
    // do nothing
}

void TauAnalyzer::Analyze(Trace &trace, const string &type, const string &subtype)
{
    // don't do analysis for piled-up traces
    if (trace.HasValue("filterEnergy2")) {
	return;
    }
    TraceAnalyzer::Analyze(trace, type, subtype);
	
    // find the maximum
    Trace::const_iterator itMax=max_element(trace.begin(), trace.end());
    Trace::const_iterator itMin=min_element(itMax, (Trace::const_iterator)trace.end());
    iterator_traits< Trace::const_iterator >::difference_type  size =distance(itMax, itMin);
    
    // skip over the area near the extrema since it may be non-exponential there
    advance(itMax, size/10);
    advance(itMin, -size/10);

    size = distance(itMax, itMin);
    double n = (double)size;

    double sum1=0, sum2=0;
    double i=0;
    for (Trace::const_iterator it=itMax; it != itMin; it++) {
	double j=i+1.;
	sum1 += double(*it)*(j*n*n-3*j*j*n+2*j*j*j);
	sum2 += double(*it)*(i*n*n-3*i*i*n+2*i*i*i);
	i+=1.;
    }
    double tau =  1 / log(sum1 / sum2) * pixie::clockInSeconds;
    trace.SetValue("tau", tau);
    
    EndAnalyze(); //update the timer
}
