require 'socket'

puts "What data would you like to transmit: "
data = gets

server = TCPServer.open(6425)
loop {
	client = server.accept
	client.puts(data + "\n")
	client.close
}
