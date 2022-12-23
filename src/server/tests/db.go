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

	db.Conn.Create(&p.Player{Name: "loona"})

	var plrs []p.Player
	db.Conn.First(&plrs)
	for plr := range plrs {
		fmt.Println(plrs[plr].Name)
	}

	db.Conn.Create(&p.Player{Name: "loona"})

	db.Conn.First(&plrs)
	for plr := range plrs {
		fmt.Println(plrs[plr].Name)
	}
}
