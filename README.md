SerialPort
==========

Boost asio serial port implementation

#### Create Pseudo Terminals

`$ socat -d -d PTY,raw,echo=0 PTY,raw,echo=0`

Output should look something like this:

    socat[3859] N PTY is /dev/pts/1
    socat[3859] N PTY is /dev/pts/2
    socat[3859] N starting data transfer loop with FDs [3,3] and [5,5]`

#### Simulate Data Though Pipe

`while [ 1 ]; do echo "blah" > /dev/pts/2; sleep 1; done`

Note: the "/dev/pts/2" should correspond to the output of socat
