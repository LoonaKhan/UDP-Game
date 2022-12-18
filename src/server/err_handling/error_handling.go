package err_handling

import (
	"fmt"
	"net"
)

func Handle(err error) { // panics. standalone good for fatal errors
	if err != nil {
		panic(err)
	}
}

//panic stops execution and goes up the stack trace until it exits the program
// after panicking, the function exits and runs the deferred functions
// by placing recover in the deferred function, you can resume the execution of the parent function

func Recover(msg string) { // if the error is not fatal, do this. // todo: just dont handle the error if it isnt fatal?
	if r := recover(); r != nil {
		fmt.Printf("Recovered: %s", msg)
	}
}

// another response function which is like recover, but it Writes to UDP the argument u send it
func UDPRespond(msg string, conn *net.UDPConn, addr *net.UDPAddr) { // recovers a thread and sends a response to the client
	if r := recover(); r != nil {
		conn.WriteToUDP([]byte(msg), addr)
	}
}
