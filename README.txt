
# Client for AHCAL Reconstruction

This package has been created by E.Brianne, DESY Hamburg.
QtReco-Client includes a Qt interface that enables to grab histgrams/graphs from the tmp rootfile created during analysis with QtReco .

## Requirements

* Ilcsoft needs to be installed (Marlin, LCIO)
* Calice framework with Marlin Processors
* CMake 2.6 minimum
* g++ 4.7 minimum
* Qt version 4.7 or 5 
* ROOT v5.30.XX

## Installation

Get the lastest version
<pre>
git clone https://github.com/CALICETB/QtReco-Client.git
</pre>

Compile by doing (for Qt 5)
<pre>
mkdir build
cd build
cmake -DCMAKE_INSTALL_PREFIX=/path/to/install -DBUILD_DOCUMENTATION=ON -DUSE_GIT=ON -DWITH_QT5=ON ..
make
make install
</pre>


