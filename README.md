linCC
=====

Is a supervisor system for the automation process with a web inferface for linux platform (linCC)

The name linCC is derived from propietary software Siemens(R) WinCC(R)

LinCC is conceived to be a web-server application where, remotely, you can connect to a Siemens PLC ( 300/400 series ) for control and monitoring the automation system and therefore the entire plant without use propietary software as WinCC or WinCC flexible, Schneider' softwares, etc..

It would be a free and an open-source alternative of not-cheaper engines for developing a web-user-end application, by using the most common open-source software like: mariaDB, apache and the most common programming languages as C, HTML5, Javascript.

Engine
------

LinCC will be divided in two different engines/services. The first one is the PLC communication service, made for read data into the plc's DB ( DB: DataBlock is a retentive mapped memory area ) and populate a sql database and vice versa: read data from database and then write to the plc.

The second service is the server-side web application, dedicated to read/write data from/to database and generate the web page for the end-user control and monitoring the entire line and the automated process, for historicize all analog signal, operator's operations, ecc..


Dependencies
============

snap7_lib
---------

snap7_lib is required for using linCC and it's used for communicate with siemens plc. Please download, compile and install library from http://snap7.sourceforge.net/.

In the future, snap7 should not longer be required, it will be integrate into linCC.
