
# Client for AHCAL Reconstruction

This package has been created by E.Brianne, DESY Hamburg.
QtReco-Client includes a Qt interface that enables to grab histograms/graphs from the temp rootfile created during analysis with QtReco.

## Requirements

* CMake 2.6 minimum
* g++ 4.7 minimum
* Qt version 4.7 
* ROOT v5.30.XX

## Installation

Get the lastest version
<pre>
git clone https://github.com/CALICETB/QtReco-Client.git
</pre>

Compile by doing
<pre>
mkdir build
cd build
cmake -DBUILD_DOCUMENTATION=ON ..
make
make install
</pre>



