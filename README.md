Gmail Sniffer
============

GmailSniffer is a Gmail Notifier for linux, written in QT4, it checks unread gmail emails, if any, it will show a popup notification, or it can be set to use default system (linux) notification

- can set popup window position
- can set to use system notifier
- can enable/disable sound alert
- can assign default browser
- can set email check interval


Tested od LMDE, Mint 14, Fedora 17. KDE, MATE, Cinnamon


REQUIREMENTS
============
libphonon-dev



INSTALL
============

qmake

make

make install

sudo cp images/gmailsniffer.png /usr/share/icons/gmailsniffer.png & cp gmail /usr/bin/gmailsniffer & cp res/gmailsniffer-newemail.ogg /usr/share/sounds/gmailsniffer-newemail.ogg
