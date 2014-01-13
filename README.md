linCC
=====

winCC web inferface service for linux (linCC)

LinCC is conceived for be a web-server application where, remotely, you can connect to a Siemens PLC for control and monitoring the automation system and therefore the entire plant without use propietary software as WinCC or WinCC 
flexible, Schneider' softwares, etc..

It would be a free and an open-source alternative of not-cheaper engines for developing a web-user-end application, by using the most common open-source software like: mariaDB, apache and the most common programming languages as C, HTML5, Javascript.


Engine
------

LinCC will be divided in two different engines/services. The first one is the PLC communication service, made for read data into the plc's DB ( DB: DataBlock is a retentive memory mapped area ) and populate a sql database and vice versa: read data from database and then write to plc.

The second service is the server-side web application, dedicated to read/write data from/to database and generate the web page for the end-user for control and monitoring the entire line and the automated process, for historicize all analog signal, operator's operations, ecc..
