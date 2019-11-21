import os
import sys
import subprocess


if __name__ == '__main__':
    if len (sys.argv) == 2:
        current_dir = os.path.dirname (os.path.abspath (__file__))
        for file in os.listdir ('%s/tests/%s/' % (current_dir, sys.argv[1])):
            f = open ('%s/tests/%s/%s' % (current_dir, sys.argv[1], file), 'r')

            arg_str = f.readline ()
            if arg_str.endswith ('\n'):
                arg_str = arg_str[0:-1]
            args = arg_str.split ('\t')

            
            proc_str = ["%s/bin/%s" % (current_dir, sys.argv[1])]
            for arg in args:
                proc_str.append ('%s' % arg)

            proc = subprocess.Popen (proc_str, stdout=subprocess.PIPE)

            out = proc.stdout.readlines ()
            out = bytes.join (b'', out).decode ('ascii')

            code = proc.wait ()

            if code != 0:
                print ('Bad return code')
            
            expected_out = ''
            for line in f:
                expected_out+= line

            if out != expected_out:
                print ('Bad output')
                print ('Expected: %s' % expected_out)
                print ('Recieved: %s' % out)

            f.close ()
