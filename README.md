
# Client for AHCAL Reconstruction

This package has been created by E.Brianne, DESY Hamburg.
QtReco-Client includes a Qt interface that enables to grab histograms/graphs from the temp rootfile created during analysis with QtReco.

## Requirements

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
export QTDIR=/path/to/qt5
mkdir build
cd build
cmake -DCMAKE_INSTALL_PREFIX=. -DBUILD_DOCUMENTATION=ON -DUSE_GIT=ON -DWITH_QT5=ON ..
make
make install
</pre>

For Qt4 :
<pre>
export QTDIR=/path/to/qt4
mkdir build
cd build
cmake -DCMAKE_INSTALL_PREFIX=. -DBUILD_DOCUMENTATION=ON -DUSE_GIT=ON -DWITH_QT5=OFF ..
make
make install
</pre>



