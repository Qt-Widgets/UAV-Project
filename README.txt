Using QWebView requires OpenSSL

	Go to http://slproweb.com/products/Win32OpenSSL.html

	Download Win64 OpenSSL... (I chose Win64 OpenSSL v1.0.1r)
	During the install, choose to copy the OpenSSL binaries by checking "The OpenSSL binaries (\bin) directory"

	Go to \OpenSSL-Win64\bin
	Copy libeay32.dll and ssleay32.dll
	Put them in \Qt\Qt5.5.1\5.5\msvc2013_64\bin (QtNetwork4.dll or QtNetworkd4.dll should be there)

It uses a QWebView widget in the .ui to run it.

On line 11 in mainwindow.cpp, change the url to the correct path to map.html on your system.