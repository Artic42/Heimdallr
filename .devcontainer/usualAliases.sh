#!/bin/bash
#Listing aliases
alias ll='ls -l'
alias lA='ls -A'
alias la='ls -la'
alias l='ls -CF'
alias lf='la | grep'

#Git shortcuts
alias gcl='git clone'
alias gco='git add -A && git commit -m'
alias gps='git push'
alias gpl='git pull'

#Shutdown and reboot
alias sdn='sudo shutdown now'
alias rbn='sudo reboot'

#Permission change macros
alias givex='chmod -v u+x'
alias givexo='chmod -v uo+x'