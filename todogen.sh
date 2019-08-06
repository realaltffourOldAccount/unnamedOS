#!/bin/bash
rm -r todolist.txt
grep --exclude=todogen.sh --include=\*.{c,cpp,h} -rnw $(pwd) -e 'TODO' -e 'FIXME' -e 'FIXTHIS' -e 'REFACTOR'
grep --exclude=todogen.sh --include=\*.{c,cpp,h} -rnw $(pwd) -e 'TODO' -e 'FIXME' -e 'FIXTHIS' -e 'REFACTOR' > todolist.txt
