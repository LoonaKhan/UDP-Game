package main

import (
	"encoding/binary"
	"fmt"
	"net"
)

type Block struct {
	X      byte
	Y      byte
	Colour byte
	Height byte
}

type Chunk struct {
	coords []int
	blocks []Block
}

func ToByte(c *Chunk) []byte {
	buffer := make([]byte, 1032)
	binary.LittleEndian.PutUint32(buffer[0:4], uint32(c.coords[0]))
	binary.LittleEndian.PutUint32(buffer[4:8], uint32(c.coords[1]))

	index := 8
	for b := range c.blocks {
		buffer[index] = c.blocks[b].X
		buffer[index+1] = c.blocks[b].Y
		buffer[index+2] = c.blocks[b].Colour
		buffer[index+3] = c.blocks[b].Height
		index += 4
	}

	return buffer
}

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
		buffer := make([]byte, 1032)
		_, addr, err := conn.ReadFromUDP(buffer) // returns length of read data and address
		if err != nil {
			fmt.Println(err)
			return
		}
		fmt.Println(buffer)

		c := Chunk{coords: []int{int(binary.LittleEndian.Uint32(buffer[:4])), int(binary.LittleEndian.Uint32(buffer[4:8]))}}
		for i := 8; i < len(buffer); i += 4 {
			c.blocks = append(c.blocks, Block{X: buffer[i], Y: buffer[i+1], Colour: buffer[i+2], Height: buffer[i+3]})
		}
		fmt.Printf("coords: %d, len: %d\n", c.coords, len(c.blocks))
		for b := range c.blocks {
			fmt.Printf("block: [%d, %d], c: %d, h: %d\n",
				c.blocks[b].X, c.blocks[b].Y, c.blocks[b].Colour, c.blocks[b].Height)
		}

		conn.WriteToUDP(ToByte(&c), addr)

	}
}
