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



Local Self-hosted Wordpress Admin Daemon That runs as an UNPRIVILEGED user and DOES NOT NEED any special plugins or login information.  Works right out of the box.
