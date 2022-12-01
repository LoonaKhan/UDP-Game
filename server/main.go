package main

import (
  "encoding/json"
  "fmt"
  "net"
)

/*
*
* tcp/udp: base layer, lower latency, less error correction
*   good if u dont need data to be so accurate and speed is better
* http: webpages
*   sends html files
*   more error checking
*   higher latency
* ftp: file transfer protocol
*   directly send files
 */

func decodeJSON[T any](conn net.Conn) (T, error) {
  d := json.NewDecoder(conn)
  var data T
  return data, d.Decode(&data)
}

func main() { // we using tcp/udp
  //listen, accept, handle 

  address := "localhost:4000" // we pass in a host:port to use

  l, err := net.Listen("tcp", address) // listens on the url 
  if err != nil {
    panic(err)
  }
  defer l.Close()

  // the given host:port may not always work, so we retrieve what we ended up hosting on here
  host, port, err := net.SplitHostPort(l.Addr().String())
  if err != nil {
    panic(err)
  }

  fmt.Printf("Listening on host: %s, post: %s\n", host, port)

  for { // listen indefinitely
    conn, err := l.Accept() // accept any incoming connections
    if err != nil {
      panic(err)
    }

    // handle em in a goroutine
    go func(conn net.Conn) {
      // creates a buffer, dyn sized and read the connection 

      msg, err := decodeJSON[map[string]interface{}](conn)

      fmt.Println(msg, err) // message can be accessed via indexes

      // responds and closes connection 
      conn.Write([]byte("recieved message"))
      conn.Close()

    }(conn)

  }
}
