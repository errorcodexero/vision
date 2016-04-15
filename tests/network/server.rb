require 'socket'

puts "What data would you like to transmit: "
data = gets
#data = "Hello World!\n"

server = TCPServer.open(6425)
loop {
	client = server.accept
	client.puts(data + "\n")
	client.close
}
