package main

import(
    "fmt"
    "net"
)

func main() {
    PORT := ":4000"
    s, err := net.ResolveUDPAddr("udp4", PORT)
    	conn, err := net.ListenUDP("udp4", s)
    	if err != nil {
    		fmt.Println(err)
    		return
    	}

    	defer conn.Close()
    	fmt.Printf("Listening on port: %s\n", PORT)

    	for {
    	    buffer := make([]byte, 6)
    	    _, _, err := conn.ReadFromUDP(buffer) // returns length of read data and address
            if err != nil {
                        			fmt.Println(err)
                        			return
                        		}
            fmt.Println(buffer)


    	}
}