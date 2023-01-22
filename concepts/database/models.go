package main

import (
	"fmt"
	"gorm.io/driver/sqlite"
	"gorm.io/gorm"
)

//

type Block struct {
	gorm.Model

	X       byte
	Y       byte
	ChunkID int
	Chunk   Chunk
}

type Chunk struct {
	gorm.Model

	X      int
	Y      int
	Blocks []Block
}

func CInit(x, y int) Chunk {
	c := Chunk{X: x, Y: y}
	c.genBlocks()
	return c
}

func (c *Chunk) genBlocks() {
	for x := 0; x < 1; x++ {
		for y := 0; y < 1; y++ {
			c.Blocks = append(c.Blocks, Block{X: byte(x), Y: byte(y)})
		}
	}
}

func main() {
	Conn, err := gorm.Open(sqlite.Open("file::memory:?cache=shared"), &gorm.Config{SkipDefaultTransaction: true})
	if err != nil {
		fmt.Println(err)
	}

	Conn.AutoMigrate(&Block{}, &Chunk{})

	c := CInit(1, 1)
	c2 := CInit(1, 3)
	Conn.Create(&c)
	Conn.Create(&c2)
	fmt.Println("Chunk created:")
	fmt.Printf("Chunk[%d, %d]: blocks(%d):[id: %d]\n", c.X, c.Y, len(c.Blocks), c.Blocks[0].ID)
	fmt.Printf("Chunk[%d, %d]: blocks(%d):[id: %d]\n", c2.X, c2.Y, len(c.Blocks), c2.Blocks[0].ID)

	var rc Chunk
	var blocks []Block
	tx := Conn.First(&rc, "x = ? AND y = ?", 1, 1)
	Conn.Model(&rc).Association("Blocks").Find(&blocks)
	rc.Blocks = blocks
	if tx.Error != nil {
		fmt.Println(tx.Error)
	}

	fmt.Println("Chunk recieved:")
	fmt.Printf("Chunk[%d, %d]: blocks(%d):[%d]\n", rc.X, rc.Y, len(rc.Blocks), rc.Blocks[0].ID)
	//fmt.Println(blocks)
}
