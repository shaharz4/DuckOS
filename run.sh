export DISPLAY=:0
sudo bash ./cpyfs.sh
printf "\n###Running QEMU...###\n"
(set -x; qemu-system-i386 -drive file=disk.img,format=raw)