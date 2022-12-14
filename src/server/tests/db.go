package main

import (
	"fmt"
	"server/db"
	b "server/db/models/blocks"
	c "server/db/models/chunks"
	p "server/db/models/players"
	"server/err_handling"
)

func main() {
	// connect
	err_handling.Handle(db.Conn_err)

	// migrate all the schema
	err_handling.Handle(db.Conn.AutoMigrate(&p.Player{}))
	err_handling.Handle(db.Conn.AutoMigrate(&c.Chunk{}))
	err_handling.Handle(db.Conn.AutoMigrate(&b.Block{}))

	// operations
	// create and manage chunks
	db.Conn.Create(&c.Chunk{X: 1, Y: 2})
	db.Conn.Create(&c.Chunk{X: 1, Y: 20})

	var coords = []int{0, 0}
	TL, BR, xspan, yspan := c.ChunkSpan(coords)
	fmt.Println("\nTL:", TL, "\nBR:", BR, "\nXspan:", xspan, "\nYspan:", yspan)

	var chunks = []c.Chunk{}
	db.Conn.Find(&chunks, "x IN ? AND y IN ?", xspan, yspan)

	fmt.Println("Found chunks: ")
	for ch := range chunks {
		fmt.Printf("Chunk [X: %d, Y: %d]\n", chunks[ch].X, chunks[ch].Y)
	}
}
