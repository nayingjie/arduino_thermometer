import urllib, os
import time, sys, signal
from time import strftime
def touch(fname, times=None):
    with open(fname, 'a'):
        os.utime(fname, times)
touch("thmr.txt")
touch("thmt.txt") 
touch("dhth.txt")
touch("dhtt.txt") 
touch("dhti.txt")
touch("thm2r.txt")
touch("thm2t.txt")
touch("thm3r.txt")
touch("thm3t.txt")
touch("times.txt")
date=strftime("%Y-%m-%d %H:%M:%S")
t=open("times.txt", "a")
t.write("BEGIN ")
t.write(' ' + date + '\n')
t.close()
print "Did you reset the arduino and  double check all values are correct?"
unneeded=raw_input();
x=0
while True:
    sys.stdout.flush()
    x+=1
    def signal_handler(signal, frame):
        print "\n "
        date=strftime("%Y-%m-%d %H:%M:%S")
        date=str(date)
        n=x
        n=str(n)
        t=open("times.txt", "a")
        t.write("END ")
        t.write(' ' + date + '\n')
        t.write(' ' + n + ' samples')
        print "\n ", n, " samples were collected."
        sys.exit(0)
    signal.signal(signal.SIGINT, signal_handler)
    sys.stdout.write('Samples: %s\r' % x)
    a=open("thmr.txt", "a")
    b=open("thmt.txt", "a") 
    c=open("dhth.txt", "a")
    d=open("dhtt.txt", "a")
    e=open("dhti.txt", "a")
    f=open("thm2r.txt", "a")
    g=open("thm2t.txt", "a")
    h=open("thm3r.txt", "a")
    j=open("thm3t.txt", "a")


    signal.signal(signal.SIGINT, signal_handler)

    touch("data.txt")
    os.system('wget http://192.168.1.3 -qO data.txt')
    data=open("data.txt")
    for i, line in enumerate(data):
        if i == 0: a.write(line)
        if i == 1: b.write(line)
        if i == 2: f.write(line)
        if i == 3: g.write(line)
        if i == 4: h.write(line)
        if i == 5: j.write(line)
        if i == 6: c.write(line)
        if i == 7: d.write(line)
        if i == 8: e.write(line)
    time.sleep(2.5)
