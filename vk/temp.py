#!/usr/bin/env python2

import sys, os, pygtk, gtk, pynotify, subprocess

def pynotifyCallback(n, action):
  print 'ok'
  subprocess.Popen(["ls"])
  n.close()

def showNotify(text, buttonText, si):
  n = pynotify.Notification('Bug 185262', text)
  if not si is None:
    n.attach_to_status_icon(si)
  n.add_action(text, buttonText, pynotifyCallback)
  n.show()

if __name__ == "__main__":
  pynotify.init('bug185262')

  n = pynotify.Notification('Bug 185262', 'Not in method')
  n.add_action('main', 'This will work', pynotifyCallback)
  n.show()

#  showNotify('before-main', "This won't work", None)

#  si = gtk.StatusIcon()
#  si.set_tooltip('Click to test notify, right-click to quit')
#  si.set_from_stock(gtk.STOCK_INFO)
#
#  si.connect('activate', lambda si, *p: showNotify(si = si, *p),
#    'status-icon', "Won't work")
#  si.connect('popup-menu', lambda si, b, t, *p: gtk.main_quit())

  gtk.main()
