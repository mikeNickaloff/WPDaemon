# WPDaemon
WPDaemon is a web-based Front End for  Managing many different Wordpress sites on a single machine.

WPDaemon requires that you run the daemon from an account which is able to read the wp-config file on 
every site that you intend to manage as this is how it retrieves information from the database.  
Some functions may also require write access to different folders of each site's wordpress installation. 

The easiest way to do this is to create a new user called 'wpdaemon' or some similar name, and then use 
Linux access control lists via setfacl  to grant wpdaemon access to each of the desired wordpress folders. 

Alternatively, you can grant group read/write access to the wordpress folder, and then addd wpdaemon to 
the group assigned to each wordpress folder. 

Once you have the user permissions all set up, 

You can compile the project by using either QtCreator to open the project or by using 'qmake' and 'make' 
from the command line in the directory containing 'WPDaemon.pro'

You will need Qt5.4+ (Must have QWebChannel module) in order to successfully compile.

In order to run, you will need:

- Python
- GNU bash
- a POSIX operating system (linux, unix, etc)
- OpenSSL
- Qt5.4+ with SQLITE3 implementation
- a valid SSL certificate* for the host you intend to run the daemon from if you wish to use SSL (recommended!)
    (installed into the 'ssl'  folder as 'certificate.pem' and 'key.pem')
    
 * NOTE:  SSL is currently disabled while WPDaemon is still in the ALPHA stage to allow for packet captures
    and connection debugging.  When WPDaemon hits beta, an self-signed SSL certificate will be generated 
    automatically when WPDaemon is first run. Currently, WPDaemon is fairly insecure, so it should not be run
    on any production sites... until it has reached the BETA phase.

If you absolutely require the use of HTTPS while this software is in ALPHA,  you may accomplish the task by 
modifying  the file  ./res_python/simple_https_server.py  and uncommenting the next-to-last line that starts with

<b># httpd.socket = ssl.wrap_socket( </b>...`

and then Modifying the file

./res_html/index.html   and changing:

<b>var wsUri = "ws://localhost:65300";</b>

to 

<b>var wsUri = "wss://localhost:65300";</b>

You will likely also have to make changes to the WebSocketController listen directive  to mske it run 
in SSLMode rather than in NonSecureMode. This can be changed via the  initialization of the 'server' object in
the <b>WebSocketController</b> constructor.

<hr>

If you would like a complete list of available actions, visit
<a href="https://developer.wordpress.org/cli/commands/">https://developer.wordpress.org/cli/commands/</a>  
WPDaemon's command structure is based on the command structure used by WP-CLI.  
(In fact WPDaemon is really just a fancy front-end for WP-CLI -- but whose keeping track of these things?)

The entire project is most like in blatent disregard for any and all License Agreements from third party software,,
but the truth of the matter is... I don't really care.. If you really want to sue me over the $0.00 that I 
will be undoubtedly making from this project, I  will be happy to pay the developers the entire sum of the profits 
made from WPDaemon (which is open source).

Feel free to clone, fork, modify, take credit for, or even duplicate / sell any part of this project as you see fit. 

My main goal was really to make other expensive WP Management Suites obsolete, and to open the doors for the open source
community to not have to update every site manually.  

This will decrease the number of passwords that have to be stored and also decrease of the number of worthless "XXX-Child"
plugins that are installed on everyone's wordpress which no-doubt are used for all sorts of nefarious purposes. 

At the time of this document's creation  (6/12/2018)  this will be the only one of its kind in the realm of
Wordpress Management Daemons, and by the time it is finished, it will likely be one of many. 

- Mike

Local Self-hosted Wordpress Admin Daemon That runs as an UNPRIVILEGED user and DOES NOT NEED any special plugins or login information.  Works right out of the box.
