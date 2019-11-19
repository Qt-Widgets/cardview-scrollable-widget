TEMPLATE = subdirs

SUBDIRS = library \
          example

library.subdir  = cardview_library
example.subdir  = cardview_example

example.depends = library
