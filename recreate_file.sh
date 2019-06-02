#! /usr/bin/bash

rm applist && touch applist && chmod +rw applist
ls -D1 /usr/share/applications > applist
./reformat
