require 'socket'

s = TCPSocket.open('127.0.0.1', 6425)

while line = s.gets
	puts line.chop
end

s.close
