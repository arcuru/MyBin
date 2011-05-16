. $HOME/.bashrc

# Startx only if no other session exists and login is on tty1
if [[ -z "$DISPLAY" ]] && [[ $(tty) = /dev/tty1 ]]; then
  startx
  logout
fi
